#include "Embedded.h"

#include <cassert>
#include <iostream>


void Embedded::read()
{
	DWORD bytesReceived;
	ClearCommError(_hPort, &_errors, &_status);
	while (_bConnected)
	{
		WaitForSingleObject(_hPortMutex, INFINITE);
		FlushFileBuffers(_hPort);
		if (ReadFile(_hPort, &_buffer, 1, &bytesReceived, NULL))
		{
			ReleaseMutex(_hPortMutex);
			if (bytesReceived > 0)
			{
				_data += _buffer;
				if (_buffer == "\n")
				{
					std::cout << _data;
				}
			}
		}
		else
		{
			ReleaseMutex(_hPortMutex);
		}
	}
}

void Embedded::start_read_thread()
{
	reader = std::thread(&Embedded::read, this);
}

Embedded::Embedded(const char* portname)
{
	open(portname);
}

void Embedded::open(const char* portname)
{
	if (!_bConnected)
	{
		_hPort = CreateFile(portname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		//Determine if error is present
		if (_hPort == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				std::cout << "COM already in use";
			}
			else
			{
				std::cout << "CreateFile() failed with: " << GetLastError() << '\n';
				assert(false);
			}
		}
		else
		{
			DCB dcbPortConfig = { 0 };
			if (!GetCommState(_hPort, &dcbPortConfig))
			{
				std::cout << "Failed to get serial configuration\n";
				assert(false);
			}

			dcbPortConfig.BaudRate = CBR_9600; // 9600 and 115200
			dcbPortConfig.ByteSize = 8;
			dcbPortConfig.StopBits = ONESTOPBIT;
			dcbPortConfig.Parity = NOPARITY;
			dcbPortConfig.fDtrControl = DTR_CONTROL_ENABLE; //PC controls recving in data terminal
			dcbPortConfig.fRtsControl = RTS_CONTROL_ENABLE; //PC controls sending in data terminal

			if (!SetCommState(_hPort, &dcbPortConfig))
			{
				std::cout << "Could not set serial params\n";
				assert(false);
			}

			_bConnected = true;
			PurgeComm(_hPort, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

			//Set constants so ReadFile doesn't hang
			_cto.ReadIntervalTimeout = 1;
			_cto.ReadTotalTimeoutConstant = 1;
			_cto.ReadTotalTimeoutMultiplier = 1;
			SetCommTimeouts(_hPort, &_cto);

			_hPortMutex = CreateMutex(NULL, FALSE, "IO_MUTEX");
			start_read_thread();
		}
	}
}

void Embedded::close()
{
	if (_bConnected)
	{
		_bConnected = false;
		if (reader.joinable())
		{
			reader.join();
		}

		CloseHandle(_hPort);
	}
}

void Embedded::clear()
{
	_data.clear();
}

void Embedded::send(std::string& msg)
{
	DWORD bytesSent;

	if (_bConnected)
	{
		WaitForSingleObject(_hPortMutex, INFINITE);
		FlushFileBuffers(_hPort);

		if (WriteFile(_hPort, msg.c_str(), msg.size(), &bytesSent, NULL))
		{
			ReleaseMutex(_hPortMutex);
		}
		else
		{
			std::cout << "Send failed\n";
			ClearCommError(_hPort, &_errors, &_status);
			ReleaseMutex(_hPortMutex);
		}
	}
}

const bool Embedded::isConnected()
{
	return _bConnected;
}

std::string Embedded::get_data()
{
	return _data;
}
