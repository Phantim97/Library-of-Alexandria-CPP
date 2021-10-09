#include "monitor.h"
#include <iostream>
#define MONITORS_ERR_UNINITIALIZED OLE_E_BLANK
#define MONITORS_ERR_INIT_FAILURE ERROR_INTERNAL_ERROR
#define MONITORS_ERR_OUT_OF_BOUNDS ERROR_DS_SIZELIMIT_EXCEEDED

BOOL Monitor::monitorproc(HMONITOR monitor, HDC, LPRECT rect)
{
	MONITORINFOEX info;
	info.cbSize = sizeof(info);
	if (!GetMonitorInfo(monitor, (LPMONITORINFO)&info))
	{
		_bValid = FALSE;
		return FALSE;
	}

	_monitors.push_back(info);
	return TRUE;
}

BOOL CALLBACK Monitor::monitorproc(HMONITOR monitor, HDC dc, LPRECT rect, LPARAM data)
{
	Monitor* self = (Monitor*)data;
	return self->monitorproc(monitor, dc, rect);
}

void Monitor::Sort(std::vector<POINT>& data, SortBy coord)
{
	if (data.size() == 0)
	{ /* initialize */
		data.resize(_monitors.size());
		for (int i = 0; i < data.size(); i++)
		{
			data[i] = { i, i };
		}
	} /* initialize */

	if (data.size() < 2)
	{
		return; // size 0 or 1 is already sorted
	}

	BOOL changed = TRUE;
	while (changed)
	{ /* sort pass */
		changed = FALSE;  // assume no changes, it is sorted
		for (int i = 0; i < data.size() - 1; i++)
		{ /* check elements */
			BOOL doswap = FALSE;
			switch (coord)
			{ /* what */
			case ByX:
				doswap = _monitors[data[i].x].rcMonitor.left > _monitors[data[i + 1].x].rcMonitor.left;
				break;
			case ByY:
				doswap = _monitors[data[i].y].rcMonitor.top > _monitors[data[i + 1].y].rcMonitor.top;
				break;
			} /* what */
			if (doswap)
			{ /* swap it */
				int t = 0;
				switch (coord)
				{
				case ByX:
					t = data[i].x;
					data[i] = data[i + 1];
					data[i + 1].x = t;
					changed = TRUE;
					break;
				case ByY:
					t = data[i].y;
					data[i] = data[i + 1];
					data[i + 1].y = t;
					changed = TRUE;
					break;
				}
			} /* swap it */
		} /* check elements */
	} /* sort pass */
} // CMonitors::Sort


BOOL Monitor::CheckValid()
{
	if (!_bValid)
	{
		SetLastError(MONITORS_ERR_UNINITIALIZED);
		return FALSE;
	}

	if (_monitors.size() == 0)
	{
		SetLastError(MONITORS_ERR_INIT_FAILURE); // should be impossible
		return FALSE;
	}

	return TRUE;
}

Monitor::Monitor()
{
	_bValid = FALSE;
}

BOOL Monitor::Initialize()
{
	_bValid = TRUE; //assume true, any error will set to false;
	_monitors.clear();
	_SortX.clear();
	_SortY.clear();
	_virtualRects.clear();

	if (!EnumDisplayMonitors(NULL, NULL, monitorproc, (LPARAM)this))
	{
		_bValid = FALSE;
		return FALSE;
	}

	if (_bValid)
	{
		Sort(_SortX, ByX);
		Sort(_SortY, ByY);
	}

	//Now fill in the rectangles
	_virtualRects.resize(_monitors.size()); //allocate vector space to match monitor size

	for (int i = 0; i < _monitors.size(); i++)
	{
		_virtualRects[i] = _monitors[i].rcMonitor;
		ScreenToVirtual(_virtualRects[i]);
	}

	return _bValid;
}

