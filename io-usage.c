#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

static inline
long blocks_to_kb(int blocks) {
	/*
	 * Assume blocks are 512 bytes, so just divine by two rounding up.
     * Also assume blocks >= 0.
	 */
	return blocks / 2 + (blocks&1);
}

int main(int argc, char** argv) {
    int ret = system(argv[1]);
    struct rusage rusage;
    getrusage(RUSAGE_CHILDREN, &rusage);
    printf("kb in:\t%li\n"
		   "kb out:\t%li\n",
            blocks_to_kb(rusage.ru_inblock),
			blocks_to_kb(rusage.ru_oublock));
}
