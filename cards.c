#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    if (argc < 6 || argc > 7) {
        printf("ERROR");
        return 1;
    }

    printf("%d", is_a_card(argv[1]));
}
