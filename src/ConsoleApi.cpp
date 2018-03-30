#include "ConsoleApi.h"
#include <windows.h>

napi_value setConsoleWindowInfo(napi_env env, napi_callback_info info)
{
	napi_status status;
	size_t argc = 1;
	int width = 0;
	int height = 1;
	napi_value argv[2];
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Failed to parse arguments");
	}

	status = napi_get_value_int32(env, argv[0], &width);

	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Invalid number was passed as argument");
	}

	status = napi_get_value_int32(env, argv[1], &height);

	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Invalid number was passed as argument");
	}
	
	HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	::GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	SMALL_RECT windowSize = { (short)consoleInfo.dwCursorPosition.X, (short)consoleInfo.dwCursorPosition.Y, width, height };
	::SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	return argv[1];
}

napi_value setConsoleTitle(napi_env env, napi_callback_info info)
{
	napi_status status;
	size_t argc = 1;
	char16_t szTitle[1024] = { 0 };
	napi_value argv[1];
	status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Failed to parse arguments");
	}

	size_t bufferLen = 0;
	status = napi_get_value_string_utf16(env, argv[0], szTitle, 1024, &bufferLen);

	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Invalid number was passed as argument");
	}

	HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL bResult = ::SetConsoleTitleW((LPCWSTR)szTitle);
	
	napi_value retValue;
	status = napi_create_int32(env, bResult, &retValue);

	if (status != napi_ok) {
		napi_throw_error(env, NULL, "Unable to create return value");
	}

	return retValue;
}