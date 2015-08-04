#include <unistd.h>
#include <stdio.h>

typedef struct {
unsigned long t[2];
}
timing;

#define timing_now(x) asm volatile(".byte 15;.byte 49" : "=a"((x)->t[0]),"=d"((x)->t[1]))
#define timing_diff(x,y) \
        (((x)->t[0] - (double) (y)->t[0]) / 3401000000.0 \
        + (4294967296.0/3401000000.0) * ((x)->t[1] - (double) (y)->t[1]))

#define timing_diff_ticks(x,y) \
        (((x)->t[0] - (double) (y)->t[0]) \
        + (4294967296.0) * ((x)->t[1] - (double) (y)->t[1]))

int main() {
    timing tstart;
    timing tend;

    double t1, t2;
    int i;

    for (i = 0; i < 10; i++)
    {
        timing_now(&tstart);
        timing_now(&tend);
        t1 = timing_diff_ticks(&tend, &tstart);

        timing_now(&tstart);
        sleep(1);
        timing_now(&tend);
        t2 = timing_diff_ticks(&tend, &tstart);

        printf("proccessor ticks for empty measurement: %.0f \t proccessor ticks for sleep(100): %.0f proc frec ??? = %.0f\n", t1, t2, t2);///(i*100.0/1e6)
    }
}
