#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/** 
* @struct enigme 
* @brief struct for enigme
*/ 


typedef struct{
    char question[100];/*!< question*/
    char reponse1[100];/*!< reponse 1*/
    char reponse2[100];/*!< Reponse 2*/
    char reponse3[100];/*!< reponse 3*/
    int numrep;/*!< numero de reponse*/
}enigme;

enigme generer();
void afficher_enigme(enigme e, SDL_Surface*ecran);


#endif // FONCTION_H_INCLUDED

