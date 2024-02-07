#pragma warning(disable:4996)

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

/* �� ũ�� */
#define yMax 80 
#define xMax 40
#define map_Max xMax * yMax

/* 2D ���� 1D�� ��ȯ �� ������ ���� */
char mapData[map_Max];

/* ĳ���� ��ġ �� ũ�� ���� ����ü */
typedef struct character {
	int x, y;
	int sizeX, sizeY;
	char sprite[6];
}plane;

/* �ܼ� â ���� */
void Setting_Console() {
	SetConsoleTitle(TEXT("Flight Game")); /* �ܼ�â �̸� */
	system("mode con:cols=80 lines=40"); /* �ܼ�â ũ�� */

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}	

void textcolor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}

/* Ŀ���� ������(2D) */
//void gotoxy(int x, int y) {
//	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD Cur;
//	Cur.X = x;
//	Cur.Y = y;
//	SetConsoleCursorPosition(consoleHandle, Cur);
//}

/* �� �ʱ�ȭ */
void reset_map(char str[], char s, int max_value) {
	for (int i = 0; i < max_value; i++) {
		str[i] = s;
	}
}

/* ĳ���� �迭 ��ġ ����*/
void edit_map(int x, int y, char c) {
	if (x > 0 && y > 0 && x - 1 < xMax - 1 && y - 1 < yMax - 1) {
		mapData[(y - 1) * xMax + x - 1] = c;
	}
}

/* ĳ���� �׸��� */
void draw_map(int x, int y, int sizeX, int sizeY, char spr[]) {
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			edit_map(x + j, y + i, spr[i * sizeX + j]);
		}
	}
}

/* ĳ���� ��� �� ������ */
void move_character(plane* air) {
	/* GetAsyncKeyState : Ű �Է� �Լ� */
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (air->y > 1) air->y--;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (air->y < yMax - 5) air->y++;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (air->x > 1) air->x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (air->x < xMax - 3) air->x += 2;
	}
}

int main(void) {
	Setting_Console();

	plane airplane;
	airplane.x = xMax / 2 + 1;
	airplane.y = yMax / 3 * 2 + 1;
	airplane.sizeX = 3;
	airplane.sizeY = 2;

	strncpy(airplane.sprite, "_^_^^^", sizeof(airplane.sprite));

	while (1) {
		textcolor();

		reset_map(mapData, ' ', map_Max);
		move_character(&airplane);
		draw_map(airplane.x, airplane.y, airplane.sizeX, airplane.sizeY, airplane.sprite);

		printf("%s", mapData);
		Sleep(50);
	}

	return 0;
}