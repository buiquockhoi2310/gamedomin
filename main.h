#pragma once
#include <iostream>
#include <Windows.h>
#define ConsoleWidth 80
#define ConsoleHeight 34

#define ClickTrai 0x5A
#define ClickPhai 0x58
struct CauTrucBang
{
	short SDong = 0;
	short SCot = 0;
	short SSoBom = 0;
	short SSoCo = 0;
	short SSoODaMo = 0;
};

struct CauTrucO
{
	bool BCoBom = false;
	bool BCamCo = false;
	bool BDaMo = false;
	short SBomLanCan = 0;
};
extern short STrang, SViTriDangChon, STongMuc;
