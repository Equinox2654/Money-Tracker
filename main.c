#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *balance;
    FILE *balance_file;
    FILE *log;
    char balance_text[17];
    double balance_amount = 0.0;

    balance = fopen("balance.txt", "a");
    fclose(balance);

    balance_file = fopen("balance.txt", "r");
    fgets(balance_text, 17, balance_file);
    fclose(balance_file);

    balance_amount = strtod(balance_text, NULL);
    if (argc == 1) printf("Balance: %.2f\n", balance_amount);

    if (argc == 3) {
	log = fopen("log.txt", "a");
	if (strcmp(argv[1], "add") == 0) {
	    double amount_to_add = strtod(argv[2], NULL);
	    balance_amount += amount_to_add;
	    fprintf(log, "Added: %.2f\n", amount_to_add);
	}
	else if (strcmp(argv[1], "spend") == 0) {
	    double amount_to_reduce = strtod(argv[2], NULL);
	    balance_amount -= amount_to_reduce;
	    fprintf(log, "Spent: %.2f\n", amount_to_reduce);
	}
	fclose(log);
    }

    if (strcmp(argv[1], "help") == 0) {
	printf("Tracks money:\nAdd: command adds money\nSpend: command spends money\n\nYou have $%.2f left.\n", balance_amount);
    }

    if (argc >= 3) printf("Balance: %.2f\n", balance_amount);

    balance_file = fopen("balance.txt", "w");
    fprintf(balance_file, "%.2f\n", balance_amount);
    fclose(balance_file);

    return 0;
}
