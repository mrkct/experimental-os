#include <stdint.h>
#include <stddef.h>
#include <kernel/lib/time.h>
#include <kernel/arch/i386/cmos.h>


int get_datetime(struct DateTime *datetime)
{
    if (datetime == NULL) {
        return -1;
    }
    int millennia = 100 * from_bcd(cmos_read_register(CMOS_REG_CENTURY));
    *datetime = (struct DateTime) {
        .hours = from_bcd(cmos_read_register(CMOS_REG_HOURS)),
        .minutes = from_bcd(cmos_read_register(CMOS_REG_MINUTES)),
        .seconds = from_bcd(cmos_read_register(CMOS_REG_SECONDS)),
        .year = millennia + from_bcd(cmos_read_register(CMOS_REG_YEAR)),
        .month = from_bcd(cmos_read_register(CMOS_REG_MONTH)),
        .day = from_bcd(cmos_read_register(CMOS_REG_DAYOFMONTH))
    };

    return 0;
}