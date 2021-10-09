#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class Monitor
{
private:
	BOOL _bValid;
	std::vector<MONITORINFOEX> _monitors;

	std::vector<POINT> _SortX;
	std::vector<POINT> _SortY;
	
	std::vector<RECT> _virtualRects;

	BOOL monitorproc(HMONITOR monitor, HDC, LPRECT rect);
	static BOOL CALLBACK monitorproc(HMONITOR monitor, HDC dc, LPRECT rect, LPARAM data);
	typedef enum { ByX, ByY } SortBy;
	void Sort(std::vector<POINT>& data, SortBy what);
	BOOL CheckValid();

public:
	Monitor();
	BOOL Initialize();

	BOOL ScreenToVirtual(RECT& r);
	BOOL ScreenToVirtual(POINT& pt);

	BOOL VirtualToScreen(RECT& r);
	int VirtualToScreen(POINT& pt);

	BOOL LeftLimitFrom(POINT& pt);
	BOOL RightLimitFrom(POINT& pt);
	BOOL TopLimitFrom(POINT& pt);
	BOOL BottomLimitFrom(POINT& pt);

	int getWidthPx(int monitor_id);
	int getHeightPx(int monitor_id);
};
