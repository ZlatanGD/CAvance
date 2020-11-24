#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

//Defines===========================================================================================
#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 0
#define CPT 100
#define Epredateur 150
#define Eproie 15



int main(void) {
  srand(time(NULL));
  FILE *file = fopen("Evol_Pop.txt","w");
  //Creation du monde de taille SIZE_X et SIZE_Y
  int monde[SIZE_X][SIZE_Y];
  for (int i = 0;i<SIZE_X;i++)
  {
    for (int j = 0;j<SIZE_Y;j++)
    {
      monde[i][j] = 0;
    }
  }
  //Creation de NB_PROIES proie(s)
  Animal *lproies;
  {
    int x = rand()%(SIZE_X-2) + 1;
    int y = rand()%(SIZE_Y-2) + 1;
    float e = (float)(rand()*1.0)/(RAND_MAX*1.0) * Eproie;
    lproies = creer_animal(x,y,e);
  }

  //Creation de NB_PREDATEURS predateur(s)
  Animal *lpredateurs;
  {
    int x = rand()%(SIZE_X-2) + 1;
    int y = rand()%(SIZE_Y-2) + 1;
    float e = (float)(rand()*1.0)/(RAND_MAX*1.0) * Epredateur;
    lpredateurs = creer_animal(x,y,e);
  }

  //Ajout de(s) proie(s) dans la liste
  for (int i = 1;i<NB_PROIES;i++)
    {
      int x = rand()%(SIZE_X-2) + 1;
      int y = rand()%(SIZE_Y-2) + 1;
      float e = (float)(rand()*1.0)/(RAND_MAX*1.0) * Eproie;
      ajouter_animal(x,y,e,&lproies);
    }
  //Ajout de(s) predateur(s) dans la liste
    for (int i = 1;i<NB_PREDATEURS;i++)
    {
      int x = rand()%(SIZE_X-2) + 1;
      int y = rand()%(SIZE_Y-2) + 1;
      float e = (float)(rand()*1.0)/(RAND_MAX*1.0) * Epredateur;
      ajouter_animal(x,y,e,&lpredateurs);
    }

  //Creation de la boucle
  int cpt = 0;
  int cptproie = compte_animal_it(lproies);
  int cptpredateur = compte_animal_it(lpredateurs);

  while (cpt<CPT && cptproie>0 && cptpredateur>0){
    //Ecrire dans le file les cpts
    fprintf(file,"%d %d %d\n",cpt,cptproie,cptpredateur);
    clear_screen();
    afficher_ecosys(lproies,lpredateurs);
    printf("Nombre de proies à la fin: %d \n",cptproie);
    printf("Nombre de predateurs à la fin: %d \n",cptpredateur);
    printf("Nombre d'iterations: %d \n",cpt);

    //Rafraichir les animaux
    rafraichir_predateurs(&lpredateurs,&lproies);
    rafraichir_proies(&lproies,monde);
    rafraichir_monde(monde);

    //Bouger les animaux
    bouger_animaux(lproies);
    bouger_animaux(lpredateurs);

    //Update des cpt
    cptproie = compte_animal_it(lproies);
    cptpredateur = compte_animal_it(lpredateurs);
    cpt++;

    //Sleep
    usleep(T_WAIT);
  }
  clear_screen();
  afficher_ecosys(lproies,lpredateurs);
  cptproie = compte_animal_it(lproies);
  cptpredateur = compte_animal_it(lpredateurs);
  fprintf(file,"%d %d %d\n",cpt,cptproie,cptpredateur);
  printf("Nombre de proies à la fin: %d \n",cptproie);
  printf("Nombre de predateurs à la fin: %d \n",cptpredateur);
  printf("Nombre d'iterations: %d \n",cpt);

  //Liberation de memoire
  liberer_liste_animaux(lproies);
  liberer_liste_animaux(lpredateurs);
  //free(file);
  return 0;
}


