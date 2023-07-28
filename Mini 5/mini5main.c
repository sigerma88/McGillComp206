#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mini5phone.h"

/**
 * This is a C file containing the main function for the phonebook program.
 * The menu function used for the execution of the program is also here.
 * The memory for the phonebook is dynamically allocated into a linked list.
 *
 * @author Kevin Luo
 *         Department: McGill, Faculty of Engineering, ECSE, Software Engineering
 *         McGill ID: 261038261
 *         Email: kevin.luo@mail.mcgill.ca
 * @author Siger Ma
 *         Department: McGill, Faculty of Engineering, ECSE, Software Engineering
 *         McGill ID: 261051828
 *         Email: siger.ma@mail.mcgill.ca
 * @author Stefan Wallin
 *         Department: McGill, Faculty of Science, School of Computer Science
 *         McGill ID: 261056176
 *         Email: stefan.wallin@mail.mcgill.ca
 */

/*
 * Displays the menu prompt and accepts input of the user
 *
 * @return option - Menu option selected by user
 */
void menu()
{
	printf("Phonebook Menu: (1)Add, (2)Delete/Clear, (3)Find, (4)List, (5)Quit> ");
}

/*
 * Main function and entry point to the program.
 *
 * @return errorCode
 */
int main()
{
	int loadingStatus, savingStatus, addRecordStatus;
	char option = 0;

	// Load CSV file
	loadingStatus = loadCSV();
	if (loadingStatus == 2)
	{
		printf("Error while loading file.\n");
		return 1;
	}

	while (option != '5')
	{
		// Display menu
		menu();

		// Get menu selection input from user
		option = getchar();
		if (option == '\n')
			continue;
		while ('\n' != getchar())
			;
		printf("\n");

		switch (option)
		{
		case '1':
			char name[50];
			char birthdate[12];
			char phone[15];

			// Get name input
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
			addRecordStatus = addRecord(name, birthdate, phone);
			if (addRecordStatus != 0)
			{
				printf("Error while adding record.\n");
			}
			break;
		case '2':
			if (loadingStatus != 0 && phonebookHead == NULL)
			{
				printf("phonebook.csv does not exist\n");
			}
			else
			{
				char option;

				// Getting option selected by user
				printf("(D)elete or (C)lear> ");
				option = getchar();
				if (option == '\n')
					continue;
				while ('\n' != getchar())
					;
				option = toupper(option);
				printf("\n");

				// Delete
				if (option == 'D')
				{
					char name[50];

					// Get name input
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
					printf("\n");

					if (delete (name) == 1)
					{
						printf("Sorry not found\n");
					}
				}

				// Clear
				else if (option == 'C')
				{
					char clearConfirmation;

					// Getting clearConfirmation
					printf("Are you sure (Y/N)> ");
					clearConfirmation = getchar();
					if (clearConfirmation == '\n')
						continue;
					while ('\n' != getchar())
						;
					clearConfirmation = toupper(clearConfirmation);
					printf("\n");

					if (clearConfirmation == 'Y')
					{
						clear();
					}
				}
			}
			break;
		case '3':
			if (loadingStatus != 0 && phonebookHead == NULL)
			{
				printf("phonebook.csv does not exist\n");
			}
			else
			{
				char name[50];

				// Get name input
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

				struct PHONE_NODE *phoneRecord = findRecord(name);
				if (phoneRecord == NULL)
				{
					printf("Does not exist\n");
				}
				else
				{
					printf("----------------------NAME----------------------- ---BIRTH--- ----PHONE-----\n");
					printf("%-49s %-11s %-14s\n",
								 phoneRecord->name,
								 phoneRecord->birthdate,
								 phoneRecord->phone);
				}
			}
			break;
		case '4':
			if (loadingStatus != 0 && phonebookHead == NULL)
			{
				printf("phonebook.csv does not exist\n");
			}
			else
			{
				listRecords();
			}
			break;
		case '5':
			break;
		default:
			printf("Sorry wrong selection!\n");
		}
	}

	// Store CSV file
	savingStatus = saveCSV();
	if (savingStatus == 1)
	{
		printf("Error while saving file.\n");
		return 1;
	}

	// End of program
	clear();
	printf("End of phonebook program\n");
	return 0;
}
