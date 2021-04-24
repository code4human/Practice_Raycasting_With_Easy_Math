#include "height_header.h"

// 벽을 그릴 픽셀 개수 반환
int 	get_wall_height(double dist)
{
	double doubled_H = 2.0 * dist * tan(FOV_V / 2.0);   // 2H
	int w = (int)(SY * (WALL_H / doubled_H));   // w = SY * (1 / 2H)
	return w;
}

void 	draw_wall(void* gr, double wdist, int x, int color)
{
	int wh = get_wall_height(wdist);   // 벽 높이 in pixels

	// y0 : 화면 상에서 벽이 그려질 시작 위치(상단), y1 : 끝 위치 (하단)
	int y0 = (int)((SY - wh)/2.0);
	int y1 = y0 + wh -1;

	// wh이 SY보다 넘칠 경우 끊어낸다. (clipping)
	int ystart = max(0, y0);
	int yend = min(SY-1, y1);

	gr_vline(gr, x, ystart, yend, color);
}