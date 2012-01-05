#include <stdlib.h>
#include "data.h"
#include "convert.h"

void print_as_words(unsigned int v)
{
	char tmp[max_words_length];
	number_to_words(tmp,v);
	printf("%s", tmp);
}

static unsigned int icount;
static unsigned long sum, ccount;

inline static int target_reached(const unsigned long count)
{
	return count >= 51000000000L;
}

inline static void yield(unsigned int number, unsigned int length)
{
	++icount;
	sum += number;
	ccount += length;
	if (target_reached(ccount)) {
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
	// Don't iterate this million if we can just account for it in bulk
	unsigned long fast = 44872000L + length * 999999L;
	if (!target_reached(ccount + fast)) {
		ccount += fast;
		icount += 999999;
		sum += 499999500000L;
		sum += 999999L * (unsigned long) number;
		return;
	}

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
