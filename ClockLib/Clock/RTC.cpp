#include "RTC.h"

void InitRTC() {
	TWSR = 0;
	TWBR = ((F_CPU/F_SCL)-16)/2;
}

void SetValueRTC(uint8_t adr, uint8_t data) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	TWDR = (DS1307_ADR)|0;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	TWDR = adr;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	if (data != RTC_RESET_POINTER){
		data = ((data/10)<<4) + data%10;
		TWDR = data;
		TWCR = (1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
	}
	
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

uint8_t GetValueRTC(uint8_t adr, bool convect) {
	uint8_t data;
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	TWDR = (DS1307_ADR)|0;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	TWDR = adr;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	TWDR = (DS1307_ADR)|1;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	data = TWDR;
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	if(convect) data = ((data)>>4)*10 + (data&0xf);
	
	return data;
}

DataTimeRTC GetDataTimeRTC(void) {
	DataTimeRTC dt;
	dt.seconds	= GetValueRTC(SECONDS_REGISTER, true);
	dt.minutes	= GetValueRTC(MINUTES_REGISTER, true);
	dt.hours	= GetValueRTC(HOURS_REGISTER, true);
	dt.dayofwk	= GetValueRTC(DAYOFWK_REGISTER, true);
	dt.days		= GetValueRTC(DAYS_REGISTER, true);
	dt.months	= GetValueRTC(MONTHS_REGISTER, true);
	dt.years	= GetValueRTC(YEARS_REGISTER, true);
	return dt;
}

void SetDataTimeRTC(DataTimeRTC dt) {
	SetValueRTC(SECONDS_REGISTER, dt.seconds);
	SetValueRTC(MINUTES_REGISTER, dt.minutes);
	SetValueRTC(HOURS_REGISTER, dt.hours);
	SetValueRTC(DAYOFWK_REGISTER, dt.dayofwk);
	SetValueRTC(DAYS_REGISTER, dt.days);
	SetValueRTC(MONTHS_REGISTER, dt.months);
	SetValueRTC(YEARS_REGISTER, dt.years);
}

TimeRTC GetTimeRTC(void) {
	TimeRTC t;
	t.seconds	= GetValueRTC(SECONDS_REGISTER, true);
	t.minutes	= GetValueRTC(MINUTES_REGISTER, true);
	t.hours		= GetValueRTC(HOURS_REGISTER, true);
	return t;
}

void SetTimeRTC(TimeRTC t) {
	SetValueRTC(SECONDS_REGISTER, t.seconds);
	SetValueRTC(MINUTES_REGISTER, t.minutes);
	SetValueRTC(HOURS_REGISTER, t.hours);
}

DataRTC GetDataRTC(void) {
	DataRTC d;
	d.dayofwk	= GetValueRTC(DAYOFWK_REGISTER, true);
	d.days		= GetValueRTC(DAYS_REGISTER, true);
	d.months	= GetValueRTC(MONTHS_REGISTER, true);
	d.years		= GetValueRTC(YEARS_REGISTER, true);
	return d;
}

void SetDataRTC(DataRTC d) {
	SetValueRTC(DAYOFWK_REGISTER, d.dayofwk);
	SetValueRTC(DAYS_REGISTER, d.days);
	SetValueRTC(MONTHS_REGISTER, d.months);
	SetValueRTC(YEARS_REGISTER, d.years);
}