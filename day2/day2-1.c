#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30

#define MAX_RED     12
#define MAX_GREEN   13
#define MAX_BLUE    14

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
    int gameSum = 0;				// sum of all gameIDs determined to be possible
    char gameID = 0;				// current game ID
    char line[256] = "";			// current line from input file

    // open input file
    FILE* in = fopen("D:\\Desktop\\Aoc\\day2\\input.txt", "rb");
    int gamecount = get_gamecount(in);
    printf("Total games played: %d\n", gamecount);

    // read lines from input file
    while (fgets(line, 256, in)) {
    	// find the newline and replace with null
        char* end = strrchr(line, '\n');
        *end = '\0';
        
        char* gamedata = strchr(line, ':') + 2; // trim off the characters to and including the ':'
        char* trial = strtok(gamedata, ";");	// tokenize each trial using delimiter';'

        bool possible = true;					// game is possible; keep processing
        ++gameID;

        // proccess each trial from the game
        while (trial != NULL && possible == true) {
        	// boundaries of current string for while loop condition
            char* cur = trial;
            char* end = trial + strlen(trial) - 1;

            int count = 0; // number of blocks; color determined by following string

            // parse the current trial string
            while (cur < end && possible == true) {
                if (*cur == ' ' || *cur == ',') {
                    cur++;	// skip spaces and commas
                }

                // parse digits in string, convert to integer type, and assign to count
                else if (isdigit(*cur)) {
                    count = *cur - ASCII_OFFSET;
                    if (isdigit(*(cur + 1))) {	// check for double digit numbers
                        count *= 10;
                        count += *(cur + 1) - ASCII_OFFSET;
                        cur++;
                    }
                    cur++;
                }

                // assign the block count to the appropriate color
                // check that each color/count combo doesn't exceed the maximum
                else if (strncmp(cur, "red", strlen("red")) == 0) {
                    if (count > MAX_RED) {
                        possible = false;
                        break;
                    }
                    cur += strlen("red");
                    count = 0;
                }
                else if (strncmp(cur, "green", strlen("green")) == 0) {
                    if (count > MAX_GREEN) {
                        possible = false;
                        break;
                    }
                    cur += strlen("green");
                    count = 0;
                }
                else if (strncmp(cur, "blue", strlen("blue")) == 0) {
                    if (count > MAX_BLUE) {
                        possible = false;
                        break;
                    }
                    cur += strlen("blue");
                    count = 0;
                }
                else {
                    cur++;	// move to the next character if no digit or matching color string
                }
            }
            trial = strtok(NULL, ";");	// move to the next trial
        }

        // add gameID to total if game was possible
        if (possible == true) {
            gameSum += gameID;
        }
    }

    printf("Sum of game ID's from possible games: %d\n", gameSum);
}
