#ifndef RTC_H
#define RTC_H

#define F_CPU 16000000UL
#define F_SCL 100000L

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define DS1307_ADR 0xD0
#define RTC_RESET_POINTER  0xff
#define SECONDS_REGISTER   0x00
#define MINUTES_REGISTER   0x01
#define HOURS_REGISTER     0x02
#define DAYOFWK_REGISTER   0x03
#define DAYS_REGISTER      0x04
#define MONTHS_REGISTER    0x05
#define YEARS_REGISTER     0x06
#define CONTROL_REGISTER   0x07
#define RAM_BEGIN          0x08
#define RAM_END            0x3F

struct DataTimeRTC {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t dayofwk;
	uint8_t days;
	uint8_t months;
	uint8_t years;
};

struct TimeRTC {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
};

struct DataRTC {
	uint8_t dayofwk;
	uint8_t days;
	uint8_t months;
	uint8_t years;
};

void InitRTC();
void SetValueRTC(uint8_t adr, uint8_t data);
uint8_t GetValueRTC(uint8_t adr, bool convect = false);

DataTimeRTC GetDataTimeRTC(void);
void SetDataTimeRTC(DataTimeRTC dt);

TimeRTC GetTimeRTC(void);
void SetTimeRTC(TimeRTC dt);

DataRTC GetDataRTC(void);
void SetDataRTC(DataRTC dt);

#endif