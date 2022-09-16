#include "pch.h"
#include <stdio.h >

FILE* g_log_fp = fopen("kgh_log.txt", "w");

void kgh_log(char* fmt, ...)
{
	va_list va;

	va_start(va, fmt);
#if 0
	char pchlog[1024] = { 0 };
	vsnprintf_s(pchlog, sizeof(pchlog), sizeof(pchlog), fmt, va);
#endif
	if(g_log_fp)
		vfprintf(g_log_fp, fmt, va);
	va_end(va);
}

void kgh_logW(wchar_t* fmt, ...)
{
	va_list va;

	va_start(va, fmt);

#if 1
	wchar_t pchlog[1024] = { 0 };
	wvsprintfW(pchlog, fmt, va);
#endif

	va_end(va);
}