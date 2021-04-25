#include "player_header.h"

// 회전 함수
void player_rotate(player_t* pp, double theta)
{
    pp->theta += theta;

    // 관리 차원에서 0 ~ 360도 범위가 넘어가면 다시 그 안으로 넣어준다.
    if (pp->theta < 0)
        pp->theta += _2PI;
    else if (pp->theta > _2PI)
        pp->theta -= _2PI;   // 회전 몇 번에 각도가 천 단위 되는 것 방지
}

static int get_move_offset(double theta, int key, double m, double* pdx, double* pdy)
{
    switch (key)
    {
        case KEY_W:
        case KEY_S:
            *pdx = (key == KEY_W ? 1 : -1) * m * cos(theta);
            *pdy = (key == KEY_W ? 1 : -1) * m * sin(theta);
        case KEY_A:
        case KEY_D:
            *pdx = m * cos(theta + (key == KEY_A ? 1 : -1) * M_PI_2);   // math.h에 정의된 파이/2 값(90도)
            *pdy = m * sin(theta + (key == KEY_A ? 1 : -1) * M_PI_2);
            break;
        default:   // invalid
            return -1;
    }
    return 0;
}

int player_move(player_t* pp, int key, double m)
{
    double dx = 0, dy = 0;
    double nx, ny;

    // player_move 호출 시 이동 방향에 따른 offset을 계산한다.
    if (get_move_offset(pp->theta, key, m, &dx, &dy) < 0)
    {
        fprintf(stderr, "player_move: invalid key %d\n", key);
        return -1;
    }
    nx = pp->x + dx;
    ny = pp->y + dy;

    // 목적지가 혹시 벽 속은 아닌지 확인하고(최소한의 충돌방지), 플레이어의 위치를 이동한다.
    if (map_get_cell((int)nx, (int)ny) != 0)
    {
        printf("** bump !\n");
        return -1;
    }
    pp->x = nx;
    pp->y = ny;
    return 0;
}