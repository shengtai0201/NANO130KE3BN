#include "Nano100Series.h"              // Device header
#include "breathe.h"
#include <stdlib.h>

int _check;
int _previousBreatheType;
WavePoint *_firstWavePoint;
WavePoint *_previousWavePoint;
Breathe *_first_breathe;
Breathe *_tail_breathe;

int get_breathe_type(WavePoint *wavePoint, int check) {
    return abs(wavePoint->point) > check ? BREATHE_EXHALE : BREATHE_INHALE;
}

Breathe *new_breathe(int begin, int end, int type) {
    Breathe *breathe = (Breathe *) malloc(sizeof(Breathe));
    if (breathe == NULL)
        return NULL;
    else {
        breathe->begin = begin;
        breathe->end = end;
        breathe->type = type;
        breathe->next = NULL;

        return breathe;
    }
}

void init_breathe(int check, int previousBreatheType, WavePoint *firstWavePoint) {
    _check = check;
    _previousBreatheType = previousBreatheType;
    _firstWavePoint = firstWavePoint;
    _previousWavePoint = firstWavePoint;
    _first_breathe = NULL;
    _tail_breathe = NULL;
}

Breathe *set_breathe(WavePoint *currentWavePoint) {
    int currentBreatheType = get_breathe_type(currentWavePoint, _check);

    if (_previousBreatheType != BREATHE_NONE && _previousBreatheType != currentBreatheType) {
        Breathe *breathe = new_breathe(_firstWavePoint->time, _previousWavePoint->time, _previousBreatheType);
        if (_first_breathe == NULL) {
            _first_breathe = breathe;
            _tail_breathe = breathe;
        } else {
            _tail_breathe->next = breathe;
            _tail_breathe = breathe;
        }

        _firstWavePoint = currentWavePoint;
    }

    _previousWavePoint = currentWavePoint;
    _previousBreatheType = currentBreatheType;

    return _first_breathe;
}

void free_breathe(void) {
    free(_first_breathe);
}
