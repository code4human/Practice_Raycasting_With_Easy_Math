#include "player_header.h"

int		main(int ac, char** av)
{
	/* ... 오류처리나 맵 출력 등은 생략 ... */

    // player_t 구조체 사용
    player_t pl;
    pl.x = atof(av[1]);
    pl.y = atof(av[2]);
    pl.theta = deg2rad(atof(av[3]));

    void* gr = gr_init(SX, SY, "ex03");
    render(gr, &pl);

    // 키보드 입력에 따른 동작
    for (;;)
    {
        int key = gr_readkey(gr);
        if (key < 0 || key == KEY_ESC)
            break;
        if (key == KEY_LEFT || key == KEY_RIGHT)
        {
            player_rotate(&pl, ROT_UNIT * (key == KEY_LEFT ? 1 : -1));
            render(gr, &pl);
        }
        else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
        {
            if (player_move(&pl, key, MOVE_UNIT) == 0)
                render(gr, &pl);
        }
    }

    gr_finish(gr);   // 포인터 종료
	return 0;
}