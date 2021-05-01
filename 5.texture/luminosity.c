#include "texture_header.h"

// 거리에 따라 밝기를 선형적으로 조절
double get_luminosity(double dist)
{
    static double D = -1;
    // 밝기 감소에 맵의 크기를 고려
    if (D < 0) D = (map_xmax() + map_ymax()) / 2.0;   // 가로 세로 크기 평균
    return (dist > D) ? 0 : (1. - dist/D);
}

// R, G, B에 밝기곱
int fade_color(int color, double lum)
{
    if (lum < 0) lum = 0;
    else if (lum > 1) lum = 1;
    int r, g, b;
    // 색상 정수 대표값 color와 RGB 개별 색상값 간의 변환함수 ( 구현 X )
    decode_color(color, &r, &g, &b);
    return encode_color((int)(r*lum), (int)(g*lum), (int)(b*lum));
}