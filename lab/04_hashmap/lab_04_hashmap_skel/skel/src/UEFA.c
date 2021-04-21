/* Gheorghisor Ileana-Teodora, 313CA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Nu mergea programul daca nu includeam tot si nu stiu de ce in
 * mainul de la hasthable merge sa includ doar Hashtable.h
 */
#include "Hashtable.h"
#include "Hashtable.c"
#include "LinkedList.h"
#include "LinkedList.c"

#define MAX_STRING_SIZE	256

/* Pentru ex 313CAa am facut un un singur fisier .c unde scriu functiile
 * si mainul (nu vreau sa ma complic cu mai multe .c-uri sau .h pentru ca)
 * inca nu le-am inteles prea bine).
*/

struct UEFA {
	char nume[MAX_STRING_SIZE];
	char nationalitate[MAX_STRING_SIZE];
	char pozitie[MAX_STRING_SIZE];
	char trofeu[MAX_STRING_SIZE];
	int rating;
	int contor1, contor2; 
	/* Pentru goluri si assisturi in cazul atacantilor si mijlocasilor
	 * si meciuri fara gol primit si tacklinguri pentru portari si fundasi.
	 */
};

static void print_jucator(struct UEFA *p_jucator)
{
	if (p_jucator == NULL) {
		printf("%s\n", "Jucator inexistent!");
		return;
	}

	printf("Nume: %s | ", p_jucator->nume);
	printf("Nationalitate: %s | ", p_jucator->nationalitate);
	printf("Pozitie: %s | ", p_jucator->pozitie);
	printf("Cel mai bun trofeu: %s | ", p_jucator->trofeu);
	printf("Rating: %d | ", p_jucator->rating);

	if (strcmp(p_jucator->pozitie, "atacant") == 0 ||
		strcmp(p_jucator->pozitie, "mijlocas") == 0) {
		printf("Goluri: %d | ", p_jucator->contor1);
		printf("Assisturi: %d\n", p_jucator->contor2);
	}

	if (strcmp(p_jucator->pozitie, "fundas") == 0 ||
		strcmp(p_jucator->pozitie, "portar") == 0) {
		printf("Meciuri fara gol primit: %d | ", p_jucator->contor1);
		printf("Tacklinguri: %d\n", p_jucator->contor2);
	}
}

int main()
{
	hashtable_t *ht_jucatori;
	struct UEFA jucator[5];
	struct UEFA *p_jucator;
	int current_key;

	/* Nu stiu nimic legat de fotbal asa ca toate datele sunt fictive. */
	/* Atribuirea datelor celor 5 jucatori. */
	strcpy(jucator[0].nume, "Alex");
	strcpy(jucator[0].nationalitate, "Roman");
	strcpy(jucator[0].pozitie, "atacant");
	strcpy(jucator[0].trofeu, "campionatul din 2016");
	jucator[0].contor1 = 20;
	jucator[0].contor2 = 6;
	jucator[0].rating = 221;

	strcpy(jucator[1].nume, "Ben");
	strcpy(jucator[1].nationalitate, "Englez");
	strcpy(jucator[1].pozitie, "mijlocas");
	strcpy(jucator[1].trofeu, "campionatul din 2018");
	jucator[1].contor1 = 14;
	jucator[1].contor2 = 10;
	jucator[1].rating = 196;

	strcpy(jucator[2].nume, "Claudiu");
	strcpy(jucator[2].nationalitate, "Roman");
	strcpy(jucator[2].pozitie, "portar");
	strcpy(jucator[2].trofeu, "campionatul din 2016");
	jucator[2].contor1 = 52;
	jucator[2].contor2 = 14;
	jucator[2].rating = 234;

	strcpy(jucator[3].nume, "Daniel");
	strcpy(jucator[3].nationalitate, "American");
	strcpy(jucator[3].pozitie, "fundas");
	strcpy(jucator[3].trofeu, "campionatul din 2020");
	jucator[3].contor1 = 33;
	jucator[3].contor2 = 9;
	jucator[3].rating = 182;

	strcpy(jucator[4].nume, "Eliot");
	strcpy(jucator[4].nationalitate, "Englez");
	strcpy(jucator[4].pozitie, "atacant");
	strcpy(jucator[4].trofeu, "campionatul din 2014");
	jucator[4].contor1 = 13;
	jucator[4].contor2 = 24;
	jucator[4].rating = 200;

	/* Initializare hashtable. */
	ht_jucatori = ht_create(10, hash_function_string,
				compare_function_strings);

	/* Adaug in hashtable jucatorii si ii afisez pentru a) si b). */
	printf("a) si b)\n");
	for(int i = 0; i < 5; i++) {
			ht_put(ht_jucatori, jucator[i].nume, strlen(jucator[i].nume) + 1,
				&jucator[i], sizeof(jucator[i]));
		p_jucator = ht_get(ht_jucatori, jucator[i].nume);
		print_jucator(p_jucator);
	}

	/* Elimin pe cei cu rating < 200 si ii afisez pe cei ramasi. */
	printf("c)\n");

	for(int i = 0; i < 5; i++) {
		if (jucator[i].rating < 200)
			ht_remove_entry(ht_jucatori, jucator[i].nume);
			p_jucator = ht_get(ht_jucatori, jucator[i].nume);
	}
	for(int i = 0; i < 5; i++) {
		p_jucator = ht_get(ht_jucatori, jucator[i].nume);
		if(p_jucator != NULL)
			print_jucator(p_jucator);
	}

	/* Nu stiu exact cum trebuie sa rezolv fara sa parcurg tot hashtableul.
	 * Ma mai gandesc duminica dimineata daca nu imi corectezi pana atunci.
	 */
	printf("d)\n");
	return 0;
}