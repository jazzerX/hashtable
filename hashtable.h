#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash_list
{
	char *key;
	char *value;
	struct hash_list *next;	
};

typedef struct hash_list hash_list_t;

struct hashtable
{
	int size;
	hash_list_t **store;
};

typedef struct hashtable hastable_t;


extern hastable_t *ht_create(int size);
extern int ht_delete(hastable_t *ht);
extern int ht_insert(hastable_t *ht, char *key, char *value);
extern char *ht_find(hastable_t *ht, char *key);
extern void ht_print(hastable_t *ht);

#endif