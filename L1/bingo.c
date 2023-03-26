#include <pic14/pic12f683.h>
#include <math.h>
#include <stdbool.h>

typedef unsigned int word;


//Vamos a apagar el WDT y el MCLR
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF);



//primero voy a definir la main y luego voy a definir el resto de cosas, porque sino me vuelvo loco


//

void main(void){
    TRISIObits.TRISIO0 = 0;
    TRISIObits.TRISIO1 = 0;



}
