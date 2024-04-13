#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_CARDS 15
#define heart 03                 // Used to print heart symbol
#define diamond 04               // Used to print diamond symbol
#define club 05                  // Used to print club symbol
#define spade 06                 // Used to print spade symbol
#define newline printf("\n")
#define clear system("cls")

//                  0    1    2    3    4    5    6    7    8     9    10   11   12   13
char cards[][3] = { " ", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
char colours[][10] = { "heart", "diamond", "club", "spade" };
char** player_cards, ** player_colours, ** dealer_cards, ** dealer_colours;

char* getCard() {

    int n = rand() % 13 + 1;
    return cards[n];
}

char* getColour() {

    int n = rand() % 4;
    return colours[n];
}

int getScore(char* str, int score) {

    if (strcmp(str, "J") == 0 || strcmp(str, "Q") == 0 || strcmp(str, "K") == 0)
        return 10;
    else if (strcmp(str, "A") == 0) {
        if (score <= 10) return 11;
        else return 1;
    }
    return atoi(str);
}

void freeMemory() {

    free(player_cards);
    free(player_colours);
    free(dealer_cards);
    free(dealer_colours);
}

void getSymbol(char* str) {

    if (strcmp(str, "heart") == 0)
        printf("\x1B[31m%c\033[0m", heart);

    else if (strcmp(str, "diamond") == 0)
        printf("\x1B[31m%c\033[0m", diamond);

    else if (strcmp(str, "club") == 0)
        printf("%c", club);

    else
        printf("%c", spade);
}

void allocateMemory() {

    player_cards = (char**)malloc(MAX_CARDS * sizeof(char*));
    player_colours = (char**)malloc(MAX_CARDS * sizeof(char*));
    dealer_cards = (char**)malloc(MAX_CARDS * sizeof(char*));
    dealer_colours = (char**)malloc(MAX_CARDS * sizeof(char*));

    if (player_cards == NULL || player_colours == NULL || dealer_cards == NULL || dealer_colours == NULL) {
        fprintf(stderr, "    Memory allocation error. \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_CARDS; i++) {
        player_cards[i] = (char*)malloc(3 * sizeof(char));
        player_colours[i] = (char*)malloc(10 * sizeof(char));
        dealer_cards[i] = (char*)malloc(3 * sizeof(char));
        dealer_colours[i] = (char*)malloc(10 * sizeof(char));

        if (player_cards[i] == NULL || player_colours[i] == NULL || dealer_cards[i] == NULL || dealer_colours[i] == NULL) {
            fprintf(stderr, "    Memory allocation error. \n");
            exit(EXIT_FAILURE);
        }
    }
}

char getplayAgainOption() {

    char answer;
    do {
        printf("    Do you want to play again? (y/n) : ");
        answer = getch();
        answer = tolower(answer);
        if (answer != 'y' && answer != 'n')
            printf("    invalid. \n");
    } while (answer != 'y' && answer != 'n');
    return answer;
}

int getUserBalance() {

    int balance;
    while (1) {
        printf("    enter balance: $");
        if (scanf("%d", &balance) != 1 || balance <= 0) {
            printf("    invalid balance. \n");
            while (getchar() != '\n');
        }
        else break;
    }
    return balance;
}

int getUserBet(int balance) {

    int bet;
    while (1) {
        printf("    How much you wanna bet? : ");
        if (scanf("%d", &bet) != 1 || bet > balance || bet <= 0) {
            printf("    invalid bet. \n");
            while (getchar() != '\n');
        }
        else break;
    }
    return bet;
}

int getMenuOption() {

    int option;
    while (1) {
        printf("\n\t\t\t\t\tEnter option: ");
        if (scanf("%d", &option) != 1 && (option != 1 || option != 2 || option != 3)) {
            printf("    invalid option. \n");
            while (getchar() != '\n');
        }
        else break;
    }
    return option;
}

char getUserOption() {

    char opt;
    do {
        printf("    Enter option ( H for hit / S for stand ):");
        opt = getch();
        opt = tolower(opt);
        if (opt != 'h' && opt != 's')
            printf("    invalid option. \n");
    } while (opt != 'h' && opt != 's');
    return opt;
}

void showMenu() {

    printf("     .--------------.  .--------------.  .--------------.  .--------------.  .--------------. \n");
    printf("     |   ______     |  |   _____      |  |      __      |  |     ______   |  |  ___  ____   | \n");
    printf("     |   |_   _ \\   |  |  |_   _|     |  |     /  \\     |  |   .' ___  |  |  | |_  ||_  _|  | \n");
    printf("     |    | |_) |   |  |    | |       |  |    / /\\ \\    |  |  / .'   \\_|  |  |   | |_/ /    | \n");
    printf("     |    |  __'.   |  |    | |   _   |  |   / ____ \\   |  |  | |         |  |   |  __'.    | \n");
    printf("     |   _| |__) |  |  |   _| |__/ |  |  | _/ /    \\ \\_ |  |  \\ `.___.'\\  |  |  _| |  \\ \\_  | \n");
    printf("     |  |_______/   |  |  |________|  |  ||____|  |____||  |   `._____.'  |  | |____||____| | \n");
    printf("     |              |  |              |  |              |  |              |  |              | \n");
    printf("     '--------------'  '--------------'  '--------------'  '--------------'  '--------------' \n");

    printf("              .--------------.  .--------------.  .--------------.  .--------------. \n");
    printf("              |     _____    |  |      __      |  |     ______   |  |  ___  ____   | \n");
    printf("              |    |_   _|   |  |     /  \\     |  |   .' ___  |  |  | |_  ||_  _|  | \n");
    printf("              |      | |     |  |    / /\\ \\    |  |  / .'   \\_|  |  |   | |_/ /    | \n");
    printf("              |   _  | |     |  |   / ____ \\   |  |  | |         |  |   |  __'.    | \n");
    printf("              |  | |_' |     |  | _/ /    \\ \\_ |  |  \\ `.___.'\\  |  |  _| |  \\ \\_  | \n");
    printf("              |  `.___.'     |  ||____|  |____||  |   `._____.'  |  | |____||____| | \n");
    printf("              |              |  |              |  |              |  |              | \n");
    printf("              '--------------'  '--------------'  '--------------'  '--------------' \n");
    printf("\n");
    printf("                                          (1) - play \n");
    printf("                                          (2) - rules \n");
    printf("                                          (3) - exit \n\n");
}

void showRules() {

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BlackJack ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("    Players aim to reach a hand value closer to 21 than the dealer's without exceeding it. \n");
    printf("    Blackjack pays 3 to 1. \n");
    printf("    Dealer must stand on 17 and must draw to 16. \n");
    printf("    Cards 2-10 are valued at face value, while face cards (Jack, Queen, King) count as 10 points each. \n");
    printf("    Aces can be valued at 1 or 11. \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void play() {

    srand(time(NULL));
    int balance = getUserBalance();

    while (1) {
        allocateMemory();
        char opt;
        int bet, player_score = 0, dealer_score = 0;
        int cnt_player = 0, cnt_dealer = 0;
        clear;
        printf("    your balance : $%d \n", balance);
        bet = getUserBet(balance);
        balance -= bet;

        player_cards[cnt_player] = getCard(); // Get player's first card
        player_colours[cnt_player++] = getColour(); /// Get colour of player's first card
        player_cards[cnt_player] = getCard(); // Get player's second card
        player_colours[cnt_player++] = getColour(); // Get colour of player's second card

        dealer_cards[cnt_dealer] = getCard(); // Get dealer's first card
        dealer_score += getScore(dealer_cards[cnt_dealer], dealer_score); // Get dealer's score
        dealer_colours[cnt_dealer++] = getColour(); // Get colour of dealer's first card
        clear;

        // Show player's hand
        printf("\n\n    you have: %s ", player_cards[0]); getSymbol(player_colours[0]); // First card
        printf("  %s ", player_cards[1]); getSymbol(player_colours[1]); // Second card

        // Show player's score
        player_score += getScore(player_cards[0], player_score) + getScore(player_cards[1], player_score);
        printf("  (score : %d)\n", player_score);

        // Show dealer's hand and dealer's score
        printf("\n    dealer have: %s ", dealer_cards[0]); getSymbol(dealer_cards[0]);
        printf("  (score : %d)\n\n\n", dealer_score);

        // Blackjack from first hand
        if (player_score == 21) {
            balance += (3 * bet);
            printf("\x1B[32m    BLACKJACK. (pays 3 to 1). \n \033[0m");
            printf("\n\n  Your new balance : $%d. ", balance);
            if (getplayAgainOption() == 'y') continue;
            else {
                printf("    Gooooooddbyeeee. \n");
                return 0;
            }
        }
        do {
            opt = getUserOption();
            if (opt == 'h') { // Hit
                // Draw a new card and its colour for the player
                player_cards[cnt_player] = getCard();
                player_score += getScore(player_cards[cnt_player], player_score);
                player_colours[cnt_player++] = getColour();

                // Show all of the player's cards
                for (int i = 0; i < cnt_player; i++) {
                    printf("  %s ", player_cards[i]);
                    getSymbol(player_colours[i]);
                }
                printf("  (score: %d)\n", player_score);

                // If the player's score is 21, they win
                if (player_score == 21) {
                    printf("\x1B[32m    Congratulations! You won. \n \033[0m");
                    balance += (2 * bet); break;
                }

                // If the player's score is 21, they lose
                if (player_score > 21) {
                    printf("\x1B[31m    Uups! You lost. \n \033[0m");
                    break;
                }
            }
            else if (opt == 's') { // Stand
                int dealer_hits = 0;

                // Dealer must stand on 17 and must draw to 16.
                while (dealer_score <= 16) {

                    // Draw a new card and its colour for the dealer
                    dealer_cards[cnt_dealer] = getCard(); dealer_hits++;
                    dealer_score += getScore(dealer_cards[cnt_dealer], player_score);

                    printf("\n    dealer hit (#%d) .", dealer_hits); 
                    printf(" : %s ", dealer_cards[cnt_dealer]);

                    getSymbol(dealer_colours[cnt_dealer]);
                    printf(" (score: %d) \n", dealer_score);
                    dealer_colours[cnt_dealer++] = getColour();
                }
                if (dealer_score > 21) {
                    printf("\x1B[32m    Dealer bust. You won! \n \033[0m");
                    balance += (2 * bet); break;
                }
                else {
                    if (player_score == dealer_score) {
                        printf("\x1B[33m    Tie. You get your bet back. \n \033[0m");
                        balance += bet; break;
                    }
                    else if (player_score > dealer_score) {
                        printf("\x1B[32m    You won. Your score is higher. \n \033[0m");
                        balance += (2 * bet); break;
                    }
                    else { printf("\x1B[31m    Sorry, You lost . . \n \033[0m"); break; }
                }
            }
        } while (player_score < 21);

        printf("\n\n    Your new balance : $%d. ", balance);

        if (getplayAgainOption() == 'y') {
            if (balance == 0)
                printf("    sorry you have no money left. byee. \n\n");
            continue;
        }
        else { printf("\x1B[33m    you left with $%d gooooooddbyeeee. \n \033[0m", balance); break; }
        freeMemory();
    }
}

int main()
{
    int opt, ruleOption;
    while (1)
    {
        showMenu();
        opt = getMenuOption();
        switch (opt)
        {
            case 1:
            {
                clear;
                play();
                break;
            }
            case 2:
            {
                clear;
                showMenu();
                showRules();
                ruleOption = getMenuOption();
                if (ruleOption == 1) {
                    play();
                    break;
                }
                if (ruleOption == 3) {
                    clear;
                    break;
                }
                break;
            }
            case 3:
            {
                printf("\n\t\t\t\t\t   Goodbye. \n");
                exit(0);
            }
        }
    }
    return 0;
}
