#include <pic14/pic12f683.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


//Se definen los pines del microcontrolador
#define BUTTON GP3
#define BCD_0 GP0
#define BCD_1 GP1
#define BCD_2 GP2
#define BCD_3 GP5
#define DISP_NEG GP4



//Vamos a apagar el WDT y el MCLR
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);



//Declaracion de funciones
unsigned char random_number_generator();
void delay(unsigned int);

void main(void){
    //Configuracion de los pines del microcontrolador
    TRISIO = 0b00001000; //Únicamente el pin 3 se toma como entrada
    ANSEL = 0; //Todas las entradas se dejan como digitales
    //CMCON = 7; //Se apagan los comparadores
    GPIO = 0x00; //Inicializan todos los pines en 0 

    //Inicialización de variables necesarias para el algoritmo del programa.
    unsigned char numbers[16];
    unsigned char i = 0;
    unsigned char j;
    unsigned char num;
    unsigned char tens;
    unsigned char ones;

    while (1){
        if (BUTTON == 0){
            while (BUTTON == 0); //Para que programa corra únicamente cuando se suelta el botón
            do {
                num = random_number_generator();
            } while (num == 100);

            //Se revisa que no se repita el número
            for (j = 0; j < i; j++) {
                if (num == numbers[j]) {
                    num = 100; //Marcar número como usado
                    break;
                }
            }
            //Almacenarlo En caso de no encontrarlo.
            if (num != 100) {
                numbers[i] = num;
                i++; //Para llevar el conteo de los números sacados

                //Si el número random es menor a cero entonces se establece decenas como 0 y unidad como número
                if (num < 10) {
                    tens = 0;
                    ones = num;
                } 
                
                //caso contrario se debe dividir el número por decenas y unidades
                else{
                    tens = num / 10;
                    ones = num % 10;
                }

                //Conversión a BCD para los displays
                unsigned char bcd_ones = (ones / 10) << 4 | (ones % 10);
                unsigned char bcd_tens = (tens / 10) << 4 | (tens % 10);

                //Se despliega el número de las decenas
                BCD_0 = bcd_ones & 0x01;
                BCD_1 = (bcd_ones >> 1) & 0x01;
                BCD_2 = (bcd_ones >> 2) & 0x01;
                BCD_3 = (bcd_ones >> 3) & 0x01;

                //Delay the tiempo para cambiar al display de las unidades
                delay(50);

                DISP_NEG = ~DISP_NEG;

                BCD_0 = bcd_tens & 0x01;
                BCD_1 = (bcd_tens >> 1) & 0x01;
                BCD_2 = (bcd_tens >> 2) & 0x01;
                BCD_3 = (bcd_tens >> 3) & 0x01;

            }

            if (i == 16){
                for (j = 0; j < 10; j++) {
                    BCD_0 = 1;
                    BCD_1 = 0;
                    BCD_2 = 0;
                    BCD_3 = 1;
                    DISP_NEG = ~DISP_NEG;
                    delay(50);
                }
                i = 0;

            }
            delay(150000);
            DISP_NEG = ~DISP_NEG;



        }
        delay(50);
    }

}

//Definimos la función para generar números aleatorios
unsigned char random_number_generator(){

    static unsigned int lfsr = 0x8F; //Se declara la semilla incial para el lfsr
    unsigned char bit;

    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1; // Función XOR que define el siguiente bit del LFSR
    lfsr = (lfsr >> 1) | (bit << 15); //Se desplaza el registro a la izquierda y se inserta el nuevo bit

    return lfsr % 100; //El número no sobrepasará el rango de 0 a 99 establecido previamente por medio del módulo

}


void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}