#include "encoder.h"
#include "kalmanfilter.h"
#include "pid.h"
#include "esc.h"

#define KP 0.5		//0.25		//0.35
#define KI 1		//1			//0.75
#define KD 0.0054	//0.006		//0.0055

PID ESC_PID(KP, KI, KD, (MAX_DUTY - MIN_DUTY));
KalmanFilter_InitTypeDef Enc_Filter;
double output;

volatile double Enc_pp10ms = 0;
volatile double Enc_pp10ms_filter = 0;
volatile double pulse = 0.0;
volatile double rpm = 0;
static volatile int pp10ms[10];
static volatile short enc_index = 1;
int timer_flag_10ms = 0, timer_flag_1s;


hw_timer_t *timer_1s = NULL; 
hw_timer_t *timer_10ms = NULL; 

void IRAM_ATTR Timer10ms_ISR()
{
	timer_flag_10ms = 1;
}
void IRAM_ATTR Timer1s_ISR()
{
	timer_flag_1s = 1;
}
void Timer1s_Init()
{
	// Khởi tạo timer với chu kỳ 1µs vì thạch anh của ESP chạy ở 80MHz
	timer_1s = timerBegin(1, 80, true);
	// Gán hàm xử lý ngắt cho Timer
	timerAttachInterrupt(timer_1s, &Timer1s_ISR, true);
	// Đặt thời gian ngắt cho Timer là 1 giây (1.000.000 µs)
	timerAlarmWrite(timer_1s, 10, true);
	// Bắt đầu Timer
	timerAlarmEnable(timer_1s);
}
void Timer10ms_Init()
{
	// Khởi tạo timer với chu kỳ 1µs vì thạch anh của ESP chạy ở 80MHz
	timer_10ms = timerBegin(0, 80, true);
	// Gán hàm xử lý ngắt cho Timer
	timerAttachInterrupt(timer_10ms, &Timer10ms_ISR, true);
	// Đặt thời gian ngắt cho Timer là 1 giây (1.000.000 µs)
	timerAlarmWrite(timer_10ms, 10000, true);
	// Bắt đầu Timer
	timerAlarmEnable(timer_10ms);
}

void IRAM_ATTR Encoder_ISR()
{
	pulse = pulse + 1;
}

void Encoder_Init()
{
	pinMode(ENCODER_PIN_A, INPUT_PULLUP);
	pinMode(ENCODER_PIN_B, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), Encoder_ISR, CHANGE);
	// attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), Encoder_ISR, CHANGE);
	KalmanFilter_Init(&Enc_Filter, 1, 1, 0.5, 2.5, 0, 0);
}

void Enc_pp10ms_output(double target)
{
	if (timer_flag_10ms)
	{
		Enc_pp10ms = pulse / 20;
		Enc_pp10ms_filter = KalmanFilter_Update(&Enc_Filter, Enc_pp10ms);
		rpm = Enc_pp10ms_filter * 60000 / PPR;
		// Serial.println(Enc_pp10ms_filter);
		Serial.println(rpm);
		pulse = 0;
		
		timer_flag_10ms = 0;
	}
	if(timer_flag_1s)
	{
		output = MIN_DUTY + ESC_PID.Update(target, rpm);
		timer_flag_1s = 0;
		setESCThrottle(output);
	}
}