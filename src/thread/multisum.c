#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

unsigned long long *_multisum = NULL;

typedef struct _add_handle{
    int n;
    unsigned long long min;
    unsigned long long max;
} _add_handle;

void *thread_add(void *_add_sum){
    _add_handle* add_sum = _add_sum;
    unsigned long long tmp = 0;
    for (unsigned long long i = add_sum->min; i < add_sum->max + 1; i++){
        tmp += i;
    }
    _multisum[add_sum->n] = tmp;
    pthread_exit(NULL);
}

unsigned long long multisum(unsigned long long m, int n){
    unsigned long long result = 0;
    _multisum = (unsigned long long *)malloc(n * sizeof(unsigned long long));
    pthread_t threads[n];
    _add_handle add_index[n];
    for (int i = 0; i < n - 1; i++) {
        add_index[i].min = (m / n) * i + 1;
        add_index[i].max = (m / n) * ( i + 1 );
        add_index[i].n = i;
        int ret = pthread_create(&threads[i], NULL, thread_add, (void*)&(add_index[i]));
        if (ret != 0){
            printf("pthread creat error:%d\n", ret);
            exit(-1);
        }
    }
    add_index[n-1].min = (m / n) * ( n - 1 ) + 1;
    add_index[n-1].max = m;
    add_index[n-1].n = n - 1;
    int ret = pthread_create(&threads[n-1], NULL, thread_add, (void*)&(add_index[n-1]));
    if(ret != 0){
        printf("pthread creat error:%d\n", ret);
        exit(-1);
    }
    for(int i = 0; i < n; i++){
        pthread_join(threads[i], NULL);
        result += _multisum[i];
    }
    return result;
}

unsigned long long char_to_long(char *num){
    char c;
    unsigned long long result = 0;
    while(*num){
        if(*num != '\n'){
            result *= 10;
            result += *num - '0';
        }
        num++;
    }
    return result;
}

void read_config(char *file_name, unsigned long long *config){
    FILE *fp;
    char line[20];
    if ((fp = fopen(file_name, "r")) == NULL){
        printf("open file failed!\n");
        exit(-1);
    }
    fgets(line, 20, fp);
    if(line[0]=='N'||line[0]=='n'){
        config[0] = char_to_long(line + 2);
        fgets(line, 20, fp);
        config[1] = char_to_long(line + 2);
    }
    else{
        config[1] = char_to_long(line + 2);
        fgets(line, 20, fp);
        config[0] = char_to_long(line + 2);
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    struct timeval start, end;
    if(argc != 2){
        printf("error param number!\n");
        return 0;
    }
    unsigned long long config[2];
    read_config(argv[1], config);

    if(config[0] < 1 || config[1] < 1 || config[0] > 100 || config[0] > 4294967295){
        printf("100 > N > 0 and 4294967296 > M > 0\n");
        return 0;
    }

    gettimeofday(&start, NULL);
    unsigned long long result = multisum(config[1], (int)config[0]);
    gettimeofday(&end, NULL);

    FILE* fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "%lld", result);
    fclose(fp);
    printf("N=%lld, M=%lld\n",config[0], config[1]);
    printf("result: %lld\n", result);
    printf("use time:%fms\n", (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec)/1000.0);
    if(result == (1 + config[1]) * config[1] / 2){
        printf("True!\n");
    }
    else printf("False!\n");
    return 0;
}
