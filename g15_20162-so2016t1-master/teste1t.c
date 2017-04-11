#ifdef _WIN32
#include <windows.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <unistd.h>
#endif

int getNumCores() {
#ifdef WIN32
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
#elif MACOS
	int nm[2];
	size_t len = 4;
	uint32_t count;

	nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
	sysctl(nm, 2, &count, &len, NULL, 0);

	if(count < 1) {
		nm[1] = HW_NCPU;
		sysctl(nm, 2, &count, &len, NULL, 0);
		if(count < 1) { count = 1; }
	}
	return count;
#else
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}


#include "calcula.h"
#include "simpletest.h"

void test1();
void test2();
void test3();
void test4();

int main() {
	test1();
	test2();
	test3();
	test4();
	return 0;
}

void test1(){
	int threads = getNumCores() + 1;
    DESCRIBE("PARALELO - 50 lines");
    WHEN("TEST1");
    IF("teste1.txt");
    THEN("the result should be 100");
	//clock_t begin = clock();
	isEqual(ocorrencias("teste1.txt","ll", threads),100);
	/*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f \n", time_spent);*/
}
void test2(){
	int threads = getNumCores() + 1;
    DESCRIBE("PARALELO - 5.000 lines");
    WHEN("TEST2");
    IF("teste2.txt");
    THEN("the result should be 10.000");
	//clock_t begin = clock();
	isEqual(ocorrencias("teste2.txt","ll", threads),10000);
	/*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f \n", time_spent);*/
}
void test3(){
	int threads = getNumCores() + 1;
    DESCRIBE("PARALELO - 25.000 lines");
    WHEN("TEST3");
    IF("teste3.txt");
    THEN("the result should be 50.000");
	//clock_t begin = clock();
	isEqual(ocorrencias("teste3.txt","ll", threads),50000);
	/*clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Elapsed time: %f \n", time_spent);*/
}
void test4(){
	int threads = getNumCores() + 1;
    DESCRIBE("PARALELO - 50.000 lines");
    WHEN("TEST4");
    IF("teste4.txt");
    THEN("the result should be 100.000");
	//clock_t begin = clock();
	isEqual(ocorrencias("teste4.txt","ll", threads),100000);
	/*clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Elapsed time: %f \n", time_spent);*/
}
