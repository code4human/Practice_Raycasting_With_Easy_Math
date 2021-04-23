#include "wall_header.h"

// cast_single_ray : 빛줄기 한 개를 쏘고, 부딪힌 벽까지의 거리를 반환한다.
double	cast_single_ray(int x, double px, double py, double theta)
{
	double ray = (theta + FOV_H_DIV2) - (x * ANGLE_PER_PIXEL);

	dir_t wdir;   	 // direction of wall
	double wx, wy;   // coord.(위도, 경도) of wall intersection point

	// get_wall_intersection : 중요한 교점 계산 (DDA 알고리즘 구현체)
	// 인자 : 빛줄기 각도 ray, 플레이어위치 px, py
	// 받아오는 것 : 벽에 닿은 맵 상의 위치 wx, wy, 벽에 닿은 방향 wdir
	if (get_wall_intersection(ray, px, py, &wdir, &wx, &wy) == false)
		return INFINITY;   // 교점이 없는 경우 (maybe bad map)
	// 플레이어 위치에서부터 벽 위치까지의 거리
	double wdist = l2dist(px, py, wx, wy);

	return wdist;
}


// get_wall_intersection : 중요한 교점 계산 (DDA 알고리즘 구현체)
bool	get_wall_intersection(double ray, double px, double py, 
								dir_t* wdir, double* wx, double* wy)
{
	// xstep, ystep : 각도대로 ray를 쏠 때 x축과 y축 방향으로 증가할지/감소할지/꼼짝말지 여부
	// ex. ray = 270도 -> xstep = 0 (정지) , ystep = -1 (-방향으로 감소)
	// 삼각함수 상에서 단위원(r=1) 상의 한 점 : (cos세타, sin세타)
	//                  -> x좌표 부호 : is_sign(cos(ray)), y좌표 부호 : is_sign(sin(ray))
	int xstep = is_sign(cos(ray));   // +1(right), 0(no change), -1(left)
	int ystep = is_sign(sin(ray));   // +1(up),    0(no change), -1(down)

	// f : 빛줄기 직선을 나타내는 일차함수
	// f(x) : 수직선이 아닌 경우(xstep != 0)에 의미가 있다. 
	//        xstep=0 이면 수직선이므로 기울기 xslope = tan세타 는 무한대(undefined)다.
	// g : 그 역함수
	// g(x) : 수평선이 아닌 경우(ystep != 0)에 의미가 있다.
	// 		  ystep=0 이면 수평선이므로 기울기 yslope = 1/tan세타 는 무한대(undefined)다.
	double xslope = (xstep == 0) ? INFINITY : tan(ray);
	double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

	// nx, ny : (px, py)에서 출발한 빛이 다음 번 격자에 도달할 x, y 좌표 
	//          초깃값은 xstep과 ystep에 따라 정해진다. -> (nx, f(nx)), (g(ny),ny) 로 사용됨.
	double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);   // floor: 내림
	double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);   // ceil: 올림

	printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
		rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

	// 수평선이나 수직선이어서 기울기가 정의되지 않을 경우, f와 g는 초깃값인 INFINITY에서 변화가 없다.
	double f = INFINITY, g = INFINITY;
	bool hit = false;
	int hit_side;   // VERT or HORIZ

	while (!hit)
	{
		int mapx, mapy;

		if (xstep != 0) f = xslope * (nx-px) + py;
		if (ystep != 0) g = yslope * (ny-py) + px;
		
		// 플레이어에게 어떤 좌표가 더 가까운가 - VERT(nx, f) or HORIZ(g, ny)
		// dist_v : (px,py)에서 빛줄기를 쐈을 때 다음 번 격자(nx,ny)=(nx,f(nx))의 세로선까지의 거리
		// dist_h : (px,py)에서 빛줄기를 쐈을 때 다음 번 격자(nx,ny)=(g(ny),ny)의 가로선까지의 거리
		double dist_v = l2dist(px, py, nx, f);
		double dist_h = l2dist(px, py, g, ny);

		// VERT 가 더 가까우면 x-axis를 따라 간다.
		if (dist_v < dist_h)
		{
			mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1;
			mapy = (int) f;
			hit_side = VERT;
			printf(" V(%d, %.2f) -->", mapx, f);
		}
		// HORIZ 가 더 가까우면 y-axis를 따라 간다.
		else
		{
			mapx = (int) g;
			mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1;
			hit_side = HORIZ;
			printf(" H(%.2f, %d) -->", g, mapy);
		}
		// 거리를 비교해서 더 가까운 교점을 택한 뒤, 그 점이 속한 맵 인덱스를 mapx, mapy로 얻어낸다. 
		// (mapx, mapy)의 cell 정보가 0(통로)인지 1(벽)인지 판단한다.
		int cell = map_get_cell(mapx, mapy);
		// out of map
		if (cell < 0) break;
		// hit wall
		// 진행방향에 따라 4가지 경우 발생주의
		if (cell == 1)
		{
			if (hit_side == VERT)   // 충돌면이 수직이면
			{
				// x축 진행 +1(right) -> 충돌벽 왼쪽 / x축 진행 -1(left) -> 충돌벽 오른쪽
				*wdir = (xstep > 0) ? DIR_W : DIR_E;
				*wx = nx;
				*wy = f;
			}
			else   // 충돌면이 수평이면
			{
				// y축 진행 +1(up) -> 충돌벽 아래쪽 / y축 진행 -1(down) -> 충돌벽 위쪽 
				*wdir = (ystep > 0) ? DIR_S : DIR_N;
				*wx = g;
				*wy = ny;
			} 
			hit = true;
			printf(" hit wall!\n");
			break;
		}
		// cell == 0 이면 while 반복
		if (hit_side == VERT) nx += xstep;
		else ny += ystep;
	}
	/* end of while(!hit) */

	return hit;
}












