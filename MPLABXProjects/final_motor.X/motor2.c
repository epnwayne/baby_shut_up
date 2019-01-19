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
int n;
//interrupt
int inter = 0;
void __interrupt(low_priority) LOW_ISR(void)
{
    //deal ccp2 interrupt and adc interrupt
    if(INTCONbits.INT0IF){//AD conversion finish = flag bit
        INTCONbits.INT0IF = 0;
        int inter = 1;
        
    }
    
    return ;
}
    
    //INTCON3bits.INT2IP = 1
void ADC_Initialize(void) {
    TRISA = 0xff;		// Set as input port
    ADCON1 = 0x0e;  	// Ref vtg is VDD & Configure pin as analog pin 
    // ADCON2 = 0x92;  	
    ADFM = 1 ;          // Right Justifie
    ADCON2bits.ADCS = 7; // 
    ADRESH=0;  			// Flush ADC output Register
    ADRESL=0;  
}

int ADC_Read(int channel)
{
    int digital;
    
    ADCON0bits.CHS =  0x07; // Select Channel7
    ADCON0bits.GO = 1;
    ADCON0bits.ADON = 1; 
    
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);
    return(digital);
}

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

void Do(int n)
{
   //PWM1_Init(224);
    
   if(n == 0){
        PWM1_Init(224);//do
        PWM1_Duty(250);
   }
   else if(n == 1){
        PWM1_Init(199);//re
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(175);//me
        PWM1_Duty(250);
   } 
}
void Re(int n)
{
   // PWM1_Init(199);
   if(n == 0){
        PWM1_Init(199);//re
        PWM1_Duty(250);
   }
   else if(n ==1){
        PWM1_Init(175);//mi
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(165);//fa
        PWM1_Duty(250);
   }
}
void Mi(int n)
{ 
    //PWM1_Init(175);
   if(n == 0){
        PWM1_Init(175); //mi
        PWM1_Duty(250);
   }
   else if(n == 1){
        PWM1_Init(165); //fa
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(145); //so
        PWM1_Duty(250);
   }
}
void Fa(int n)
{
    //PWM1_Init(165);
   if(n == 0){
        PWM1_Init(165); //fa
        PWM1_Duty(250);
   }
   else if(n == 1){
        PWM1_Init(145); //so
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(132); //la
        PWM1_Duty(250);
   }
}
void So(int n)
{
    //PWM1_Init(145);
   if(n == 0){
        PWM1_Init(145); //so
        PWM1_Duty(250);
   }
   else if(n == 1){
        PWM1_Init(132); //la
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(119); //si
        PWM1_Duty(250);
   }
}
void La(int n)
{
    //PWM1_Init(145);
   if(n == 0){
        PWM1_Init(132); //la
        PWM1_Duty(250);
   }
   else if(n == 1){
        PWM1_Init(119); //si
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(111); //higher do
        PWM1_Duty(250);
   }
}

void Si(int n)
{
    //PWM1_Init(145);
   if(n == 0){
        PWM1_Init(119); //si
        PWM1_Duty(250);
   }
   else if(n == 1){
        PWM1_Init(111); //higher do
        PWM1_Duty(250);
   }
   else if(n == 2){
        PWM1_Init(100); //higher re
        PWM1_Duty(250);
   }
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
        if( RD0 == 0 || RD1 == 0 || RD2 == 0 || RD3 == 0 || RD4 == 0 || RD5 == 0 || RC3 == 0)
            flag = 1;
    }

}

