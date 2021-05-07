#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <math.h> 
#include "enigme.h"


/** 
* @brief generer l'enigme . 
* @param e enigme 
* @return e 
*/ 

enigme generer()
{

    enigme e;
    srand(time(NULL)); 
    int a, b;
    int x=1+rand()%6; 
    int y=1+rand()%7;
    int i=rand()%4; 
    float rv,rf1,rf2;
    char operations[4]="+-/*";  
     
   
    e.numrep=rand()%3; 
    a=rand()%101;  
    b=1+rand()%101;  

   if(i==0)
    {
        rv=(a)+(b);     
        rf1=rv-x;      
        rf2=rv+y;     
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",a,operations[i],b);
    }
    if(i==1)
    {
        rv=(a)-(b);  
        rf1=rv-y;      
        rf2=rv+y;      
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",a,operations[i],b);
    }
    if(i==2)
    {

        rv=(float)a/b;    
        rf1=rv-3;           
        rf2=rv+2;           
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",a,operations[i],b);

    }
    if(i==3)
    {
        rv=a*b;       
        rf1=rv-y;       
        rf2=rv+x;       
        sprintf(e.question,"Quelle est la reponse de cette operation %d %c %d : ",a,operations[i],b);
    }

    switch (e.numrep)   
    {
    case 0:
        sprintf(e.reponse1,"Reponse 1 : %.1f",rv);
        sprintf(e.reponse2,"Reponse 2 : %.1f",rf1);
        sprintf(e.reponse3,"Reponse 3 : %.1f",rf2);
        break;
    case 1:
        sprintf(e.reponse1,"Reponse 1 : %.1f",rf1);
        sprintf(e.reponse2,"Reponse 2 : %.1f",rv);
        sprintf(e.reponse3,"Reponse 3 : %.1f",rf2);
        break;
    case 2:
        sprintf(e.reponse1,"Reponse 1 : %.1f",rf2);
        sprintf(e.reponse2,"Reponse 2 : %.1f",rf1);
        sprintf(e.reponse3,"Reponse 3 : %.1f",rv);
        break;
    }

    return e;
}


/** 
* @brief affichage de l'enig . 
* @param e enigme 
* @param ecran surface 
* @return nothing
*/ 

