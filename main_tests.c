#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20

float p_ch_dir=0.01;
int gain_energie_proie=6;
int gain_energie_predateur=20;
float p_reproduce_proie=0.8;
float p_reproduce_predateur=0.8;
float p_manger= 0.5;
int temps_repousse_herbe=-10;



int main(void) {
  /* A Completer. Exercice 5, question 3 */
	srand(time(NULL));
	int i;
	Animal *liste_proie = NULL;
	Animal *liste_predateur = NULL;
	int nb_proies = 0, nb_predateurs = 0;
	printf("\nLe NB de proies (*):%d",nb_proies);
	printf("\nLe NB de predateur (O):%d",nb_predateurs);
	for (i = 0; i < NB_PROIES; i++) {
		ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y,&liste_proie);
	}

	for (i = 0; i < NB_PREDATEURS; i++) {
		ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_predateur);
	}
	
	afficher_ecosys(liste_proie, liste_predateur);		

	nb_proies = compte_animal_rec(liste_proie);
	nb_predateurs = compte_animal_rec(liste_predateur);
	printf("\nLe NB de proies (*):%d",nb_proies);
	printf("\nLe NB de predateur (O):%d\n",nb_predateurs);

	printf("\nBouger animaux \n");
 	bouger_animaux(liste_proie);
 	bouger_animaux(liste_predateur);
	afficher_ecosys(liste_proie, liste_predateur);	

	printf("\n\nReproduction\n");
	reproduce(&liste_proie,p_reproduce_proie);
	reproduce(&liste_predateur,p_reproduce_predateur);
 	afficher_ecosys(liste_proie, liste_predateur);	

	printf("\n\nLiberation animaux\n");
	liste_proie=liberer_liste_animaux(liste_proie);
	liste_predateur=liberer_liste_animaux(liste_predateur);
	assert(liste_proie==NULL);
	assert(liste_predateur==NULL);

	return 0;
}
