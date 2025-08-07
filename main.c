#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 100

typedef struct
{
	char name[30];
	char num[15];
	int isEmpty;
} Contact;

Contact contacts[ARRAY_SIZE];

void init(void);
int navigator(void);
void list_contacts(void);
void search_contacts(void);
void clear_input(void);
void add_contact(void);
void edit_contact(void);
void delete_contact(void);
int load_contacts_from_file(void);
void save_contacts_to_file(void);
int search_func(int);

int main(void)
{
	init();
	printf("Welcome! This is Simple Phonebook written in C by Suleyman Kara.\n");
	if (navigator())
	{
		save_contacts_to_file();
		return 1;
	}
	save_contacts_to_file();
	return 0;
}

void init(void)
{
	if (load_contacts_from_file() != 0)
	{
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			contacts[i].isEmpty = 1;
		}
	}
}

int navigator(void)
{
	int choice;
	while (1)
	{
		printf("This is main menu. What would you like to do?\n"
			"0: Quit\n"
			"1: List Contacts\n"
			"2: Search Contacts\n"
			"3: Add Contact\n"
			"4: Edit Contact\n"
			"5: Delete Contact\n"
			"6: Save Contacts Manually\n"
			">> ");
		scanf("%d", &choice);
		clear_input();

		switch (choice)
		{
		case 0:
			printf("Goodbye!\n");
			return 1;
		case 1:
			list_contacts(); break;
		case 2:
			search_contacts(); break;
		case 3:
			add_contact(); break;
		case 4:
			edit_contact(); break;
		case 5:
			delete_contact(); break;
		case 6:
			save_contacts_to_file(); break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
		puts("");
	}
}

void clear_input(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void list_contacts(void)
{
	int counter = 0;
	printf("Contacts:\n");
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (contacts[i].isEmpty == 0)
		{
			printf("%30s %15s\n", contacts[i].name, contacts[i].num);
			counter++;
		}
	}
	if (counter == 0)
	{
		printf("Contact list is empty.\n");
	}
}

void search_contacts(void)
{
	printf("0: Quit Search\n"
		"1: Search with name\n"
		"2: Search with number\n"
		">> ");

	int search_choice = 0;
	scanf("%d", &search_choice);
	clear_input();

	if (search_choice == 0)
	{
		printf("Quitting search menu.\n");
		return;
	}
	else if (search_choice == 1 || search_choice == 2)
	{
		search_func(search_choice);
	}
	else
	{
		printf("Invalid choice. Please try again.\n");
		search_contacts();
	}
}

int search_func(int choice)
{
	int check = 0;
	printf("Input for search >> ");
	char search[30] = { "" };
	fgets(search, sizeof(search), stdin);
	search[strcspn(search, "\n")] = 0;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (contacts[i].isEmpty == 0)
		{
			if (choice == 1)
			{
				if (strcmp(search, contacts[i].name) == 0)
				{
					printf("%s found!\n"
						"%30s %15s\n", search, contacts[i].name, contacts[i].num);
					return i;
				}
			}
			else if (choice == 2)
			{
				if (strcmp(search, contacts[i].num) == 0)
				{
					printf("%s found!\n"
						"%30s %15s\n", search, contacts[i].name, contacts[i].num);
					return i;
				}
			}
		}
	}
	printf("Unfortunately, %s could not found.\n", search);
	return -1;
}

void add_contact(void)
{
	int counter = -1;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (contacts[i].isEmpty == 1)
		{
			counter = i;
			break;
		}
	}
	if (counter == -1)
	{
		printf("Unfortunately, there is not enough space for a new contact.\n");
		return;
	}
	else
	{
		char new_name[30] = { "" };
		char new_num[15] = { "" };

		printf("Please enter the name for new contact >> ");
		fgets(new_name, sizeof(new_name), stdin);
		new_name[strcspn(new_name, "\n")] = 0;
		printf("Please enter the number for new contact >> ");
		fgets(new_num, sizeof(new_num), stdin);
		new_num[strcspn(new_num, "\n")] = 0;


		contacts[counter].isEmpty = 0;
		strcpy(contacts[counter].name, new_name);
		strcpy(contacts[counter].num, new_num);

		printf("New contacts information:\n"
			"Name: %30s Number: %15s\n", contacts[counter].name, contacts[counter].num);
	}
}

void edit_contact(void)
{
	int key = search_func(1);
	if (key == -1)
	{
		printf("Unfortunately there is not a contact with that name to edit.\n");
		return;
	}
	else
	{
		char new_name[30] = { "" };
		char new_num[15] = { "" };

		printf("Please enter the name for new contact >> ");
		fgets(new_name, sizeof(new_name), stdin);
		new_name[strcspn(new_name, "\n")] = 0;

		printf("Please enter the number for new contact >> ");
		fgets(new_num, sizeof(new_num), stdin);
		new_num[strcspn(new_num, "\n")] = 0;


		printf("Old contacts information:\n"
			"Name: %30s Number: %15s\n", contacts[key].name, contacts[key].num);

		strcpy(contacts[key].name, new_name);
		strcpy(contacts[key].num, new_num);

		printf("New contacts information:\n"
			"Name: %30s Number: %15s\n", contacts[key].name, contacts[key].num);
	}
}

void delete_contact(void)
{
	int key = search_func(1);
	if (key == -1)
	{
		printf("Unfortunately there is not a contact with that name to delete.\n");
		return;
	}
	else
	{
		printf("Deleted contact's information:\n"
			"Name: %30s Number: %15s\n", contacts[key].name, contacts[key].num);

		contacts[key].isEmpty = 1;
	}
}

int load_contacts_from_file(void)
{
	FILE* fPtr;
	fPtr = fopen("contacts.bin", "rb");
	if (fPtr == NULL)
	{
		perror("Contacts file could not open.");
		return 1;
	}
	fread(contacts, sizeof(Contact), ARRAY_SIZE, fPtr);
	fclose(fPtr);
	printf("INFO: Contacts loaded.\n");
	return 0;
}

void save_contacts_to_file(void)
{
	FILE* fPtr;
	fPtr = fopen("contacts.bin", "wb");
	if (fPtr == NULL)
	{
		perror("Contacts file could not open.");
		return;
	}
	fwrite(contacts, sizeof(Contact), ARRAY_SIZE, fPtr);
	fclose(fPtr);
	printf("INFO: Contacts saved.\n");
}