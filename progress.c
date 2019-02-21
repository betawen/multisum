#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ULLONG unsigned long long
#define MAXM 4294967296
#define MAXN 100
// ····················································
ULLONG params[2];  // 输入参数组

ULLONG multisum (ULLONG m, int n) {
	pid_t pid[n];
	int i;
	int j;
	int k;
	int pipes[n][2];
	ULLONG multisum = 0;
	for (i = 0; i < n; i++){
		// 初始化管道,成功返回-，失败返回1；0为读取端，1为写入端
		int pip = pipe(pipes[i]);
		if (pip < 0) {
			printf("PIPE FAILED\n");
			return -1;
		}
	}
	for (j = 0; j < n; j++) {
		// 初始化线程，
		// 父进程返回正值，子进程返回0值，错误返回负值
		pid[j] = fork();
		if (pid[j] < 0) {
			printf("FOLK FAILED\n");
			return -1;
		}
		if (pid[j] == 0) {
			close(pipes[j][0]);
			ULLONG tmp = 0, start = m / n * j + 1, end = m / n * j + 1;
			if (i == n-1 ) {
				end = m;
			}
			tmp = start;
			while (tmp <= end) {
				tmp ++;
			}
			// 写入管道
			write(pipes[j][1], &tmp, sizeof(tmp));
			return 0;
		}
	}
	for (k = 0; k < n; k++) {
		close(pipes[k][1]);
		// 等待子进程退出
		waitpid(pid[k], NULL, 0);
		ULLONG tmp = 0;
		// 从管道读取
		read(pipes[k][0], &tmp, sizeof(tmp));
		multisum += tmp;
	}
	return multisum;
}

void fileRead (char *filePath) {
	printf("start\n");
	printf("%s\n", filePath);
	FILE *fp;
	char readLine[20];
	int i;
	fp = fopen(filePath, "r");
	printf("fopen ok\n");
	if (fp == NULL) {
		printf('FILE READ FAILED\n');
		exit(-1);
	}
	ULLONG line1;
	ULLONG line2;
	while(!feof(fp)) {
	fscanf(fp, "M=%lld", &line1);
	fscanf(fp, "M=%lld", &line2);
	printf("%lld\n", line1);
	printf("%lld\n", line2);
	printf("reading......\n");
	}
	printf("readline ok\n");
	printf("%lld\n", line1);
	printf("%lld\n", line2);
	params[0] = line1;
	params[1] = line2;
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
