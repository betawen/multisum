#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ULLONG unsigned long long
#define MAXM 4294967296
#define MAXN 100
ULLONG *multiResList;
ULLONG start_num[100];
ULLONG end_num[100];
ULLONG params[2];

void thread_cal (int thread_id) {
    ULLONG tmp = 0;
    while(tmp <= end_num[thread_id] - start_num[thread_id]){
        tmp ++;
    }
    printf("thread_%d: %d\n",thread_id,tmp);
    multiResList[thread_id] = tmp;
    pthread_exit(NULL);
}

ULLONG multisum(ULLONG m, int n) {
    ULLONG sum = 0;
    multiResList = (ULLONG *) malloc (n * sizeof(ULLONG));
    printf("init\n");
    pthread_t threads[n];
    int i,j,k;
    // 创建线程
    for (i = 0; i < n; i++) {
	printf("start\n");
        start_num[i] = (m / n) * i + 1;
	printf("end\n");
        end_num[i] = (m / n) * (i + 1);
	printf("test\n");
	end_num[n-1] = m;
        int res = pthread_create(&threads[i], NULL, thread_cal, i);
        if (res != 0) {
            printf("PTHREAD_CREATE ERROR!\n");
            exit(-1);
        }
	printf("创建成功\n！");
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
    printf("%lld\n",m);
    fgetc(fp);
    printf("%lld\n",n);
    fscanf(fp, "N=%lld", &n);
    printf("%lld\n",n);
    params[1] = 1000;
    params[0] = 10;
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
