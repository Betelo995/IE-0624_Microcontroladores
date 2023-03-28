#include <pic14/pic12f683.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

typedef unsigned int word;

//Definición de variables globales
uint8_t used_numbers[100] = {0};
uint8_t counter = 0;




//Vamos a apagar el WDT y el MCLR
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);


//Definimos la función para generar números aleatorios

unsigned char random_number_generator(){
    static unsigned char lfsr = 0x8F; //Se declara la semilla incial para el lfsr
    unsigned char bit;

    bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1; // Función XOR que define el siguiente bit del LFSR
    lfsr = (lfsr >> 1) | (bit << 7); //Se desplaza el registro a la izquierda y se inserta el nuevo bit

    return lfsr % 100 //El número no sobrepasará el rango de 0 a 99 establecido previamente por medio del módulo

}


//

void main(void){
    //Vamos a configurar los pines del microcontrolador
    TRISIO = 0b00001000; //Únicamente el pin 3 se toma como entrada
    ANSEL = 0; //Todas las entradas se dejan como digitales
    CMCON = 7; //Se apagan los comparadores
    GPIO = 0x00; //Inicializan todos los pines en 0 



}
