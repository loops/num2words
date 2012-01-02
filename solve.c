#include <stdlib.h>
#include "data.h"
#include "convert.h"

inline static void yield(unsigned int number, unsigned int length)
{
	static unsigned long sum, ccount;
	static unsigned int icount;

	++icount;
	sum += number;
	ccount += length;
	if (ccount >= 51000000000L) {
		printf("Final Integer: %u\n", number);
		printf("Written as: "); print_as_words(number); printf("\n");
		printf("Integer Sum: %lu\n", sum);
		printf("Character Count: %lu\n", ccount);
		printf("Number of integers: %u\n", icount);
		exit(0);
	}
}

inline static void thousands(unsigned int number, unsigned int length)
{
	for (int i=0; i<BASE; ++i)
		yield(number + base[i].num, length + base[i].len);
}

inline static void millions(unsigned int number, unsigned int length)
{
	for (int i=0; i<MIDDLE; ++i) {
		unsigned int mn = middle[i].num;
		unsigned int tn = number + mn, tl = length + middle[i].len;
		yield(tn, tl);
		if (mn > 999)
			thousands(tn,tl);
	}
}

inline static void iterate_sorted_word_numbers()
{
	for (int i=0; i<HIGH; ++i) {
		unsigned int hn = high[i].num, hl = high[i].len;
		yield(hn, hl);
		if (hn > 999999)
			millions(hn,hl);
		else if (hn > 999)
			thousands(hn,hl);
	}
}

int main()
{
	iterate_sorted_word_numbers();
	return 1;
}
