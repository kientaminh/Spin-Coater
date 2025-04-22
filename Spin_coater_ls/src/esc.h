#ifndef _ESC_H_
#define _ESC_H_
#include <Arduino.h>

#define MIN_DUTY 4000
#define MAX_DUTY 6553

extern const int freq;     // tan so 
extern const int pwmChannel; //kenh
extern const int resolution; // do phan giai
extern int dutyCycle;
#define ESC_PIN  13  // Change this to your PWM output pin

void Esc_Init();
void setESCThrottle(int throttle);
#endif