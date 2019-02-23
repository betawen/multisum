multisum: thread/multisum.c process/multisum.c
	gcc thread/multisum.c -o thread/multisum
	gcc process/multisum.c -o process/multisum

test:
	sh test.sh input
	