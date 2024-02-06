#pragma warning(disable:4996)

#include <windows.h>
#include <conio.h>
#include <stdio.h>

/* �ܼ� â ���� */
void Setting_Console() {
	system("Flight Game"); /* �ܼ�â �̸� */
	system("mode con:cols=60 lines=60"); /* �ܼ�â ũ�� */

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}	

void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(consoleHandle, Cur);
}

int main() {
	Setting_Console();
	int x = 0, y = 0; /* ���� ��ǥ */
	int yMax = 60, xMax = 60; /* �� ũ�� */

	while (1) {
		gotoxy(x, y);
		printf("*");

		/* GetAsyncKeyState : Ű �Է� �Լ� */
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (y > 0) y--;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (y < yMax - 1) y++;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (x > 0) x -= 2;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (x < xMax - 2) x += 2;
		}

		Sleep(50);
	}
	return 0;
}