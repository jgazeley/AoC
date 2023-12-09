#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30

typedef struct {
    int value;      // numerical value
    int pos;        // position in file horizontally
    size_t digits;  // amount of digits in number
    int line;       // line that number was found on
} Number;

typedef struct {
    char value;     // character * & % $ etc.
    int pos;        // position in file horizontally
    int line;       // line that symbol was found on
} Symbol;

int main()
{
    Number* nums = malloc(sizeof(Number) * 2048);
    Number* currentnumber = nums;
    int numcount = 0;

    Symbol* syms = malloc(sizeof(Symbol) * 2048);
    Symbol* currentsymbol = syms;
    int symbolcount = 0;

    char line[256] = "";
    int line_number = 0;
    int sum = 0;

    // open input file
    FILE* in = fopen("D:\\Desktop\\Aoc\\day3\\input.txt", "rb");

    // read a line
    while (fgets(line, 256, in)) {
        ++line_number;
        char* cur = line;
        char* end = line + strlen(line) - 1;

        // find numbers and symbols
        while (cur < end) {
            if (isdigit(*cur)) {
                currentnumber->value = *cur - ASCII_OFFSET;
                currentnumber->pos = cur - line;
                currentnumber->digits = 1;
                currentnumber->line = line_number;
                cur++;
                while (isdigit(*cur)) {
                    currentnumber->value *= 10;
                    currentnumber->value += *cur - ASCII_OFFSET;
                    currentnumber->digits++;
                    cur++;
                }
                //printf("Line #%d\n", currentnumber->line);
                //printf("Number value  = %d\n", currentnumber->value);
                //printf("Number offset = %d\n", currentnumber->pos);
                //printf("Number digits = %d\n", currentnumber->digits);
                numcount++;
                currentnumber++;
            }
            else {
                if (*cur != '.' && *cur != '\n') { 
                    currentsymbol->value = *cur;
                    currentsymbol->pos = cur - line;
                    currentsymbol->line = line_number;
                    //printf("Line #%d\n", currentsymbol->line);
                    //printf("Symbol value  = %c\n", currentsymbol->value);
                    //printf("Symbol offset = %d\n", currentsymbol->pos);
                    currentsymbol++;
                    symbolcount++;
                }
                cur++;
            }
        }
    }

    // print the length of the lines
    printf("Line length: %zu\n\n", strlen(line));

    // reset nums and syms pointer and find end pointers
    Number* lastnumber = nums + numcount;
    Symbol* lastsymbol = syms + symbolcount;
    currentnumber = nums;
    currentsymbol = syms;

    // find adjacent numbers/symbols and sum them up
    for (currentsymbol; currentsymbol <= lastsymbol; currentsymbol++) {
        for (currentnumber; currentnumber < lastnumber; currentnumber++) {
            if (currentsymbol->line -1 == currentnumber->line || currentsymbol->line +1 == currentnumber->line || currentsymbol->line == currentnumber->line) {
                int digitIndex = 0;
                for (digitIndex = currentnumber->pos; digitIndex < currentnumber->pos + currentnumber->digits; digitIndex++) {
                    if (digitIndex == currentsymbol->pos || digitIndex == currentsymbol->pos -1 || digitIndex == currentsymbol->pos +1) {
                         //printf("Number %d is adjacent to %c\n", currentnumber->value, currentsymbol->value);

                        sum += currentnumber->value;
                        break;
                    }
                }
            }
        }
        currentnumber = nums;
    }
    printf("The sum of the engine part numbers is: %d\n", sum);
    free(syms);
    free(nums);
}