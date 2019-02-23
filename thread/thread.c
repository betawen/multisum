#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ULLONG unsigned long long
#define MAXM 4294967296
#define MAXN 100
ULLONG *multiResList;
ULLONG *start_num;
ULLONG *end_num;

void thread_cal (int thread_id) {
    ULLONG tmp = 0;
    while(tmp <= end_num - start_num){
        tmp ++;
    }
    multiResList[thread_id] = tmp;
    pthread_exit(NULL);
}

ULLONG multisum(ULLONG m, ULLONG n) {
    ULLONG sum = 0;
    multiResList = (ULLONG *) malloc (n * sizeof(ULLONG));
    pthread_t threads[n];
    int i,j,k;
    // 创建线程
    for (i = 0; i < n; i++) {
        start_num[i] = (m / n) * i + 1;
        end_num[i] = (m / n) * (i + 1);

    }
}
