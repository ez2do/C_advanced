#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

typedef SymbolTable PhoneBook;

Entry *makePhoneNode(void *name, void *number);
int comparePhoneNode(void *key1, void *key2);
PhoneBook *createPhoneBook();
void dropPhoneBook(PhoneBook *book);
Entry *getPhoneEntry(void *key, PhoneBook *book);
void addPhoneEntry(void *key, void *value, PhoneBook *book);
void printPhoneItems(PhoneBook *book);

#endif