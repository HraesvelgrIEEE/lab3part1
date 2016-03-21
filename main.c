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
   
    int leftMotor, rightMotor;
    char buffer[5];
    
    while (1) {
        switch (state) {
            case wait:
                
                break;
            case colorado:
                itoa(pot, buffer, 10);
                printStringLCD(buffer);
                state = setPWMs;
                break;
            case setPWMs:
                leftMotor = 1 - float(511 - pot) / 511.0;
                rightMotor = 1 - float(pot - 511) / 511.0;
                setPWM(PWM_MOTOR_A, leftMotor, PWM_MOTOR_FORWARD);
                setPWM(PWM_MOTOR_B, rightMotor, PWM_MOTOR_FORWARD);
                state = wait;
                break;
        }
    }
}

__ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt() {
    IFS0bits.AD1IF = 0;
    
    pot = ADC1BUF0;
    
    state = colorado;
}

