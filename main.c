#include "hashtable.h"

int main(int argc, char const *argv[])
{
	hastable_t *ht = ht_create(7);
	if (ht == NULL)
	{
		printf("Error: Can not create the hash table.\n");			
		return -1;
	}
	ht_insert(ht, "Sam", "Dilon");
	ht_insert(ht, "Alex", "Brown");
	ht_insert(ht, "Karen", "Williams");
	ht_insert(ht, "Karen", "Williams");
	ht_insert(ht, "Karen", "Williams");

	char *val;

	printf("%s\n", (val = ht_find(ht, "Alex")) ? val : "Error: Key not found");
	printf("%s\n", (val = ht_find(ht, "Karen")) ? val : "Error: Key not found");
	printf("%s\n", (val = ht_find(ht, "Dilon")) ? val : "Error: Key not found");
	printf("%s\n", (val = ht_find(ht, "Sam")) ? val : "Error: Key not found");

	printf("\n-------------------------\n");
	ht_print(ht);
	
	ht_delete(ht, "Sam");
	ht_delete(ht, "Alex");
	ht_delete(ht, "Karen");

	printf("\n-------------------------\n");
	ht_print(ht);

	ht_insert(ht, "Karen", "Dilon");
	ht_insert(ht, "Karen", "Dilons");
	ht_delete(ht, "Karen");

	printf("\n-------------------------\n");
	ht_print(ht);
	if (ht_clear(ht) != 0)
		printf("Error: Can not delete the hash table.\n");

	return 0;
}