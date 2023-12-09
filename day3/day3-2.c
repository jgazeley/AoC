#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30

typedef struct {
    int value;
    int pos;
    size_t length;
    int line;
} Number;

typedef struct {
    char value;
    int pos;
    int line;
    int adj_part_numbers_count;
    char adj_part_numbers[32];
    bool is_gear;
    long gear_ratio;
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
    long sum = 0;

    // open input file
    FILE* in = fopen("D:\\Desktop\\Aoc\\day3\\input.txt", "rb");

    // read a line
    while (fgets(line, 256, in)) {
        ++line_number;
        char* cur = line;
        char* end = line + strlen(line) - 1;
        while (cur < end) {
            if (isdigit(*cur)) {
                currentnumber->value = *cur - ASCII_OFFSET;
                currentnumber->pos = cur - line;
                currentnumber->length = 1;
                currentnumber->line = line_number;
                cur++;
                while (isdigit(*cur)) {
                    currentnumber->value *= 10;
                    currentnumber->value += *cur - ASCII_OFFSET;
                    currentnumber->length++;
                    cur++;
                }
                //printf("Line #%d\n", currentnumber->line);
                //printf("Number value  = %d\n", currentnumber->value);
                //printf("Number offset = %d\n", currentnumber->pos);
                //printf("Number length = %d\n", currentnumber->length);
                numcount++;
                currentnumber++;
            }
            else {
                if (*cur == '*') {
                    currentsymbol->value = *cur;
                    currentsymbol->pos = cur - line;
                    currentsymbol->line = line_number;
                    currentsymbol->adj_part_numbers_count = 0;
                    memset(currentsymbol->adj_part_numbers, 0, 32);
                    currentsymbol->is_gear = false;
                    currentsymbol->gear_ratio = -1;
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
    currentnumber = nums;
    currentsymbol = syms;
    // print the length of the line
    printf("Line length: %zu\n\n", strlen(line));
    Number* lastnumber = nums + numcount;
    Symbol* lastsymbol = syms + symbolcount;
    for (currentsymbol; currentsymbol <= lastsymbol; currentsymbol++) {
        for (currentnumber; currentnumber < lastnumber; currentnumber++) {
            if (currentsymbol->line - 1 == currentnumber->line || currentsymbol->line + 1 == currentnumber->line || currentsymbol->line == currentnumber->line) {
                int digitIndex = 0;
                for (digitIndex = currentnumber->pos; digitIndex < currentnumber->pos + currentnumber->length; digitIndex++) {
                    if (digitIndex == currentsymbol->pos || digitIndex == currentsymbol->pos - 1 || digitIndex == currentsymbol->pos + 1) {
                        //printf("Number %d is adjacent to %c\n", currentnumber->value, currentsymbol->value);
                        currentsymbol->adj_part_numbers_count++;
                        char ascii[16] = "";
                        _itoa(currentnumber->value, ascii, 10);
                        strcat(currentsymbol->adj_part_numbers, ascii);
                        strcat(currentsymbol->adj_part_numbers, ";");
                        break;
                    }
                }
            }
        }
        if (currentsymbol->adj_part_numbers_count == 2) {
            currentsymbol->gear_ratio = 1;
            currentsymbol->is_gear = true;
            char* pns = currentsymbol->adj_part_numbers;
            char* part = strtok(pns, ";");
            while (part != NULL) {
                //printf("%s\n", part);
                int n = atoi(part);
                currentsymbol->gear_ratio *= n;
                part = strtok(NULL, ";");
            }
        }
        currentnumber = nums;
    }
    currentsymbol = syms;
    for (currentsymbol; currentsymbol < lastsymbol; currentsymbol++) {
        if (currentsymbol->is_gear) {
            sum += currentsymbol->gear_ratio;
        }
    }
    printf("The sum of the gear ratios is %lu", sum);
    free(nums);
    free(syms);
}