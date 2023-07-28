#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini4Bphone.c"

/**
 * This is a C file containing the main function for the phonebook program.
 * The menu function used for the execution of the program is also here.
 * The memory for the phonebook is dynamically allocated.
 *
 * @author Siger Ma
 *         Department: McGill, Faculty of Engineering, ECSE, Software Engineering
 *         McGill ID: 261051828
 *         Email: siger.ma@mail.mcgill.ca
 */

/*
 * Displays the menu prompt and accepts input of the user
 *
 * @return option - Menu option selected by user
 */
int menu()
{
	// Print out menu
	printf("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit> ");

	// Get input from user
	char option = getchar();
	if (option == '\n')
		return 0;
	while ('\n' != getchar())
		;

	printf("\n");
	return option;
}

/*
 * Main function that calls mini4Bphone.c functions and the menu.
 * Also asks for the phonebook size.
 * It loops until 4 is selected from the menu.
 */
int main()
{
	int numberOfRecords = 0, phonebookSize = 0, loadingStatus, savingStatus, addRecordStatus;
	char sizeInput[12];

	// Ask for phonebook size
	while (phonebookSize < 1)
	{
		printf("Size of phonebook: ");
		if (fgets(sizeInput, sizeof(sizeInput), stdin) == NULL)
			continue;
		// Remove left over input
		if (sizeInput[strlen(sizeInput) - 1] != '\n' && sizeInput[strlen(sizeInput) - 1] != '\0')
		{
			int leftover;
			while ((leftover = getchar()) != '\n' && leftover != EOF)
				;
		}
		if (sscanf(sizeInput, "%d", &phonebookSize) != 1)
			continue;
	}
	printf("\n");

	// Allocate space for phonebook memory buffer
	phonebook = (struct PHONE_RECORD *)calloc(phonebookSize, sizeof(struct PHONE_RECORD));
	if (phonebook == NULL)
	{
		printf("Array to large! Program terminated.\n");
		return 1;
	}

	// Load CSV file
	loadingStatus = loadCSV(&numberOfRecords, phonebookSize);
	if (loadingStatus == 2)
	{
		printf("Error while loading file.\n");
		return 1;
	}

	// Call menu to get option selection from user
	char option = 0;
	while (option != '4')
	{
		option = menu();
		switch (option)
		{
		case '1':
			// Check current size of array
			if (numberOfRecords >= phonebookSize)
			{
				printf("No more space in the CSV file.\n");
				break;
			}

			// Get name input
			char name[50];
			do
			{
				printf("Name: ");
			} while (fgets(name, sizeof(name), stdin) == NULL);
			// Remove left over input
			if (name[strlen(name) - 1] != '\n' && name[strlen(name) - 1] != '\0')
			{
				int leftover;
				while ((leftover = getchar()) != '\n' && leftover != EOF)
					;
			}
			// Remove trailing newline character
			name[strcspn(name, "\n\0")] = '\0';
			if (strlen(name) == 0)
			{
				printf("No empty field allowed\n");
				break;
			}
			printf("\n");

			// Get birthdate input
			char birthdate[12];
			do
			{
				printf("Birth: ");
			} while (fgets(birthdate, sizeof(birthdate), stdin) == NULL);
			// Remove left over input
			if (birthdate[strlen(birthdate) - 1] != '\n' && birthdate[strlen(birthdate) - 1] != '\0')
			{
				int leftover;
				while ((leftover = getchar()) != '\n' && leftover != EOF)
					;
			}
			// Remove trailing newline character
			birthdate[strcspn(birthdate, "\n\0")] = '\0';
			if (strlen(birthdate) == 0)
			{
				printf("No empty field allowed\n");
				break;
			}
			printf("\n");

			// Get phone input
			char phone[15];
			do
			{
				printf("Phone: ");
			} while (fgets(phone, sizeof(phone), stdin) == NULL);
			// Remove left over input
			if (phone[strlen(phone) - 1] != '\n' && phone[strlen(phone) - 1] != '\0')
			{
				int leftover;
				while ((leftover = getchar()) != '\n' && leftover != EOF)
					;
			}
			// Remove trailing newline character
			phone[strcspn(phone, "\n\0")] = '\0';
			if (strlen(phone) == 0)
			{
				printf("No empty field allowed\n");
				break;
			}
			printf("\n");

			// Add record
			addRecordStatus = addRecord(&numberOfRecords, phonebookSize, name, birthdate, phone);
			if (addRecordStatus != 0)
			{
				printf("Error while adding record.\n");
			}
			break;
		case '2':
			if (loadingStatus != 0 && numberOfRecords == 0)
			{
				printf("phonebook.csv does not exist\n");
			}
			else
			{
				// Get name input
				char name[50];
				do
				{
					printf("Find name: ");
				} while (fgets(name, sizeof(name), stdin) == NULL);
				// Remove left over input
				if (name[strlen(name) - 1] != '\n' && name[strlen(name) - 1] != '\0')
				{
					int leftover;
					while ((leftover = getchar()) != '\n' && leftover != EOF)
						;
				}
				// Remove trailing newline character
				name[strcspn(name, "\n\0")] = '\0';
				printf("\n");

				int index = findRecord(&numberOfRecords, name);
				if (index == -1)
				{
					printf("Does not exist\n");
				}
				else
				{
					printf("----------------------NAME----------------------- ---BIRTH--- ----PHONE-----\n");
					printf("%-49s %-11s %-14s\n",
								 (phonebook + index)->name,
								 (phonebook + index)->birthdate,
								 (phonebook + index)->phone);
				}
			}
			break;
		case '3':
			if (loadingStatus != 0 && numberOfRecords == 0)
			{
				printf("phonebook.csv does not exist\n");
			}
			else
			{
				listRecords(&numberOfRecords);
			}
			break;
		}
	}

	// Store CSV file
	savingStatus = saveCSV(&numberOfRecords);
	if (savingStatus == 1)
	{
		printf("Error while saving file.\n");
		return 1;
	}

	// End of program
	free(phonebook);
	printf("End of phonebook program\n");
	return 0;
}

