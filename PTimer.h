#ifndef PTIMER_H
#define PTIMER_H

#include <time.h>

#ifndef PTIMER_IMPLEMENTATION
#define _DECL extern
#else
#define _DECL
#endif

#define MAX_TIMERS 20
#define NS_TO_MS(x) (x/1.e6)
#define NS_TO_SEC(x) (x/1.e9)

#ifdef _WIN32
#define GET_TIME(t) (timespec_get(&t, TIME_UTC))
#elif __linux__
#define GET_TIME(t) (clock_gettime(CLOCK_REALTIME, &t))
#endif

typedef struct {
    struct timespec start;
    struct timespec end;
} Timer_t;

_DECL Timer_t timers[MAX_TIMERS];

typedef enum {NS, MS, SEC} PT_Units_t;

inline void pt_start (unsigned tid)
{
    GET_TIME(timers[tid].start);
}

inline void pt_stop (unsigned tid)
{
    GET_TIME(timers[tid].end);
}

double pt_result (unsigned tid, PT_Units_t unit)
{
    Timer_t *t = &timers[tid];
    double t_ns = (double)(t->end.tv_sec - t->start.tv_sec)*1.e9 + (double)(t->end.tv_nsec - t->start.tv_nsec);

    if (unit == MS)
    {
        t_ns = NS_TO_MS(t_ns);
    }
    else if (unit == SEC)
    {
        t_ns = NS_TO_SEC(t_ns);
    }

    return t_ns;
}

#endif