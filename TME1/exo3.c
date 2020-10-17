#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 5

int compte_mots_chaine(char *chaine)
{
    int cpt=0;
    while(*chaine)
    {
        if(*chaine==' ')
        {
            cpt++;
        }chaine++;
    }return cpt+1;
}

int compte_mots(char *chaine[])
{
    int cpt=0;
    while(*chaine)
    {
        cpt++;
        chaine++;
    }return cpt;
}

void AffichageMotsTab(char *chaine[])
{
    int cpt=0;
    while(*chaine)
    {
        printf("%s ",chaine[cpt]);
        chaine++;
    }printf("\n");
}

void detruit_tab_mots(char **chaine)
{
    int cpt=0;
    while(*chaine)
    {
        free(chaine[cpt]);
        cpt++;
    }free(chaine);
}

char *compose_chaine(char **chaine)
{
    int cpt;
    int nb_char=0;
    int nb_mots = compte_mots(chaine);
    char *res=malloc(sizeof(char));
    for(cpt=0;cpt<nb_mots;cpt++)
    {
        nb_char+=compte_mots_chaine(chaine[cpt])+1;
        res=realloc(res,sizeof(char)*nb_char);
        if(cpt != 0)
        {
            strcat(res," ");
            strcat(res, chaine[cpt]);
        }
        else
        {
            strcat(res, chaine[cpt]);
        }
        
    }return res;
}

int main(void)
{
    char *chaine={"B ao ja sae vrev m ezev bio"};
    char *chaine2[TAILLE]={"ja","sam","kao","tipa",NULL};
    printf("%d \n",compte_mots(chaine2));
    AffichageMotsTab(chaine2);
    printf("%s \n",compose_chaine(chaine2));
    //printf("%d \n",compte_mots_chaine(chaine));
}