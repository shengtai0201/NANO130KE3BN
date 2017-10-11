#include "Nano100Series.h"              // Device header

#define WAVE_RISE   0   // ??
#define WAVE_FALL   1   // ??
#define WAVE_SAME   2

typedef struct wave {
    int time;
    int previous;
    int current;
} Wave;

typedef struct wavePoint {
    int time;
    int point;
    int is_crest;
    struct wavePoint *next;
} WavePoint;

void init_wave_point(void);

WavePoint *set_wave_point(int);

void free_wave_point(void);
