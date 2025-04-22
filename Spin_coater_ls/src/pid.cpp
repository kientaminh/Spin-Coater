#include "pid.h"

float Abs(float num) { return num > 0 ? num : -num; }

float PID::Update(float sp, float pv)
{
    cur_time = micros();
    if (cur_time - pre_time >= 1) {  // Giảm tần suất cập nhật PID
        dt = cur_time - pre_time;
        pre_time = cur_time;
        error = sp - pv;
        P = kp * error;
        I += ki * error * dt / 1000000;
        
        if (pre_pv != 0) {
            D = -kd * (pv - pre_pv) * 1000000 / dt;
        }
        pre_pv = pv;

        output = P + I + D;

        if ((output > max_output && error > 0) || (output < -max_output && error < 0)) {
            I -= ki * error * dt / 1000000;
        }

        output = P + I + D;
    }

    return constrain(output, -max_output, max_output);
}
