#include "main.h"
#include "function.h"
#include "Console.h"
using namespace std;
CauTrucBang CTBang;
CauTrucO** CTO;
COORD CViTriConTro;
bool BSuDungPhim = false;
short SToaDoX;
short SToaDoY;
bool BTrangThaiChoiGame = false;
void taoMang2ChieuDong()
{
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
};
void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
};
void luuToaDoBang()
{
	SToaDoX = ((ConsoleWidth / 2) - CTBang.SDong);
	SToaDoY = (((ConsoleHeight - 6) - CTBang.SCot) / 2) + 7;
}
void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	taoBomNgauNhien();
	luuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	veBang();
	veTrangThaiChoiGame(1, 0, 0);
}
short toaDoX(short SX)
{
	return ((SX * 2) + SToaDoX);
}
short toaDoY(short SY)
{
	return (SY + SToaDoY);
}
void veO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, "  ");
		break;
	case 1:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, "1 ");
		break;
	case 2:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, "2 ");
		break;
	case 3:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, "3 ");
		break;
	case 4:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, "4 ");
		break;
	case 5:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, "5 ");
		break;
	case 6:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, "6 ");
		break;
	case 7:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, "7 ");
		break;
	case 8:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, "8 ");
		break;
	case 9:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, "B ");
		break;
	case 10:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, "  ");
		break;
	case 11:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, "  ");
		break;
	case 12:
		setColorBGTextXY(toaDoX(SX) + 1, toaDoY(SY), 0, 13, " ");
		break;
	case 13:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, "P ");
		break;
	case 14:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, "Px");
		break;
	case 15:
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, "B ");
		break;
	}
}
void veBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
				veO(j, i, 13);
			else if (CTO[i][j].SBomLanCan)
				veO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo)
				veO(j, i, 0);
			else if ((i + j) % 2)
				veO(j, i, 11);
			else
				veO(j, i, 10);
			if (BSuDungPhim)
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}
void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ;
	srand(time(NULL));
	while (SSoBom)
	{
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;
	}
}
void clickPhai(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
	}
	veBang();
}
short demBomLanCan(short SX, short SY)
{
	short SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY + 1; ++j)
		{
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;
			if (CTO[i][j].BCoBom)
				++SDem;
		}
	}
	return SDem;
}
void moO(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom)
			thua();
		else
		{
			CTBang.SSoODaMo++;
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan)
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else
			{
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;
						moO(i, j);
					}
				}
			}
		}
	}
}
bool thongKeCo()
{
	if ((CTBang.SSoODaMo + CTBang.SSoBom) == (CTBang.SDong + CTBang.SCot))
		return true;
	return false;
}
void clickTrai(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		moO(SX, SY);
		if (BTrangThaiChoiGame)
		{
			veBang();

			if (thongKeCo())
				thang();
		}
	}
}
void thang()
{
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2, 2, 0);
}
void thua()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
			{
				if (CTO[i][j].BCoBom)
					veO(j, i, 15);
				else
					veO(j, i, 14);
			}
			else
			{
				if (CTO[i][j].BCoBom)
					veO(j, i, 9);
			}
		}
	}

	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0);
}
void xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP:
			//cout << "Mui ten len"<<endl;
			switch (STrang)
			{
			case 1:
				if (STongMuc == 4)
				{
					if (SViTriDangChon == 0)
						SViTriDangChon = STongMuc - 1;
					else
						SViTriDangChon -= 1;
					veMenuChinh(SViTriDangChon);
				}
				break;
			case 2:
				if (STongMuc == 4)
				{
					if (SViTriDangChon == 0)
						SViTriDangChon = STongMuc - 1;
					else
						SViTriDangChon -= 1;
					veMenuCapDo(SViTriDangChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(3, 3, (SViTriDangChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(2, 2, (SViTriDangChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_DOWN:
			//cout << "Mui ten xuong"<<endl;
			switch (STrang)
			{
			case 1:
				if (STongMuc == 4)
				{
					if (SViTriDangChon == STongMuc - 1)
						SViTriDangChon = 0;
					else
						SViTriDangChon += 1;
					veMenuChinh(SViTriDangChon);
				}
				break;
			case 2:
				if (STongMuc == 4)
				{
					if (SViTriDangChon == STongMuc - 1)
						SViTriDangChon = 0;
					else
						SViTriDangChon += 1;
					veMenuCapDo(SViTriDangChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(3, 3, (SViTriDangChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(2, 2, (SViTriDangChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_LEFT:
			//cout << "Mui ten trai"<<endl;
			if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				veBang();
			}
			break;
		case VK_RIGHT:
			//cout << "Mui ten phai"<<endl;
			if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				veBang();
			}
			break;
		case VK_RETURN:
			//cout << "Enter" << endl;
			switch (STrang)
			{
			case 1:
				if (SViTriDangChon == 0)
				{
					STrang = 2;
					deleteRow(4, 5);
					veMenuCapDo(0);
				}
				else if (SViTriDangChon == 1)
				{

				}
				else if (SViTriDangChon == 2)
				{

				}
				else
				{
					exit(0);
				}
				break;
			case 2:
				if (SViTriDangChon == 0)
				{
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(9, 9, 10);


				}
				else if (SViTriDangChon == 1)
				{
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(16, 16, 40);


				}
				else if (SViTriDangChon == 2)
				{
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(24, 24, 99);


				}
				else
				{
					STrang = 1;
					deleteRow(4, 10);
					veMenuChinh(0);
				}
				break;
			case 4:
				if (SViTriDangChon == 1)
				{
					STrang = 1;
					deleteRow(3, ConsoleHeight - 7);
					veMenuChinh(0);
				}
				else
				{
					STrang = 3;
					deleteRow(3, ConsoleHeight - 7);
					khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
				}
				break;
			case 5:
				break;
			case 6:
				if (SViTriDangChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHeight - 3);
					veMenuChinh(0);
				}
				else
				{
					//Luu Game
				}
				break;
			}
			break;
		case VK_ESCAPE:
			switch (STrang)
			{
			case 1:
				exit(0);
				break;
			case 2:
				STrang = 1;
				deleteRow(4, 10);
				veMenuChinh(0);
				break;
			case 3:
				STrang = 6;
				veTrangThaiChoiGame(1, 1, 0);
				break;
			case 4:
				break;
			case 5:
				STrang = 2;
				deleteRow(3, ConsoleHeight - 3);
				veMenuCapDo(0);
				break;
			}
			break;
		case ClickTrai://Mo O(Z)
			//cout << "Z"<<endl;
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai://Cam Co(X)
			//cout << "X"<<endl;
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}
void xuLySuKien()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0;
		DWORD DWNumberOfEventsRead = 0;
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);
		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents];
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)
				{
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
			}
		}
	}
}
void veTieuDeGame()
{
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
	setColorBGTextXY((ConsoleWidth / 2) - 10, 1, 5, 0, "Game Do Min - Bui Quoc Khoi\n");
	setColor(7);
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}
void veTrangThaiChoiGame(short STrangThai, short SCheDo, short SIndex)
{
	SViTriDangChon = SIndex;
	STongMuc = 2;
	setColorBGTextXY(1, 3, 15, 0, "Ban Do: %d * %d", CTBang.SDong, CTBang.SCot);
	setColorBGTextXY(1, 4, 15, 0, "So Bom: %d", CTBang.SSoBom);

	const char* STRCheDo;
	if (SCheDo == 1)
	{
		STRCheDo = "  LUU LAI ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRCheDo) / 2), 3, 15, (SIndex == 0) ? 2 : 0, STRCheDo);
	}
	if (SCheDo == 2)
	{
		STRCheDo = "  LUU TEN ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRCheDo) / 2), 3, 15, (SIndex == 0) ? 2 : 0, STRCheDo);
	}
	if (SCheDo == 3)
	{
		STRCheDo = "  CHOI LAI ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRCheDo) / 2), 3, 15, (SIndex == 0) ? 2 : 0, STRCheDo);
	}
	if (SCheDo >= 1)
	{
		STRCheDo = "  THOAT ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRCheDo) / 2), 4, 15, (SIndex == 1) ? 2 : 0, STRCheDo);
	}
	if (STrangThai == 1)
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, "Trang Thai: %s", "Dang Choi");
	if (STrangThai == 2)
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, "Trang Thai: %s", "Thang");
	if (STrangThai == 3)
		setColorBGTextXY(ConsoleWidth - 22, 4, 12, 0, "Trang Thai: %s", "Thua");
	cout << endl;
	setColor(7);
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}
void veMenuChinh(short SIndex)
{
	SViTriDangChon = SIndex;
	STongMuc = 4;


	const char* STRNewGame = "  GAME MOI  ";

	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2) + 1, 7, 15, (SIndex == 0) ? 2 : 0, STRNewGame);
	STRNewGame = "  BANG DIEM  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 8, 15, (SIndex == 1) ? 2 : 0, STRNewGame);
	STRNewGame = "  HUONG DAN  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 9, 15, (SIndex == 2) ? 2 : 0, STRNewGame);
	STRNewGame = "  THOAT  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 10, 15, (SIndex == 3) ? 2 : 0, STRNewGame);
}
void veMenuCapDo(short SIndex)
{
	SViTriDangChon = SIndex;
	STongMuc = 4;


	const char* STRNewGame = "  CHON CAP DO  ";

	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 4, 1, 0, STRNewGame);
	STRNewGame = "  DE (9 * 9 VA 10 BOM))  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 7, 15, (SIndex == 0) ? 2 : 0, STRNewGame);
	STRNewGame = "  TRUNG BINH (16 * 16 VA 40 BOM)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 8, 15, (SIndex == 1) ? 2 : 0, STRNewGame);
	STRNewGame = "  KHO (24 * 24 VA 99 BOM)  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 9, 15, (SIndex == 2) ? 2 : 0, STRNewGame);
	STRNewGame = "  TRO VE  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRNewGame) / 2), 10, 15, (SIndex == 3) ? 2 : 0, STRNewGame);
}