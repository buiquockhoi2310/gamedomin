#include "main.h"
#include "Console.h"
#include "function.h"
using namespace std;
short STrang, SViTriDangChon, STongMuc;
int main()
{
	resizeConsole(ConsoleWidth, ConsoleHeight);

	SetConsoleTitle(TEXT("Game Do Min"));

	veTieuDeGame();
	Cursor(false);
	//khoiTao(9, 9, 10);
	//veTrangThaiChoiGame(1);
	veMenuChinh(0);
	//veMenuCapDo(0);
	STrang = 1;
	xuLySuKien();
	//cout << endl << endl;
	//system("pause");
	return 0;
}