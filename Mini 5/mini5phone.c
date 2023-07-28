#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini5phone.h"

/**
 * This is a C file containing the functions used by mini5main.c.
 * It contains loadCSV, saveCSV, addRecord, findRecord, listRecords,
 * delete, clear.
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
 * Head of linked list structure used to store and buffer the records
 */
struct PHONE_NODE *phonebookHead;

/*
 * Load data structure from the CSV database
 *
 * @return 0 - Success
 *         1 - Error no file
 *         2 - Error while loading the file
 */
int loadCSV()
{
	FILE *phonebookCSV;
	char header[100];
	struct PHONE_NODE *currentNode;
	struct PHONE_NODE *tailNode;

	// Open file
	phonebookCSV = fopen("phonebook.csv", "r");

	// Detect if file exists
	if (phonebookCSV == NULL)
	{
		return 1;
	}

	// Skip the first line (header)
	fgets(header, 100, phonebookCSV);

	// Store it into memory
	while (!feof(phonebookCSV))
	{
		// Allocate memory for node
		currentNode = (struct PHONE_NODE *)malloc(sizeof(struct PHONE_NODE));
		if (currentNode == NULL)
			return 2;

		// Read file
		fscanf(phonebookCSV,
					 "%49[^,],%11[^,],%14[^\n]\n",
					 currentNode->name,
					 currentNode->birthdate,
					 currentNode->phone);
		currentNode->next = NULL;

		// Detect if error occurs
		if (ferror(phonebookCSV))
		{
			return 2;
		}

		// Chain list
		if (phonebookHead == NULL)
			phonebookHead = currentNode;
		else
		{
			tailNode = phonebookHead;
			while (tailNode->next != NULL)
				tailNode = tailNode->next;
			tailNode->next = currentNode;
		}
	}

	// close file
	fclose(phonebookCSV);

	return 0;
}

/*
 * Save data structure to the CSV database
 *
 * @return 0 - Success
 *         1 - Error while saving
 */
int saveCSV()
{
	FILE *phonebookCSV;
	struct PHONE_NODE *tempNode = phonebookHead;

	// Open file
	phonebookCSV = fopen("phonebook.csv", "w");

	// Write the first line (header)
	fprintf(phonebookCSV, "Name,birthdate,phone");

	// Store it into the file
	while (tempNode != NULL)
	{
		// Read file
		fprintf(phonebookCSV,
						"\n%s,%s,%s",
						tempNode->name,
						tempNode->birthdate,
						tempNode->phone);

		// Detect if error occurs
		if (ferror(phonebookCSV))
		{
			return 1;
		}

		// Iterate phonebook linked list
		tempNode = tempNode->next;
	}

	// close file
	fclose(phonebookCSV);

	return 0;
}

/*
 * Add a new phone entry to the data structure
 *
 * @param name - Pointer to the name of the record to be added
 *        birthdate - Pointer to the birthdate of the record to be added
 *        phone - Pointer to the phone of the record to be added
 * @return 0 - Success
 *         1 - Error while adding record
 */
int addRecord(char *name, char *birthdate, char *phone)
{
	struct PHONE_NODE *newNode;
	struct PHONE_NODE *tailNode;

	// Create new node
	newNode = (struct PHONE_NODE *)malloc(sizeof(struct PHONE_NODE));
	if (newNode == NULL)
		return 1;

	strcpy(newNode->name, name);
	strcpy(newNode->birthdate, birthdate);
	strcpy(newNode->phone, phone);
	newNode->next = NULL;

	// Append new node to tail of phonebook linked list
	if (phonebookHead == NULL)
		phonebookHead = newNode;
	else
	{
		// Get the tail of the phonebook linked list
		tailNode = phonebookHead;
		while (tailNode->next != NULL)
		{
			tailNode = tailNode->next;
		}

		tailNode->next = newNode;
	}

	return 0;
}

/*
 * Find record in the data structure and return back its node pointer
 *
 * @param name - Pointer to the name to find in the records
 * @return tempNode - pointer of record found
 *         NULL - Not found
 */
struct PHONE_NODE *findRecord(char *name)
{
	struct PHONE_NODE *tempNode = phonebookHead;

	while (tempNode != NULL)
	{
		if (strcmp(name, tempNode->name) == 0)
		{
			// Found, return node
			return tempNode;
		}

		tempNode = tempNode->next;
	}

	// If not found return NULL
	return NULL;
}

/*
 * Displays all the records in the data structure
 *
 * @return 0 - Success
 *         1 - Error
 */
int listRecords()
{
	struct PHONE_NODE *tempNode = phonebookHead;

	// Print header
	printf("----------------------NAME----------------------- ---BIRTH--- ----PHONE-----\n");

	// Print all the records
	while (tempNode != NULL)
	{
		printf("%-49s %-11s %-14s\n",
					 tempNode->name,
					 tempNode->birthdate,
					 tempNode->phone);
		tempNode = tempNode->next;
	}

	return 0;
}

/*
 * Removes NODE of a person by their name from data structure
 *
 * @param person - Name of person to delete
 * @return 0 - Success
 *         1 - Not found
 */
int delete(char *person)
{
	struct PHONE_NODE *current = phonebookHead;
	struct PHONE_NODE *prev = NULL;

	// Looking for person in phonebook
	while (current != NULL && strcmp(current->name, person) != 0)
	{
		prev = current;
		current = current->next;
	}

	// If person was not found in phonebook
	if (current == NULL)
	{
		return 1;
	}
	// If person is at head of phonebook
	else if (prev == NULL)
	{
		phonebookHead = current->next;
	}
	else
	{
		prev->next = current->next;
	}
	free(current);

	return 0;
}

/**
 * Clears the phonebook
 *
 * @return 0 - Success
 *         1 - Error
 */

int clear()
{
	struct PHONE_NODE *tempNode;

	while (phonebookHead != NULL)
	{
		tempNode = phonebookHead;
		phonebookHead = phonebookHead->next;
		free(tempNode);
	}

	return 0;
}
