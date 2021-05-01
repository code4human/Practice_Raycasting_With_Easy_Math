#ifndef TEXTURE_HEADER.H
# define TEXTURE_HEADER.H

// 텍스처 이미지 정보
typedef struct {
    int w, h;
    char* name;
    void* sfc;   // SDL 특정 이미지 데이터 
} img_t;

/* ---- SDL 그래픽스 라이브러리를 변형하여 아래와 같은 형태로 사용 ---- */
/*
// 텍스쳐 비트맵 (x, y)에 위치한 픽셀의 색상값 얻는 함수
int gr_img_getpixel(imt_t*, int x, int y);
// 점 하나를 찍는 함수
int gr_putpixel(void*, int x, int y, int color);
*/

#endif