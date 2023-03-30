#include <pic14/pic12f683.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>


//Se definen los pines del microcontrolador
#define BUTTON GP3
#define BCD_0 GP5
#define BCD_1 GP2
#define BCD_2 GP1
#define BCD_3 GP0
#define DISP_NEG GP4



//Vamos a apagar el WDT y el MCLR
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);



//Declaracion de funciones
unsigned char random_number_generator();
void delay(unsigned int);
void set_pins(unsigned char);


void main(void){
    //Configuracion de los pines del microcontrolador
    TRISIO = 0b00001000; //Únicamente el pin 3 se toma como entrada
    ANSEL = 0; //Todas las entradas se dejan como digitales
    CMCON0 = 0x07; //Se apagan los comparadores
    GPIO = 0x00; //Inicializan todos los pines en 0 

    //Inicialización de variables necesarias para el algoritmo del programa.
    unsigned char numbers[16];
    unsigned char i = 0;
    unsigned char j;
    unsigned char num;
    unsigned char tens = 0;
    unsigned char ones = 0;
    int found;
    bool not_repeated;
    

    while (1){
        //Poniendo los pines para las decenas
        set_pins(tens);
        
        delay(10);

        //Delay the tiempo para cambiar al display de las unidades
        DISP_NEG = ~DISP_NEG;
        set_pins(ones);
        
        delay(10);
        DISP_NEG = ~DISP_NEG;
        not_repeated = true;


        
        if (BUTTON == 0){

            while (not_repeated){
                num = random_number_generator();
                found = 0;
                for(j = 0; j < i; j++){
                    if(num == numbers[j]){
                        found = 1;
                    }
                }
                if (found != 1){
                    not_repeated = false;
                }
            }

            numbers[i] = num;
            i++;

            //Si el número random es menor a diez entonces se establece decenas como 0 y unidad como número
            if (num < 10) {
                tens = 0;
                ones = num;
            } 
            
            //caso contrario se debe dividir el número por decenas y unidades
            else if(num > 10){
                tens = num / 10;
                ones = num % 10;
            }

            if (i == 16){
                for (j = 0; j < 100; j++) {
                    set_pins(9);
                    DISP_NEG = ~DISP_NEG;
                    delay(15);
                    DISP_NEG = ~DISP_NEG;
                    delay(15);
                    DISP_NEG = ~DISP_NEG;
                    delay(15);
                }
                i = 0;
                tens = 0;
                ones = 0;

            }
        }
    
        
        
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
	unsigned int a;
	unsigned int b;

	for(a=0;a<tiempo;a++)
	  for(b=0;b<1275;b++);
}

void set_pins(unsigned char decimal){
    if (decimal == 0){
        BCD_0 = 0;
        BCD_1 = 0;
        BCD_2 = 0;
        BCD_3 = 0;
    }
    else if (decimal == 1){
        BCD_0 = 0;
        BCD_1 = 0;
        BCD_2 = 0;
        BCD_3 = 1;
    }
    else if (decimal == 2){
        BCD_0 = 0;
        BCD_1 = 0;
        BCD_2 = 1;
        BCD_3 = 0;
    }
    else if (decimal == 3){
        BCD_0 = 0;
        BCD_1 = 0;
        BCD_2 = 1;
        BCD_3 = 1;
    }
    else if (decimal == 4){
        BCD_0 = 0;
        BCD_1 = 1;
        BCD_2 = 0;
        BCD_3 = 0;
    }
    else if (decimal == 5){
        BCD_0 = 0;
        BCD_1 = 1;
        BCD_2 = 0;
        BCD_3 = 1;
    }
    else if (decimal == 6){
        BCD_0 = 0;
        BCD_1 = 1;
        BCD_2 = 1;
        BCD_3 = 0;
    }
    else if (decimal == 7){
        BCD_0 = 0;
        BCD_1 = 1;
        BCD_2 = 1;
        BCD_3 = 1;
    }
    else if (decimal == 8){
        BCD_0 = 1;
        BCD_1 = 0;
        BCD_2 = 0;
        BCD_3 = 0;
    }
    else if (decimal == 9){
        BCD_0 = 1;
        BCD_1 = 0;
        BCD_2 = 0;
        BCD_3 = 1;
    }


}

//Se puede arreglar el problema definiendo el número nuevo siempre que el botón es 0, pero la asignación de los bits del BCD se hacen afuera de esto para que se mantengan con cada ciclo
