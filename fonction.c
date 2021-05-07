/**
* @file fonction.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "struct.h"


void init_background(background *b) 
{
	b->ecran= SDL_SetVideoMode(1800,500,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (b->ecran==NULL)
	{
		printf("Unable to set video mode:%s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	b->background1=IMG_Load("b1.png"); 
	if (b->background1==NULL)
	{
		printf("Unable to load the background:%s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	b->background1m=SDL_LoadBMP("b1m.bmp"); 
	if (b->background1m==NULL)
	{
		printf("Unable to load the masque background:%s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	b->Positionecran.x=0; 
	b->Positionecran.y=0;
	b->Positionecran.w=b->background1->w; 
	b->Positionecran.h=b->background1->h; 


}

void afficher_background(background b)
{

	SDL_BlitSurface(b.background1, NULL, b.ecran, NULL);
}

void init_perso(personnage *p,background b)                               
{
	p->perso=IMG_Load("perso.png");                                           
	if (p->perso==NULL)
	{
		printf("Unable to load the personnage:%s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	p->positionperso.x=0;
	p->positionperso.y=b.background1->h-p->perso->h-120;
	p->positionperso.w=p->perso->w;
	p->positionperso.h=p->perso->h;
	
}


void initmap( minimap * m)
{
	m->miniload=IMG_Load("minimap.png");
	m->persomini=IMG_Load("persomini.png");
	m->posmini.x=2;
	m->posmini.y=2;

}
void MAJMinimap(personnage *p)
{
	p->positionpersomini.x=p->positionperso.x/5;
	p->positionpersomini.y=p->positionperso.y/5;
}

void  afficherminimap (minimap m, background b,personnage p)
{
	SDL_BlitSurface(m.miniload,NULL,b.ecran,&m.posmini);
	SDL_BlitSurface(m.persomini,NULL,b.ecran,&p.positionpersomini);

	MAJMinimap(&p);
}

void affichertemps (int m,int s,char min[3],char sec[3],char fulltime[10], SDL_Surface *time, int* temps,TTF_Font *font,SDL_Color colortemps,SDL_Rect postemp,background b)
{

	m=(*temps)/60;   /*!<calculer division comme minutes*/
	s=(*temps)%60; /*!<calculer reste division comme secondes*/
	sprintf(min,"%d",m); 
	sprintf(sec,"%d",s);
	if(m==0){min[0]='0';min[1]='0';} /*!<regulation de l'affichage en fonction de m et s*/
	else if(m<10){
	min[1]=min[0]; 
	min[0]='0';
	}
	if(s==0){sec[0]='0';sec[1]='0';}
	else if(s<10){
	sec[1]=sec[0];
	sec[0]='0';
	}
	strcpy(fulltime,min); 
	strcat(fulltime,":"); 
	strcat(fulltime,sec);
	time=TTF_RenderText_Blended(font,fulltime,colortemps);
	SDL_BlitSurface(time,NULL,b.ecran,&postemp);
}

void majtemp(int *temps,int *timer)
{
	if((*temps)>=0){(*timer)++;
	if((*timer)==24){
	(*temps)++;(*timer)=0;}}
}

void afficher_perso(personnage p,background b)
{
	SDL_BlitSurface(p.perso, NULL, b.ecran,&p.positionperso);
	SDL_Flip(b.ecran);
}

void mouvement_perso(int direction,personnage *p, background b,int collision)
{

	

		if (direction==1) 
		{
			if(collision==0)			
			p->positionperso.x+=p->speed;
			else
			p->positionperso.x-=p->perso->w;
		}
		if(direction==2)
		 {
			if (collision==0)
			p->positionperso.x-=p->speed;
			else
			p->positionperso.x+=p->perso->w;/*!<quand collision reculer comme largeur*/
		}
		if (direction==4) 
		{
			if(collision==0)			
			p->positionperso.y+=p->speed;
			else
			p->positionperso.y-=p->perso->w;
		}
		if(direction==3)
		 {
			if (collision==0)
			p->positionperso.y-=p->speed;
			else
			p->positionperso.y+=p->perso->w;
		}

	
}

SDL_Color GetPixel(background b,int x,int y) // kenet bm
{/*!<initialisation de X et Y aux cordonnes du personnage*/
SDL_Color color;
Uint32 col=0;
char* pPosition=(char* ) b.background1m->pixels;// pointeur ypointi al les pixels
pPosition+= (b.background1m->pitch * y);
pPosition+= (b.background1m->format->BytesPerPixel * x);//kol pixel kadeh feha mn b
memcpy(&col ,pPosition ,b.background1m->format->BytesPerPixel);
/*!<convertir color*/
SDL_GetRGB(col,b.background1m->format, &color.r, &color.g, &color.b);
return (color);
}

int collisionPP( personnage p, background b){
SDL_Color color[8];
color[0]=GetPixel(b,p.positionperso.x,p.positionperso.y);
color[1]=GetPixel(b,p.positionperso.x+p.positionperso.w/2,p.positionperso.y);
color[2]=GetPixel(b,p.positionperso.x+p.positionperso.w,p.positionperso.y);
color[3]=GetPixel(b,p.positionperso.x,p.positionperso.y+p.positionperso.h/2);
color[4]=GetPixel(b,p.positionperso.x,p.positionperso.y+p.positionperso.h);
color[5]=GetPixel(b,p.positionperso.x+p.positionperso.w/2,p.positionperso.y+p.positionperso.h);
color[6]=GetPixel(b,p.positionperso.x+p.positionperso.w,p.positionperso.y+p.positionperso.h);
color[7]=GetPixel(b,p.positionperso.x+p.positionperso.w,p.positionperso.y+p.positionperso.h/2);
int i=0;
while(i<8&& color[i].r!=0)
i++;
return i!=8;
}
