#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

unsigned long long multisum(unsigned long long m, int n){
    pid_t pid[n];
    int i,j;
    unsigned long long k;
    int pip[n][2];
    unsigned long long result = 0;
    for(j = 0; j < n; j++){
        if(pipe(pip[j]) < 0){
            printf("Failed to create pipe!\n");
            return 0;
        }
    }
    for(i = 0; i < n; i++){
        pid[i] = fork();
        if(pid[i] < 0){
            printf("Failed to create process!\n");
            return 0;
        }
        else if(pid[i] == 0){
            close(pip[i][0]);
            unsigned long long tmp = 0;
            unsigned long long start = (m / n) * i + 1;
            unsigned long long end = (m / n) * (i + 1);
            if ( i == (n - 1)) end = m;
            for (k = start; k <= end; k++){
                tmp += k;
            }
            write(pip[i][1], &tmp, sizeof(tmp));
            return -1;
        }  
    }
    for(j = 0; j < n; j++){
        close(pip[j][1]);
        waitpid(pid[j], NULL, 0);
        unsigned long long tmp = 0;
        read(pip[j][0], &tmp, sizeof(tmp));
        result += tmp;
    }
    return result;
}

unsigned long long char_to_long(char *num){
    char c;
    unsigned long long result = 0;
    while (*num)
    {
        if (*num != '\n')
        {
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
    if (argc != 2){
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
    if(result == -1) return 0;
    gettimeofday(&end, NULL);

    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "%lld", result);
    fclose(fp);
    printf("N=%lld, M=%lld\n", config[0], config[1]);
    printf("result: %lld\n", result);
    printf("use time:%fms\n", (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec) / 1000.0);
    if (result == (1 + config[1]) * config[1] / 2){
        printf("True!\n");
    }
    else
        printf("False!\n");
    return 0;
}
