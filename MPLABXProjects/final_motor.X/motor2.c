/*
 * File:   motor2.c
 * Author: wayne
 *
 * Created on 2018?12?30?, ?? 4:26
 */


#include <xc.h>
#include<stdio.h>
// BEGIN CONFIG
#pragma config OSC = INTIO67   // Oscillator Selection bits (HS oscillator)
#pragma config WDT = OFF  // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRT = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//END CONFIG

//let TMR2 Prescale Value = 16
#define TMR2PRESCALE 16
//period = (PR2+1)*4*Tosc*TMR2PRESCALE
void PWM1_Init(long setDuty)
{
    PR2 = setDuty;
    //(155+1)*4*(1/500k)*16=20ms
    //period = 20ms
}

void PWM1_Duty(int duty)
{
    //set duty to CCPR1L , CCP1X(CCP1CON:5) and CCP1Y(CCP1CON:4).
        TRISA = duty;
        CCP1CONbits.CCP1X = TRISAbits.RA1;
        CCP1CONbits.CCP1Y = TRISAbits.RA0;
  //      CCP1CONbits.CCP1X = 0;
  //      CCP1CONbits.CCP1Y = 0;
        CCPR1L = duty >> 2;
  //      CCPR1L = 0;        

}

void PWM1_Duty2()
{
        CCPR1L = 0;
        CCP1CONbits.CCP1X = 0;
        CCP1CONbits.CCP1Y = 0;
}

void PWM1_Start()
{
    //set CCP1CON
    CCP1CONbits.CCP1M0 = 0;
    CCP1CONbits.CCP1M1 = 0;
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M3 = 1;
    //set TIMER2 on
    T2CONbits.TMR2ON = 1;
    //set FOSC = 500kHz
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;    
    //TRISC: set RC2 as output
    TRISCbits.RC2 = 0;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    //set TIMER2 prescaler
        T2CONbits.T2CKPS0 = 0;
        T2CONbits.T2CKPS1 = 1;
        
        PWM1CONbits.PRSEN = 1;
//    }
}

void main()
{
    PWM1_Init(155);
    PWM1_Start();
    int i = 0, j = 0, flag = 0;
    //TRISB: set RB0 as input button
    TRISDbits.RD0 = 1;
    TRISDbits.RD1 = 1;
    //PWM1_Duty();
    
    //light
    TRISA = 0;
    LATA = 0;
    
    int k = 0;
    while(1)
    {
        if(RD0 == 0)//Re
        {
                //Init?period??????
                LATAbits.LATA0 = 1;//LED
                PWM1_Init(225);
                i=i+1;
                PWM1_Duty(200);
                for(j = 0;j < 200;j++);//delay for breath LED
                if(i == 255)           
                    i = 0;
        }
        if(RD1 == 0)//Do
        {
            LATAbits.LATA1 = 1;
            PWM1_Init(250);
            PWM1_Duty(200);
        }
        else
        {
            PWM1_Duty(0);
            LATA = 0;
        }
    }
}
