#include <string.h>
#include <stdio.h>

char *digits[] = {
	"one","two","three","four","five", "six","seven","eight","nine",
	"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen",
	"seventeen","eighteen","nineteen"
};
char *tens[] = {
	"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"
};

void three_digits(char *str, unsigned int v)
{
	if (v > 99) {
		strcat(str,digits[v/100-1]);
		strcat(str,"hundred");
		v %= 100;
	}
	if (v > 19) {
		strcat(str,tens[v/10-2]);
		v %= 10;
	}
	if (v > 0)
		strcat(str,digits[v-1]);
}
 
void number_to_words(char *str, unsigned int v)
{
	strcpy(str,"");
	if (v > 999999) {
		three_digits(str, v/1000000);
		strcat(str, "million");
		v %= 1000000;
	}
	if (v > 999) {
		three_digits(str, v/1000);
	       	strcat(str, "thousand");
		v %= 1000;
	}
	three_digits(str,v);
}

const int max_words_length = 100;  // Real max is 87 + a null
