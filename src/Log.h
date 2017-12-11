#pragma once
#ifdef ANDROID
#include <android/log.h>
#else

#endif

#define LOGD(tag, ...)				LOG(tag, "LOG_DEBUG", __VA_ARGS__);
#define LOGI(tag, ...)				LOG(tag, "LOG_INFO", __VA_ARGS__);
#define LOGW(tag, ...)				LOG(tag, "LOG_WARNING", __VA_ARGS__);
#define LOGE(tag, ...)				LOG(tag, "LOG_ERROR", __VA_ARGS__);


#ifdef ANDROID
#	define LOG(tag, level, ...)		{  __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__); }
#else
#	define LOG(tag, level, ...)		{  printf("UYENKIM/"); printf(tag); printf(level); printf(__VA_ARGS__); }
#endif