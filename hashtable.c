#include "hashtable.h"

hastable_t *ht_create(int size)
{
	hastable_t *ht = (hastable_t *) malloc(sizeof(hastable_t));
	if (ht != NULL)
	{
		ht->size = size;
		ht->store = (hash_list_t **) malloc(size * sizeof(hash_list_t *));

		if (ht->store != NULL)
		{
			for (int i = 0; i < ht->size; i++)
			{
				ht->store[i] = (hash_list_t *) malloc(sizeof(hash_list_t));
				ht->store[i]->key = NULL;
				ht->store[i]->value = NULL;
				ht->store[i]->next = NULL;
			}

		return ht;		
		}	
	}	
		
	return NULL;
}

static void ht_list_delete(hash_list_t *head)
{
	while (head->next != NULL)
	{
		head->key = NULL;
		head->value = NULL;
		head = head->next;
	}

	head->key = NULL;
	head->value = NULL;
	head->next = NULL;
	head = NULL;
}

int ht_delete(hastable_t *ht)
{
	if (ht->store != NULL)
	{
		for (int i = 0; i < ht->size; i++)
		{
			ht->store[i]->key = NULL;
			ht->store[i]->value = NULL;

			if (ht->store[i]->next != NULL)
				ht_list_delete(ht->store[i]);
			else
				ht->store[i]->next = NULL;

			free(ht->store[i]);
			ht->store[i] = NULL;
		}

		free(ht->store);
		ht->store = NULL;
		ht->size = 0;

		return 0;	
	}

	return -1;
}

static int ht_get_hash(const char *s, int size)
{
	int p = 31;
	long long int hash = 0, p_pow = 1;

	for (int i = 0; i < strlen(s); i++)
	{
		hash += s[i] * p_pow;
		p_pow *= p;
	}

	return hash % size;
}

static int ht_insert_in_list(hash_list_t *head, char *key, char *value)
{
	while (head->next != NULL)
		head = head->next;

	head->next = (hash_list_t *) malloc(sizeof(hash_list_t));

	if (head->next != NULL)
	{
		head->next->key = key;
		head->next->value = value;
		head->next->next = NULL;	

		return 0;	
	}

	return -1;
}

int ht_insert(hastable_t *ht, char *key, char *value)
{
	int idx = ht_get_hash(key, ht->size);

	if (ht->store[idx]->key == NULL)
	{
		ht->store[idx]->key = key;
		ht->store[idx]->value = value;
		ht->store[idx]->next = NULL;
	}
	else
		if (ht_insert_in_list(ht->store[idx], key, value) != -1)
			return 0;
		return -1;
}

static char *ht_find_in_list(hash_list_t *head, char *key)
{
	while (head->next != NULL)
		if (head->key == key)
			return head->key;
		head = head->next;

	return NULL;
}

char *ht_find(hastable_t *ht, char *key)
{
	int idx = ht_get_hash(key, ht->size);

	if (ht->store[idx]->key == key)	
		return ht->store[idx]->value;
	else
		return ht_find_in_list(ht->store[idx], key);

}

static void ht_list_bypass(hash_list_t *head)
{
	while (head->next != NULL) 
	{
		head = head->next;	
		printf(", %s : %s", head->key, head->value);
	}
}

void ht_print(hastable_t *ht)
{
	for (int i = 0; i <= ht->size - 1; i++)
	{
		printf("%d | %s : %s", i + 1, ht->store[i]->key, ht->store[i]->value);

		if (ht->store[i]->next != NULL)
			ht_list_bypass(ht->store[i]);

	printf("\n");
	}
}