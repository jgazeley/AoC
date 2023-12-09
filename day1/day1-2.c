#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30
#define MAX_STRING 256

int main()
{
	char* strDigits[10] = { "zero","one","two","three","four","five","six","seven","eight","nine" };

	// open input file
	FILE* in = fopen("input.txt", "rb");

	// create buffer for strings
	char* line = malloc(MAX_STRING);
	char* translated = malloc(MAX_STRING);
	memset(translated, 0, MAX_STRING);
	char firstDigit = 0;
	char lastDigit = 0;
	unsigned int sum = 0;

	while (fgets(line, MAX_STRING, in)) {
		int index = 0;
		memset(translated, 0, MAX_STRING);
		while (index < strlen(line)) {
			if (isdigit(*(line + index))) {
				strncat(translated, line + index, 1);
				index++;
			}
			else {
				bool numStr = false;
				for (int i = 0; i < 10; i++) {
					if (strncmp(line + index, strDigits[i], strlen(strDigits[i])) == 0) {
						char int2str[2] = "";
						strcat(translated, _itoa(i, int2str, 10));
						index += strlen(strDigits[i]) - 1;
						numStr = true;
					}
				}
				if (!numStr) {
					index++;
				}
			}
		}
		firstDigit = translated[0] - ASCII_OFFSET;
		lastDigit = translated[strlen(translated) - 1] - ASCII_OFFSET;
		int bothDigits = (firstDigit * 10) + lastDigit;
		sum += bothDigits;
	}

	printf("Answer: %d", sum);
}