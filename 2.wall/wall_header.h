#ifndef WALL_HEADER_H
# define WALL_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ---- 레이캐스팅 기본 매크로 정의 ---- */
#define EPS			(1e-06)  			 // 부동소수점 실수가 0인지 알아보기 위한 매크로 (IEEE754, machine epsilon)
#define is_zero(d)	(fabs(d) < EPS) 	 // abs는 정수 절댓값, fabs는 실수 절댓값

#define deg2rad(d)	((d)*M_PI / 180.0)   // degree to radian (c언어 math 라이브러리 함수들은 라디안 단위를 가정)
#define rad2deg(d)	((d)*180.0 / M_PI)   // radian to degree
#define min(a, b)	((a)<(b) ? (a):(b))
#define max(a, b)	((a)>(b) ? (a):(b))

// 시선방향과 좌우 +-5도로 광선 3개가 나가는 예시
#define SX			3    	// 임시 screen width (화면 가로 해상도이자 빛줄기 개수)
#define FOV			10   	// field of view (degree)
#define FOV_H		deg2rad(FOV)	// 좌우 +- FOV  

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOV_H_DIV2 = FOV_H / 2.0;

enum { VERT, HORIZ };

typedef enum { false=0, true=1 } bool;
typedef	enum { DIR_N=0, DIR_E, DIR_W, DIR_S } dir_t;


/* ---- MAP 정의 ---- */
// 6, 5 예시
#define MAPX 		6
#define MAPY		5


/* ---- utils.c ---- */
int		is_sign(double d);
double	l2dist(double x0, double y0, double x1, double y1);


/* ---- map.c ---- */
int		map_get_cell(int x, int y);


/* ---- cast.c ---- */
double	cast_single_ray(int x, double px, double py, double theta);
bool	get_wall_intersection(double ray, double px, double py, 
								dir_t* wdir, double* wx, double* wy);
#endif