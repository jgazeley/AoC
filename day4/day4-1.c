#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30

int main()
{
	// open input file
	FILE* in = fopen("D:\\Desktop\\AoC\\day4\\input.txt", "rb");
	int* winners = malloc(sizeof(int) * 32);
	int* mypicks = malloc(sizeof(int) * 32);

	int* current_winner = winners;
	int* current_pick = mypicks;
	size_t winner_count = 0;
	size_t pick_count = 0;
	int card_number = 0;

	int score = 0;

	char card[256] = { 0 };
	while (fgets(card, 256, in)) {
		
		char* cur = card + strlen("Card   x: ");
		char* end = strrchr(card, '\n');
		int current_number = 0;
		bool is_winner = true;

		while (cur < end) {
			if (*cur == '|') {
				is_winner = false;
			}

			if (isdigit(*cur)) {

				while (isdigit(*cur)) {
					current_number *= 10;
					current_number += *cur - ASCII_OFFSET;
					cur++;
				}

				if (is_winner) {
					*current_winner = current_number;
					current_winner++;
					winner_count++;
				}

				else {
					*current_pick = current_number;
					current_pick++;
					pick_count++;
				}

				current_number = 0;
			}

			else {
				cur++;
			}
		}
		//printf("Card %d\n", ++card_number);

		// get the score of the current card
		int current_score = 0;
		current_winner = winners;
		bool first_match = true;
		for (current_pick = mypicks; current_pick < mypicks + pick_count; current_pick++) {
			while (current_winner < winners + winner_count) {
				if (*current_winner == *current_pick) {
					// first match is worth 1 point
					if (first_match) {
						current_score += 1;
						first_match = false;
					}
					// score doubles for each subsequent match
					else current_score *= 2;
					
					//printf("%d is the current score \n", current_score);
				}
				current_winner++;
			}
			current_winner = winners;
		}

		// total the score and reset the variables
		current_pick = mypicks;
		score += current_score;
		memset(winners, 0, 32);
		memset(mypicks, 0, 32);
		pick_count = 0;
		winner_count = 0;
	}
	printf("Answer: %d\n", score);
}