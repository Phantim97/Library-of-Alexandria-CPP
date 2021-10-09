#include <string>
#include <windows.h>
#include <wincodec.h>
#include <commdlg.h>
#include <d2d1.h>
#include <sstream> 
#include <future>
#include <cassert>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <vector>
#include "monitor.h"

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#pragma comment(lib, "user32.lib")

static void DumpDevice(const DISPLAY_DEVICE& dd, size_t nSpaceCount)
{
    printf("%*sDevice Name: %s\n", nSpaceCount, "", dd.DeviceName);
    printf("%*sDevice String: %s\n", nSpaceCount, "", dd.DeviceString);
    printf("%*sState Flags: %x\n", nSpaceCount, "", dd.StateFlags);
    printf("%*sDeviceID: %s\n", nSpaceCount, "", dd.DeviceID);
    printf("%*sDeviceKey: ...%s\n\n", nSpaceCount, "", dd.DeviceKey + 42);
}

static void split_string(std::string& name, std::string& guid)
{
	std::string base = name;
	size_t pos = 0;
	std::string delimiter = "\\";

	std::string token;
	if ((pos = base.find(delimiter)) != std::string::npos)
	{
		name = base.substr(0, pos);
		base.erase(0, pos + delimiter.length());
	}

	guid = base;
}

struct ScreenDimsPhys
{
	int height;
	int width;
};

static BOOL GetMonitorSizeFromEDID(std::string MonitorKey/*, DWORD& Width, DWORD& Height*/)
{
	MonitorKey.erase(0, 8); // Remove "MONITOR\{"
	MonitorKey.erase(MonitorKey.size() - 6, MonitorKey.size()); //Remove } + monitor index
	MonitorKey.erase(std::remove(MonitorKey.begin(), MonitorKey.end(), '{'), MonitorKey.end());

	std::string monitor_guid;
	split_string(MonitorKey, monitor_guid);

	DISPLAY_DEVICE ddMon;
	ZeroMemory(&ddMon, sizeof(ddMon));
	ddMon.cb = sizeof(ddMon);
	std::string path = "System\\CurrentControlSet\\Enum\\DISPLAY\\";
	path.append(MonitorKey);
	//path.append("\\Device Parameters\\EDID");
	//read edid
	bool result = false;
	DWORD Width = 0;
	DWORD Height = 0;

	HKEY hKey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		//Iterate through subkeys and find the matching guid
		TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
		DWORD    cbName;                   // size of name string 
		TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
		DWORD    cchClassName = MAX_PATH;  // size of class string 
		DWORD    cSubKeys = 0;               // number of subkeys 
		DWORD    cbMaxSubKey;              // longest subkey size 
		DWORD    cchMaxClass;              // longest class string 
		DWORD    cValues;              // number of values for key 
		DWORD    cchMaxValue;          // longest value name 
		DWORD    cbMaxValueData;       // longest value data 
		DWORD    cbSecurityDescriptor; // size of security descriptor 
		FILETIME ftLastWriteTime;      // last write time 

		DWORD i, retCode;

		// Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 

		// Enumerate the subkeys, until RegEnumKeyEx fails.

		if (cSubKeys)
		{
			//printf("\nNumber of subkeys: %d\n", cSubKeys);

			for (i = 0; i < cSubKeys; i++)
			{
				cbName = MAX_KEY_LENGTH;
				retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);

				if (retCode == ERROR_SUCCESS)
				{
					_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
				}

				HKEY hKey2;
				if (RegOpenKeyEx(hKey, achKey, 0, KEY_READ, &hKey2) == ERROR_SUCCESS) //propagate down to subkey
				{
					BYTE data[256];
					DWORD size = 256;
					memset(data, 0, size);

					if (RegQueryValueEx(hKey2, "ClassGUID", NULL, NULL, data, &size) == ERROR_SUCCESS) //find the matching guid
					{
						char guid[256];
						memset(guid, 0, size);
						memcpy(guid, data, 256);

						if (strstr(guid, monitor_guid.c_str()) != 0) // correct guid found
						{
							//propagate down to EDID
							path.append("\\");
							path.append(achKey);
							path.append("\\Device Parameters");

							HKEY hKey3;
							if (RegOpenKeyEx(hKey2, "Device Parameters", 0, KEY_READ, &hKey3) == ERROR_SUCCESS)
							{
								BYTE EDID[256];
								DWORD size2 = 256;
								memset(EDID, 0, size2);

								if (RegQueryValueEx(hKey3, "EDID", NULL, NULL, EDID, &size2) == ERROR_SUCCESS)
								{
									DWORD p = 8;

									//Get Model Name (optional)
									TCHAR model[9];
									char byte1 = EDID[p];
									char byte2 = EDID[p + 1];
									model[0] = ((byte1 & 0x7C) >> 2) + 64;
									model[1] = ((byte1 & 3) << 3) + ((byte2 & 0xE0) >> 5) + 64;
									model[2] = (byte2 & 0x1F) + 64;
									sprintf_s(model + 3, 5, _T("%X%X%X%X"), (EDID[p + 3] & 0xf0) >> 4, EDID[p + 3] & 0xf, (EDID[p + 2] & 0xf0) >> 4, EDID[p + 2] & 0x0f);
									
									//Get Height and width of monitor in cm
									Width = EDID[21];
									Height = EDID[22];
									std::cout << "Width: " << Width << " || " << "Height: " << Height << '\n';

									result = true;
								}
								else
								{
									std::cout << "Failed to query EDID: " << GetLastError() << "\n";
								}
							}
							else
							{
								std::cout << "Unable to open final hkey\n";
							}

							RegCloseKey(hKey3);
						}
					}
				}
				else
				{
					std::cout << "Failed to open subkey\n";
				}
				RegCloseKey(hKey2);
				if (result)
				{
					break;
				}
			}
		}
	}
	else
	{
		std::cout << "Failed to open key\n";
	}

	RegCloseKey(hKey);

	return result;
}

int main()
{
	std::vector<DISPLAY_DEVICE> monitors;
	DISPLAY_DEVICE dd;

	dd.cb = sizeof(DISPLAY_DEVICE);

	DWORD deviceNum = 0;
	while (EnumDisplayDevices(NULL, deviceNum, &dd, 0))
	{
		DumpDevice(dd, 0);
		DISPLAY_DEVICE newdd = { 0 };
		newdd.cb = sizeof(DISPLAY_DEVICE);
		DWORD monitorNum = 0;

		while (EnumDisplayDevices(dd.DeviceName, monitorNum, &newdd, 0))
		{
			DumpDevice(newdd, 4);
			monitors.push_back(newdd);
			monitorNum++;
		}

		puts("");
		deviceNum++;
	}

	for (std::vector<DISPLAY_DEVICE>::iterator it = monitors.begin(); it != monitors.end(); it++)
	{
		GetMonitorSizeFromEDID(it->DeviceID);
	}

	POINT pt;
	pt.x = 1280;
	pt.y = 200;

	Monitor mon;
	mon.Initialize();
	std::cout << "Monitor: " << mon.VirtualToScreen(pt) << '\n';

	for (int i = 0; i < 3; i++)
	{
		std::cout << "Width #" << i << ": " << mon.getWidthPx(i) << '\n';
		std::cout << "Height #" << i << ": " << mon.getHeightPx(i) << '\n';
	}

	system("pause");
    return 0;
}
