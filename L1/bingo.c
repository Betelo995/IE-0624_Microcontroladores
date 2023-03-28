#include <pic14/pic12f683.h>
#include <math.h>
#include <stdbool.h>

typedef unsigned int word;


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
    TRISIObits.TRISIO0 = 0;
    TRISIObits.TRISIO1 = 0;



}
