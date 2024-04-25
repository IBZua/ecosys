#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.3;
float p_reproduce_predateur=0.1;
int temps_repousse_herbe=-8;

/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
	Animal *animal = (Animal *)malloc(sizeof(Animal));
	assert(animal);
	animal->x = x;
	animal->y = y;
	animal->energie = energie;
	animal->dir[0] = rand() % 3 - 1;
	animal->dir[1] = rand() % 3 - 1;
	animal->suivant = NULL;
	return animal;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
	assert(animal);
	assert(!animal->suivant);
	animal->suivant = liste;
	return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
	//on verifie que x et y sont dans les limites du monde
	assert(x<SIZE_X);
  	assert(y<SIZE_Y);
  	//on cree l'animal
	Animal *animal = creer_animal(x,y,energie);
	//on l'ajoute
	*liste_animal = ajouter_en_tete_animal(*liste_animal,animal);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
	//Si le pointeur est null, si liste vide ou si l'animal est null
	if  (liste == NULL || *liste == NULL || animal == NULL)
	{
    	return ;
	}
	//Si animal premier element
	if (*liste == animal)
	{
		Animal *tmp = *liste;
		*liste = (*liste)->suivant;
		free(tmp);
		return ;
	}
	//On declare actuel un pointeur sur animal qui sert de "curseur" dans la liste
	Animal *actuel = *liste;
	//On parcourt la liste tant que l'animal suivant n'est pas animal
	while(actuel->suivant != animal && actuel != NULL){
		actuel = actuel->suivant;
	}
	//Si animal n'est pas dans la liste
	if (actuel == NULL)
	{
		return ;
	}
	//Sinon animal trouve
	Animal *tmp = actuel->suivant;
	actuel->suivant = animal->suivant;
	free(tmp);
	return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
	//Si liste vide
	if (liste == NULL)
	{
    	return NULL;
	}
	//Sinon on parcourt la liste tant que pas NULL
	Animal *stock = NULL;
	while(liste != NULL){
		stock = liste->suivant;
		free(liste);
		liste = stock;
	}
	return NULL;
}

// Fourni: part 1, exercice 4, question 4
unsigned int compte_animal_rec(Animal *la) {
	if (!la) return 0;
	return 1 + compte_animal_rec(la->suivant);
}

//Fourni: part 1, exercice 4, question 4
unsigned int compte_animal_it(Animal *la) {
	int cpt=0;
	while (la) {
		++cpt;
		la=la->suivant;
	}
	return cpt;
}



//Fourni en TD : part 1. Exercice 5, question 1
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur)
{
	int i, j;
    char ecosys[SIZE_X][SIZE_Y];
    Animal *pa = NULL;

    /* on initialise le tableau */
    i = 0;
    while (i < SIZE_X)
    {
        j = 0;
        while (j < SIZE_Y)
        {
            ecosys[i][j] = ' ';
            j++;
        }
        i++;
    }

    /* on ajoute les proies */
    pa = liste_proie;
    while (pa)
    {
        ecosys[pa->x][pa->y] = '*';
        pa = pa->suivant;
    }

    /* on ajoute les predateurs */
    pa = liste_predateur;
    while (pa)
    {
        if (ecosys[pa->x][pa->y] == '*')
        { 
        	/* proies aussi present */
            ecosys[pa->x][pa->y] = '@';
        }
        else
        {
            ecosys[pa->x][pa->y] = 'O';
        }
        pa = pa->suivant;
    }
    /* on affiche le tableau */
    printf("+");
    for (j = 0; j < SIZE_Y; j++)
    {
        printf("-");
    }
    printf("+\n");
    i = 0;
    while (i < SIZE_X)
    {
        printf("|");
        j = 0;
        while (j < SIZE_Y) {
        	//Coloration proie
	        if (ecosys[i][j] == '*') {
	            // Changer la couleur en bleu pour '*'
	            printf("\x1b[96m*\x1b[0m");
	            //Coloration predateurs
	        } else if (ecosys[i][j] == 'O') {
	            // Changer la couleur en jaune pour 'O'
	            printf("\x1b[93mO\x1b[0m");
	        } else {
	            putchar(ecosys[i][j]);
	        }
	        j++;
	    }
        printf("|\n");
        i++;
    }
    printf("+");
    for (j = 0; j < SIZE_Y; j++)
    {
        printf("-");
    }
    printf("+\n\n");
    int nbproie = compte_animal_it(liste_proie);
    int nbpred = compte_animal_it(liste_predateur);

    printf("Nb proies (*): %d\nNb predateurs (O) : %d\n", nbproie, nbpred);
}

