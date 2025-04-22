#ifndef _ENCODER_MODULE_H_
#define _ENCODER_MODULE_H_

#include <Arduino.h>

#define PPR     16

#define ENCODER_PIN_A  33  // Chân A của encoder
#define ENCODER_PIN_B  32  // Chân B của encoder  
#define ENCODER_PULSES_PER_REV  1600 // Số xung trên mỗi vòng của encoder

extern float ppms;
extern volatile double Enc_pp10ms;
extern volatile double pulse;
extern volatile double rpm;
void IRAM_ATTR Encoder_ISR();
void IRAM_ATTR Timer10ms_ISR();
void IRAM_ATTR Timer1s_ISR();
void Timer10ms_Init();
void Timer1s_Init();
void Encoder_Init();

void ESC_Run(float level);
void Enc_pp10ms_output(double target);
#endif
