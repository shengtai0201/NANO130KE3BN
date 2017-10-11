#include "Nano100Series.h"              // Device header
#include "wave.h"

#define BREATHE_NONE    0
#define BREATHE_EXHALE  1   // ??
#define BREATHE_INHALE  2   // ??

typedef struct breathe {
    int begin;
    int end;
    int type;
    struct breathe *next;
} Breathe;

void init_breathe(int, int, WavePoint *);

Breathe *set_breathe(WavePoint *);

void free_breathe(void);
