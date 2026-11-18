#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AMOUNT_OF_CARDS 5
#define AMOUNT_OF_FLAGS 1
#define MIN_AMOUNT_OF_ARGUMENTS (AMOUNT_OF_CARDS + 1)
#define MAX_AMOUNT_OF_ARGUMENTS (AMOUNT_OF_CARDS + AMOUNT_OF_FLAGS + 1)
#define TARGET_SUM 15
#define WEIGHT_OF_A 1
#define WEIGHT_OF_JQK 10

bool flag_correct(const char input[]) {
    if (strcmp(input, "1") == 0 || strcmp(input, "0") == 0) return true;
    return false;
}

bool has_duplicates(char *cards[]) {
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        for (int j = i + 1; j < AMOUNT_OF_CARDS; j++) {
            if (strcmp(cards[i], cards[j]) == 0) {
                return true;
            }
        }
    }

    return false;
}

bool is_a_card(const char * card) {
    size_t len = strlen(card);
    if (len < 2 || len > 3) return false;

    const char first_letters[] = "AJQK23456789";
    const char second_letters[] = "HCSD";

    if (len == 2 && (strchr(first_letters, card[0]) == NULL || strchr(second_letters, card[1]) == NULL)) return false;
    if (len == 3 && (card[0] != '1' || card[1] != '0' || strchr(second_letters, card[2]) == NULL)) return false;

    return true;
}

bool input_is_bad(int argc, char * argv[]) {
    // Check whether the number of arguments is right
    if (argc < MIN_AMOUNT_OF_ARGUMENTS || argc > MAX_AMOUNT_OF_ARGUMENTS) {
        return true;
    }

    // Check if the cards are, in fact, cards
    for (int i = 1; i < MIN_AMOUNT_OF_ARGUMENTS; i++) {
        if (is_a_card(argv[i]) == false) {
            return true;
        }
    }

    // Check if the cards are from the same suit
    if (has_duplicates(&argv[1])) {
        return true;
    }

    return false;
}

void convert_cards_to_weights(char * cards[], unsigned short weights[]) {
    for (int i = 0; i < AMOUNT_OF_CARDS; i++) {
        if (strlen(cards[i]) == 3) {
            weights[i] = 10;
        } else {
            if (cards[i][0] == 'A') {
                weights[i] = WEIGHT_OF_A;
            } else if (strchr("JQK", cards[i][0]) != NULL) {
                weights[i] = WEIGHT_OF_JQK;
            } else {
                weights[i] = atoi(&cards[i][0]);
            }
        }
    }
}

void count_combinations(unsigned short weights[], unsigned short *combinations, unsigned short sum, unsigned short i) {
    if (sum < 0 || i >= AMOUNT_OF_CARDS) {
    } else if (sum - weights[i] == 0) {
        *combinations += 1;
        count_combinations(weights, combinations, sum, i + 1);
    } else {
        count_combinations(weights, combinations, sum, i + 1);
        count_combinations(weights, combinations, sum - weights[i], i + 1);
    }
}

int main(int argc, char *argv[]) {
    if (input_is_bad(argc, argv) == true) {
        printf("ERROR");
        return 1;
    }

    unsigned short flag = 0;

    if (argc == MAX_AMOUNT_OF_ARGUMENTS) {
        if (flag_correct(argv[MAX_AMOUNT_OF_ARGUMENTS - 1]) == true) {
            flag = atoi(argv[MAX_AMOUNT_OF_ARGUMENTS - 1]);
        } else {
            printf("ERROR");
            return 1;
        }
    }

    unsigned short weights[AMOUNT_OF_CARDS] = {0};
    unsigned short combinations = 0;
    convert_cards_to_weights(&argv[1], weights);
    count_combinations(weights, &combinations, TARGET_SUM, 0);

    printf("%d\n", combinations);
    return 0;
}