void afficher_enigme(enigme e, SDL_Surface*ecran){

	SDL_Surface *menu=NULL, *question=NULL, *resultat1=NULL, *resultat1a=NULL, *resultat2=NULL, *resultat2a=NULL, *resultat3=NULL, *resultat3a=NULL, *reponsef=NULL, *reponsev=NULL; 
	SDL_Rect position
, positionenigme, positionresultat1, positionresultat2, positionresultat3, positionvrai, positionfaux, positionrep, positionreponsef, positionreponsev, positioncasevide1, positioncasevide2, positioncasevide3;
	SDL_Event event;
        SDL_Surface *couche[2], *casevide=NULL;   
	TTF_Font *policetexte=NULL;
	SDL_Color couleurblanc={255,255,255};
    SDL_Color couleurrouge={255,0,0};
    SDL_Color couleurvert={0,255,0};
	int continuer=1;
	e=generer();
	int choix, v;
	
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	ecran=SDL_SetVideoMode(600,399,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

        couche[0] = IMG_Load("casevrai.png");
        couche[1] = IMG_Load("casefaux.png");
        casevide  = IMG_Load("casevide.png");



	policetexte=TTF_OpenFont("angelina.ttf",23);
	question=TTF_RenderText_Blended(policetexte,e.question,couleurblanc);

	resultat1=TTF_RenderText_Blended(policetexte,e.reponse1,couleurblanc);

	resultat2=TTF_RenderText_Blended(policetexte,e.reponse2,couleurblanc);

	resultat3=TTF_RenderText_Blended(policetexte,e.reponse3,couleurblanc);

	reponsef=TTF_RenderText_Blended(policetexte,"c'est faux :(((",couleurrouge);
	reponsev=TTF_RenderText_Blended(policetexte,"trés Bien !! c'est vrai ;)",couleurvert);

	menu=IMG_Load("tache.png");

	positionmenu.x=0;
	positionmenu.y=0;
	SDL_BlitSurface(menu,NULL,ecran,&positionmenu);
    
	positioncasevide1.x=125;
	positioncasevide1.y=135;

	positioncasevide2.x=125;
	positioncasevide2.y=185;

	positioncasevide3.x=125;
	positioncasevide3.y=235;

	positionvrai.x = 125;  
        positionfaux.x = 125;   

	positionenigme.x=40;  
	positionenigme.y=100;

	positionresultat1.x=205;
	positionresultat1.y=150;

	positionresultat2.x=205;
	positionresultat2.y=200;

	positionresultat3.x=205;
	positionresultat3.y=250;

	positionreponsef.x=200;   
	positionreponsef.y=300;

	positionreponsev.x=120;   
	positionreponsev.y=300;


         switch(e.numrep)
         {
            case 0:
             positionvrai.y = positionresultat1.y-15;   
            break;
            case 1:
             positionvrai.y = positionresultat2.y-15;
            break;
            case 2:
             positionvrai.y = positionresultat3.y-15;
	    break;
         }

	while(continuer!=0){

	if(SDL_PollEvent(&event)){
	switch(event.type){
		case SDL_QUIT:
            	continuer = 0;
              	break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			   case SDLK_KP1:   
			     choix=0;
                              positionfaux.y =positionresultat1.y-15;

				if(choix!=e.numrep){
				
                		v = 1;
                		positionrep = positionfaux; 
			  SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				}
				else{
                		v = 0;
				
                		positionrep = positionvrai; 
			  SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
			  SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);    
				SDL_Delay(1000); 
        			}
			if(v!=0){

			  SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				 v=0;				
			  SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}

				 continuer=0;

				break;
				case SDLK_KP2:
				choix=1;
                                positionfaux.y =positionresultat2.y-15;


				if(choix!=e.numrep){
				
                		v = 1;
                		positionrep = positionfaux;
			   SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				}
				else{
               			 v = 0;
				
                		positionrep = positionvrai;
			   SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);


			  SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
        			}
			if(v!=0){

			  SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;
			  SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}

				continuer=0;

				break;
				case SDLK_KP3:
				choix=2;
                                positionfaux.y =positionresultat3.y-15;

				if(choix!=e.numrep){
				
                		v = 1;
                		positionrep = positionfaux;
			   SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				}
				else{
                		v = 0;
				
                		positionrep = positionvrai;
			    SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);

			  SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
        			}
			if(v!=0){


			 SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;
			 SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}

				continuer=0;

				break;
			}
		break;
		case SDL_MOUSEBUTTONDOWN:
		if(event.button.button == SDL_BUTTON_LEFT){
			if((event.button.x >= 125 && event.button.x <= 170) && (event.button.y >= 135 && event.button.y <= 184))
                 	{
				choix=0;
                                positionfaux.y =positionresultat1.y-15;


				if(choix!=e.numrep){
				
                		v = 1;
                		positionrep = positionfaux;
			SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				}
				else{
                		v = 0;
				
                		positionrep = positionvrai;
			SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);

			SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
        			}
				if(v!=0){


			 SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;
			 SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
			continuer=0;

			}
			if((event.button.x >= 125 && event.button.x <= 170) && (event.button.y >= 185 && event.button.y <= 234))
                 	{
				choix=1;
                                positionfaux.y =positionresultat2.y-15;


				if(choix!=e.numrep){
				
                		v = 1;
                		positionrep = positionfaux;
			   SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				}
				else{
               			 v = 0;
				
                		positionrep = positionvrai;
			   SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);

			 SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
        			}
				if(v!=0){


			 SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;
			   SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
			continuer=0;

			}
			if((event.button.x >= 125 && event.button.x <= 170) && (event.button.y >= 235 && event.button.y <= 285))
                 	{
				choix=2;
                                positionfaux.y =positionresultat3.y-15;


				if(choix!=e.numrep){
				
                		v = 1;
                		positionrep = positionfaux;
			    SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);
				}
				else{
                		v = 0;
				
                		positionrep = positionvrai;
			      SDL_BlitSurface(couche[v],NULL,ecran,&positionrep);


			  SDL_BlitSurface(reponsev,NULL,ecran,&positionreponsev);
				SDL_Flip(ecran);
				SDL_Delay(1000);
        			}
				if(v!=0){


			  SDL_BlitSurface(reponsef,NULL,ecran,&positionreponsef);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				v=0;
			  SDL_BlitSurface(couche[v],NULL,ecran,&positionvrai);
				SDL_Flip(ecran);
				SDL_Delay(1000);
				}
			continuer=0;

			}


		}
		break;
	}
	}


	SDL_BlitSurface(casevide,NULL,ecran,&positioncasevide1);
	SDL_BlitSurface(casevide,NULL,ecran,&positioncasevide2);
	SDL_BlitSurface(casevide,NULL,ecran,&positioncasevide3);
	SDL_BlitSurface(question,NULL,ecran,&positionenigme);
	SDL_BlitSurface(resultat1,NULL,ecran,&positionresultat1);
	SDL_BlitSurface(resultat2,NULL,ecran,&positionresultat2);
	SDL_BlitSurface(resultat3,NULL,ecran,&positionresultat3);
	SDL_Flip(ecran);

	}

TTF_CloseFont(policetexte);
TTF_Quit;
SDL_FreeSurface(couche[0]);
SDL_FreeSurface(couche[1]);
SDL_FreeSurface(question);
SDL_FreeSurface(resultat1);
SDL_FreeSurface(resultat2);
SDL_FreeSurface(resultat3);
SDL_Quit();
}
