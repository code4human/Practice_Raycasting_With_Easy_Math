#include "wall_header.h"

/* 유틸리티 함수 */
// 부호를 +1, 0, -1 중 하나로 선정한다. is_zero를 통해 0.00000005도 0으로 취급할 수 있다.
int		is_sign(double d)
{
	return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

// 두 점 간의 거리, 즉 유클리드 거리(L2distance)
double	l2dist(double x0, double y0, double x1, double y1)
{
	double dx = x0 - x1;
	double dy = y0 - y1;

	return sqrt(dx*dx + dy*dy);
}