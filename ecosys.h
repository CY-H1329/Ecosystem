#ifndef _ECOSYS_H_
#define _ECOSYS_H_

#define SIZE_X 20
#define SIZE_Y 50
#define NB_PROIES 20
#define NB_PREDATEURS 20

#define Modulo(x, y) (((x) % (y) + (y)) % (y))
#define Probabilite(p) ((float)rand()/(float)RAND_MAX < (p))




/* Parametres globaux de l’ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir; //probabilte de changer de direction de dsplacement
int gain_energie_proie;
int gain_energie_predateur;
float p_reproduce_proie;
float p_reproduce_predateur;
float p_manger;
int temps_repousse_herbe;


typedef struct _animal {
  int x;
  int y;
  int dir[2]; /* direction courante sous la forme (dx, dy) */
  float energie;
  struct _animal *suivant;
} Animal;



Animal *creer_animal(int x, int y, float energie);
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);
unsigned int compte_animal_rec(Animal *la);
unsigned int compte_animal_it(Animal *la);

void ajouter_animal(int x, int y, Animal **liste_animal);
void enlever_animal(Animal **liste, Animal *animal);
Animal* liberer_liste_animaux(Animal *liste);
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie);



void bouger_animaux(Animal *la);
void reproduce(Animal **liste_animal, float p_reproduce);
Animal *animal_en_XY(Animal *l, int x, int y);
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) ;
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);

void clear_screen();

#endif
