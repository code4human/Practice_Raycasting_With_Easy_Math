#include "height_header.h"

double	cast_single_ray(int x, double px, double py, double theta, dir_t* pdir)
{
	double ray = (theta + FOV_H_DIV2) - (x * ANGLE_PER_PIXEL);

	dir_t wdir;
	double wx, wy;

	if (get_wall_intersection(ray, px, py, &wdir, &wx, &wy) == false)
		return INFINITY;
	double wdist = l2dist(px, py, wx, wy);
	wdist *= cos(theta - ray);   // 벽과의 거리를 평면으로 보정

	return wdist;
}