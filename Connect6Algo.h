// Samsung Go Tournament Form C Connect6Algo Header (g++-4.8.3)

// <--------------- 이 Code를 수정하면  작동하지 않을 수 있습니다 ------------------>

#pragma once
extern int width, height;
extern int terminateAI;
extern unsigned s_time;

extern FILE *fp;


extern int isFree(int x, int y);
extern int showBoard(int x, int y);
extern void init();
extern void restart();
extern void mymove(int x[], int y[], int cnt = 2);
extern void opmove(int x[], int y[], int cnt = 2);
extern void block(int, int);
extern int setLine(char *fmt, ...);
extern void domymove(int x[], int y[], int cnt = 2);
extern void writeLog(char *log);

extern int getLimitTime();

void myturn(int cnt = 2);
char info[];

struct Coordinate {
	int x, y;
};

struct Point {
	int x, y, v;
};

struct Count {
	int v, vm, vs;
};

struct Heuristic {
	int v, t, j;
};

void initHeuristic();
void heuristicCount(Count *cnt, int turn);
int getStatus(int turn, int fs);
int abp(int alpha, int beta, int dep, Point *usp);
