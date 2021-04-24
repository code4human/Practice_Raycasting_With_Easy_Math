/* ---- 2.wall 매크로 재사용 ---- */
#define  SX         400     // screen width
#define  SY         250     // screen height
#define  FOV        60      // field of view (in degree)
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY / (double)SX)
#define  WALL_H     1.0


/* ---- SDL 그래픽스 라이브러리 ---- */
/*
// 초기화한 그래픽스용 구조체 포인터 반환
void*	gr_init(int w, int h, const char* title);
// 다 쓴 그래픽스용 구조체 포인터를 완료처리
void	gr_finish(void*);
// 현재까지의 변경사항을 실제로 화면에 그리라는 명령 (double buffering 개념)
void	gr_flush(void*);
// 주어진 색으로 화면 전체를 칠한다. 색상은 0xRRGGBB 형식의 정수
int 	gr_clear(void*, int color);
// 세로줄 하나를 그린다.
int 	gr_vline(void*, int x, int y0, int y1, int color);
// 아무 키나 눌릴 때까지 기다린다.
int 	gr_waitkey(void*);
*/


/* ---- draw.c ---- */
int 	get_wall_height(double dist);
void 	draw_wall(void* gr, double wdist, int x, int color);