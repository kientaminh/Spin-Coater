#include "esc.h"

const int freq = 50;
const int pwmChannel = 0;
const int resolution = 16;
int dutyCycle = 0;
void Esc_Init()
{
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ESC_PIN, pwmChannel);
  setESCThrottle(MIN_DUTY);
  delay(1000);
  Serial.println("ok");
}

void setESCThrottle(int output) {
    dutyCycle = constrain(output, MIN_DUTY, MAX_DUTY);
    ledcWrite(pwmChannel, dutyCycle);
}
  