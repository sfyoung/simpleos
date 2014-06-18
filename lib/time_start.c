#include <time.h>
#include <io.h>

static char read_RTC_CMOS(int value)
{
	outb(value, 0x70);
	return inb(0x71);
}

static int BCD_To_Int(int t)
{
	return (t & 0x0f) + ((t >> 4) * 10);
}

struct tm time_start()
{
	struct tm time;

	do {
		time.tm_sec = (int)read_RTC_CMOS(0x00);
		time.tm_min = (int)read_RTC_CMOS(0x02);
		time.tm_hour = (int)read_RTC_CMOS(0x04);
		time.tm_mday = (int)read_RTC_CMOS(0x07);
		time.tm_mon = (int)read_RTC_CMOS(0x08);
		time.tm_year = (int)read_RTC_CMOS(0x09);
	} while(time.tm_sec != (int)read_RTC_CMOS(0) || time.tm_min != (int)read_RTC_CMOS(0x02) || time.tm_hour != (int)read_RTC_CMOS(0x04)|| time.tm_mday != (int)read_RTC_CMOS(0x07) || time.tm_mon != (int)read_RTC_CMOS(0x08) || time.tm_year != (int)read_RTC_CMOS(0x09));

//	time.tm_sec = BCD_To_Int(time.tm_sec);
	time.tm_sec = (time.tm_sec & 0x0f) + ((time.tm_sec >> 4) * 10);
	time.tm_min = BCD_To_Int(time.tm_min);
	time.tm_hour = BCD_To_Int(time.tm_hour);
	time.tm_mday = BCD_To_Int(time.tm_mday);
	time.tm_mon = BCD_To_Int(time.tm_mon) - 1;
	time.tm_year = BCD_To_Int(time.tm_year);

	return time;
}
