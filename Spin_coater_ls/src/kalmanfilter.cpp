#include "kalmanfilter.h"

void KalmanFilter_Init(KalmanFilter_InitTypeDef *KF_Struct, float A, float H, float Q, float R, float initial_x, float initial_P)
{
	KF_Struct->A = A;
	KF_Struct->H = H;
	KF_Struct->Q = Q;
	KF_Struct->R = R;
	KF_Struct->x = initial_x;
	KF_Struct->P = initial_P;
	KF_Struct->initialized = 1;
}

float KalmanFilter_Update(KalmanFilter_InitTypeDef *KF_Struct, float mea)
{
	KF_Struct->x = KF_Struct->A * KF_Struct->x;
	// Du doan sai so: P = A*P*A' + Q
	KF_Struct->P = KF_Struct->A * KF_Struct->P * KF_Struct->A + KF_Struct->Q;
	// Tính toán Kalman gain: K = P*H' / (H*P*H' + R)
	float K = KF_Struct->P * KF_Struct->H / (KF_Struct->H * KF_Struct->P * KF_Struct->H + KF_Struct->R);
	
	// Cap nhat trang thai: x = x + K*(z - H*x)
	KF_Struct->x = KF_Struct->x + K * (mea - KF_Struct->H * KF_Struct->x);
	
	// Cap nhat sai so: P = (1 - K*H)*P
	KF_Struct->P = (1 - K * KF_Struct->H) * KF_Struct->P;
    
  return KF_Struct->x;
}
