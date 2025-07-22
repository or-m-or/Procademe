#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned long myseed = 1L;

int myrand(void) {
    myseed = myseed * 214013L + 2531011L;
    return (myseed >> 16) & 0x7fff; // RAND_MAX: 32767 (0x7fff)
}

void mysrand(unsigned int seed) {
    myseed = (unsigned long)seed;
}

int main()
{
    srand(10); // srand(time(NULL));
    
    for (int i = 0; i < 10; i++)
    {
        int a = rand(); //f11
        printf("%d \n", a);
	}


	mysrand(10); // mysrand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        int a = myrand();
        printf("%d \n", a);
	}

    return 0;
}