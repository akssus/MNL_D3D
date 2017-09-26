#pragma once
#include <windows.h>
#include <string>

//Macro that shows variable info about file name, called line and function, variable name as string
#define MN_VAR_INFO(varName) (std::string(__FILE__) + "(" + std::to_string(__LINE__) + ")\n@" +std::string(__FUNCTION__) + ": " + std::string(#varName))

namespace MNL
{
	/*
	Helper class to show error messges.
	g_MnLog is already declared so don't need to instantiate this.
	@Usage:
	g_MnLog.MB_Missing(MN_VAR_INFO(var));
	*/
	class MnLog
	{
	public:
		MnLog();
		~MnLog();

		/*
		Formatted message box. Not safe and not efficient, so not recommend to use
		*/
		void MB_Error(const char* format, ...);
		/*
		Formatted message box. Not safe and not efficient, so not recommend to use
		*/
		void MB_Error(const wchar_t* format, ...);
		void MB_Missing(const std::wstring& missingThing);
		void MB_Missing(const std::string& missingThing);
		void MB_IsNull(const std::wstring& nullThing);
		void MB_IsNull(const std::string& nullThing);
	};

	extern MnLog g_MnLog;
}