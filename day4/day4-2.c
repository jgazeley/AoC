#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define ASCII_OFFSET 0x30
#define WINNER_COUNT 10
#define MYPICK_COUNT 25

typedef struct {
	unsigned char number;		// card identifying number
	char matches;				// number of matches this card has
	int instances;				// number of instances of this card
	int* winners;				// pointer to this card's winning numbers
	int* mypicks;				// pointer to my number picks for this card
} Card;

Card* read_cards_from_file(const char* file_name, int* count);
void initialize_card(Card* card, int line_number, char* line);
int count_matches(Card* card);
void print_cardinfo(Card* card);

int main()
{
	const char* file_name = "D:\\Desktop\\AoC\\day4\\input.txt";
	Card* cards;			// pointer to scratchcards
	int card_count = 0;		// number of scratchcards

	// get the pointer to the first scratchcard
	cards = read_cards_from_file(file_name, &card_count);

	//printf("Initial number of scratchcards = %d\n", card_count);

	// count matches
	for (int i = 0; i < card_count; i++) {
		(cards + i)->matches = count_matches(cards + i);
	}

	// count instances
	unsigned int i;	// iterator for current card
	unsigned int j; // iterator for how many matches current card has
	unsigned int k; // iterator for how many instances there are of the current card
	for (i = 0; i < card_count; i++) {
		for (k = 0; k < (cards + i)->instances; k++) {
			for (j = 1; j <= (cards + i)->matches; j++) {
				(cards + i + j)->instances++;
			}
		}
	}

	//print card information
	for (int i = 0; i < card_count; i++) {
		print_cardinfo(cards + i);
	}

	int total_cards = 0;
	for (int i = 0; i < card_count; i++) {
		total_cards += (cards + i)->instances;
	}

	printf("Answer: %d\n", total_cards);
	free(cards);
}

Card* read_cards_from_file(const char* file_name, int* count)
{
	Card* cards = NULL;
	char line[256] = { 0 };

	// open input file
	FILE* in = fopen(file_name, "rb");

	while (fgets(line, 256, in)) {
		Card* temp = realloc(cards, sizeof(Card) * (*count + 1));
		if (!temp) {
			// Handle memory allocation failure
			fclose(in);
			free(cards);
			return NULL;
		}

		cards = temp;
		initialize_card(cards + *count, *count + 1, line);
		(*count)++;
	}

	fclose(in);
	return cards;
}

void initialize_card(Card* card, int line_number, char* line)
{
	card->winners = malloc(sizeof(int) * WINNER_COUNT);
	card->mypicks = malloc(sizeof(int) * MYPICK_COUNT);
	card->number = line_number;
	card->instances = 1;	// each card has at least one instance

	memset(card->winners, 0x0, sizeof(int) * WINNER_COUNT);
	memset(card->mypicks, 0x0, sizeof(int) * MYPICK_COUNT);

	char* cur = line + strlen("Card   x: ");
	char* end = strrchr(line, '\n');

	int i = 0;    // iterator for current winner/pick value
	bool is_winner = true;
	while (cur < end) {
		if (*cur == '|') {
			is_winner = false;
			i = 0;	
		}
		if (isdigit(*cur)) {

			while (isdigit(*cur)) {
				int* current_number;

				if (is_winner) {
					current_number = card->winners + i;
				}

				else {
					current_number = card->mypicks + i;
				}

				if (*(current_number) == 0) {
					*(current_number) = *cur - ASCII_OFFSET;
				}

				else {
					*(current_number) *= 10;
					*(current_number) += *cur - ASCII_OFFSET;
				}
				cur++;
			}
			i++;
		}
		cur++;
	}
}

int count_matches(Card* card)
{
	int matches = 0;
	for (int i = 0; i < WINNER_COUNT; i++) {
		for (int j = 0; j < MYPICK_COUNT; j++) {
			if (*(card->mypicks + j) == *(card->winners + i))
				matches++;
		}
	}
	return matches;
}

void print_cardinfo(Card* card)
{
	printf("Card [%d] {\n", card->number);

	printf("  winners = ");
	for (int i = 0; i < WINNER_COUNT; i++) {
		printf("%d,", *(card->winners + i));
	}
	printf("\b \n");

	printf("  my picks = ");
	for (int i = 0; i < MYPICK_COUNT; i++) {
		printf("%d,", *(card->mypicks + i));
	}
	printf("\b \n");

	printf("  matches = %d\n", card->matches);
	printf("  instances = %d\n", card->instances);
	printf("}\n");
}
