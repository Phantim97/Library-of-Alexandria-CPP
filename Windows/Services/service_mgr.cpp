#include <Windows.h>
#include <iostream>

//Note this code needs to be run in admin mode to function properly.

class InvalidInputException
{
public:
	void ErrorMessage() { std::cout << "invalid input\n"; }
};

static void inline CloseService(SC_HANDLE& sc, SC_HANDLE& scm)
{
	CloseServiceHandle(sc);
	CloseServiceHandle(scm);
}

static VOID _stdcall DoServiceStart(std::string& service_name)
{
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwOldCheckpoint;
	DWORD dwStartTickCount;
	DWORD dwWaitTime;
	DWORD dwBytesNeeded;

	//Get a handle to SCM database
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (schSCManager == NULL)
	{
		printf("OpenSCManager failed(%d)\n", GetLastError());
		return;
	}

	//Get a handle to the service
	SC_HANDLE schService = OpenService(schSCManager, service_name.c_str(), SERVICE_ALL_ACCESS);

	if (schService == NULL)
	{
		printf("OpenService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}

	//Check the status in case the service is not stopped
	if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		printf("QueryServiceStatusEx failed(%d)", GetLastError());
		CloseService(schService, schSCManager);
		return;
	}

	//Check if the service is already running
	if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
	{
		printf("Cannot start service because service is already running\n");
		CloseService(schService, schSCManager);
		return;
	}

	//Save the tick count and initial checkpoint

	dwStartTickCount = GetTickCount();
	dwOldCheckpoint = ssStatus.dwCheckPoint;

	//Wait for the service to stop before attempting to start it
	while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
	{
		//Do not wait longer than the wait hint. No less than 1 and not more than 10 seconds

		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
		{
			dwWaitTime = 1000;
		}
		else if (dwWaitTime > 10000)
		{
			dwWaitTime = 10000;
		}

		Sleep(dwWaitTime);

		//Check the status until the service is no longer stop pending
		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
		{
			printf("QueryServiceStatusEx failed(%d)\n", GetLastError());
			CloseService(schService, schSCManager);
			return;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckpoint)
		{
			//continue to wait and check
			dwStartTickCount = GetTickCount();
			dwOldCheckpoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				printf("Timeout waiting for service to stop\n");
				CloseService(schService, schSCManager);
				return;
			}
		}
	}

	//Attempt to start the service
	if (!StartService(schService, 0, NULL))
	{
		printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		CloseService(schService, schSCManager);
		return;
	}
	else
	{
		printf("Service start pending...\n");
	}

	//Check the status until the service is no longer start pending
	if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		printf("QueryServiceStatusEx failed(%d)", GetLastError());
		CloseService(schService, schSCManager);
		return;
	}

	//Save the tick count and initial checkpoint
	dwStartTickCount = GetTickCount();
	dwOldCheckpoint = ssStatus.dwCheckPoint;

	while (ssStatus.dwCurrentState == SERVICE_START_PENDING)
	{
		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
		{
			dwWaitTime = 1000;
		}
		else if (dwWaitTime > 10000)
		{
			dwWaitTime = 10000;
		}

		Sleep(dwWaitTime);

		//Check the status again
		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
		{
			printf("QueryServiceStatusEx failed(%d)", GetLastError());
			break;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckpoint)
		{
			//Continue to wait and check
			dwStartTickCount = GetTickCount();
			dwOldCheckpoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				//No progress made within the wait hint
				break;
			}
		}
	}

	//Determine whether service is running
	if (ssStatus.dwCurrentState == SERVICE_RUNNING)
	{
		printf("Service started successfully.\n");
	}
	else
	{
		printf("Service not started.\n");
		printf("  Current State: %d\n", ssStatus.dwCurrentState);
		printf("  Exit code: %d\n", ssStatus.dwWin32ExitCode);
		printf("  Checkpoint: %d\n", ssStatus.dwCheckPoint);
		printf("  Wait Hint: %d\n", ssStatus.dwWaitHint);
	}

	CloseService(schService, schSCManager);
}