BOOL Monitor::ScreenToVirtual(RECT& r)
{
	if (!ScreenToVirtual((POINT&)r.left))
	{
		return FALSE;
	}

	if (!ScreenToVirtual((POINT&)r.right))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Monitor::ScreenToVirtual(POINT& pt)
{
	if (!CheckValid())
	{
		return FALSE;
	}

	if (_monitors.size() == 1)
	{
		return TRUE; //Already in virutal coordinates since there is only one monitor
	}

	POINT v{ 0,0 };

	//Convert X
	BOOL bFound = false;

	for (int i = 0; i < _monitors.size(); i++)
	{
		if (pt.x <= _monitors[_SortX[i].x].rcMonitor.right)
		{
			v.x = -_monitors[_SortX[0].x].rcMonitor.left + pt.x;
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		//set last error to be MONITORS_ERR_OUT_OF_BOUNDS
		SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
		return FALSE; //point is outside virtual screen
	}

	//Convert Y
	bFound = false;
	
	for (int i = 0; i < _monitors.size(); i++)
	{
		if (pt.y <= _monitors[_SortY[i].y].rcMonitor.bottom)
		{
			v.y = -_monitors[_SortY[0].y].rcMonitor.top + pt.y;
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
		return FALSE;
	}

	pt = v;

	return TRUE;
}

BOOL Monitor::VirtualToScreen(RECT& r)
{
	if (!ScreenToVirtual((POINT&)r.left))
	{
		return FALSE;
	}

	if (!ScreenToVirtual((POINT&)r.right))
	{
		return FALSE;
	}

	return TRUE;
}

static bool inline point_in_rect(RECT& r, POINT p)
{
	return (p.x >= r.left && p.x <= r.right && p.y <= r.bottom && p.y >= r.top);
}

int Monitor::VirtualToScreen(POINT& pt)
{
	if (!CheckValid())
	{
		return -1;
	}

	if (_monitors.size() == 1)
	{
		return 0;
	}

	BOOL bFound = FALSE;
	POINT s = { 0, 0 };

	for (int i = 0; i < _virtualRects.size(); i++)
	{
		//if point is in the rectangle
		if (point_in_rect(_virtualRects[i], pt))
		{
			bFound = TRUE;
			return i;
		}
	}

	SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
	return -1;
}

BOOL Monitor::LeftLimitFrom(POINT& pt)
{
	if (!CheckValid())
	{
		return FALSE;
	}

	if (_monitors.size() == 1)
	{
		pt.x = _monitors[0].rcMonitor.left;
		return TRUE;
	}

	BOOL bFound = FALSE;
	int first;

	for (first = _monitors.size() - 1; first >= 0; first--)
	{
		RECT r = _monitors[_SortX[first].x].rcMonitor;

		if (point_in_rect(r, pt))
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		std::cout << "LeftLimitFrom: out of bounds\n";
		SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
		return FALSE;
	}

	POINT result = pt;
	result.x = _monitors[_SortX[first].x].rcMonitor.left;

	for (int i = first - 1; i >= 0; i--)
	{
		POINT test = result;
		test.x--;
		RECT target = _monitors[_SortX[i].x].rcMonitor;

		if (!point_in_rect(target, test))
		{
			break;
		}

		result.x = target.left;
	}

	pt = result;
	return TRUE;
}

BOOL Monitor::RightLimitFrom(POINT& pt)
{
	if (!CheckValid())
	{
		return FALSE;
	}

	if (_monitors.size() == 1)
	{
		pt.x = _monitors[0].rcMonitor.right - 1;
		return TRUE;
	}

	int first;
	BOOL bFound = FALSE;
	for (first = 0; first < _monitors.size(); first++)
	{
		RECT r = _monitors[_SortX[first].x].rcMonitor;
		if (point_in_rect(r, pt))
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		std::cout << "RightLimitFrom: out of bounds\n";
		SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
		return FALSE;
	}

	POINT result = pt;
	result.x = _monitors[_SortX[first].x].rcMonitor.right;

	for (int i = first + 1; i < _monitors.size(); i++)
	{
		POINT test = result;
		test.x++; //See if it is in the next monitor
		RECT target = _monitors[_SortX[i].x].rcMonitor;
		if (!point_in_rect(target, test))
		{
			break;
		}
		result.x = target.right;
	}

	pt = result;
	return TRUE;
}

BOOL Monitor::TopLimitFrom(POINT& pt)
{
	if (!CheckValid())
	{
		return FALSE;
	}

	if (_monitors.size() == 1)
	{
		pt.y = _monitors[0].rcMonitor.top;
		return TRUE;
	}

	BOOL bFound = FALSE;

	int first;
	for (first = _monitors.size() - 1; first >= 0; first--)
	{
		RECT r = _monitors[_SortY[first].y].rcMonitor;
		if (point_in_rect(r, pt))
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		std::cout << "TopLimitFrom: Out of bounds\n";
		SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
		return FALSE;
	}

	POINT result = pt;
	result.y = _monitors[_SortY[first].y].rcMonitor.top;

	for (int i = first - 1; i >= 0; i--)
	{
		POINT test = result;
		test.y--;
		RECT target = _monitors[_SortY[i].y].rcMonitor;
		
		if (!point_in_rect(target, test))
		{
			break;
		}

		result.y = target.top;
	}

	pt = result;
	return TRUE;
}

BOOL Monitor::BottomLimitFrom(POINT& pt)
{
	if (!CheckValid())
	{
		return FALSE;
	}

	if (_monitors.size() == 1)
	{
		pt.y = _monitors[0].rcMonitor.bottom = 1;
		return TRUE;
	}

	BOOL bFound = FALSE;
	int first;
	for (first = 0; first < _monitors.size(); first++)
	{
		RECT r = _monitors[_SortY[first].y].rcMonitor;
		if (point_in_rect(r, pt))
		{
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
	{
		std::cout << "BottomLimitFrom: out of bounds\n";
		SetLastError(MONITORS_ERR_OUT_OF_BOUNDS);
		return FALSE;
	}

	POINT result = pt;
	result.y = _monitors[_SortY[first].y].rcMonitor.bottom;

}

int Monitor::getWidthPx(int monitor_id)
{
	return _monitors[monitor_id].rcMonitor.right - _monitors[monitor_id].rcMonitor.left;
}

int Monitor::getHeightPx(int monitor_id)
{
	return _monitors[monitor_id].rcMonitor.bottom - _monitors[monitor_id].rcMonitor.top;
}
