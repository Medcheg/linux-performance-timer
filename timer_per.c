#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t t[2];
} timing_t;

#define timing_now(x) asm volatile(".byte 15;.byte 49" : "=a"((x)->t[0]),"=d"((x)->t[1]))

uint64_t time_diff_ticks(timing_t end, timing_t start)
{
    uint64_t diff = end.t[0] - start.t[0];

    if ( end.t[1] > start.t[1] )
    {
        uint32_t  high_part = end.t[1] - start.t[1] - 1;
        diff = high_part * 4294967296 + 4294967296 - start.t[0] + end.t[0];
    }

    return diff;
}

int main()
{
    timing_t tstart;
    timing_t tend;

    uint64_t t1, t2;
    int i;

    double delay_time = 2.5; //sec

    for (i = 0; i < 10; i++)
    {
        timing_now(&tstart);
        timing_now(&tend);
        t1 = time_diff_ticks(tend, tstart);

        timing_now(&tstart);
        usleep(delay_time * 1e6);
        timing_now(&tend);
        t2 = time_diff_ticks(tend, tstart);

        printf("proccessor ticks for empty measurement: %lu \t proccessor ticks for sleep(%.2f): %lu \t proc frec = %.1f\n", t1, delay_time, t2, t2/delay_time);///(i*100.0/1e6)
    }

    return 0;
}
