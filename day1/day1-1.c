#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ASCII_OFFSET 0x30

int main()
{
	FILE* in = fopen("D:\\Desktop\\AoC\\day1\\input.txt", "rb");
	fseek(in, 0, SEEK_END);
	size_t fsize = ftell(in);
	rewind(in);
	char* data = malloc(fsize * sizeof(char));
	fread(data, fsize, 1, in);

	char* currentChar = data;
	int sum = 0;
	int bytesRead = 0;

	while (bytesRead < fsize) {
		char firstDigit = 0;
		char lastDigit = 0;
		char twoDigit = 0;
		while (*currentChar != '\n') {
			bool isNum = false;
			if (*currentChar > '0' && *currentChar < ':') {
				isNum = true;
			}
			if (isNum && firstDigit == 0) {
				firstDigit = *currentChar - ASCII_OFFSET;
			}
			if (isNum) {
				lastDigit = *currentChar - ASCII_OFFSET;
			}
			currentChar++;
			bytesRead++;
		}
		twoDigit = (firstDigit * 10) + lastDigit;
		sum += twoDigit;
		currentChar++;
		bytesRead++;
	}
	
	printf("Answer: %d\n", sum);
}