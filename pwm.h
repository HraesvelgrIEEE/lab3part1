/* File:   pwm.h
 * Author: dhung
 */

#ifndef PWM_H
#define	PWM_H

#define PWM_MOTOR_A 1
#define PWM_MOTOR_B 2

#define PWM_MOTOR_FORWARD 0
#define PWM_MOTOR_BACKWARD 1

void initPWM();
void setPWM(int motorSelect, float dutyCycle, short direction, short idle);

#endif	/* PWM_H */