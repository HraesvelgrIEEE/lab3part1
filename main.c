/* File: main.c
 * Author: dhung 
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "lcd.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"

typedef enum stateTypeEnum {wait, colorado, setPWMs} stateType; 

volatile stateType state, nextState;

volatile int pot;

int main(void) {
    //Initialize
    enableInterrupts(); 
    SYSTEMConfigPerformance(10000000);
    //Initialize stuff that I actually understand
    initLCD();
    initTimers();
    initADC();
    initPWM();
   
    float leftMotor, rightMotor;
    char buffer[5];
    
    int min = 500, max = 500;
    
    int i = 0;
    
    //Calibrate pot
    printStringLCD("Calibrate Pot");
    for (i = 0; i != 50; ++i) {
        if (pot < min) min = pot;
        if (pot > max) max = pot;
        delayMs(100);
    }
    
    float average = (float) (max - min) / 2.0 + min;
    //End calibrate
    
    while (1) {
        switch (state) {
            case wait:
                
                break;
            case colorado:
                itoa(buffer, pot, 10);
                clearLCD();
                printStringLCD(buffer);
                state = setPWMs;
                break;
            case setPWMs:
                leftMotor = 1 - 2 * (float) (average - pot) / average;
                rightMotor = 1 - 2 * (float) (pot - average) / average;
                setPWM(PWM_MOTOR_A, leftMotor, PWM_MOTOR_FORWARD, 0);
                setPWM(PWM_MOTOR_B, rightMotor, PWM_MOTOR_FORWARD, 0);
                state = wait;
                break;
        }
    }
}

__ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt() {
    IFS0bits.AD1IF = 0;
    
    pot = ADC1BUF0;
    
    if (state == wait) state = colorado;
}

