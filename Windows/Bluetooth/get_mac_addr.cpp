#include <stdio.h>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <string>
#include <iostream>
#pragma comment(lib, "iphlpapi.lib")

void getMAC() {
	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
	char mac_addr[18];
	memset(mac_addr, 0, sizeof(mac_addr));

	AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if (AdapterInfo == NULL) {
		printf("Error allocating memory needed to call GetAdaptersinfo\n");
		return; // it is safe to call free(NULL)
	}

	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
		free(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
		if (AdapterInfo == NULL) {
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
			return;
		}
	}
	bool bt_found = false;
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		// Contains pointer to current adapter info
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
		do {
			if (pAdapterInfo->AddressLength == 6)
			{
				if (strstr(pAdapterInfo->Description, "Bluetooth"))
				{

					sprintf_s(mac_addr, 18, "%02X%02X%02X%02X%02X%02X",
						pAdapterInfo->Address[0], pAdapterInfo->Address[1],
						pAdapterInfo->Address[2], pAdapterInfo->Address[3],
						pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

					bt_found = true;
					break;
				}
			}

			pAdapterInfo = pAdapterInfo->Next;
		} while (pAdapterInfo);
	}
	free(AdapterInfo);
	s.append(mac_addr);
	std::cout << "Mac addr: " << s << '\n';
}

int main() {
	getMAC();
	system("pause");
}
