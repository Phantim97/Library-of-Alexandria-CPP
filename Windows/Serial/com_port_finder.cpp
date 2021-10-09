#include <string>
#include <vector>

#include <windows.h>
#include <tchar.h>
#include <SetupAPI.h>
#include <initguid.h>
#include <devguid.h>

#pragma comment(lib, "Setupapi.lib")

struct PortInfo
{
	std::string _port;
	std::string _friendly_name;
	std::string _hardware_id;
	int _addr;
};

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

std::vector<PortInfo> gather_ports()
{
	//TODO: Just subtistute all of these to one constant (property_max_length)
	
	static constexpr DWORD port_name_max_length = 256;
	static constexpr DWORD friendly_name_max_length = 256;
	static constexpr DWORD hardware_id_max_length = 256;
	static constexpr DWORD addr_max_length = 256;

	std::vector<PortInfo> port_list;
	
	HDEVINFO dev_info_set = SetupDiGetClassDevs(
		(const GUID*)&GUID_DEVCLASS_PORTS,
		NULL,
		NULL,
		DIGCF_PRESENT);

	unsigned int dev_info_set_index = 0;
	SP_DEVINFO_DATA dev_info_data;

	dev_info_data.cbSize = sizeof(SP_DEVINFO_DATA);

	//Enumerate the devices
	while (SetupDiEnumDeviceInfo(dev_info_set, dev_info_set_index, &dev_info_data))
	{
		dev_info_set_index++;

		//Open the Serial Port Device Class Registry

		HKEY hkey = SetupDiOpenDevRegKey(
			dev_info_set,
			&dev_info_data,
			DICS_FLAG_GLOBAL,
			NULL,
			DIREG_DEV,
			KEY_READ);

		TCHAR port_name[port_name_max_length];
		DWORD port_name_length = port_name_max_length;

		//Query COM Ports in use
		LONG ret = RegQueryValueEx(
			hkey,
			_T("PortName"),
			NULL,
			NULL,
			(LPBYTE)port_name,
			&port_name_length
		);

		RegCloseKey(hkey);

		if (ret != EXIT_SUCCESS)
		{
			continue;
		}

		if (port_name_length > 0 && port_name_length <= port_name_max_length)
		{
			port_name[port_name_length - 1] = '\0';
		}
		else
		{
			port_name[0] = '\0';
		}

		//Ignore Parallel Ports
		if (_tcsstr(port_name, _T("LPT")) != NULL)
		{
			continue;
		}

		//Get Friendly Name
		TCHAR friendly_name[friendly_name_max_length];
		DWORD friendly_name_length = 0;

		BOOL got_friendly_name = SetupDiGetDeviceRegistryProperty(
			dev_info_set,
			&dev_info_data,
			SPDRP_FRIENDLYNAME,
			NULL,
			(PBYTE)friendly_name,
			friendly_name_max_length,
			&friendly_name_length);

		if (got_friendly_name == TRUE && friendly_name_length > 0)
		{
			friendly_name[friendly_name_length - 1] = '\0';
		}
		else
		{
			friendly_name[0] = '\0';
		}

		//Get Hardware ID
		TCHAR hardware_id[hardware_id_max_length];
		DWORD hardware_id_length = 0;

		BOOL got_hardware_id = SetupDiGetDeviceRegistryProperty(
			dev_info_set,
			&dev_info_data,
			SPDRP_HARDWAREID,
			NULL,
			(PBYTE)hardware_id,
			hardware_id_max_length,
			&hardware_id_length);

		if (got_hardware_id == TRUE && hardware_id_length > 0)
		{
			hardware_id[hardware_id_length - 1] = '\0';
		}
		else
		{
			hardware_id[0] = '\0';
		}

		TCHAR address[256];
		DWORD addr_length = 0;

		SetupDiGetDeviceRegistryProperty(
			dev_info_set,
			&dev_info_data,
			SPDRP_HARDWAREID,
			NULL,
			(PBYTE)address,
			addr_max_length,
			&addr_length);

#ifdef UNICODE
		std::string portName = utf8_encode(port_name);
		std::string friendlyName = utf8_encode(friendly_name);
		std::string hardwareID = utf8_encode(hardware_id);
		std::string devAddress = utf8_encode(address);
#else
		std::string portName = port_name;
		std::string friendlyName = friendly_name;
		std::string hardwareId = hardware_id;
		std::string devAddress = address;
#endif

		PortInfo port;

		port._port = portName;
		port._friendly_name = friendlyName;
		port._hardware_id = hardwareId;

		port_list.push_back(port);
	}

	SetupDiDestroyDeviceInfoList(dev_info_set);

	return port_list;
}

std::string FindDevicePort(const char* vid_pid)
{
	std::vector<PortInfo> ports = gather_ports();

	std::string DesiredPort;
	
	for (size_t i = 0; i < ports.size(); i++)
	{
		if (strstr(ports[i]._hardware_id.c_str(), vid_pid))
		{
			if (ports[i]._port.size() > 4) // for COM Ports larger than single digit number
			{
				DesiredPort = "\\\\.\\" + ports[i]._port;
				break;
			}
			else
			{
				DesiredPort = ports[i]._port;
				break;
			}
		}
	}

	return DesiredPort;
}
