#include <WinSock2.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <vector>

#pragma comment(lib, "bthprops.lib")
#pragma comment(lib, "Ws2_32.lib")

//Gathers all devices and 

typedef ULONGLONG bt_addr, * pbt_addr, BT_ADDR, * PBT_ADDR;

std::vector<BLUETOOTH_DEVICE_INFO> scanDevices()
{
	std::vector<BLUETOOTH_DEVICE_INFO> res;

	BLUETOOTH_DEVICE_SEARCH_PARAMS bdsp;
	BLUETOOTH_DEVICE_INFO bdi;
	HBLUETOOTH_DEVICE_FIND hbf;

	ZeroMemory(&bdsp, sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS));

	// set options for how we want to load our list of BT devices
	bdsp.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
	bdsp.fReturnAuthenticated = TRUE;
	bdsp.fReturnRemembered = TRUE;
	bdsp.fReturnUnknown = TRUE;
	bdsp.fReturnConnected = TRUE;
	bdsp.fIssueInquiry = TRUE;
	bdsp.cTimeoutMultiplier = 4;
	bdsp.hRadio = NULL;

	bdi.dwSize = sizeof(bdi);

	// enumerate our bluetooth devices
	hbf = BluetoothFindFirstDevice(&bdsp, &bdi);
	if (hbf)
	{
		do
		{
			res.push_back(bdi);
		} while (BluetoothFindNextDevice(hbf, &bdi));

		// close our device enumerator
		BluetoothFindDeviceClose(hbf);
	}

	return res;
}

BOOL CALLBACK bluetoothAuthCallback(LPVOID param, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS params)
{
	BLUETOOTH_DEVICE_INFO aw = params->deviceInfo;
	HANDLE lRadio = NULL;

	BLUETOOTH_AUTHENTICATE_RESPONSE bar2Send;
	::ZeroMemory(&bar2Send, sizeof(BLUETOOTH_AUTHENTICATE_RESPONSE));
	bar2Send.bthAddressRemote = params->deviceInfo.Address;
	bar2Send.authMethod = params->authenticationMethod;

	DWORD result = BluetoothSendAuthenticationResponseEx(lRadio, &bar2Send);
	return TRUE;
}

void pairDevice(BLUETOOTH_DEVICE_INFO device)
{
	std::wstring ws = device.szName;
	std::cout << "Pairing device " << std::string(ws.begin(), ws.end()) << std::endl;

	// register callback
	std::cout << "Registering callback" << std::endl;
	HBLUETOOTH_AUTHENTICATION_REGISTRATION hCallbackHandle = 0;
	
	DWORD result = BluetoothRegisterForAuthenticationEx(&device, &hCallbackHandle, (PFN_AUTHENTICATION_CALLBACK_EX)& bluetoothAuthCallback, NULL);
	if (result != ERROR_SUCCESS)
	{
		std::cout << "Failed to register callback" << std::endl;
		return;
	}

	// authentication options
	result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotRequired);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionRequired);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotRequiredBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionRequiredBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotRequiredGeneralBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionRequiredGeneralBonding);
	//DWORD result = BluetoothAuthenticateDeviceEx(NULL, NULL, &device, NULL, MITMProtectionNotDefined);
	switch (result)
	{
	case ERROR_SUCCESS:
		std::cout << "pair device success" << std::endl;
		break;

	case ERROR_CANCELLED:
		std::cout << "pair device failed, user cancelled" << std::endl;
		break;

	case ERROR_INVALID_PARAMETER:
		std::cout << "pair device failed, invalid parameter" << std::endl;
		break;
		 
	case ERROR_NO_MORE_ITEMS:
		std::cout << "pair device failed, device appears paired already" << std::endl;
		break;

	default:
		std::cout << "pair device failed, unknown error, code " << (unsigned int)result << std::endl;
		break;
	}
}

int getTrafficFromDevice(BLUETOOTH_DEVICE_INFO device)
{
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("Unable to load Winsock! Error code is %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("WSAStartup() is OK, Winsock lib loaded!\n");
	
	SOCKADDR_BTH addr = { 0 };
	SOCKET s, server;
	int status;

	// allocate a socket
	s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	if (s == INVALID_SOCKET)
	{
		printf("Socket creation failed, error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	else
		printf("socket() looks fine!\n");


	// set the connection parameters (who to connect to)
	addr.addressFamily = AF_BTH;
	addr.btAddr = device.Address.ullLong;
	addr.serviceClassId = SerialPortServiceClass_UUID;

	// connect to server
	status = connect(s, (SOCKADDR*)& addr, sizeof(addr));
	if (status == INVALID_SOCKET)
	{
		std::cout << "Creation failed: " << WSAGetLastError() << '\n';
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			char buff[1024];
			memset(buff, 0, sizeof(buff));

			int bytes_read = 0;
			bytes_read = recv(s, buff, sizeof(buff), NULL);
			if (bytes_read > 0)
			{
				printf("received [%s]", buff);
			}

			system("pause");
		}
	}

	if (closesocket(s) == 0)
		printf("closesocket() pretty fine!\n");
	if (WSACleanup() == 0)
		printf("WSACleanup() is OK!\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Scanning bluetooth devices..." << std::endl;
	std::cout.flush();

	// scan devices
	std::vector<BLUETOOTH_DEVICE_INFO> devices = scanDevices();

	std::cout << "Got " << devices.size() << " devices" << std::endl;

	// list all devices
	int pdIndex = -1;
	int foundDev = -1;
	std::vector<BLUETOOTH_DEVICE_INFO>::const_iterator device;
	
  for (device = devices.begin(); device != devices.end(); device++)
	{
		pdIndex++;
		std::wstring ws = (*device).szName;
		std::cout << "Device: " << std::string(ws.begin(), ws.end()) << std::endl;
		 
		// see if we find our device (case sensitive)
		if (ws.find(L"DEVICE NAME HERE") != std::string::npos)
    {
			foundDev = pdIndex;
    }
	}

	// pick our ismp device
	if (foundDev == -1)
	{
		std::cout << "Could not find a device to pair" << std::endl;
		return 1;
	}

	BLUETOOTH_DEVICE_INFO pd = devices[foundDev];
	std::wstring ws = pd.szName;
	std::cout << "Found device to pair, " << std::string(ws.begin(), ws.end()) << std::endl;
	// attempt to pair device
	pairDevice(pd);

	getTrafficFromDevice(pd);

	return 0;
}
