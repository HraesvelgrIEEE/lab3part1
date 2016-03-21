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

typedef enum stateTypeEnum {/*TODO: THIS*/} stateType; 

volatile stateType state, nextState;

/* TODO LIST:
 * All the noted TO-DOs
 * Displaying detected pot reading on LCD
 * Part 2 stuff
 */

int main(void) {
    //Initialize
    enableInterrupts(); 
    SYSTEMConfigPerformance(10000000);
    //Initialize stuff that I actually understand
    initLCD();
    initTimers();
    initADC();
    initPWM();
   
   while (1) {
        switch (state) {
            //TODO: This FSM
        }
    }
}

__ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt() {
    IFS0bits.AD1IF = 0;
    
    /* TODO: STUFF
     * dutyCycle = float(ADC1BUF0) / 1023 or something
     * ^something could be using clever PR values and (optionally) bit shifting this value to directly get the proportion
     * 
     * Do some FSM magic or something
     */
    
}

