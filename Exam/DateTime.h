#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <ctime>

using std::time_t;

char* TimeToStr(time_t tt, const char* format);

char* TimeToDTStr(time_t tt);
char* TimeToDStr(time_t tt);
char* TimeToTStr(time_t tt);

char* NowToDTStr();
char* NowToDStr();
char* NowToTStr();

char* TimeToDbDTStr(time_t tt);
char* TimeToDbDStr(time_t tt);

time_t CreateDateTime(int year, int month, int day,
	int hour, int min, int sec);

time_t CreateDate(int year, int month, int day);

time_t CreateTime(int hour, int min, int sec);

time_t StrToDateTime(const char* str);
time_t StrToDate(const char* str);
time_t StrToTime(const char* str);

int GetMonth(time_t tt);

time_t DbDateStrToDate(const char* str);

const char* AddWeek(const char* dbDateStr);
const char* AddMonth(const char* dbDateStr);