#ifndef PHONEBOOK_H_ //include guard
#define PHONEBOOK_H_

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct{
	char name[80];
	long number;
} PhoneEntry;

typedef struct{
	PhoneEntry *entries;
	int total;
	int size;
} PhoneBook;

PhoneEntry *newEntry(char *name, long number);
PhoneBook *createPhoneBook();
void dropPhoneBook(PhoneBook *book);

//add entry to the phone book
//if the name is exist, overwritten it
void addPhoneNumber(char *name, long number, PhoneBook *book);

//find an entry in the phonebook, return null if the entry does not exist
PhoneEntry *getPhoneNumber(char *name, PhoneBook *book);

void printPhoneBook(PhoneBook *book);

#endif