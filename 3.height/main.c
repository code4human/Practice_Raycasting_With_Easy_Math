#include "height_header.h"

int		main(int ac, char** av)
{
	/* ... 중간생략 ... */
	void* gr = gr_init(SX, SY, "ex02");   // 그래픽스용 구조체 포인터 초기화
	gr_clear(gr, 0x000000);    // 검은색으로 화면을 칠한다.

	for (int x=0; x<SX; x++)
	{
		dir_t wdir;
		// cast_single_ray에서 얻어온 벽까지의 거리 wdist를 사용하여, draw_wall에서 화면에 그린다.
		double wdist = cast_single_ray(x, px, py, theta, &wdir);
		draw_wall(gr, wdist, x, wall_colors[wdir]);
	}
	gr_flush(gr);   // 변경사항 반영하여 그리기
	gr_waitkey(gr);   // 키 대기

	gr_finish(gr);   // 포인터 종료
	return 0;
}