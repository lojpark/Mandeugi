// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI �ڵ� �ۼ� ���]

1. char info[]�� �迭 �ȿ�					"TeamName:�ڽ��� ����,Department:�ڽ��� �Ҽ�"					������ �ۼ��մϴ�.
( ���� ) Teamname:�� Department:�� �� ���� �մϴ�.
"�ڽ��� ����", "�ڽ��� �Ҽ�"�� �����ؾ� �մϴ�.

2. �Ʒ��� myturn() �Լ� �ȿ� �ڽŸ��� AI �ڵ带 �ۼ��մϴ�.

3. AI ������ �׽�Ʈ �Ͻ� ���� "���� �˰����ȸ ��"�� ����մϴ�.

4. ���� �˰��� ��ȸ ���� �����ϱ⿡�� �ٵϵ��� ���� ��, �ڽ��� "����" �� �� �˰����� �߰��Ͽ� �׽�Ʈ �մϴ�.



[���� �� �Լ�]
myturn(int cnt) : �ڽ��� AI �ڵ带 �ۼ��ϴ� ���� �Լ� �Դϴ�.
int cnt (myturn()�Լ��� �Ķ����) : ���� �� �� �־��ϴ��� ���ϴ� ����, cnt�� 1�̸� ���� ���� ��  �� ����  �δ� ��Ȳ(�� ��), cnt�� 2�̸� �� ���� ���� �δ� ��Ȳ(�� ��)
int  x[0], y[0] : �ڽ��� �� ù �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
int  x[1], y[1] : �ڽ��� �� �� �� ° ���� x��ǥ , y��ǥ�� ����Ǿ�� �մϴ�.
void domymove(int x[], int y[], cnt) : �� ������ ��ǥ�� �����ؼ� ���


//int board[BOARD_SIZE][BOARD_SIZE]; �ٵ��� �����Ȳ ��� �־� �ٷλ�� ������. ��, ���������ͷ� ���� �������
// ������ ���� ��ġ�� �ٵϵ��� ������ �ǰ��� ó��.

boolean ifFree(int x, int y) : ���� [x,y]��ǥ�� �ٵϵ��� �ִ��� Ȯ���ϴ� �Լ� (������ true, ������ false)
int showBoard(int x, int y) : [x, y] ��ǥ�� ���� ���� �����ϴ��� �����ִ� �Լ� (1 = �ڽ��� ��, 2 = ����� ��, 3 = ��ŷ)


<-------AI�� �ۼ��Ͻ� ��, ���� �̸��� �Լ� �� ���� ����� �������� �ʽ��ϴ�----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include "Connect6Algo.h"
#define N 19
#define INF 10000000
#define WALL 4

// "�����ڵ�[C]"  -> �ڽ��� ���� (����)
// "AI�μ�[C]"  -> �ڽ��� �Ҽ� (����)
// ����� ���������� �ݵ�� �������� ����!
char info[] = { "TeamName:������,Department:���հ����б�" };
Heuristic hv[70];
int t[21][21];
int stTime;
Point firstStone, secondStone;
int bn;
std::vector<Coordinate> blocks;
int w[2][8] = { { -1, 1, 0, 0, -1, -1, 1, 1 },{ 0, 0, -1, 1, -1, 1, 1, -1 } };
int limits;

