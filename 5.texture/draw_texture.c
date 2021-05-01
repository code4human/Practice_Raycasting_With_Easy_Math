#include "texture_header.h"

int 	get_wall_height(double dist)
{
	double _2H = 2.0 * dist * tan(FOV_V / 2.0);
	int w = (int)(SY * (WALL_H / _2H));
	return w;
}

// gr_vline 코드 변경
void 	draw_wall(void* gr, double wdist, int x, int color)
{
	int wh = get_wall_height(wdist);

	int y0 = (int)((SY - wh)/2.0);
	int y1 = y0 + wh -1;

	int ystart = max(0, y0);
	int yend = min(SY-1, y1);

	// gr_vline(gr, x, ystart, yend, color);
    img_t* ptex = texture_get(wdir);
    double txratio = (wdir == DIR_W || wdir == DIR_E) ? (wy-floor(wy)) : (wx-floor(xw));
    int tx = (int)(txratio * ptex->w);

    for (int y=ystart; y<yend; y++)
    {
        int ty = (int)((double)(y-y0) * ptex->h / wh);
        double lum = get_luminosity(wdist);
        // 텍스처 (tx, ty)에 있는 색상을 fade 시킨다.
        int color = fade_color(gr_img_getpixel(ptex, tx, ty), lum);
        gr_putpixel(gr, x, y, color);
    }
}