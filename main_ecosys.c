#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define NUM_ITERATIONS 500


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
int gain_energie_proie=6;
int gain_energie_predateur=20;
float p_reproduce_proie=0.8;
float p_reproduce_predateur=0.8;
float p_manger= 1;
int temps_repousse_herbe=-15;



int main(void) {

	FILE *ficher;
	ficher= fopen("Evol_pop.txt", "w");
	if (ficher==NULL) {fprintf (stderr, "probleme d'ouverture %s\n","Evol_pop_txt");}
	
 	srand(time(NULL));

  /* exercice 6, question 1*/
	int grass[SIZE_X][SIZE_Y] = {0};
  /* exercice 7, question 2*/
	Animal *liste_proie=NULL;
	for (int i=0;i<NB_PROIES;i++){
		ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, &liste_proie);
		liste_proie->energie= gain_energie_proie;
	}
	
	Animal *liste_predateur=NULL;
	for (int i=0;i<NB_PREDATEURS;i++){
		ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, &liste_predateur);
		liste_predateur->energie= gain_energie_predateur;
	}

	
	afficher_ecosys(liste_proie, liste_predateur);	
	assert(!sleep(3));
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		fprintf(ficher, "%d ", i);
		rafraichir_monde(grass);
    	rafraichir_proies(&liste_proie,grass);
		rafraichir_predateurs(&liste_predateur,&liste_proie);
		afficher_ecosys(liste_proie, liste_predateur);	
		int nb_proies = compte_animal_rec(liste_proie);
		int nb_predateurs = compte_animal_rec(liste_predateur);
		if(ficher)fprintf(ficher, "%d %d", nb_proies, nb_predateurs);
		fprintf(ficher, "\n");	
		if(liste_proie==NULL){
			if(liste_predateur==NULL){
				printf("Tout le monde est mort");
			}
			else{
				printf("Extinction des proies, les predateurs vont starving");
			}
			break;
		}
		else if(liste_predateur==NULL){
			printf("PEACE & LOVE");
			break;
		}
			
		assert(!usleep(T_WAIT));
  	}
  /* exercice 9, question 1*/
	fclose(ficher);

	return 0;
}