void small_bee()
{
    So(n);LATBbits.LATB5 = 1; delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    
    Fa(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Re(n); LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
 
    Do(n);  LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n);  LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n);  LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(n);  LATBbits.LATB4 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(n);  LATBbits.LATB5 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(n);  LATAbits.LATA2 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(n); LATA = 255;LATB = 255;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0; LATB = 0; delay();if(flag == 1){flag = 0;return;}
    
    So(n);LATBbits.LATB5 = 1; delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    
    Fa(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Re(n); LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    
    Do(n);  LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n);  LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();LATAbits.LATA2 = 0;  delay();if(flag == 1){flag = 0;return;}
    So(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATBbits.LATB4 = 0; delay();if(flag == 1){flag = 0;return;}
    So(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0; LATB = 0; delay();if(flag == 1){flag = 0;return;}
    
    Re(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n);LATAbits.LATA2 = 0; delay();if(flag == 1){flag = 0;return;}
    Quiet(); delay();if(flag == 1){flag = 0;return;}
    Re(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n); LATBbits.LATB4 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n); LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(n); LATAbits.LATA4 = 1;delay();if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    
    Mi(n); LATA = 0;LATB = 0;LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB4 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB5 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Fa(n); LATAbits.LATA2 = 0;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    So(n); LATA = 255; LATB = 255;delay();if(flag == 1){flag = 0;return;}delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0; delay();if(flag == 1){flag = 0;return;}
    
    So(n);LATBbits.LATB5 = 1; delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Mi(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    
    Fa(n); LATBbits.LATB4 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  LATA = 0;LATB = 0;delay();if(flag == 1){flag = 0;return;}
    Re(n); LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}
    Quiet();  delay();if(flag == 1){flag = 0;return;}
    Re(n); LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} delay();if(flag == 1){flag = 0;return;}
    Quiet();LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    
    Do(n);  LATA = 255; LATB = 255;delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    Mi(n);LATA = 255;LATB = 255;  delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    So(n);LATA = 255;LATB = 255;  delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    So(n); LATA = 255;LATB = 255; delay();if(flag == 1){flag = 0;return;}
    Quiet(); LATA = 0;LATB = 0;  delay();if(flag == 1){flag = 0;return;}
    Do(n);LATBbits.LATB4 = 1; delay(); if(flag == 1){flag = 0;return;}LATBbits.LATB5 = 1;delay();if(flag == 1){flag = 0;return;}LATAbits.LATA2 = 1;delay();if(flag == 1){flag = 0;return;} LATA = 0; LATB = 0;delay();if(flag == 1){flag = 0;return;}
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
    TRISDbits.RD4 = 1;
    TRISDbits.RD5 = 1;
    TRISDbits.RD6 = 1;
    //PWM1_Duty();
    INTCONbits.GIEH = 1; //Global Interrupt Enable bit
    INTCONbits.INT0IE = 1; // Enables external interrupt
    INTCON2bits.INTEDG0 = 0; //falling
    INTCON3bits.INT1IP = 1;// INT1 External Interrupt Priority bit
    INTCON3bits.INT1IE = 1;//enables the INT1 external interrupt 
    INTCON3bits.INT1IF = 0;//The INT1 external interrupt did not occur 
    //light
    TRISA = 0;
    TRISB = 0;
    LATB = 0;
    LATA = 0;
    //adc
    ADC_Initialize();
    
    while(1)
    {
        //adc
        int digital = ADC_Read(0);
        int voltage = digital * ((float)3/1023); // 5v / 2^10-1  (10bits)
        float speed = voltage*100;
        n = (int)voltage;
        
        if(RD0 == 0)//Re
        {
            //LATA = 0;
            LATBbits.LATB4 = 1;
            Re(n);
           
        }
        else if(RD1 == 0)//Do
        {
           // LATA = 0;
            LATBbits.LATB5 = 1;
            Do(n);
        }
        
        else if(RC3 == 0)//Mi
        {
            //LATA = 0;
            LATAbits.LATA2 = 1;
            Mi(n);
        }
        else if(RD3 == 0)//Fa
        {
            //LATA = 0;
             LATBbits.LATB5 = 1;
            Fa(n);
        }
        else if(RD2 == 0)//So
        {
             //LATA = 0;
             LATBbits.LATB4 = 1;
             So(n);
            
        }
        else if(RD4 == 0)//la
        {
             //LATA = 0;
            LATAbits.LATA2 = 1;
             La(n);
            
        }
        else if(RD5 == 0)//si
        {
             //LATA = 0;
            LATBbits.LATB5 = 1;
             Si(n);
            
        }
        else if(inter == 1)//s
        {
            inter = 0;
             small_bee();
        }
        else
        {
           // LATAbits.LATA5 = 1;
            PWM1_Duty(0);
            LATA = 0;
            LATB = 0;
        }
    }
}