#pragma once
#include <windows.h>
#include <thread>
#include <atomic>
#include <string>

class Embedded
{
private:
	HANDLE _hPort;
	HANDLE _hPortMutex;
	COMMTIMEOUTS _cto;
	COMSTAT _status;
	DWORD _errors;
	const void start_read_thread();
	std::atomic<bool> _bConnected = false;
	std::string _buffer;
	std::string _data;
	std::thread reader;
	void read();
public:
	Embedded() {}
	Embedded(const char* portname);
	void open(const char* portname);
	void close();
	void clear();
	void send(std::string& msg);
	const bool isConnected();
	std::string get_data();
};
