#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y, Animal **liste_animal) {
  assert(x>=0 && x<SIZE_X);
  assert(y>=0 && x<SIZE_Y);
  Animal *new1=creer_animal(x,y,10);
  *liste_animal=ajouter_en_tete_animal(*liste_animal,new1);
}
	

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
	Animal *temp=*liste;
	if (animal !=*liste ){
	while(temp->suivant != animal)
		temp=temp->suivant;

	temp->suivant=animal->suivant;
	}else
	*liste=animal->suivant;
	free(animal);
return ;
}


/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
	Animal *new;
	while(liste){
		new=liste->suivant;
		free(liste);
		liste=new;
	}
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
	unsigned int i, j;
	char ecosys[SIZE_X][SIZE_Y];
	int nbpred=0,nbproie=0;
	Animal *pa=NULL;


	/* on initialise le tableau */
	for (i = 0; i < SIZE_X; i++) {
		for (j = 0; j < SIZE_Y; j++) {
			ecosys[i][j]=' ';
		}
	}
	/* on ajoute les proies */
	pa = liste_proie;
	while (pa) {
		++nbproie;
		assert (pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y);
		ecosys[pa->x][pa->y] = '*';
		pa=pa->suivant;
	}

	/* on ajoute les predateurs */
	pa = liste_predateur;
	while (pa) {
		++nbpred;
		assert (pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y);
		if ((ecosys[pa->x][pa->y] =='@') || (ecosys[pa->x][pa->y] == '*')){ /*
proies aussi present */
		ecosys[pa->x][pa->y] = '@';
		} else {
			ecosys[pa->x][pa->y] = 'O';
		}
	pa = pa->suivant;
}

/* on affiche le tableau */
printf("+");
for (j = 0; j < SIZE_Y; ++j) {
	printf("-");
}
printf("+\n");
for (i = 0; i < SIZE_X; ++i) {
	printf("|");
	for (j = 0; j < SIZE_Y; ++j) {
		putchar(ecosys[i][j]);
		}printf("|\n");
}
	printf("+");
for (j = 0; j<SIZE_Y; ++j) {
	printf("-");
}
printf("+\n");
printf("Nb proies(*) : %5d\tNb predateurs(O) : %5d\n", nbproie, nbpred);
}



void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
	while(la){
		if(Probabilite(p_ch_dir)){
			la->dir[0]=rand()%3-1;
			la->dir[1]=rand()%3-1;
		}
		la->x= Modulo(la->x - la->dir[0], SIZE_X);
		la->y= Modulo(la->y - la->dir[1], SIZE_Y);
		la=la->suivant;
	}
}
	
	

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
	Animal *temp=*liste_animal;
	while(temp){
		if(Probabilite(p_reproduce)){
			ajouter_animal(temp->x,temp->y,liste_animal);
			temp-> energie = temp->energie/2.0; /*/=2.0*/
			(*liste_animal)->energie= temp->energie;
			assert((*liste_animal)->energie != 0.0);
			assert(temp->energie != 0.0);
		}
	temp=temp->suivant;
	}
}

/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
	bouger_animaux(*liste_proie);
	Animal *temp=*liste_proie;
	while(temp){
		temp->energie--;
		if(monde[temp->x][temp->y]>=0){
			temp->energie+=gain_energie_proie;
			monde[temp->x][temp->y]= temps_repousse_herbe;
		}
	temp=temp->suivant;
	}
	for(Animal *temp=*liste_proie;temp;temp=temp->suivant){
		if(temp->energie<=0.0){
			enlever_animal(liste_proie,temp);
		}
	}
	reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
	while(l){
		if(l->x == x && l->y == y)
			return l;
		l=l->suivant;
	}
  	return NULL;
} 

/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/
	bouger_animaux(*liste_predateur);
	Animal *temp=*liste_predateur;
	while(temp){
		temp->energie--;
		Animal *delt=animal_en_XY(*liste_proie,temp->x,temp->y);
		if(delt && Probabilite(p_manger)){
			enlever_animal(liste_proie,delt);
			temp->energie += gain_energie_predateur;
		}
		temp=temp->suivant;
	}
	for(Animal *temp=*liste_predateur;temp;temp=temp->suivant){
		if(temp->energie<=0.0){
			enlever_animal(liste_predateur,temp);
		}
	}
	reproduce(liste_predateur, p_reproduce_predateur);
}



/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
   /*A Completer*/
	for (int i = 0; i < SIZE_X; i++){
    	for (int j = 0; j < SIZE_Y; j++){
      		monde[i][j]++;
		}
	}
}






