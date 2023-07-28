#include <stdio.h>
#include <string.h>

/**
 * This is a C file containing the functions used by mini4Bmain.c.
 * It will be compiled into the program phonebook.
 * It contains loadCSV, saveCSV, addRecord, findRecord.
 *
 * @author Siger Ma
 *         Department: McGill, Faculty of Engineering, ECSE, Software Engineering
 *         McGill ID: 261051828
 *         Email: siger.ma@mail.mcgill.ca
 */

/*
 * Data structure used to store and buffer the records
 */
struct PHONE_RECORD
{
	char name[50];
	char birthdate[12];
	char phone[15];
} *phonebook;

/*
 * Load data structure from the CSV database
 *
 * @param numberOfRecords - Pointer to number of records in the buffer
 *        phonebookSize - Size of the phonebook allocated
 * @return 0 - Success
 *         1 - Error no file
 *         2 - Error while loading the file
 */
int loadCSV(int *numberOfRecords, int phonebookSize)
{
	// Open file
	FILE *phonebookCSV;
	phonebookCSV = fopen("phonebook.csv", "r");

	// Detect if file exists
	if (phonebookCSV == NULL)
	{
		return 1;
	}

	// Skip the first line (header)
	char header[100];
	fgets(header, 100, phonebookCSV);

	// Store it into memory
	for (int i = 0; i < phonebookSize && !feof(phonebookCSV); i++)
	{
		// Read file
		fscanf(phonebookCSV,
					 "%49[^,],%11[^,],%14[^\n]\n",
					 phonebook[i].name,
					 phonebook[i].birthdate,
					 phonebook[i].phone);

		// Detect if error occurs
		if (ferror(phonebookCSV))
		{
			return 2;
		}

		// Update number of records
		*numberOfRecords = i + 1;
	}

	// close file
	fclose(phonebookCSV);

	return 0;
}

/*
 * Save data structure to the CSV database
 *
 * @param numberOfRecords - Pointer to number of records in the buffer
 * @return 0 - Success
 *         1 - Error while saving
 */
int saveCSV(int *numberOfRecords)
{
	// Open file
	FILE *phonebookCSV;
	phonebookCSV = fopen("phonebook.csv", "w");

	// Write the first line (header)
	fprintf(phonebookCSV, "Name,birthdate,phone");

	// Store it into the file
	for (int i = 0; i < *numberOfRecords; i++)
	{
		// Read file
		fprintf(phonebookCSV,
						"\n%s,%s,%s",
						(phonebook + i)->name,
						(phonebook + i)->birthdate,
						(phonebook + i)->phone);

		// Detect if error occurs
		if (ferror(phonebookCSV))
		{
			return 1;
		}
	}

	// close file
	fclose(phonebookCSV);

	return 0;
}

/*
 * Add a new phone entry to the data structure
 *
 * @param numberOfRecords - Pointer to the number of records in the buffer
 *        phonebookSize - Size of the phonebook allocated
 *        name - Pointer to the name of the record to be added
 *        birthdate - Pointer to the birthdate of the record to be added
 *        phone - Pointer to the phone of the record to be added
 * @return 0 - Success
 *         1 - Error while adding record
 */
int addRecord(int *numberOfRecords, int phonebookSize, char *name, char *birthdate, char *phone)
{
	strcpy((phonebook + *numberOfRecords)->name, name);
	strcpy((phonebook + *numberOfRecords)->birthdate, birthdate);
	strcpy((phonebook + *numberOfRecords)->phone, phone);
	(*numberOfRecords)++;

	return 0;
}

/*
 * Find record in the data structure and return back its index
 *
 * @param numberOfRecords - Pointer to the number of records in the buffer
 *        name - Pointer to the name to find in the records
 * @return index of found - Success
 *         -1 - Error
 */
int findRecord(int *numberOfRecords, char *name)
{
	for (int i = 0; i < *numberOfRecords; i++)
	{
		if (strcmp(name, (phonebook + i)->name) == 0)
		{
			// Found, return index
			return i;
		}
	}

	// If not found return -1
	return -1;
}

/*
 * Displays all the records in the data structure
 *
 * @param numberOfRecords - Pointer to the number of records in the buffer
 * @return 0 - Success
 *         1 - Error
 */
int listRecords(int *numberOfRecords)
{
	// Print header
	printf("----------------------NAME----------------------- ---BIRTH--- ----PHONE-----\n");

	// Print all the records
	for (int i = 0; i < *numberOfRecords; i++)
	{
		printf("%-49s %-11s %-14s\n",
					 (phonebook + i)->name,
					 (phonebook + i)->birthdate,
					 (phonebook + i)->phone);
	}

	return 0;
}

