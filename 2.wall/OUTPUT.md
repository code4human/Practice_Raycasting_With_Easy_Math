### 프로그램 컴파일
```
shell $ cc -Wall *.h *.c -lm
```

### 프로그램 입력 예시
```
shell $ ./a.out 1.5 3.5 355
```

### 프로그램 출력 예시
```
# # # # # # 
# . . . . # 
# . . . . # 
# . . # # # 
# # # # # # 

ray=360.00 deg, xstep=1, ystep=0, xslope=-0.00, yslope=inf, nx=2.00, ny=3.50
 V(2, 3.50) --> V(3, 3.50) --> V(4, 3.50) --> V(5, 3.50) --> hit wall!
** ray   0 : dist 3.50

ray=355.00 deg, xstep=1, ystep=-1, xslope=-0.09, yslope=-11.43, nx=2.00, ny=3.00
 V(2, 3.46) --> V(3, 3.37) --> V(4, 3.28) --> V(5, 3.19) --> hit wall!
** ray   1 : dist 3.51

ray=350.00 deg, xstep=1, ystep=-1, xslope=-0.18, yslope=-5.67, nx=2.00, ny=3.00
 V(2, 3.41) --> V(3, 3.24) --> V(4, 3.06) --> H(4.34, 2) --> V(5, 2.88) --> hit wall!
** ray   2 : dist 3.55
```