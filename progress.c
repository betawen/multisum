#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ULLONG unsigned long long
#define MAXM 4294967296
#define MAXN 100
// ····················································
int params[2];  // 输入参数组

ULLONG multisum (ULLONG M, int n) {
	pid_t pid[n];
	int i;
	int pipe[n][2];
	ULLONG multisum = 0;
	for (int i = 0; i < n; i++){
		// 初始化管道,成功返回-，失败返回1；0为读取端，1为写入端
		int pip = pipe(pipe[i]);
		if (pip < 0) {
			printf("PIPE FAILED\n");
			return -1;
		}
	}
	for (int j = 0; j < n; j++) {
		// 初始化线程，
		// 父进程返回正值，子进程返回0值，错误返回负值
		pid[i] = folk();
		if (pid[i] < 0) {
			printf("FOLK FAILED\n");
			return -1;
		}
		if (pid[i] == 0) {
			close(pipe[1][0]);
			ULLONG tmp = 0, start = m / n * i + 1, end = m / n * i + 1;
			if (i == n-1 ) {
				end = m;
			}
			tmp = start;
			while (tmp <= end) {
				tmp ++;
			}
			// 写入管道
			write(pipe[i][1], &tmp, sizeof(tmp));
			return 0;
		}
	}
	for (int k = 0; k < n; k++) {
		close(pipe[k][1]);
		// 等待子进程退出
		waitpid(pid[k], NULL, 0);
		ULLONG tmp = 0;
		// 从管道读取
		read(pipe[k][0], &tmp, sizeof(tmp));
		multisum += tmp;
	}
	return multisum;
}

void fileRead (char *filePath) {
	FILE *fp;
	char line[20][2];
	char readLine[20];
	fp = fopen( filePath, 'r');
	if (fp == NULL) {
		printf('FILE READ FAILED\n');
		return -1;
	}
	fgets(readLine, 20, fp);
	if(realLine[0] == 'N') {

	}
}