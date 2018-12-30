#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
using namespace std;
int factorial(int n)
{
	if(n == 1)
		return 1;
	else
		return n * factorial(n - 1);
}
int factorial2(int n, int result)
{
	if(n == 1)
		return result;
	else
		return factorial2(n - 1, n * result);
}

int main ()
{
	int n = 20;
	float time, start;
	start = clock();
	unsigned long long result1 = factorial(n);
	time = clock() - start;
	printf("factorial1: task was finished!costTime1 : %f\n", time/CLOCKS_PER_SEC);
	printf("result1: %lld\n", result1);

	start = clock();
	unsigned long long result2 = factorial2(n,1);
	time = clock() - start;
	printf("factorial2: task was finished!costTime2 : %f\n", time/CLOCKS_PER_SEC);
	printf("result2: %lld\n", result2);
	return 0;
}
