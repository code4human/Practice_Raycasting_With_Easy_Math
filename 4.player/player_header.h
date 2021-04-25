#ifndef PLAYER_HEADER.H
# define PLAYER_HEADER.H

#define _2PI    6.28318530717958647692   // 2*M_PI

#define ROT_UNIT        0.03   // <- or -> 방향키 한번 누를 때 회전할 각도
#define MOVE_UNIT       0.1    // WASD 키 한번 누를 때 움직일 거리

// KEY_* : gr_readkey() 함수가 키 하나를 읽어서 이 enum 중 하나로 리턴 (0, 1, 2, ... 7)
enum { KEY_OTHER, KEY_W, KEY_A, KEY_S, KEY_D, KEY_LEFT, KEY_RIGHT, KEY_ESC };

// 플레이어의 위치, 방향각 구조체
typedef struct {
    double x;
    double y;
    double theta;
} player_t;

#endif