static BOOL _stdcall StopDependentServices(SC_HANDLE &sc, SC_HANDLE &scm)
{
	DWORD i;
	DWORD dwBytesNeeded;
	DWORD dwCount;

	LPENUM_SERVICE_STATUS lpDependencies = NULL;
	ENUM_SERVICE_STATUS ess;
	SC_HANDLE hDepService;
	SERVICE_STATUS_PROCESS ssp;

	DWORD dwStartTime = GetTickCount();
	DWORD dwTimeout = 30000;

	//pass zero length buffer to get the required buffer size
	if (EnumDependentServices(sc, SERVICE_ACTIVE, lpDependencies, 0, &dwBytesNeeded, &dwCount))
	{
		//If the enum cal succeeds then there are no dependent services so do nothing
		return TRUE;
	}
	else
	{
		if (GetLastError() != ERROR_MORE_DATA)
		{
			return FALSE; //unexpected data
		}

		//Allocate a buffer for the dependencies
		lpDependencies = (LPENUM_SERVICE_STATUS)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded);

		if (!lpDependencies)
		{
			return FALSE;
		}

		__try
		{
			//Enumerate Dependencies
			if (!EnumDependentServices(sc, SERVICE_ACTIVE, lpDependencies, dwBytesNeeded, &dwBytesNeeded, &dwCount))
			{
				return FALSE;
			}

			for (i = 0; i < dwCount; i++)
			{
				ess = *(lpDependencies + i);
				//Open the service
				hDepService = OpenService(scm, ess.lpServiceName, SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!hDepService)
				{
					return FALSE;
				}

				__try
				{
					//Send a stop code
					if (!ControlService(hDepService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp))
					{
						return FALSE;
					}

					//wait for service to stop
					while (ssp.dwCurrentState != SERVICE_STOPPED)
					{
						Sleep(ssp.dwWaitHint);
						if (!QueryServiceStatusEx(hDepService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
						{
							return FALSE;
						}

						if (ssp.dwCurrentState == SERVICE_STOPPED)
						{
							break;
						}

						if (GetTickCount() - dwStartTime > dwTimeout)
						{
							return FALSE;
						}
					}
				}
				__finally
				{
					//Always release the service handle
					CloseServiceHandle(hDepService);
				}
			}
		}
		__finally
		{
			//Always free the enumeration buffer
			HeapFree(GetProcessHeap(), 0, lpDependencies);
		}
	}

	return TRUE;
}

static VOID _stdcall DoStopService(std::string& service_name)
{
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwStartTime = GetTickCount();
	DWORD dwBytesNeeded;
	DWORD dwTimeout = 30000; // 30 second timeout
	DWORD dwWaitTime;

	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); //(local pc, servicesactive db, full access rights)

	if (schSCManager == NULL)
	{
		if (GetLastError() == 5)
		{
			printf("Cannot open Service Manager (not in admin mode)\n");
		}
		else
		{
			printf("OpenSCManagerFailed (%d)\n", GetLastError());
		}
		return;
	}

	//pass data base and name of service to stop
	SC_HANDLE schService = OpenService(schSCManager, service_name.c_str(), SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS);

	if (schService == NULL)
	{
		printf("OpenServiceFailed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}

	//make sure service is not already stopped
	if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		CloseService(schService, schSCManager);
		return;
	}

	if (ssp.dwCurrentState == SERVICE_STOPPED)
	{
		printf("Service is already stopped.\n");
		CloseService(schService, schSCManager);
		return;
	}

	//If a stop is pending wait for it
	while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
	{
		printf("Service stop pending...\n");

		//Do not wait longer than the wait hint. A good interval is one-tenth of the wait hint.
		//but not less than one second and not more than 10 seconds

		dwWaitTime = ssp.dwWaitHint / 10;

		if (dwWaitTime < 1000)
		{
			dwWaitTime = 1000;
		}
		else if (dwWaitTime > 10000)
		{
			dwWaitTime = 10000;
		}

		Sleep(dwWaitTime);

		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
		{
			printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			CloseService(schService, schSCManager);
			return;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			printf("Service stopped successfully.\n");
			CloseService(schService, schSCManager);
			return;
		}

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			printf("Service stop timed out.\n");
			return;
		}
	}

	//If service is running, dependencies must bet stopped first
	StopDependentServices(schService, schSCManager);

	if (!ControlService(schService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)& ssp))
	{
		printf("ControlService failed(%d)", GetLastError());
		CloseService(schService, schSCManager);
		return;
	}

	//wait for the service to stop
	while (ssp.dwCurrentState != SERVICE_STOPPED)
	{
		Sleep(ssp.dwWaitHint);
		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)& ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
		{
			printf("QueryServiceStatusEx Failed (%d)\n", GetLastError());
			CloseService(schService, schSCManager);
			return;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			break;
		}

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			printf("Wait timed out\n");
			CloseService(schService, schSCManager);
			return;
		}
	}

	printf("Service Stopped Successfully\n");

	CloseService(schService, schSCManager);
}

int main()
{
	int opt;
	std::string service_name;
	std::cout << "Start or stop a service? (start:1/stop:2):";
	do
	{
		try
		{
			std::cin >> opt;
			if (std::cin.fail())
			{
				throw InvalidInputException();
			}
		}
		catch (InvalidInputException& e)
		{
			e.ErrorMessage();
			std::cin.clear();
			std::cin.ignore(99999, '\n');
		}
	} while (opt != 1 && opt != 2);
	std::cout << "Enter service name:";
	std::cin >> service_name;

	if (opt == 1)
	{
		DoServiceStart(service_name);
	}
	else
	{
		DoStopService(service_name);
	}
	
	return 0;
}
