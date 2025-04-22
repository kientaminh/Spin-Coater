/*
 * @file       pid library
 * @board      STM32F10x
 * @author     Tong Sy Tan
 * @date       Sun, 09/02/2025
*/

#ifndef __PID__
#define __PID__

#include <Arduino.h>

class PID
{
  private:
    float pre_pv;
    uint64_t cur_time;
    uint64_t pre_time;
    uint32_t dt;
	
  public:
    float kp, ki, kd;
    float error;
    float P, I, D;
    float output;
    float max_output;

    PID(float kp, float ki, float kd, float max_output):
      kp(kp),
      ki(ki),
      kd(kd),
      max_output(max_output),
      P(0),
      D(0),
      I(0),
      error(0),
      pre_pv(0) {};

    float Update(float sp, float pv);
};

#endif