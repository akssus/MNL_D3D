#include "MnLog.h"

using namespace MNL;

MNL::MnLog MNL::g_MnLog;

MnLog::MnLog()
{
}


MnLog::~MnLog()
{
}

void MnLog::MB_Error(const char* format, ...)
{
	va_list argList;
	va_start(argList, format);
	
	const UINT MAX_CHARS = 1023;
	static char s_buffer[MAX_CHARS + 1];
	vsnprintf(s_buffer, MAX_CHARS, format, argList);
	s_buffer[MAX_CHARS] = '\0';
	::MessageBoxA(0, s_buffer, "Error", MB_ICONERROR);

	va_end(argList);
}
void MnLog::MB_Error(const wchar_t* format, ...)
{
	va_list argList;
	va_start(argList, format);

	const UINT MAX_CHARS = 1023;
	static wchar_t s_buffer[MAX_CHARS + 1];
	vswprintf(s_buffer, MAX_CHARS, format, argList);
	s_buffer[MAX_CHARS] = '\0';
	::MessageBox(0, s_buffer, L"Error", MB_ICONERROR);

	va_end(argList);
}
void MnLog::MB_Missing(const std::wstring& missingThing)
{
	std::wstring msg = missingThing + L" is missing.";
	::MessageBox(0, msg.c_str(), L"Error", MB_ICONERROR);
}
void MnLog::MB_Missing(const std::string& missingThing)
{
	std::string msg = missingThing + " is missing.";
	::MessageBoxA(0, msg.c_str(), "Error", MB_ICONERROR);
}
void MnLog::MB_IsNull(const std::wstring& nullThing)
{
	std::wstring msg = nullThing + L" was nullptr";
	::MessageBox(0, msg.c_str(), L"Error", MB_ICONERROR);
}
void MnLog::MB_IsNull(const std::string& nullThing)
{
	std::string msg = nullThing + " was nullptr.";
	::MessageBoxA(0, msg.c_str(), "Error", MB_ICONERROR);
}