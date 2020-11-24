#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"
#define NB_PROIES 60
#define NB_PREDATEURS 5

int main(void)
{
  clear_screen();//effacer tout affichage du terminal
  srand(time(NULL));//reset de srand
  //Creation du monde de taille SIZE_X et SIZE_Y
  int monde[SIZE_X][SIZE_Y];
  for (int i = 0;i<SIZE_X;i++){
    for (int j = 0;j<SIZE_Y;j++){
      monde[i][j] = 0;
    }
  }

  Animal *proie;
  Animal *predateur;

//Creation de la premiere proie et predateur========================================================
  proie = creer_animal(2,2,15);
  predateur = creer_animal(5,5,20);

//Attribution des positions et energie a NB_PROIES proie(s)=========================================
  for(int i=1; i<NB_PROIES; i++)
  {
    int x = rand()%(SIZE_X-2) + 1;
    int y = rand()%(SIZE_Y-2) + 1;
    float energie = (float)(rand()*1.0)/(RAND_MAX*1.0) * 20;
    ajouter_animal(x,y,energie,&proie);
  }  
//Attribution des positions et energie a NB_PREDATEURS predateur(s)=================================
  for(int i=1; i<NB_PREDATEURS; i++)
  {
    int x = rand()%(SIZE_X-2) + 1;
    int y = rand()%(SIZE_Y-2) + 1;
    float energie = (float)(rand()*1.0)/(RAND_MAX*1.0) * 20;
    ajouter_animal(x,y,energie,&predateur);
  }
//Affichage du nombre de proie(s) et predateur(s)====================================================
  printf("Nombre proie(s): %d \n",compte_animal_it(proie));
  printf("Nombre predateur(s): %d \n",compte_animal_it(predateur));
  
//Affichage du tableau===============================================================================
  afficher_ecosys(proie,predateur);

//Simulation de l'ecosysteme==========================================================================

for(int i=0; i<15; i++)
{
    printf("Tableau:\n");
//Refresh==============================================================================================

    rafraichir_predateurs(&predateur,&proie);
    rafraichir_proies(&predateur,monde);
    rafraichir_monde(monde);

//Bouger===============================================================================================

    bouger_animaux(proie);
    bouger_animaux(predateur);

//Afficher=============================================================================================
    afficher_ecosys(proie,predateur);
    printf("Nombre de proies restant: %d \n",compte_animal_it(proie));
    printf("Nombre de predateurs restant: %d \n",compte_animal_it(predateur));
    
    usleep(500000);
    clear_screen();
}

//Libere la memoire alloué pour les deux liste (proie et predateur)===================================
  printf("Done.\n");
  printf("Nombre de proies final: %d \n",compte_animal_it(proie));
  printf("Nombre de predateurs final: %d \n",compte_animal_it(predateur));
  afficher_ecosys(proie,predateur);
  liberer_liste_animaux(proie);
  liberer_liste_animaux(predateur);
  return 0;
}
