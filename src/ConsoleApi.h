#pragma once

#include <node_api.h>

EXTERN_C_START

napi_value setConsoleTitle(napi_env env, napi_callback_info info);
napi_value getConsoleTitle(napi_env env, napi_callback_info info);

napi_value setBackgroundColor(napi_env env, napi_callback_info info);
napi_value getBackgroundColor(napi_env env, napi_callback_info info);

napi_value setConsoleWindowInfo(napi_env env, napi_callback_info info);
napi_value getConsoleWindowInfo(napi_env env, napi_callback_info info);

EXTERN_C_END