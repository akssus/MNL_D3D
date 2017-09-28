#pragma once
#include <windows.h>
#include <string>

//Macro that shows variable info about file name, called line and function, variable name as string
#define MN_VAR_INFO(varName) (std::string(__FILE__) + "(" + std::to_string(__LINE__) + ")\n@" +std::string(__FUNCTION__) + ": " + std::string(#varName))

namespace MNL
{
	/*
	Helper functions to show error messges.
	@Usage:
	MnLog::MB_Missing(MN_VAR_INFO(var));
	*/
	namespace MnLog
	{
		/*
		Formatted message box. Not safe and not efficient, so not recommend to use
		*/
		void MB_Error(const char* format, ...);
		/*
		Formatted message box. Not safe and not efficient, so not recommend to use
		*/
		void MB_Error(const wchar_t* format, ...);
		void MB_Failed(const std::wstring& failedThing);
		void MB_Failed(const std::string& failedThing);
		void MB_InitFailed(const std::wstring& initThing);
		void MB_InitFailed(const std::string& initThing);
		void MB_Missing(const std::wstring& missingThing);
		void MB_Missing(const std::string& missingThing);
		void MB_IsNull(const std::wstring& nullThing);
		void MB_IsNull(const std::string& nullThing);
	};
}