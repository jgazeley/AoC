#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30


int get_gamecount(FILE* in)
{
    char line[256] = "";
    int gamecount = 0;

    while (fgets(line, 256, in)) {
        gamecount++;
    }

    rewind(in);
    return gamecount;
}

int main()
{
    int gameSum = 0;                // sum of the powers of the sets of minimum cubes per game
    char gameID = 0;                // current game ID
    char line[256] = "";            // current line from input file

    // minimum r/g/b count for each game, -1 means value hasn't been initialized
    int min_red = -1;
    int min_green = -1;
    int min_blue = -1;

    // open input file
    FILE* in = fopen("D:\\Desktop\\Aoc\\day2\\input.txt", "rb");
    int gamecount = get_gamecount(in);
    printf("Total games played: %d\n", gamecount);

    // read lines from input file
    while (fgets(line, 256, in)) {
        // find the newline and replace with null
        char* end = strrchr(line, '\n');
        *end = '\0';

        char* gamedata = strchr(line, ':') + 2; // trim off characters up to and including ':'
        char* trial = strtok(gamedata, ";");    // tokenize each trial using delimiter ';'

        min_red = -1;
        min_green = -1;
        min_blue = -1;

        ++gameID;
 //       printf("Game #%d\n", gameID);

        // proccess each trial from the game
        while (trial != NULL) {
            // boundaries of current string for while loop condition
            char* cur = trial;
            char* end = trial + strlen(trial) - 1;

            int count = 0; // number of blocks; color to be determined

            // parse the current trial string
            while (cur < end) {
                if (*cur == ' ' || *cur == ',') {
                    cur++;  // skip spaces and commas
                }

                // parse digits in string, convert to integer type, and assign to count
                else if (isdigit(*cur)) {
                    count = *cur - ASCII_OFFSET;
                    if (isdigit(*(cur + 1))) {  // check for double digit numbers
                        count *= 10;
                        count += *(cur + 1) - ASCII_OFFSET;
                        cur++;
                    }
                    cur++;
                }

                // assign the block count to the appropriate color
                else if (strncmp(cur, "red", strlen("red")) == 0) {
                    if (min_red == -1) {
                        min_red = count;
                    }
                    else if (min_red < count) {
                        min_red = count;
                    }
                    cur += strlen("red");
                    count = 0;
                }
                else if (strncmp(cur, "green", strlen("green")) == 0) {
                    if (min_green == -1) {
                        min_green = count;
                    }
                    else if (min_green < count) {
                        min_green = count;
                    }
                    cur += strlen("green");
                    count = 0;
                }
                else if (strncmp(cur, "blue", strlen("blue")) == 0) {
                    if (min_blue == -1) {
                        min_blue = count;
                    }
                    else if (min_blue < count) {
                        min_blue = count;
                    }
                    cur += strlen("blue");
                    count = 0;
                }
                else {
                    cur++;  // move to the next character if no digit or matching color string
                }
            }
            trial = strtok(NULL, ";");  // move to the next trial
        }
        int power = min_red * min_green * min_blue;
        // printf("Min red:   %d\n", min_red);
        // printf("Min green: %d\n", min_green);
        // printf("Min blue:  %d\n", min_blue);
        // printf("Power:     %d\n", power);
        gameSum += power;
    }

    printf("Sum of the power of the set of minimum cubes: %d\n", gameSum);
}
