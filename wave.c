#include "Nano100Series.h"              // Device header
#include "wave.h"
#include <stdio.h>
#include <stdlib.h>

int *_previous;
int _time_count;
int *_previous_subtraction;
Wave *_previous_wave;
WavePoint *_first_wave_point;
WavePoint *_tail_wave_point;

int get_wave_status(Wave *wave) {
    int status = WAVE_SAME;

    if (wave->current > 0) {
        // ????
        if (wave->previous < 0 || wave->previous < wave->current)
            status = WAVE_RISE;
        else if (wave->previous > wave->current)
            status = WAVE_FALL;
    } else {
        // ????
        if (wave->previous > 0 || wave->previous > wave->current)
            status = WAVE_FALL;
        else if(wave->previous < wave->current)
            status = WAVE_RISE;
    }

    return status;
}

Wave *new_wave(int time, int previous, int current) {
    Wave *wave = (Wave *) malloc(sizeof(Wave));
    if (wave == NULL)
        return NULL;
    else {
        wave->time = time;
        wave->previous = previous;
        wave->current = current;

        return wave;
    }
}

WavePoint *new_wave_point(int time, int point) {
    WavePoint *wave_point = (WavePoint *) malloc(sizeof(WavePoint));
    if (wave_point == NULL)
        return NULL;
    else {
        wave_point->time = time;
        wave_point->point = point;
        wave_point->next = NULL;

        return wave_point;
    }
}

void init_wave_point(void) {
    _previous = NULL;
    _time_count = 0;
    _previous_subtraction = NULL;
    _previous_wave = NULL;
    _first_wave_point = NULL;
    _tail_wave_point = NULL;
}

WavePoint *set_wave_point(int value) {
    if (_previous != NULL) {
        int subtraction = value - *_previous;

        if (_previous_subtraction != NULL) {
            Wave *currentWave = new_wave(_time_count, *_previous_subtraction, subtraction);
            int currentWaveStatus = get_wave_status(currentWave);

            if (currentWaveStatus != WAVE_SAME) {
                int previousWaveStatus;
                if (_previous_wave != NULL &&
                    ((previousWaveStatus = get_wave_status(_previous_wave)) != currentWaveStatus)) {
                    WavePoint *wavePoint = new_wave_point(_previous_wave->time, _previous_wave->current);
                    if (previousWaveStatus == WAVE_RISE && currentWaveStatus == WAVE_FALL)
                        wavePoint->is_crest = 1;    // ???
                    else if (previousWaveStatus == WAVE_FALL && currentWaveStatus == WAVE_RISE)
                        wavePoint->is_crest = 0;    // ???

                    if (_first_wave_point == NULL) {
                        _first_wave_point = wavePoint;
                        _tail_wave_point = wavePoint;
                    } else {
                        _tail_wave_point->next = wavePoint;
                        _tail_wave_point = wavePoint;
                    }
                }

                _previous_wave = currentWave;
            }
        } else {
            _previous_subtraction = (int *) malloc(sizeof(int));
        }

        *_previous_subtraction = subtraction;
    } else {
        _previous = (int *) malloc(sizeof(int));
    }

    *_previous = value;
    _time_count++;

    return _first_wave_point;
}

void free_wave_point(void) {
    free(_previous_wave);
    free(_previous_subtraction);

    free(_first_wave_point);
}
