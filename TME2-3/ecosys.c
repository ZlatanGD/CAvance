#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

//Probabilités
float p_ch_dir=0.3;
int gain_energie_proie=6;
int gain_energie_predateur = 20;
float p_reproduce_proie=0.01;
float p_reproduce_predateur=0.02;
float p_manger = 1;
int temps_repousse_herbe=-15;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na); //na existe
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand()%3-1;
  na->dir[1] = rand()%3-1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal); //asert animal existe
  assert(!animal->suivant); //assert animal suivant n'existe pas
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **lanimal) {
  Animal *nouvanimal = creer_animal(x,y,energie);
  Animal *temp = *lanimal;
  while(temp)
  {
    if(temp->suivant == NULL)
    {
      temp->suivant = nouvanimal;
      nouvanimal->suivant = NULL;
      return;
    }
    temp=temp->suivant;
  }
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *temp = *liste;//Creation d'un animal temp
  Animal *avant = NULL;//Creation d'un animal d'avant
  if(temp == animal)//Verifier si l'animal donné en parametre est egale au temp
  {
    *liste = (*liste)->suivant;
    free(animal);
    return;
  }

  while(temp)//While temp existe(jusqu'a la fin de la liste)
  {
    if(temp == animal)
    {
      avant->suivant = temp ->suivant;
      free(animal);
      return;
    }
    avant = temp;
    temp = temp->suivant;
  }
  return;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
   Animal *temp;//Creation d'un animal temp
   while(liste)//Jusqu'a la fin de la liste, faire:
   {
     temp = liste->suivant;
     free(liste);
     liste = temp;
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
  char ecosys[SIZE_X][SIZE_Y];//Initialiser le tableau
  for(i = 0;i<SIZE_X;i++)
  {
    for(j = 0; j<SIZE_Y;j++)
    {
      if( (i == 0 && j == 0)
       || (i==SIZE_X-1 && j == 0)
       || (i==0 && j==SIZE_Y-1)
       || (i==SIZE_X-1 && j==SIZE_Y-1))
        {
        ecosys[i][j] = '+'; //mettre les + dans les coins
        }
        else if(j==0 || j==SIZE_Y - 1){
          ecosys[i][j] = '|';//barre vertical des cotes
        }
        else if (i==0 || i==SIZE_X - 1){
          ecosys[i][j] = '-';//brodure du haut et bas
        }
        else{
          ecosys[i][j] = ' ';
        }
    }
  }

  Animal *proiesuiv = liste_proie;
  while(proiesuiv){
    ecosys[proiesuiv->x][proiesuiv->y] = '*';//proie representé par *
    proiesuiv = proiesuiv->suivant;
  }
 //Ajoue des predateurs
  Animal *nextPredateur = liste_predateur;
  while(nextPredateur){//parcourire les predateurs
    if(ecosys[nextPredateur->x][nextPredateur->y]=='*'){
      ecosys[nextPredateur->x][nextPredateur->y] = '@';
    }
    else{
      ecosys[nextPredateur->x][nextPredateur->y] = 'O';
    }
    nextPredateur = nextPredateur->suivant;
  }
  //Affichage du tableau
  for (int i = 0;i<SIZE_X;i++){
    if(i<10){printf(" ");}
    printf("%d",i);
    for(int j = 0;j<SIZE_Y;j++){
      printf("%c",ecosys[i][j]);
    }
    printf("\n");
  }
}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H"); 
}

/* PARTIE 2*/
/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *liste_animal) {
  while(liste_animal){
    int x = liste_animal->x + liste_animal->dir[0];
    int y = liste_animal->y + liste_animal->dir[1];

    if (x == SIZE_X -1)
    {
      x = 1;
    }

    if (x == 0)
    {
      x = SIZE_X -2;
    }

    if (y == SIZE_Y-1)
    {
      y = 1;
    }

    if (y == 0)
    {
      y = SIZE_Y - 2;
    }

    liste_animal->x = x;
    liste_animal->y = y;

    float randInt = (float)(rand()*1.0/RAND_MAX*1.0);
    if (randInt < p_ch_dir){
      liste_animal->dir[0]=(rand()%3)-1;
      liste_animal->dir[1]=(rand()%3)-1;
    }
    liste_animal = liste_animal->suivant;
  }
}

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *anim = NULL;
  Animal *temp = *liste_animal;
  while(temp)
  {
    float r = (float)(rand()*1.0/RAND_MAX*1.0);
    if(r<p_reproduce)
    {
      if(compte_animal_it(anim)==0){
        anim = creer_animal(temp->x,temp->y,temp->energie / 2);
        temp->energie *=0.5;
      }
      else
      {
        ajouter_animal(temp->x,temp->y,temp->energie / 2,&anim);
        temp->energie *=0.5;
      }
    }
    temp = temp->suivant;
  }
  temp = *liste_animal;
  while(temp)
  {
    if(temp->suivant ==NULL)
    {
      temp->suivant = anim;
      return;
    }
    temp = temp->suivant;
  }
}


/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) 
{
  Animal *temp = *liste_proie;
  while (temp)
  {
    temp->energie--;
    if(monde[temp->x][temp->y]>0)
    {
      temp->energie += gain_energie_proie;
      monde[temp->x][temp->y] = temps_repousse_herbe;
    }
    if(temp->energie<=0)
    {
      enlever_animal(liste_proie,temp);
    }
    temp = temp->suivant;
  }
  reproduce(liste_proie,p_reproduce_proie);
}    

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) 
{
      while (l)
      {
      if(l->x==x && l->y==y)
      {
        return l;
      }
      l = l->suivant;
    }
  return NULL;
}


/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) 
{
  Animal *temp = *liste_predateur;
  while (temp)
  {
    float r = (float)(rand()*1.0/RAND_MAX*1.0);
    temp->energie--;
    Animal *proie = animal_en_XY(*liste_proie,temp->x,temp->y);
    if(proie !=NULL && r<p_manger)
    {
      temp->energie +=gain_energie_predateur;
      enlever_animal(liste_proie,proie);
      proie = NULL;
    }
    if(temp->energie<=0)
    {
      enlever_animal(liste_predateur,temp);
    }
    temp = temp->suivant;
  }
  reproduce(liste_predateur,p_reproduce_predateur);
}


/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y])
{
  for(int i = 0;i<SIZE_X-1;i++){
    for (int j = 1;j<SIZE_Y-1;j++){
      monde[i][j] +=1;
    }
  }
}

