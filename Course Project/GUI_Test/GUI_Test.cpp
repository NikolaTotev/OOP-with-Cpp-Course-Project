#include <windows.h>
#include <iostream>
#include "ConsoleOps.h"
HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);
COLORREF COLOR_4 = RGB(255, 0, 0);

void DrawLine(HWND Wnd, int x1, int y1, int x2, int y2, int Pen, HDC DrawHDC)
{
	int a, b = 0;
	HPEN hOPen;
	// penstyle, width, color
	HPEN hNPen = CreatePen(PS_SOLID, 2, Pen);
	if (!DrawHDC)
	{	
		DrawHDC = GetDC(Wnd);
		b = 1;
	} 
	hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
	// starting point of line
	MoveToEx(DrawHDC, x1, y1, NULL);
	// ending point of line
	a = LineTo(DrawHDC, x2, y2);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	if (b)
	{
	ReleaseDC(Wnd, DrawHDC);
	}
	
}

void drawButton(COORD topLeft, int width, int height)
{
	//go_to(topLeft);
	//LineTo(mydc, topLeft.X + width , topLeft.Y);
	DrawLine(myconsole, topLeft.X, topLeft.Y, topLeft.X + width, topLeft.Y, COLOR_4, mydc);

}


int main()
{
	
//	ShowWindow(myconsole, SW_SHOWMAXIMIZED);

	int posX = 40;
	int posY = 40;

	COORD top;
	top.X = 50;
	top.Y = 50;

	COORD size;
	drawButton(top, 30, 20);
	set_cursor_visibility(false);
		SetPixel(mydc, posX, posY, COLOR_4);
	SetPixel(mydc, posX+95, posY+20, COLOR_4);

	SetPixel(mydc, posX+23, posY+100, COLOR_4);

	SetPixel(mydc, posX+20, posY+200, COLOR_4);

	//clear_console();
	int a;
	std::cin >> a;

	return 0;
}

