#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *balance;
    FILE *balance_file;
    FILE *log;
    char balance_text[17];
    double balance_amount = 0.0;

    FILE *items;
    items = fopen("items.txt", "a"); fclose(items);

    balance = fopen("balance.txt", "a"); fclose(balance);

    balance_file = fopen("balance.txt", "r");
    if (!balance_file) { perror("Error opening balance file"); return 1; }
    fgets(balance_text, 17, balance_file);
    if (ferror(balance_file)) { perror("Error reading from balance file"); return 1;}
    fclose(balance_file);

    balance_amount = strtod(balance_text, NULL);
    if (argc == 1) printf("Balance: %.2f\n", balance_amount);

    log = fopen("log.txt", "a");
    if (!log) { perror("Error Opening Log"); return 1; }

    if (argc == 3) {
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
    }

    if (argc == 5) {
	if (strcmp(argv[1], "budget") == 0) {
	    items = fopen("items.txt", "rb");
	    if (!items) { perror("Error Opening File"); return 1; }

	    fseek(items, 0, SEEK_END);
	    long file_size = ftell(items);
	    rewind(items);

	    char *buffer = (char *)malloc(file_size + 1);
	    if (!buffer) {
		perror("Memory allocation failed: Checking Items");
		fclose(items);
		return 1;
	    }

	    size_t bytesRead = fread(buffer, 1, file_size, items);
	    if (bytesRead < file_size && ferror(items)) {
		perror("Error reading file");
		free(buffer);
		fclose(items);
		return 1;
	    }
	    buffer[bytesRead] = '\0';

	    if (strcmp(argv[2], "check") == 0) {
		/// <Important>TODO: Finish</Important>
	    }
	    else if (strcmp(argv[2], "add") == 0) {
		char *item = argv[3];
		int cost = strtod(argv[4], NULL);
		if (!cost) {
		    perror("Invalid pricing for item");
		    return 1;
		}
		fprintf(items, "%s: %d\n", item, cost);
		printf("%s: %d\n", item, cost);
	    }
	    free(buffer);
	    fclose(items);
	}
    }

    fclose(log);

    if (strcmp(argv[1], "help") == 0) {
	printf("Tracks money:\nAdd: command adds money\nSpend: command spends money\n\nYou have $%.2f left.\n", balance_amount);
    }

    if (argc >= 3) printf("\nBalance: %.2f\n", balance_amount);

    balance_file = fopen("balance.txt", "w");
    if (!balance_file) { perror("Error open balance file"); return 1; }
    fprintf(balance_file, "%.2f\n", balance_amount);
    if (ferror(balance_file)) { perror("Error writing to balance file"); return 1; }
    fclose(balance_file);

    return 0;
}