void myturn(int cnt) {

	int x[2], y[2];

	// �� �κп��� �˰��� ���α׷�(AI)�� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����Ͻø� �˴ϴ�.
	// ���� Sample code�� AI�� Random���� ���� ���� Algorithm�� �ۼ��Ǿ� �ֽ��ϴ�.

	// Set start time
	stTime = clock();

	int i, j, k;

	// Initialize table
	blocks.clear();
	for (i = 0; i <= N + 1; i++) {
		for (j = 0; j <= N + 1; j++) {
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1) {
				t[i][j] = WALL;
				continue;
			}
			else {
				t[i][j] = showBoard(j - 1, i - 1);
				if (t[i][j] == 3) blocks.push_back({ j, i });
			}
		}
	}
	bn = blocks.size();
	limits = getLimitTime() * CLOCKS_PER_SEC - 500;

	// If it's first stone, set the stone next to the block stone
	if (cnt == 1) {
		int max = 0, count = 0, dir = 0, length = 1, curLength = 0, l;
		i = j = 10;
		for (l = 1; l <= 361; l++) {
			// Count the block stones
			if (t[i][j] == 0) {
				count = 0;
				for (k = 0; k < 8; k++) {
					if (t[i + w[0][k]][j + w[1][k]] == 3) {
						count++;
					}
				}
				if (max < count) {
					max = count;
					x[0] = j - 1;
					y[0] = i - 1;
				}
			}

			switch (dir) {
			// Up
			case 0:
				i--;
				curLength++;
				if (curLength >= length) {
					curLength = 0;
					dir = 1;
				}
				break;
			// Right
			case 1:
				j++;
				curLength++;
				if (curLength >= length) {
					curLength = 0;
					dir = 2;
					length++;
				}
				break;
			// Down
			case 2:
				i++;
				curLength++;
				if (curLength >= length) {
					curLength = 0;
					dir = 3;
				}
				break;
			// Left
			case 3:
				j--;
				curLength++;
				if (curLength >= length) {
					curLength = 0;
					dir = 0;
					length++;
				}
				break;
			}
		}
		if (max == 0) {
			x[0] = 9;
			y[0] = 9;
		}
	}
	// Else, Run AI ( Alpha Beta Pruning )
	else {
		initHeuristic();
		abp(-INF, INF, 0, NULL);
		x[0] = firstStone.x - 1;
		y[0] = firstStone.y - 1;
		x[1] = secondStone.x - 1;
		y[1] = secondStone.y - 1;
	}

	// �� �κп��� �ڽ��� ���� ���� ����Ͻʽÿ�.
	// �ʼ� �Լ� : domymove(x�迭,y�迭,�迭ũ��)
	// ���⼭ �迭ũ��(cnt)�� myturn()�� �Ķ���� cnt�� �״�� �־���մϴ�.
	domymove(x, y, cnt);
}

bool cmp(Point arg1, Point arg2) {
	return arg1.v > arg2.v;
}

