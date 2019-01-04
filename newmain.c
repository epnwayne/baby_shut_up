/*
 * File:   newmain.c
 * Author: renu
 *
 * Created on January 1, 2019, 5:10 PM
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pic18f4520.h>
#define TMR2PRESCALE 16
#define _XTAL_FREQ 100000

// CONFIG1H
#pragma config OSC  = INTIO67      // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

unsigned int i;
int j=1;
int k;
int red[10][8]={
                   {0,0,126,26,42,68,0,126},
                   {0,126,26,42,68,0,126,74},
                   {126,26,42,68,0,126,74,74},
                   {26,42,68,0,126,74,74,74},
                   {42,68,0,126,74,74,74,0},
                   {68,0,126,74,74,74,0,126},
                   {0,126,74,74,74,0,126,66},
                   {126,74,74,74,0,126,66,66},
                   {74,74,74,0,126,66,66,24},
                   {0,0,0,0,0,0,0,0}
}; 

int yellow[28][8]={
                   {0,0,2,4,120,4,2,0},
                   {0,2,4,120,4,2,0,126},
                   {2,4,120,4,2,0,126,74},
                   {4,120,4,2,0,126,74,74},
                   {120,4,2,0,126,74,74,74},
                   {4,2,0,126,74,74,74,0},
                   {2,0,126,74,74,74,0,126},
                   {0,126,74,74,74,0,126,64},
                   {126,74,74,74,0,126,64,64},
                   {74,74,74,0,126,64,64,64},
                   {74,74,0,126,64,64,64,0},
                   {74,0,126,64,64,64,0,126},
                   {0,126,64,64,64,0,126,64},
                   {126,64,64,64,0,126,64,64},
                   {64,64,64,0,126,64,64,64},
                   {64,64,0,126,64,64,64,0},
                   {64,0,126,64,64,64,0,60},
                   {0,126,64,64,64,0,60,66},
                   {126,64,64,64,0,60,66,66},
                   {64,64,64,0,60,66,66,66},
                   {64,64,0,60,66,66,66,60},
                   {64,0,60,66,66,66,60,0},
                   {0,60,66,66,66,60,0,126},
                   {60,66,66,66,60,0,126,32},
                   {66,66,66,60,0,126,32,16},
                   {66,66,60,0,126,32,16,32},
                   {66,60,0,126,32,16,32,126},
                   {0,0,0,0,0,0,0,0}
}; 

int blue[15][8]={
                   {0,0,254,146,146,108,0,126},
                   {0,254,146,146,108,0,126,64},
                   {254,146,146,108,0,126,64,64},
                   {146,146,108,0,126,64,64,64},
                   {146,108,0,126,64,64,64,0},
                   {108,0,126,64,64,64,0,62},
                   {0,126,64,64,64,0,62,64},
                   {126,64,64,64,0,62,64,64},
                   {64,64,64,0,62,64,64,62},
                   {64,64,0,62,64,64,62,0},
                   {64,0,62,64,64,62,0,126},
                   {0,62,64,64,62,0,126,74},
                   {62,64,64,62,0,126,74,74},
                   {64,64,62,0,126,74,74,74},
                   {0,0,0,0,0,0,0,0}
}; 


void main(void) {
    
    //TRISA: set RA0~7 as output
    TRISAbits.RA0= 0;
    TRISAbits.RA1= 0;
    TRISAbits.RA2= 0;
    TRISAbits.RA3= 0;
    TRISAbits.RA4= 0;
    TRISAbits.RA5= 0;
    TRISAbits.RA6= 0;
    TRISAbits.RA7= 0;
    //TRISD: set RD0~7 as output
    TRISDbits.RD0= 0;
    TRISDbits.RD1= 0;
    TRISDbits.RD2= 0;
    TRISDbits.RD3= 0;
    TRISDbits.RD4= 0;
    TRISDbits.RD5= 0;
    TRISDbits.RD6= 0;
    TRISDbits.RD7= 0;
    //TRISB: set RB as input
    TRISBbits.RB5 = 1;
    TRISCbits.RC3 = 1;
    TRISEbits.RE1 = 1;
    PORTBbits.RB5 = 1;
    PORTCbits.RC3 = 1;
    PORTEbits.RE1 = 1;
    

    int my[8][8]={{128,192,128,0,0,0,0,0},
                  {0,128,192,128,0,0,0,0},
                  {0,0,128,192,128,0,0,0},
                  {0,0,0,128,192,128,0,0},
                  {0,0,0,0,128,192,128,0},
                  {0,0,0,0,0,128,192,128},
                  {0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0}};
    
    int count=0;
    int bb;
    while(1)
    {
        if(RB5 == 0){ //red button pushed
            for(count=0;count<10;count++){
                for(k=0;k<8;k++){
                    for(i=0;i<8;i++){
                        if(RC3 == 0 || RE1 == 0)
                            break;
                        LATA=~j;
                        LATD=red[count][i];
                        __delay_ms(25);
                        j=j<<1;
                    }
                j=1;
                }
                //j=1;
            }
            //j=1;
        }
        else if(RC3 == 0){ //blue button pushed
            for(count=0;count<28;count++){
                for(k=0;k<8;k++){
                    for(i=0;i<8;i++){
                        if(RB5 == 0 || RE1 == 0)
                            break;
                        LATA=~j;
                        LATD=yellow[count][i];
                        __delay_ms(25);
                        j=j<<1;
                    }
                j=1;
                }
                //j=1;
            }
            //j=1;
        }
        else if(RE1 == 0){ //yellow button pushed
            for(count=0;count<28;count++){
                for(k=0;k<8;k++){
                    for(i=0;i<8;i++){
                        if(RB5 == 0 || RC3 == 0)
                            break;
                        LATA=~j;
                        LATD=blue[count][i];
                        __delay_ms(25);
                        j=j<<1;
                    }
                j=1;
                }
                //j=1;
            }
            //j=1;
        }
        
     
    }
        
    return;
}
