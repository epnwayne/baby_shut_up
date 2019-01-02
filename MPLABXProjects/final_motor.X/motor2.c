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
int flag = 0;
void piano();
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

void Do()
{
   PWM1_Init(224);
   PWM1_Duty(250);
}
void Re()
{
    PWM1_Init(199);
    PWM1_Duty(250);
}
void Mi()
{
    PWM1_Init(175);
    PWM1_Duty(250);
}
void Fa()
{
    PWM1_Init(165);
    PWM1_Duty(250);
}
void So()
{
    PWM1_Init(145);
    PWM1_Duty(250);
}
void Quiet()
{
    PWM1_Duty(0);
}
void delay()
{
    int i;
    for(i = 0; i < 5000; i++)
    {
        if( RD1 == 0 || RD2 == 0 || RD3 == 0 || RC3 == 0 )
            flag = 1;
    }
}

void small_bee()
{
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Do(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay(); if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Do(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
     So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(); delay();if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(); delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Do(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
     So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(); delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Do(); delay(); if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
}

void main()
{
    //PWM1_Init(155);
    PWM1_Start();
    int i = 0, j = 0, flag = 0;
    //set input button
    TRISDbits.RD0 = 1;
    TRISDbits.RD1 = 1;
    TRISDbits.RD2 = 1;
    TRISDbits.RD3 = 1;
    TRISCbits.RC3 = 1;
    //PWM1_Duty();
    
    //light
    TRISA = 0;
    LATA = 0;
    while(1)
    {
        
        if(RD0 == 0)//Re
        {
           small_bee();
            //Init?period??????
           LATAbits.LATA0 = 1;//LED
           Re();
        }
        else if(RD1 == 0)//Do
        {
            LATAbits.LATA1 = 1;
            Do();
        }
        else if(RC3 == 0)//Me
        {
            Mi();
        }
        else if(RD3 == 0)//Fa
        {
            Fa();
        }
        else if(RD2 == 0)//So
        {
            So();
        }
        else
        {
            PWM1_Duty(0);
            LATA = 0;
        }
    }
}
