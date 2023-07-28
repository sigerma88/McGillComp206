#include <stdio.h>

/**
 * This is a C program that asks for three space separated numbers after the program is run.
 * It detects if the numbers are strictly increasing from left to right and if the last two
 * numbers are divisible by the first number.
 *
 * @stdin 3 space separated integers
 * @return 0 - They are divisible and increasing
 *         1 - They are not divisible and increasing
 *         2 - They are divisible and not increasing
 *         3 - They are not divisible and not increasing
 *         4 - The stdin is wrong
 * @author Siger Ma
 *         Department: McGill, Faculty of Engineering, ECSE, Software Engineering
 *         McGill ID: 261051828
 *         Email: siger.ma@mail.mcgill.ca
 */

int main(void) {
	int divisor, dividendOne, dividendTwo;
	int isIncreasing = 0;
	int isDivisible = 0;

	// Prompt and get inputs from the user
	printf("Please input three numbers: ");
	int numOfArgs = scanf("%d %d %d", &divisor, &dividendOne, &dividendTwo);
	
	// Input validation
	if (numOfArgs != 3) {
		printf("Please input three numbers that are space separated\n");
		return 4;
	}

	// Check for increasing
	if (divisor < dividendOne && dividendOne < dividendTwo) {
		isIncreasing = 1;
	}

	// Check for divisible
	if (divisor != 0 && dividendOne % divisor == 0 && dividendTwo % divisor == 0) {
		isDivisible = 1;
	}
	
	// Return result
	if (isDivisible && isIncreasing) {
		printf("Divisible & Increasing\n");
		return 0;
	}
	else if (!isDivisible && isIncreasing) {
		printf("Not divisible & Increasing\n");
		return 1;
	}
	else if (isDivisible && !isIncreasing) {
		printf("Divisible & Not increasing\n");
		return 2;
	}
	else {
		printf("Not divisible & Not increasing\n");
		return 3;
	}
}

