#include "clock.h"

#include <stddef.h>
#include <stdlib/stdio/stdio.h>
#include <stdlib/sys/io.h>
#include <stdlib/string/string.h>
#include <stdlib/stdlib.h>

int century_register = 0x00;
unsigned char second, minute, hour, day, month, year;

int is_update_in_progress() {
	outb(0x70, 0x0A);
	return (inb(0x71) & 0x80);
}

unsigned char get_RTC_register(int reg) {
	outb(0x70, reg);
	return inb(0x71);
}

void read_rtc() {
	unsigned char last_second, last_minute, last_hour, last_day, last_month, last_year, last_century, registerB;

	// Loop until any pending updates are complete
	while (is_update_in_progress());

	second = get_RTC_register(0x00);
	minute = get_RTC_register(0x02);
	hour = get_RTC_register(0x04);
	day = get_RTC_register(0x07);
	month = get_RTC_register(0x08);
	year = get_RTC_register(0x09);

	do {
		last_second = second;
		last_minute = minute;
		last_hour = hour;
		last_day = day;
		last_month = month;
		last_year = year;

		// Loop again until any pending updates are complete
	    while (is_update_in_progress());

		second = get_RTC_register(0x00);
		minute = get_RTC_register(0x02);
		hour = get_RTC_register(0x04);
		day = get_RTC_register(0x07);
		month = get_RTC_register(0x08);
		year = get_RTC_register(0x09);
	} while ((last_second != second) || (last_minute != minute) || (last_hour != hour) || (last_day != day) || (last_month != month) || (last_year != year));

	registerB = get_RTC_register(0x0B);

	if (!(registerB & 0x04)) {
		second = (second & 0x0F) + ((second / 16) * 10);
		minute = (minute & 0x0F) + ((minute / 16) * 10);
		hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
		day = (day & 0x0F) + ((day / 16) * 10);
		month = (month & 0x0F) + ((month / 16) * 10);
		year = (year & 0x0F) + ((year / 16) * 10);
	}
}

int days_in_year(int year) {
	if (year % 4 == 0) return 366;
	return 365;
}

int days_in_month(int month, int year) {
	switch (month) {
		case 0:
			return 31;
		case 1:
			if (year % 4 == 0) return 29;
			return 28;
		case 2:
			return 31;
		case 3:
			return 30;
		case 4:
			return 31;
		case 5:
			return 30;
		case 6:
		case 7:
			return 31;
		case 8:
			return 30;
		case 9:
			return 31;
		case 10:
			return 30;
		case 11:
		case 12:
			return 31;
		default:
			return -1;
	}
}

unsigned char epoch_time() {
	size_t epoch_time = 0;
	read_rtc();

	// compute years since 1970
	int years_since_1970 = 30 + year;
	// 1 year = 60s * 60m * 24h * 365d
	for (int i = 1; i <= years_since_1970; i++) {
		int current_year = year - i;
		epoch_time += (days_in_year(current_year) * 24 * 60 * 60);
	}

	// compute months in year
	// month = 60s * 60m * 24h
	for (int i = 0; i < month; i++) {
		epoch_time += (days_in_month(i, year) * 24 * 60 * 60);
	}

	// compute days in month
	// day = 60s * 60m * 24h
	epoch_time += day * 24 * 60 * 60;

	// compute hours in day
	// hour = 60s * 60m
	epoch_time += hour * 60 * 60;

	// compute minutes in hour
	// minutes = 60s
	epoch_time += minute * 60;

	// compute seconds in minute
	// seconds = seconds
	epoch_time += second;

	return epoch_time;
}

char *date_time() {
	read_rtc();

	char *date_time = malloc(sizeof(char) * 64);
	char buf[8];

	itoa(hour, buf);
	if (hour < 10) strcat(buf, "0");
	strcat(date_time, buf);
	strcat(date_time, ":");

	itoa(minute, buf);
	if (minute < 10) strcat(buf, "0");
	strcat(date_time, buf);
	strcat(date_time, ":");

	itoa(second, buf);
	if (second < 10) strcat(buf, "0");
	strcat(date_time, buf);
	strcat(date_time, ", ");

	itoa(month, buf);
	strcat(date_time, buf);
	strcat(date_time, "/");

	itoa(day, buf);
	strcat(date_time, buf);
	strcat(date_time, "/");

	itoa(year, buf);
	strcat(date_time, buf);

	return date_time;
}

void sleep(int secs) {
	int end = epoch_time() + secs;
	while (epoch_time() < end) {}
}