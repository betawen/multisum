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
ULLONG params[2];

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
    for (i = 0; i < n - 1; i++) {
        start_num[i] = (m / n) * i + 1;
        end_num[i] = (m / n) * (i + 1);
        int res = pthread_create(&threads[i], NULL, thread_cal, i);
        if (res != 0) {
            printf("PTHREAD_CREATE ERROR!\n");
            exit(-1);
        }
    }

    // 计算总和
    for (j = 0; j < n; j ++) {
        pthread_join(threads[j], NULL);
        sum += multiResList[j];
    }
    return sum;
}

void fileRead(char *filePath) {
    FILE *fp;
    ULLONG m;
    ULLONG n;
    fp = fopen(filePath, "w");
    if ( fp == NULL ) {
        printf("FILEREAD FAILD!\n");
        exit(-1);
    }
    fscanf(fp, "M=%lld", &m);
    fscanf(fp, "N=%lld", &n);
    params[1] = m;
    params[0] = n;
    fclose(fp);
}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("PARAM ERROR: %s\n", argv[1]);
        return 0;
    }
    fileRead(argv[1]);
    printf("ok\n");
    if(params[0] < 1 || params[1] < 1 || params[0] >= MAXN || params[1] >= MAXM){
        printf("PARAMS ERROR\n");
        return 0;
    }

    ULLONG sum = multisum (params[1], (int)params[0]);
    if(sum == -1) return 0;

    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "%lld", sum);
    fclose(fp);
    printf("N=%lld, M=%lld\n", params[0], params[1]);
    printf("multisum: %lld\n", sum);
    if (sum == params[1]) {
        printf("True!\n");
	return 0;
    }
    else
        printf("False!\n");
    return 0;
}