#include <stdio.h>

typedef struct
{
	char name[30];
	char num[15];
} Contact;

Contact contacts[100];

void navigator(void);
void add_contact(void);
void update_contact(void);
void delete_contact(void);
void search_contact(void);
void list_contacts(void);
void save_contacts_to_file(void);
void load_contacts_from_file(void);

int main(void)
{
	printf("Welcome! This is Simple Phonebook written in C by Suleyman Kara.");
	navigator();
	printf("Goodbye!\n");
	return 0;
}

void navigator(void)
{

}