void initHeuristic() {
	/* index : Sequence -> Binary Code */
	/* v : Value */
	/* t : Number of stone which is necessory to defense */
	/* j : Number of skipped stone */

	hv[0].v = 0;
	hv[0].t = 0;
	hv[0].j = 2;

	hv[1].v = 1;// 000001
	hv[1].t = 2;
	hv[1].j = 7;
	hv[2].v = 1;// 000010
	hv[2].t = 2;
	hv[2].j = 6;
	hv[3].v = 2;// 000011
	hv[3].t = 2;
	hv[3].j = 7;
	hv[4].v = 1;// 000100
	hv[4].t = 2;
	hv[4].j = 5;
	hv[5].v = 2;// 000101
	hv[5].t = 3;
	hv[5].j = 5;
	hv[6].v = 2;// 000110
	hv[6].t = 2;
	hv[6].j = 6;
	hv[7].v = 3;// 000111
	hv[7].t = 2;
	hv[7].j = 7;
	hv[8].v = 1;// 001000
	hv[8].t = 2;
	hv[8].j = 4;
	hv[9].v = 2;// 001001
	hv[9].t = 1;
	hv[9].j = 4;
	hv[10].v = 2;// 001010
	hv[10].t = 3;
	hv[10].j = 4;
	hv[11].v = 3;// 001011
	hv[11].t = 3;
	hv[11].j = 4;
	hv[12].v = 2;// 001100
	hv[12].t = 2;
	hv[12].j = 5;
	hv[13].v = 3;// 001101
	hv[13].t = 3;
	hv[13].j = 5;
	hv[14].v = 3;// 001110
	hv[14].t = 2;
	hv[14].j = 6;
	hv[15].v = 4;// 001111
	hv[15].t = 2;
	hv[15].j = 7;
	hv[16].v = 1;// 010000
	hv[16].t = 2;
	hv[16].j = 3;
	hv[17].v = 2;// 010001
	hv[17].t = 1;
	hv[17].j = 3;
	hv[18].v = 2;// 010010
	hv[18].t = 1;
	hv[18].j = 3;
	hv[19].v = 3;// 010011
	hv[19].t = 1;
	hv[19].j = 3;
	hv[20].v = 2;// 010100
	hv[20].t = 3;
	hv[20].j = 3;
	hv[21].v = 3;// 010101
	hv[21].t = 1;
	hv[21].j = 3;
	hv[22].v = 3;// 010110
	hv[22].t = 3;
	hv[22].j = 3;
	hv[23].v = 4;// 010111
	hv[23].t = 3;
	hv[23].j = 3;
	hv[24].v = 2;// 011000
	hv[24].t = 2;
	hv[24].j = 4;
	hv[25].v = 3;// 011001
	hv[25].t = 1;
	hv[25].j = 4;
	hv[26].v = 3;// 011010
	hv[26].t = 3;
	hv[26].j = 4;
	hv[27].v = 4;// 011011
	hv[27].t = 3;
	hv[27].j = 4;
	hv[28].v = 3;// 011100
	hv[28].t = 2;
	hv[28].j = 5;
	hv[29].v = 4;// 011101
	hv[29].t = 3;
	hv[29].j = 5;
	hv[30].v = 4;// 011110
	hv[30].t = 2;
	hv[30].j = 6;
	hv[31].v = 5;// 011111
	hv[31].t = 2;
	hv[31].j = 7;
	hv[32].v = 1;// 100000
	hv[32].t = 2;
	hv[32].j = 2;
	hv[33].v = 2;// 100001
	hv[33].t = 1;
	hv[33].j = 2;
	hv[34].v = 2;// 100010
	hv[34].t = 1;
	hv[34].j = 2;
	hv[35].v = 3;// 100011
	hv[35].t = 1;
	hv[35].j = 2;
	hv[36].v = 2;// 100100
	hv[36].t = 1;
	hv[36].j = 2;
	hv[37].v = 3;// 100101
	hv[37].t = 1;
	hv[37].j = 2;
	hv[38].v = 3;// 100110
	hv[38].t = 1;
	hv[38].j = 2;
	hv[39].v = 4;// 100111
	hv[39].t = 1;
	hv[39].j = 2;
	hv[40].v = 2;// 101000
	hv[40].t = 3;
	hv[40].j = 2;
	hv[41].v = 3;// 101001
	hv[41].t = 1;
	hv[41].j = 2;
	hv[42].v = 3;// 101010
	hv[42].t = 1;
	hv[42].j = 2;
	hv[43].v = 4;// 101011
	hv[43].t = 1;
	hv[43].j = 2;
	hv[44].v = 3;// 101100
	hv[44].t = 3;
	hv[44].j = 2;
	hv[45].v = 4;// 101101
	hv[45].t = 1;
	hv[45].j = 2;
	hv[46].v = 4;// 101110
	hv[46].t = 3;
	hv[46].j = 2;
	hv[47].v = 5;// 101111
	hv[47].t = 3;
	hv[47].j = 2;
	hv[48].v = 2;// 110000
	hv[48].t = 2;
	hv[48].j = 3;
	hv[49].v = 3;// 110001
	hv[49].t = 1;
	hv[49].j = 3;
	hv[50].v = 3;// 110010
	hv[50].t = 1;
	hv[50].j = 3;
	hv[51].v = 4;// 110011
	hv[51].t = 1;
	hv[51].j = 3;
	hv[52].v = 3;// 110100
	hv[52].t = 3;
	hv[52].j = 3;
	hv[53].v = 4;// 110101
	hv[53].t = 1;
	hv[53].j = 3;
	hv[54].v = 4;// 110110
	hv[54].t = 3;
	hv[54].j = 3;
	hv[55].v = 5;// 110111
	hv[55].t = 3;
	hv[55].j = 3;
	hv[56].v = 3;// 111000
	hv[56].t = 2;
	hv[56].j = 4;
	hv[57].v = 4;// 111001
	hv[57].t = 1;
	hv[57].j = 4;
	hv[58].v = 4;// 111010
	hv[58].t = 3;
	hv[58].j = 4;
	hv[59].v = 5;// 111011
	hv[59].t = 3;
	hv[59].j = 4;
	hv[60].v = 4;// 111100
	hv[60].t = 2;
	hv[60].j = 5;
	hv[61].v = 5;// 111101
	hv[61].t = 3;
	hv[61].j = 5;
	hv[62].v = 5;// 111110
	hv[62].t = 2;
	hv[62].j = 6;
	hv[63].v = 5;// 111111
	hv[63].t = 2;
	hv[63].j = 7;
}

