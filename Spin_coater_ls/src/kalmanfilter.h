#ifndef __KALMANFILTER__
#define __KALMANFILTER__

#ifdef __cplusplus
extern "C" {
#endif
#include "math.h"
typedef struct
{
	// Model parameters
	float A;  // State transition matrix
	float H;  // Observation matrix
	float Q;  // Process noise covariance
	float R;  // Measurement noise covariance
	
	// Filter state
	float x;  // State estimate
	float P;  // Estimate error covariance
	int initialized;
	
}KalmanFilter_InitTypeDef;
	
void KalmanFilter_Init(KalmanFilter_InitTypeDef *KF_Struct, float A, float H, float Q, float R, float initial_x, float initial_P);
float KalmanFilter_Update(KalmanFilter_InitTypeDef *KF_Struct, float mea);


#ifdef __cplusplus
}
#endif
#endif
