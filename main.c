#include <stdio.h>
#include <time.h>

unsigned long long big_sqrt(unsigned long long A) {
    unsigned long long MIN = 0;
    unsigned long long MAX = ((unsigned long long) 1) << 32; // multiply llu of 1 by 32-bit int of 2 pow 32 to get llu of 9,223,372,036,854,775,807

    while(1) {
        if (MAX <= MIN + 1)
             return MIN;

        unsigned long long SQT = MIN + (MAX - MIN) / 2;
        unsigned long long SQ = SQT * SQT; // multiply is faster than square

        if (SQ == A) 
             return SQT;

        if (SQ > A)
             MAX = SQT;
        else
             MIN = SQT;
    }
}

void find_primes(unsigned long long *PRIMES, unsigned long long PRIMES_TO_FIND, unsigned short WRITE_TO_FILE) {	
	FILE *FP;
	FP = fopen("primes.log", "w+"); 
	PRIMES[0] = 2; // first prime is 2
    unsigned long long NEXT = 1; // next number to check = 1, will be changed later
    unsigned long long PRIMES_FOUND = 1; // already found prime 2
    clock_t BEGIN = clock(); // get current clock and store
    unsigned short MODE = 0;
    unsigned long long LOOP;
    printf("Finding primes. . .\n");
    while (1) {
        if (PRIMES_FOUND >= PRIMES_TO_FIND) 
			break;
        // Primes that are not 2 or 3 follow 6k (+/-) 1
        NEXT += 2 + 2 * (MODE == 3);
        MODE += 1 - 2 * (MODE == 3);
        unsigned short IS_PRIME = 1;
        // Divide number with found primes to check primality.
        for (LOOP = 0; LOOP < PRIMES_FOUND - 1; LOOP++) {
            unsigned long long PRIME = PRIMES[LOOP];
            if (PRIME > big_sqrt(NEXT))
				break;
            if (NEXT % PRIME == 0) {
                IS_PRIME = 0;
                break;
            }
        }

        if (IS_PRIME & 1) {
            PRIMES[PRIMES_FOUND] = NEXT;
            ++PRIMES_FOUND;
        }
    }

    printf("Found %llu primes in %lf seconds\n", PRIMES_FOUND, (double)(clock() - BEGIN) / CLOCKS_PER_SEC);

	if (WRITE_TO_FILE & 1) {
        BEGIN = clock();
        printf("Writing. . .\n");
        for (LOOP = 0; LOOP < PRIMES_FOUND; LOOP++)
            fprintf(FP, "%llu\n", PRIMES[LOOP]);
        printf("Finished writing to file in %lf seconds.\n", (double)(clock() - BEGIN) / CLOCKS_PER_SEC);
    }
	fclose(FP);
}

int main() {
    static unsigned long long PRIMES[100000000];
	unsigned long long PRIMES_TO_FIND;
	printf("How many primes to find?: ");
	scanf("%llu", &PRIMES_TO_FIND);
    getchar();
	printf("\n");
	unsigned short WRITE_TO_FILE;
	printf("Write to file? (1/0): ");
	scanf("%hu", &WRITE_TO_FILE);
    getchar();
    printf("\n\n\n");
    find_primes(PRIMES, PRIMES_TO_FIND, WRITE_TO_FILE);
    printf("\nPress ENTER to continue. . .");
    getchar();
    return 0;
}