void heuristicCount(Count *cnt, int turn) {
	int i, j, k;
	int notTurn = 0;
	int cntVal = 0;
	int v = 0;
	int jump = 0;

	if (turn == 1) notTurn = 2;
	else notTurn = 1;

	for (i = 0; i < bn; i++) {
		t[blocks[i].y][blocks[i].x] = turn;
	}

	/* Up */
	for (i = 1; i <= N; i++) {
		cntVal = 0;
		v = 0;
		jump = 0;
		for (j = 1; j <= N; j++) {
			if (t[i][j] == turn || t[i][j] == 0) {
				cntVal++;
				if (cntVal == 6) {
					if (v == 0) {
						for (k = -5; k <= 0; k++) {
							if (t[i][j + k] != 0) v++;
							if (k != 0) v <<= 1;
						}

						if (v == 0) {
							if (t[i][j] == 0) {
								cntVal--;
								continue;
							}
							if (t[i][j] == turn) {
								v = 1;
								cntVal--;
								continue;
							}
						}
					}
					else {
						if (t[i][j - 6] == turn) {
							v -= 32;
						}
						v <<= 1;
						if (t[i][j] != 0) v++;
					}

					// Skip
					if (jump > 0) {
						jump--;
						cntVal--;
						continue;
					}

					// Back == O or After == O
					if (t[i][j - 6] == turn || t[i][j + 1] == turn) {
					}
					// Connect 6
					else if (v == 63) {
						cnt[6].v++;
					}
					// Back == X or After == X
					else if (t[i][j - 6] == notTurn || t[i][j + 1] == notTurn || t[i][j - 6] == WALL || t[i][j + 1] == WALL) {
						cnt[hv[v].v].vm++;
					}
					// Back2 == O or After2 == O
					else if ((j - 7 > 0 && t[i][j - 7] == turn) || (j + 2 <= N && t[i][j + 2] == turn)) {
						cnt[hv[v].v].vm++;
					}
					// It's free
					else {
						if (hv[v].t == 2) {
							cnt[hv[v].v].v++;
						}
						else {
							if (hv[v].t == 3) {
								cnt[hv[v].v].vs++;
							}
							cnt[hv[v].v].vm++;
						}
						jump = (hv[v].j - 2);
					}
					cntVal--;
				}
			}
			else {
				cntVal = 0;
				v = 0;
				jump = 0;
			}
		}
	}

	/* Down */
	for (j = 1; j <= N; j++) {
		cntVal = 0;
		v = 0;
		jump = 0;
		for (i = 1; i <= N; i++) {
			if (t[i][j] == turn || t[i][j] == 0) {
				cntVal++;
				if (cntVal == 6) {
					if (v == 0) {
						for (k = -5; k <= 0; k++) {
							if (t[i + k][j] != 0) v++;
							if (k != 0) v <<= 1;
						}

						if (v == 0) {
							if (t[i][j] == 0) {
								cntVal--;
								continue;
							}
							if (t[i][j] == turn) {
								v = 1;
								cntVal--;
								continue;
							}
						}
					}
					else {
						if (t[i - 6][j] == turn) {
							v -= 32;
						}
						v <<= 1;
						if (t[i][j] != 0) v++;
					}

					// Skip
					if (jump > 0) {
						jump--;
						cntVal--;
						continue;
					}

					// Back == O or After == O
					if (t[i - 6][j] == turn || t[i + 1][j] == turn) {
					}
					// Connect 6
					else if (v == 63) {
						cnt[6].v++;
					}
					// Back == X or After == X
					else if (t[i - 6][j] == notTurn || t[i + 1][j] == notTurn || t[i - 6][j] == WALL || t[i + 1][j] == WALL) {
						cnt[hv[v].v].vm++;
					}
					// Back2 == O or After2 == O
					else if ((i - 7 > 0 && t[i - 7][j] == turn) || (i + 2 <= N && t[i + 2][j] == turn)) {
						cnt[hv[v].v].vm++;
					}
					// It's free
					else {
						if (hv[v].t == 2) {
							cnt[hv[v].v].v++;
						}
						else {
							if (hv[v].t == 3) {
								cnt[hv[v].v].vs++;
							}
							cnt[hv[v].v].vm++;
						}
						jump = (hv[v].j - 2);
					}
					cntVal--;
				}
			}
			else {
				cntVal = 0;
				v = 0;
				jump = 0;
			}
		}
	}

	/* Right Up */
	for (i = 1; i < N * 2; i++) {
		cntVal = 0;
		v = 0;
		jump = 0;
		int st = 1, ed = i;
		if (i > N) {
			st += i - N;
			ed -= i - N;
		}
		for (j = st; j <= ed; j++) {
			if (t[(i - j + 1)][j] == turn || t[(i - j + 1)][j] == 0) {
				cntVal++;
				if (cntVal == 6) {
					if (v == 0) {
						for (k = -5; k <= 0; k++) {
							if (t[(i - j + 1) - k][j + k] != 0) v++;
							if (k != 0) v <<= 1;
						}

						if (v == 0) {
							if (t[(i - j + 1)][j] == 0) {
								cntVal--;
								continue;
							}
							if (t[(i - j + 1)][j] == turn) {
								v = 1;
								cntVal--;
								continue;
							}
						}
					}
					else {
						if (t[(i - j + 1) + 6][j - 6] == turn) {
							v -= 32;
						}
						v <<= 1;
						if (t[(i - j + 1)][j] != 0) v++;
					}

					// Skip
					if (jump > 0) {
						jump--;
						cntVal--;
						continue;
					}

					// Back == O or After == O
					if (t[(i - j + 1) + 6][j - 6] == turn || t[(i - j + 1) - 1][j + 1] == turn) {
					}
					// Connect 6
					else if (v == 63) {
						cnt[6].v++;
					}
					// Back == X or After == X
					else if (t[(i - j + 1) + 6][j - 6] == notTurn || t[(i - j + 1) - 1][j + 1] == notTurn ||
						t[(i - j + 1) + 6][j - 6] == WALL || t[(i - j + 1) - 1][j + 1] == WALL) {
						cnt[hv[v].v].vm++;
					}
					// Back2 == O or After2 == O
					else if (((i - j + 1) + 7 <= N && j - 7 > 0 && t[(i - j + 1) + 7][j - 7] == turn) ||
						((i - j + 1) - 2 > 0 && j + 2 <= N && t[(i - j + 1) - 2][j + 2] == turn)) {
						cnt[hv[v].v].vm++;
					}
					// It's free
					else {
						if (hv[v].t == 2) {
							cnt[hv[v].v].v++;
						}
						else {
							if (hv[v].t == 3) {
								cnt[hv[v].v].vs++;
							}
							cnt[hv[v].v].vm++;
						}
						jump = (hv[v].j - 2);
					}
					cntVal--;
				}
			}
			else {
				cntVal = 0;
				v = 0;
				jump = 0;
			}
		}
	}

	/* Right Down */
	for (i = 1; i < N * 2; i++) {
		cntVal = 0;
		v = 0;
		jump = 0;
		int st = 1, ed = i;
		if (i > N) {
			st += i - N;
			ed -= i - N;
		}
		for (j = st; j <= ed; j++) {
			if (t[N - (i - j)][j] == turn || t[N - (i - j)][j] == 0) {
				cntVal++;
				if (cntVal == 6) {
					if (v == 0) {
						for (k = -5; k <= 0; k++) {
							if (t[N - (i - j) + k][j + k] != 0) v++;
							if (k != 0) v <<= 1;
						}

						if (v == 0) {
							if (t[N - (i - j)][j] == 0) {
								cntVal--;
								continue;
							}
							if (t[N - (i - j)][j] == turn) {
								v = 1;
								cntVal--;
								continue;
							}
						}
					}
					else {
						if (t[N - (i - j) - 6][j - 6] == turn) {
							v -= 32;
						}
						v <<= 1;
						if (t[N - (i - j)][j] != 0) v++;
					}

					// Skip
					if (jump > 0) {
						jump--;
						cntVal--;
						continue;
					}

					// Back == O or After == O
					if (t[N - (i - j) - 6][j - 6] == turn || t[N - (i - j) + 1][j + 1] == turn) {
					}
					// Connect 6
					else if (v == 63) {
						cnt[6].v++;
					}
					// Back == X or After == X
					else if (t[N - (i - j) - 6][j - 6] == notTurn || t[N - (i - j) + 1][j + 1] == notTurn ||
						t[N - (i - j) - 6][j - 6] == WALL || t[N - (i - j) + 1][j + 1] == WALL) {
						cnt[hv[v].v].vm++;
					}
					// Back2 == O or After2 == O
					else if ((N - (i - j) - 7 > 0 && j - 7 > 0 && t[N - (i - j) - 7][j - 7] == turn) ||
						(N - (i - j) + 2 <= N && j + 2 <= N && t[N - (i - j) + 2][j + 2] == turn)) {
						cnt[hv[v].v].vm++;
					}
					// It's free
					else {
						if (hv[v].t == 2) {
							cnt[hv[v].v].v++;
						}
						else{
							if (hv[v].t == 3) {
								cnt[ hv[ v ].v ].vs++;
							}
							cnt[ hv[ v ].v ].vm++;
						}
						jump = (hv[v].j - 2);
					}
					cntVal--;
				}
			}
			else {
				cntVal = 0;
				v = 0;
				jump = 0;
			}
		}
	}
}

