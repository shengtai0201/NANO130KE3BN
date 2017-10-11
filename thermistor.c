#include "Nano100Series.h"              // Device header
#include "thermistor.h"
#include "lcd1602.h"

// ¼ö±Ó¹qªý

static const short tb[] = {
	939,977,1017,1057,1098,1140,1182,1225,1269,1313,
	1357,1402,1447,1493,1539,1585,1631,1678,1724,1771,
	1817,1864,1910,1956,2002,2048,2093,2138,2182,2227,
	2270,2314,2356,2398,2440,2481,2521,2561,2600,2639,
	2676,2713,2750,2785,2820,2854,2888,2920,2952,2983,
	3014,3043,3073,3101,3128,3155,3182,3207,3232,3256,
	3280 };

int get_temperature(void) {
	int i, data, result;

	ADC_START_CONV(ADC);
	while (ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT) == 0) {
	}
	data = ADC_GET_CONVERSION_DATA(ADC, 0);
	for (i = 0; i < 61; i++) {
		if (data < tb[i])
			break;
	}

	if (i == 0 || i == 61)
		return -1;

	result = (((data - tb[i - 1]) * 10) + ((tb[i] - tb[i - 1]) >> 1)) / (tb[i] - tb[i - 1]);
	result += (i - 1) * 10;

	return result;
}
