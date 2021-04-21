/* Gheorghisor Ileana-Teodora, 313CA*/

/*
 * Hashtable.c
 * Alexandru-Cosmin Mihai
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "Hashtable.h"

#define MAX_BUCKET_SIZE 64

/*
 * Functii de comparare a cheilor:
 */
int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int
hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

/*
 * Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
 * Trebuie alocate si initializate si listele inlantuite.
 */
hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	/* TODO */
	unsigned int i;
	hashtable_t *ht;

	ht = malloc(sizeof(hashtable_t));
	ht->buckets = malloc(hmax * sizeof(linked_list_t *));
	for (i = 0; i < hmax; i++)
		ht->buckets[i] = ll_create(sizeof(struct info));

	ht->hmax = hmax;
	ht->size = 0;
	ht->hash_function = hash_function;
	ht->compare_function = compare_function;

	return ht;
}

/*
 * Atentie! Desi cheia este trimisa ca un void pointer (deoarece nu se impune tipul ei), in momentul in care
 * se creeaza o noua intrare in hashtable (in cazul in care cheia nu se gaseste deja in ht), trebuie creata o copie
 * a valorii la care pointeaza key si adresa acestei copii trebuie salvata in structura info asociata intrarii din ht.
 * Pentru a sti cati octeti trebuie alocati si copiati, folositi parametrul key_size_bytes.
 *
 * Motivatie:
 * Este nevoie sa copiem valoarea la care pointeaza key deoarece dupa un apel put(ht, key_actual, value_actual),
 * valoarea la care pointeaza key_actual poate fi alterata (de ex: *key_actual++). Daca am folosi direct adresa
 * pointerului key_actual, practic s-ar modifica din afara hashtable-ului cheia unei intrari din hashtable.
 * Nu ne dorim acest lucru, fiindca exista riscul sa ajungem in situatia in care nu mai stim la ce cheie este
 * inregistrata o anumita valoare.
 */
void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	/* TODO */
	unsigned int index;
	ll_node_t *it;
	struct info *new;

	if (ht ==  NULL)
		return;
	
	index = ht->hash_function(key) % ht->hmax;
	it = ht->buckets[index]->head;

	if (it == NULL) {
		ht->size++;
		new = malloc(sizeof(struct info));
		new->key = malloc(key_size * sizeof(char));
		new->value = malloc(value_size * sizeof(char));
		memcpy(new->key, key, key_size);
		memcpy(new->value, value, value_size);
		ll_add_nth_node(ht->buckets[index], 0, new);

		free(new);
		return;
	}

	while (it != NULL) {
		void *it_key = ((struct info *)(it->data))->key;
		if (!ht->compare_function(it_key, key)) {
			void *it_value = ((struct info *)(it->data))->value;
			memcpy(it_value, value, value_size);
			return;
		}
		it = it->next;
	}

	new = malloc(sizeof(struct info));
	new->key = malloc(key_size * sizeof(char));
	new->value = malloc(value_size * sizeof(char));
	memcpy(new->key, key, key_size);
	memcpy(new->value, value, value_size);
	ll_add_nth_node(ht->buckets[index], ht->buckets[index]->size, new);
	
	free(new);
}

void *
ht_get(hashtable_t *ht, void *key)
{
	/* TODO */
	unsigned int index;
	ll_node_t *it;

	index = ht->hash_function(key) % ht->hmax;
	it = ht->buckets[index]->head;

	while (it != NULL) {
		void *it_key = ((struct info *)(it->data))->key;
		if (!ht->compare_function(it_key, key))
			return (((struct info *)(it->data))->value);
		it = it->next;
	}
	return NULL;
}

/*
 * Functie care intoarce:
 * 1, daca pentru cheia key a fost asociata anterior o valoare in hashtable folosind functia put
 * 0, altfel.
 */
int
ht_has_key(hashtable_t *ht, void *key)
{
	/* TODO */
	void *value;
	value = ht_get(ht, key);
	if (value != NULL)
		return 1;
	return 0;
}

/*
 * Procedura care elimina din hashtable intrarea asociata cheii key.
 * Atentie! Trebuie avuta grija la eliberarea intregii memorii folosite pentru o intrare din hashtable (adica memoria
 * pentru copia lui key --vezi observatia de la procedura put--, pentru structura info si pentru structura Node din
 * lista inlantuita).
 */
void
ht_remove_entry(hashtable_t *ht, void *key)
{
	/* TODO */
	unsigned int index;
	ll_node_t *it, *delete;
	int nr = 0;
	void *it_key;

	index = ht->hash_function(key) % ht->hmax;
	it = ht->buckets[index]->head;

	while (it != NULL) {
		it_key = ((struct info *)(it->data))->key;
		if (!ht->compare_function(it_key, key)) {
			delete = ll_remove_nth_node(ht->buckets[index], nr);
			free(((struct info *)(delete->data))->key);
			free(((struct info *)(delete->data))->value);
			free(delete->data);
			free(delete);
			if (ht->buckets[index]->size == 0)
				ht->size--;
			return;
		}
		nr++;
		it = it->next;
	}
}

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable, dupa care elibereaza si memoria folosita
 * pentru a stoca structura hashtable.
 */
void
ht_free(hashtable_t *ht)
{
	/* TODO */
	unsigned int i;
	ll_node_t *it;

	for (i = 0; i < ht->hmax; i++) {
		it = ht->buckets[i]->head;
		while (it != NULL) {
			free(((struct info *)(it->data))->key);
			free(((struct info *)(it->data))->value);
			it = it->next;
		}
		ll_free(ht->buckets + i);
	}
	free(ht->buckets);
	free(ht);
}

unsigned int
ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}

unsigned int
ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}

/* Rezolvarea ex 313CAa*/


