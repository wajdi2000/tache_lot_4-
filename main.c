/**
* @file main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "struct.h"
int main(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);	
	TTF_Init();
	SDL_Color colortemps; /*!<initialiser variable de type sdl couleur pour couleur de temps ( couleur rouge )*/
	colortemps.r = 150;
	colortemps.g =0;
	colortemps.b =0;
	SDL_Rect postemps;
	SDL_Surface *time;
       SDL_Surface *screen;
	char min[3],sec[3],fulltime[10];
	int minute,s;
	SDL_Rect posperso;
	postemps.y=40;
	postemps.x=600;
            screen= SDL_SetVideoMode(1800,500,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	TTF_Font *font;
	font = TTF_OpenFont("Ubuntu-Title.ttf", 50);
	minimap m;
	initmap(&m);
 	background b;
	personnage p;
	int done=1,x,y,collision=0,direction=0,temps=0,timer=0;
	p.speed=15;
	SDL_Event event;
	init_background(&b);
	afficher_background(b);
init_perso(&p,b);
while (done==1)
	{
	majtemp(&temps,&timer);
	collision=collisionPP(p,b);
	mouvement_perso(direction,&p,b,collision);afficher_background(b);afficher_perso(p, b);SDL_Flip(b.ecran);
		while(SDL_PollEvent(&event))
		{
	 		switch(event.type)
	 			 {
					case SDL_QUIT:
	     					done=0;
	     					break;
					case SDL_KEYDOWN :
						switch (event.key.keysym.sym) 
						{
							case SDLK_ESCAPE:
							done=0;
							break;
							case SDLK_LEFT:
                                                    direction=2;
      
			
							
							break;
							case SDLK_RIGHT:

       
                                                         direction=1;
        
							
							break;
							case SDLK_UP:
							direction=3;
							break;
							case SDLK_DOWN:
							direction=4;
							break;
						}break;
					case SDL_KEYUP :
						switch (event.key.keysym.sym) 
						{
							case SDLK_LEFT:
							direction=0;
							break;
							case SDLK_RIGHT:
							direction=0;
							break;
							case SDLK_UP:
							direction=0;
							break;
							case SDLK_DOWN:
							direction=0;
							break;
						}break;
	
					}
		}
		if(collision==0){colortemps.b=255;colortemps.g=255;colortemps.r=255;} 
	else  { colortemps.r=150,colortemps.g=0,colortemps.b=0;}
	affichertemps (minute,s,min,sec,fulltime,time,&temps,font,colortemps,postemps,b);
	MAJMinimap(&p);
	afficherminimap (m,b,p);
	SDL_Flip(b.ecran);

	
	}

SDL_FreeSurface(b.ecran);
SDL_FreeSurface(m.persomini);
SDL_FreeSurface(m.miniload);
SDL_FreeSurface(b.background1);
SDL_FreeSurface(b.background1m);
SDL_FreeSurface(p.perso);
TTF_Quit;
SDL_Quit();
return EXIT_SUCCESS;
}
