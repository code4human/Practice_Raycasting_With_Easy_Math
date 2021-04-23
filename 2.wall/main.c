#include "wall_header.h"

/* main 함수*/
// 프로그램 인자 : 플레이어 x좌표, y좌표, 시선방향
int		main(int ac, char** av)
{
	if (ac != 4)
	{
		fprintf(stderr, "usage: %s px py theta(deg)\n", av[0]);
		exit(1);
	}
	double px, py, theta;

	px = atof(av[1]);   // atof는 문자열을 실수로 변환
	py = atof(av[2]);
	theta = deg2rad(atof(av[3]));

	// 인자 처리 뒤에 MAP을 한번 출력한다. 
	// 2차원 배열은 인덱스 순서가 다르므로 MAP(y가 위로, x가 오른쪽으로 증가하는 좌표평면)에 맞게 출력한다. 
	for (int y=MAPY-1; y>=0; y--)
	{
		for (int x=0; x<MAPX; x++)
		{
			printf("%c ", (map_get_cell(x,y)==1 ? '#':'.'));
		}
		putchar('\n');
	}
	// 메인 루프 : x=0부터 SX-1까지 빛줄기를 쏘는 과정
	for (int x=0; x<SX; x++)
	{
		// cast_single_ray : 빛줄기 한 개를 쏜다.
		double wdist = cast_single_ray(x, px, py, theta);
		printf("** ray %3d : dist %.2f\n", x, wdist);
	}
}