//Fourni
void clear_screen() {
	printf("\x1b[3J");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

// Part 2. Exercice 4, question 1
void bouger_animaux(Animal *la)
{
	//Initialisation pointeur parcourt liste animaux
	Animal *tmp = la;
	//On parcourt la liste
	while (tmp)
    {
    	//On test si l'animal change de direction
        if (rand() * RAND_MAX / (float) (RAND_MAX) < p_ch_dir)
        {
            tmp->dir[0] = rand() % 3-1;
            tmp->dir[1] = rand() % 3-1;
        }
        //On maj ses coordonnées
        tmp->x = (tmp->x + tmp->dir[0] + SIZE_X) % SIZE_X;
        tmp->y = (tmp->y + tmp->dir[1] + SIZE_Y) % SIZE_Y;

        tmp = tmp->suivant;
    }
}

///* Part 2. Exercice 4, question 3 
void reproduce(Animal **liste_animal, float p_reproduce)
{
	//permet d'éviter un pointeur sur null, éviter d'avoir *tmp = *NULL;
    Animal *tmp = liste_animal ? *liste_animal : NULL;

    //On parcourt la liste
    while (tmp)
    {
    	//On verifie la probabilite que l'animal se reproduise
        if (rand() / (float) (RAND_MAX) < p_reproduce)
        {
            ajouter_animal(tmp->x, tmp->y, tmp->energie/2, liste_animal);
            tmp->energie /= 2;
        }
        tmp = tmp->suivant;
    }
}
//*/

/* Part 2. Exercice 6, question 1 */
///*
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y])
{
	//On rafraichit le monde
    rafraichir_monde(monde);
    //variable de parcourt de la liste
	Animal *tmp = *liste_proie;
    bouger_animaux(tmp);
    while(tmp)
    {
    	assert(tmp->x >= 0 && tmp->x < SIZE_X);
        assert(tmp->y >= 0 && tmp->y < SIZE_Y);
    	//s'il y a de l'herbe
		if (monde[tmp->x][tmp->y] > 0)
		{
			tmp->energie = tmp->energie + monde[tmp->x][tmp->y];
			monde[tmp->x][tmp->y] = temps_repousse_herbe;
		}
		tmp->energie = tmp->energie - 1.0;
		//si animal n'a plus d'energie
		if (tmp->energie <= 0.0)
		{
			Animal *a_supp = tmp;
			tmp = tmp->suivant;
			enlever_animal(liste_proie,a_supp);
		}else
		{
			tmp = tmp->suivant;
		}
		
    }
    reproduce(liste_proie,p_reproduce_proie);
}
//*/

/* Part 2. Exercice 7, question 1 */
///*
Animal *animal_en_XY(Animal *l, int x, int y)
{
	Animal *tmp = l;
	while(tmp)
	{
		if (tmp->x == x && tmp->y == y)
		{
			return tmp;
		}
		tmp = tmp->suivant;
	}
	return NULL;
} 
//*/

/* Part 2. Exercice 7, question 2 */
///*
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie)
{
	Animal *tmp_predateur = *liste_predateur;
    bouger_animaux(tmp_predateur);
    while(tmp_predateur)
    {
    	assert(tmp_predateur->x >= 0 && tmp_predateur->x < SIZE_X);
        assert(tmp_predateur->y >= 0 && tmp_predateur->y < SIZE_Y);
    	Animal *proie = animal_en_XY(*liste_proie, tmp_predateur->x, tmp_predateur->y);
    	//si proie
    	if (proie)
    	{
    		tmp_predateur->energie += proie->energie;
    		enlever_animal(liste_proie, proie);
    	}
		tmp_predateur->energie -= 1.0;
		if (tmp_predateur->energie <= 0.0)
		{
			Animal *a_supp = tmp_predateur;
			tmp_predateur = tmp_predateur->suivant;
			enlever_animal(liste_predateur,a_supp);
		}else
		{
			tmp_predateur = tmp_predateur->suivant;
		}	
    }
	reproduce(liste_predateur,p_reproduce_predateur);
}
//*/

/* Part 2. Exercice 5, question 2 */
///*
void rafraichir_monde(int monde[SIZE_X][SIZE_Y])
{
	for(int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			monde[i][j] += 1;
		}
	}
}
//*/
