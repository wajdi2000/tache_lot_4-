typedef struct
{
	SDL_Surface *ecran;
	SDL_Rect Positionecran;	/*!< rectangle*/
	SDL_Surface *background1;
	SDL_Surface *background1m;

}background;

typedef struct 
{
	int speed;
	SDL_Surface *perso;/*!<surface*/
	SDL_Rect positionperso; 
	SDL_Rect positionpersomini; 	
}personnage;

typedef struct{
SDL_Surface *persomini,*miniload,*masque;
SDL_Rect pospermini,posmini;
}minimap;



void init_background(background *b);
void afficher_background(background b);
void init_perso(personnage *p,background b);

void MAJMinimap(personnage *p);
void initmap( minimap * m);
void  afficherminimap (minimap m, background b,personnage p);
void affichertemps (int m,int s,char min[3],char sec[3],char fulltime[10], SDL_Surface *time,int* temps,TTF_Font *font,SDL_Color colortemps,SDL_Rect postemp,background b);
void majtemp(int *temps,int *timer);
void afficher_perso(personnage p,background b);
void mouvement_perso(int direction,personnage *p, background b,int collision);
SDL_Color GetPixel(background b,int x,int y);
int collisionPP( personnage p, background b);
