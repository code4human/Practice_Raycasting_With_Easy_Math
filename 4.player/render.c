#include "player_header.h"

// 벽을 찾아 그려주는 함수
void    render(void* gr, player_t* pp)
{
    static int wall_colors = {
        // DIR_N, E, W, S - 빨강, 초록, 파랑, 회색
        0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
    };
    gr_clear(gr, 0x000000);   // 검정색 바탕
    for (int x=0; x<SX; x++)
    {
        dir_t  wdir;
        double wdist = cast_single_ray(x, pp->x, pp->y, pp->theta, &wdir);
        draw_wall(gr, wdist, x, wall_colors[wdir]);
    }
    gr_flush(gr);   // 변경사항 render
}