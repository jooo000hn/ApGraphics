#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

namespace apanoo {
	#define MATH_PI 3.1415926535897932384626433832795
	#define toRadians(x) (float)(((x) * MATH_PI / 180.0f))  // �Ƕ�ת����
	#define toDegrees(x) (float)(((x) * 180.0f / MATH_PI))  // ����ת�Ƕ�
}