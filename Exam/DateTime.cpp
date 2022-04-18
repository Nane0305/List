#include "DateTime.h"

#include <string.h>
#include <stdlib.h>

using namespace std;

// struct tm *localtime( const time_t *timer );
// size_t strftime( char *strDest, size_t maxsize, 
//   const char *format, const struct tm *timeptr);
char* TimeToStr(time_t tt, const char* format) {
	static char buff[64];
	strftime(buff, sizeof buff, format, localtime(&tt));
	return buff;
}

char* TimeToDTStr(time_t tt) {
	return TimeToStr(tt, "%d.%m.%Y %H:%M:%S");
}

char* TimeToDStr(time_t tt) {
	return TimeToStr(tt, "%d.%m.%Y");
}

char* TimeToTStr(time_t tt) {
	return TimeToStr(tt, "%H:%M:%S");
}

char* NowToDTStr() {
	return TimeToStr(time(nullptr), "%d.%m.%Y %H:%M:%S");
}

char* NowToDStr() {
	return TimeToStr(time(nullptr), "%d.%m.%Y");
}

char* NowToTStr() {
	return TimeToStr(time(nullptr), "%H:%M:%S");
}

char* TimeToDbDTStr(time_t tt) {
	return TimeToStr(tt, "%Y.%m.%d %H:%M:%S");
}

char* TimeToDbDStr(time_t tt) {
	return TimeToStr(tt, "%Y.%m.%d");
}

// time_t mktime( struct tm *timeptr );
time_t CreateDateTime(int year, int month, int day,
	int hour, int min, int sec) {

	tm tm;
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = min;
	tm.tm_sec = sec;
	tm.tm_isdst = -1;
	tm.tm_wday = 0;
	tm.tm_yday = 0;
	return mktime(&tm);
}

time_t CreateDate(int year, int month, int day) {
	return CreateDateTime(year, month, day, 0, 0, 0);
}

time_t CreateTime(int hour, int min, int sec) {
	return CreateDateTime(1970, 1, 1, hour, min, sec);
}

// char *strtok(char* strToken, const char* strDelimit);
time_t StrToDateTime(const char* str) {
	int year = 1971, month = 1, day = 1, 
		hour = 0, min = 0, sec = 0;
	char buff[128];
	strncpy(buff, str, sizeof buff);
	char* p = strtok(buff, "./ \r\n\0");
	day = atoi(p);
	p = strtok(nullptr, "./ \r\n\0");
	month = atoi(p);
	p = strtok(nullptr, "./ \r\n\0");
	year = atoi(p);

	p = strtok(nullptr, ":");
	if (p == nullptr)
		goto create;
	hour = atoi(p);
	p = strtok(nullptr, ": \r\n\0");
	min = atoi(p);
	p = strtok(nullptr, " \r\n\0");
	if (p == nullptr)
		goto create;
	sec = atoi(p);

	create:
	return CreateDateTime(year, month, day, hour, min, sec);
}

time_t StrToDate(const char* str) {
	int year = 1971, month = 1, day = 1;

	char buff[128];
	strncpy(buff, str, sizeof buff);
	char* p = strtok(buff, "./ \r\n\0");
	day = atoi(p);
	p = strtok(nullptr, "./ \r\n\0");
	month = atoi(p);
	p = strtok(nullptr, "./ \r\n\0");
	year = atoi(p);
	return CreateDate(year, month, day);
}

time_t StrToTime(const char* str) {
	int hour = 0, min = 0, sec = 0;
	char buff[128];
	strncpy(buff, str, sizeof buff);

	char* p = strtok(buff, ":");
	hour = atoi(p);
	p = strtok(nullptr, ": \r\n\0");
	min = atoi(p);
	p = strtok(nullptr, " \r\n\0");
	if (p == nullptr)
		goto create;
	sec = atoi(p);

create:
	return CreateTime(hour, min, sec);
}

int GetMonth(time_t tt) {
	return localtime(&tt)->tm_mon + 1;
}

time_t DbDateStrToDate(const char* str) {
	int year = 1971, month = 1, day = 1;

	char buff[128];
	strncpy(buff, str, sizeof buff);
	char* p = strtok(buff, "./");
	year = atoi(p);
	p = strtok(nullptr, "./");
	month = atoi(p);
	p = strtok(nullptr, " \r\n\0");
	day = atoi(p);
	return CreateDate(year, month, day);
}

const char* AddWeek(const char* dbDateStr) {
	time_t tt = DbDateStrToDate(dbDateStr);
	tm tm = *localtime(&tt);
	tm.tm_mday += 6;
	time_t tt2 = mktime(&tm);
	return TimeToDbDStr(tt2);
}

const char* AddMonth(const char* dbDateStr) {
	time_t tt = DbDateStrToDate(dbDateStr);
	tm tm = *localtime(&tt);
	tm.tm_mon += 1;
	tm.tm_mday -= 1;
	time_t tt2 = mktime(&tm);
	return TimeToDbDStr(tt2);
}