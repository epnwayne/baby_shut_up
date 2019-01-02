/*
 * File:   testmotor.c
 * Author: wayne
 *
 * Created on 2018?12?31?, ?? 1:45
 */


#include <xc.h>

#pragma config OSC = INTIO67  //Internal Oscillator set to 4MHz 
#pragma config WDT = OFF    /* set watchdog timer off */ 
#pragma config LVP = OFF    /* Low Voltage Programming Off */ 
#pragma config DEBUG = ON  /* Compile without extra Debug compile Code */ 
#pragma config MCLRE = ON /* Set Master Clear */ 


void delay(int k);

void main(){
    TRISC=0x00;             //make PORTC as output port
    LATC = 0x00;
    TRISBbits.TRISB1=1;     //make pin RB1 as input
    
    while(1){
        int value = 100;
        value = value/100;
        LATC=0x66;  //rotate clockwise
        delay(value);
        LATC=0x33;
        delay(value);
        LATC=0x99;
        delay(value);
        LATC=0xcc;
        delay(value);
    }
}

void delay(int k)
{
    int i,j;
    for(i=0;i<10;i++)
        for(j=0;j<k;j++);
}