int getStatus(int turn, int fs) {
	int i;
	int status = 0, value = 0;

	Count cnt[N];

	/* Initialize count array */
	for (i = 0; i < N; i++) {
		cnt[i].v = cnt[i].vm = cnt[i].vs = 0;
	}
	/* Count my continuous stones */
	heuristicCount(cnt, 1);

	/* Set value */
	value = 0;
	if (turn == 1) {
		if (fs == 1) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v >= 1 || cnt[5].vm >= 1) value += 30000;
			else if (cnt[4].v >= 1 || cnt[4].vm >= 1) value += 30000;
			else if (cnt[3].v + cnt[3].vs >= 2) value += 1200;
			else if (cnt[3].v + cnt[3].vs >= 1 && cnt[3].vm >= 1) value += 1200;
			else if (cnt[3].v + cnt[3].vs >= 1 && cnt[2].v + cnt[2].vs >= 3) value += 1200;
			else if (cnt[2].v + cnt[2].vs >= 2) value += 1000;

			value += (cnt[3].v + cnt[3].vs) * 15;
			if ((cnt[3].v + cnt[3].vs) > 0) {
				if (cnt[2].v + cnt[2].vs >= 1) {
					value += (cnt[2].v + cnt[2].vs) * 15;
				}
			}
			else if (cnt[2].v + cnt[2].vs > 0) {
				if (cnt[2].v + cnt[2].vs >= 2) {
					value += (cnt[2].v + cnt[2].vs) * 15;
				}
			}
			value += (cnt[2].v + cnt[2].vs) * 10;
			value += cnt[3].vm * 2;
			value += cnt[2].vm;
		}
		else if (fs == 2) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v + cnt[5].vs >= 1 || cnt[5].vm >= 1) value += 30000;
			else if (cnt[4].v + cnt[4].vs >= 2) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].v + cnt[3].vs >= 1) value += 5000;
			else if (cnt[4].v + cnt[4].vs >= 1 && cnt[3].v >= 1) value += 5000;
			else if (cnt[4].vm >= 1 && cnt[3].v + cnt[3].vs >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[2].v + cnt[2].vs >= 1) value += 5000;
			else if (cnt[3].v >= 1 && cnt[2].v + cnt[2].vs >= 1) value += 5000;

			value += (cnt[4].v + cnt[4].vs) * 15;
			value += (cnt[3].v + cnt[3].vs) * 15;
			if (cnt[3].v > 0) {
				if ((cnt[3].v + cnt[3].vs) >= 2) {
					value += (cnt[3].v + cnt[3].vs) * 20;
				}
				if (cnt[2].v + cnt[2].vs >= 2) {
					value += (cnt[2].v + cnt[2].vs) * 15;
				}
			}
			value += (cnt[2].v + cnt[2].vs) * 10;
			value += cnt[4].vm * 5;
			value += cnt[3].vm * 2;
			value += cnt[2].vm;
		}
	}
	if (turn == 2) {
		if (fs == 1) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v >= 1 && cnt[4].v >= 1) value += 5000;
			else if (cnt[5].v >= 1 && cnt[4].vm >= 1) value += 5000;
			else if (cnt[5].v >= 1 && cnt[3].v >= 2) value += 5000;
			else if (cnt[5].v >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[5].vm >= 1 && cnt[4].v >= 1) value += 5000;
			else if (cnt[4].v >= 2) value += 5000;
			else if (cnt[4].v >= 1 && cnt[4].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].v >= 2) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[2].v >= 1) value += 2000;
			else if (cnt[3].v >= 3) value += 1000;

			value += cnt[5].v * 15;
			value += cnt[4].v * 15;
			if (cnt[4].v > 0) {
				if (cnt[3].v >= 2) {
					value += (cnt[3].v) * 20;
				}
				if (cnt[2].v >= 2) {
					value += (cnt[2].v) * 15;
				}
			}
			value += cnt[3].v * 15;
			value += cnt[2].v * 10;
			value += cnt[5].vm * 5;
			value += cnt[4].vm * 5;
			value += cnt[3].vm * 2;
			value += cnt[2].vm * 2;
		}
		else if (fs == 2) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v >= 1) value += 5000;
			else if (cnt[5].vm >= 1 && cnt[4].vm >= 1) value += 5000;
			else if (cnt[5].vm >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1) value += 5000;
			else if (cnt[4].vm >= 2) value += 5000;
			else if (cnt[4].vm >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 1000;
			else if (cnt[4].vm >= 1 && cnt[2].v >= 2) value += 1000;
			else if (cnt[3].v >= 2) value += 1000;

			value += cnt[5].vm * 10;
			value += cnt[4].vm * 10;
			value += cnt[3].v * 15;
			if (cnt[3].v > 0) {
				if (cnt[2].v >= 2) {
					value += (cnt[2].v) * 15;
				}
			}
			else if (cnt[2].v > 0) {
				if (cnt[2].v >= 3) {
					value += (cnt[2].v) * 15;
				}
			}
			value += cnt[3].vm * 2;
			value += cnt[2].v * 10;
			value += cnt[2].vm * 2;
			value *= 2;
		}
	}
	status += value;

	/* Initialize count array */
	for (i = 0; i < N; i++) {
		cnt[i].v = cnt[i].vm = cnt[i].vs = 0;
	}
	/* Count enemy's continuous stones */
	heuristicCount(cnt, 2);

	/* Set value */
	value = 0;
	if (turn == 2) {
		if (fs == 1) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v >= 1 || cnt[5].vm >= 1) value += 30000;
			else if (cnt[4].v >= 1 || cnt[4].vm >= 1) value += 30000;
			else if (cnt[3].v + cnt[3].vs >= 2) value += 1200;
			else if (cnt[3].v + cnt[3].vs >= 1 && cnt[3].vm >= 1) value += 1200;
			else if (cnt[3].v + cnt[3].vs >= 1 && cnt[2].v + cnt[2].vs >= 3) value += 1200;
			else if (cnt[2].v + cnt[2].vs >= 2) value += 1000;

			value += (cnt[3].v + cnt[3].vs) * 15;
			if ((cnt[3].v + cnt[3].vs) > 0) {
				if (cnt[2].v + cnt[2].vs >= 1) {
					value += (cnt[2].v + cnt[2].vs) * 15;
				}
			}
			else if (cnt[2].v + cnt[2].vs > 0) {
				if (cnt[2].v + cnt[2].vs >= 2) {
					value += (cnt[2].v + cnt[2].vs) * 15;
				}
			}
			value += (cnt[2].v + cnt[2].vs) * 10;
			value += cnt[3].vm * 2;
			value += cnt[2].vm;
		}
		else if (fs == 2) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v + cnt[5].vs >= 1 || cnt[5].vm >= 1) value += 30000;
			else if (cnt[4].v + cnt[4].vs >= 2) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].v + cnt[3].vs >= 1) value += 5000;
			else if (cnt[4].v + cnt[4].vs >= 1 && cnt[3].v >= 1) value += 5000;
			else if (cnt[4].vm >= 1 && cnt[3].v + cnt[3].vs >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[2].v + cnt[2].vs >= 1) value += 5000;
			else if (cnt[3].v >= 1 && cnt[2].v + cnt[2].vs >= 1) value += 5000;

			value += (cnt[4].v + cnt[4].vs) * 15;
			value += (cnt[3].v + cnt[3].vs) * 15;
			if (cnt[3].v > 0) {
				if ((cnt[3].v + cnt[3].vs) >= 2) {
					value += (cnt[3].v + cnt[3].vs) * 20;
				}
				if (cnt[2].v + cnt[2].vs >= 2) {
					value += (cnt[2].v + cnt[2].vs) * 15;
				}
			}
			value += (cnt[2].v + cnt[2].vs) * 10;
			value += cnt[4].vm * 5;
			value += cnt[3].vm * 2;
			value += cnt[2].vm;
		}
	}
	if (turn == 1) {
		if (fs == 1) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v >= 1 && cnt[4].v >= 1) value += 5000;
			else if (cnt[5].v >= 1 && cnt[4].vm >= 1) value += 5000;
			else if (cnt[5].v >= 1 && cnt[3].v >= 2) value += 5000;
			else if (cnt[5].v >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[5].vm >= 1 && cnt[4].v >= 1) value += 5000;
			else if (cnt[4].v >= 2) value += 5000;
			else if (cnt[4].v >= 1 && cnt[4].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].v >= 2) value += 5000;
			else if (cnt[4].v >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1 && cnt[2].v >= 1) value += 2000;
			else if (cnt[3].v >= 3) value += 1000;

			value += cnt[5].v * 15;
			value += cnt[4].v * 15;
			if (cnt[4].v > 0) {
				if (cnt[3].v >= 2) {
					value += (cnt[3].v) * 20;
				}
				if (cnt[2].v >= 2) {
					value += (cnt[2].v) * 15;
				}
			}
			value += cnt[3].v * 15;
			value += cnt[2].v * 10;
			value += cnt[5].vm * 5;
			value += cnt[4].vm * 5;
			value += cnt[3].vm * 2;
			value += cnt[2].vm * 2;
		}
		else if (fs == 2) {
			if (cnt[6].v >= 1 || cnt[6].vm >= 1) value += 100000;
			else if (cnt[5].v >= 1) value += 5000;
			else if (cnt[5].vm >= 1 && cnt[4].vm >= 1) value += 5000;
			else if (cnt[5].vm >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 5000;
			else if (cnt[4].v >= 1) value += 5000;
			else if (cnt[4].vm >= 2) value += 5000;
			else if (cnt[4].vm >= 1 && cnt[3].v >= 1 && cnt[3].vm >= 1) value += 1000;
			else if (cnt[4].vm >= 1 && cnt[2].v >= 2) value += 1000;
			else if (cnt[3].v >= 2) value += 1000;

			value += cnt[5].vm * 10;
			value += cnt[4].vm * 10;
			value += cnt[3].v * 15;
			if (cnt[3].v > 0) {
				if (cnt[2].v >= 2) {
					value += (cnt[2].v) * 15;
				}
			}
			else if (cnt[2].v > 0) {
				if (cnt[2].v >= 3) {
					value += (cnt[2].v) * 15;
				}
			}
			value += cnt[3].vm * 2;
			value += cnt[2].v * 10;
			value += cnt[2].vm * 2;
			value *= 2;
		}
	}
	status -= value;

	return status;
}

