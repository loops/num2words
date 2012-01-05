#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

#define BASE 999
#define MIDDLE (BASE * 2)
#define HIGH (BASE * 3)

typedef struct {
	unsigned int num;
	unsigned int len;
} WORDS;

const char* defstr=	"#define BASE 999\n"
			"#define MIDDLE (BASE * 2)\n"
			"#define HIGH (BASE * 3)\n"
			"\n"
			"typedef struct {\n"
			"	unsigned int num;\n"
			"	unsigned int len;\n"
			"} WORDS;\n"
			"\n";

unsigned int length(unsigned int v)
{
	char tmp[max_words_length];
	number_to_words(tmp,v);
	return strlen(tmp);
}

int compare(const void *a, const void *b)
{
	char ta[max_words_length], tb[max_words_length];
	number_to_words(ta,((WORDS*) a)->num);
	number_to_words(tb,((WORDS*) b)->num);
	return strcmp(ta,tb);
}

void dump(const WORDS* table, const unsigned int size, const char *name)
{
	const int stride = 6;
	printf("WORDS %s[] = {\n", name);
	for (int i=0; i<size; i+=stride) {
		printf("  ");
		for (int x=i; x<size && x<i+stride; ++x)
			printf("{%d,%d}%s",	table[x].num,
						table[x].len,
						x+1<size ? "," : "");
		printf("\n");
	}
	printf("};\n");
}

void generate_data()
{
	WORDS low[BASE], mid[MIDDLE], hi[HIGH];

	for (int i=0,l=1,m=1000,h=1000000;i<BASE;++i,l+=1,m+=1000,h+=1000000) {
		low[i].num=l;		low[i].len=length(l);
		mid[i+BASE].num=m;	mid[i+BASE].len=length(m);
		hi[i+MIDDLE].num=h;	hi[i+MIDDLE].len=length(h);
		hi[i]=low[i];		hi[i+BASE]=mid[i+BASE];
		mid[i]=low[i];
	}

	printf("%s", defstr);

	qsort(low, BASE, sizeof(WORDS), compare);
	dump(low,BASE,"base");

	qsort(mid, MIDDLE, sizeof(WORDS), compare);
	dump(mid,MIDDLE,"middle");

	qsort(hi, HIGH, sizeof(WORDS), compare);
	dump(hi,HIGH,"high");
}

int main()
{
	generate_data();
	return 0;
}
