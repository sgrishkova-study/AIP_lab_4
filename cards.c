#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define AMOUNT_OF_CARDS 5

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

int main(int argc, char *argv[]) {
    // Check whether the number of arguments is right
    if (argc < 6 || argc > 7) {
        printf("ERROR");
        return 1;
    }

    // Check if the cards are, in fact, cards
    for (int i = 1; i < 6; i++) {
        if (is_a_card(argv[i]) == false) {
            printf("ERROR");
            return 1;
        }
    }

    if (has_duplicates(&argv[1])) {
        printf("ERROR");
        return 1;
    }
}
