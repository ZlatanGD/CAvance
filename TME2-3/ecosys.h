#ifndef _ECOSYS_H_
#define _ECOSYS_H_

#define SIZE_X 20
#define SIZE_Y 50

//Structure d'un animal=============================================================================
typedef struct _animal {
  int x;
  int y;
  int dir[2]; /* direction courante sous la forme (dx, dy) */
  float energie;
  struct _animal *suivant;
} Animal;

//Probabulités=========================================================================================
extern float p_ch_dir; 
extern int gain_energie_proie;
extern int gain_energie_predateur;
extern float p_reproduce_proie;
extern float p_reproduce_predateur;
extern int temps_repousse_herbe;

//Creation, ajout et enlever============================================================================
extern Animal *creer_animal(int x, int y, float energie);
extern Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);
extern void ajouter_animal(int x, int y, float energie, Animal **liste_animal);
extern Animal* liberer_liste_animaux(Animal *liste);
extern void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie);
extern void enlever_animal(Animal **liste, Animal *animal);

//Compteurs==============================================================================================
extern unsigned int compte_animal_rec(Animal *la);
extern unsigned int compte_animal_it(Animal *la);

//Bouger et reproduire les animaux========================================================================
extern void bouger_animaux(Animal *la);
extern void reproduce(Animal **liste_animal, float p_reproduce);

//Refresh=================================================================================================
extern void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie);
extern void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) ;
extern void rafraichir_monde(int monde[SIZE_X][SIZE_Y]);

extern void clear_screen();

#endif
