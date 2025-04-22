#include "encoder.h"
#include "esc.h"

int setpoint;
void setup() {
  Serial.begin(9600);
  Encoder_Init();
  Esc_Init();
  Timer10ms_Init();
  Timer1s_Init();
}
void loop() {
  double value = analogRead(34);
  value = map(value, 0, 4096, 0, MAX_DUTY);
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    if (data.toFloat() < 10000)
    {
      setpoint = data.toFloat();
    }
  }
  Enc_pp10ms_output(setpoint);
  // output = MIN_DUTY + ESC_PID.Update(target, rpm);
  // setESCThrottle(data);
  // Serial.println(Enc_pp10ms);
}