int abp(int alpha, int beta, int dep, Point *usp) {
	/* Return status when dep is max */
	if (dep == 4) {
		return getStatus(1, 1);
	}

	int i, j, k;

	Point sp, spc;
	sp.x = sp.y = 0;
	spc.x = spc.y = 0;

	int cn;
	std::vector<Point> cand;

	/* Find candidates */
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			for (k = 0; k < 8; k++) {
				if (t[i][j] == 0 && t[i + w[0][k]][j + w[1][k]] != 0 && t[i + w[0][k]][j + w[1][k]] != 4) {
					cand.push_back({ j, i, 0 });
					break;
				}
			}
		}
	}

	cn = cand.size();
	/* Set value to candidates */
	for (i = 0; i < cn; i++) {
		if (dep <= 1) t[cand[i].y][cand[i].x] = 1;
		else t[cand[i].y][cand[i].x] = 2;

		if (dep == 0) cand[i].v += getStatus(1, 2);
		if (dep == 1) cand[i].v += getStatus(2, 1);
		if (dep == 2) cand[i].v += getStatus(2, 2);
		if (dep == 3) cand[i].v += getStatus(1, 1);

		t[cand[i].y][cand[i].x] = 0;

		if (dep == 2 || dep == 3 || dep == 6 || dep == 7) cand[i].v *= -1;

		if (cand[i].v > 80000) {
			if (dep == 1) {
				usp->x = cand[i].x;
				usp->y = cand[i].y;
			}
			if (dep == 0) {
				firstStone.x = cand[i].x;
				firstStone.y = cand[i].y;
				secondStone.x = sp.x;
				secondStone.y = sp.y;
			}
			if (dep == 2 || dep == 3 || dep == 6 || dep == 7) cand[i].v *= -1;
			if (secondStone.x == 0 && secondStone.y == 0 && dep == 0) continue;
			return cand[i].v;
		}
		if (cand[i].v < -80000) {
			if (dep == 1) {
				usp->x = cand[i].x;
				usp->y = cand[i].y;
			}
			if (dep == 0) {
				firstStone.x = cand[i].x;
				firstStone.y = cand[i].y;
				secondStone.x = sp.x;
				secondStone.y = sp.y;
			}
			if (dep == 2 || dep == 3 || dep == 6 || dep == 7) cand[i].v *= -1;
			
			if (secondStone.x == 0 && secondStone.y == 0 && dep == 0) continue;
			return cand[i].v;
		}
	}

	/* Sort candidates */
	std::sort(cand.begin(), cand.end(), cmp);

	int value = 0, index = -1;
	/* Max player */
	if (dep == 0 || dep == 1 || dep == 4 || dep == 5) {
		for (i = 0; i < cn; i++) {
			t[cand[i].y][cand[i].x] = 1;
			value = abp(alpha, beta, dep + 1, &spc);
			t[cand[i].y][cand[i].x] = 0;

			if (alpha < value) {
				alpha = value;
				sp.x = spc.x;
				sp.y = spc.y;
				index = i;
			}
			/* Beta cut-off */
			if (alpha >= beta || alpha >= 80000 || clock() - stTime >= limits) {
				break;
			}
		}
		if (dep == 1) {
			if (index >= 0) {
				usp->x = cand[index].x;
				usp->y = cand[index].y;
			}
			else {
				usp->x = cand[0].x;
				usp->y = cand[0].y;
			}
		}
		if (dep == 0) {
			firstStone.x = cand[index].x;
			firstStone.y = cand[index].y;
			secondStone.x = sp.x;
			secondStone.y = sp.y;
		}
		return alpha;
	}
	/* Min player */
	else {
		for (i = 0; i < cn; i++) {
			t[cand[i].y][cand[i].x] = 2;
			value = abp(alpha, beta, dep + 1, &sp);
			t[cand[i].y][cand[i].x] = 0;

			if (beta > value) {
				beta = value;
			}
			/* Alpha cut-off */
			if (alpha >= beta || beta <= -80000 || clock() - stTime >= limits) {
				break;
			}
		}
		return beta;
	}
}