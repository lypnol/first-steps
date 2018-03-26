#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <string.h>
#include <time.h>

typedef struct direction direction;
struct direction
{
    int x ;
    int y ;
};

int checkcollision(SDL_Rect *position,SDL_Rect *position1);
void movepoint(SDL_Rect *position1, int vitesse, direction *direction1);
void init_position(SDL_Rect *position, const int *i);

int pause(int *niveau);
int game_on(SDL_Event *event,int *score_f,int *t, const int *tempsdebut, SDL_Rect *position, SDL_Rect positions[], direction directions[],int *niveau);

void explode(SDL_Surface *source, SDL_Surface *explosion,int *frame, int x,int y);

int main ( int argc, char** argv )
{
    SDL_Surface *ecran = NULL,*point = NULL, *points = NULL, *arriere_plan[13]= {NULL},*icon=NULL, *score = NULL, *record = NULL, *explosion=NULL, *source=NULL;
    SDL_Rect position, positions[20], positionarriere_plan, positionscore, positionrecord, pos_expl;
    direction directions[20]={{0,0}};
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    int fin = 1, t = 1,i=0, tempsdebut = 0, debutparti = 1, tempsPrecedent = 0, tempsActuel = 0, choix = 0,score_f = 0, niveau = 7,frame=0;
    long best_score = 0;
    char texte[40];
    char best[40];
    char best1[40],s[10];
    FILE *file_score=NULL;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    icon=SDL_LoadBMP("icone.bmp");
    SDL_SetColorKey(icon, SDL_SRCCOLORKEY, SDL_MapRGB(icon->format, 255, 255, 255));
    SDL_WM_SetIcon(icon,NULL);

    ecran = SDL_SetVideoMode(300, 300, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    SDL_WM_SetCaption("Stralen", NULL);

    source = SDL_LoadBMP("SkybusterExplosion.bmp");
    explosion = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);


    for(i=0;i<11;i++)
    {
        sprintf(s,"%d.bmp",i+1);
        arriere_plan[i] = SDL_LoadBMP(s);
    }
    arriere_plan[11] = SDL_LoadBMP("acceuil.bmp");
    arriere_plan[12] = SDL_LoadBMP("fin.bmp");

    point = SDL_LoadBMP("star.bmp");
    SDL_SetColorKey(point, SDL_SRCCOLORKEY, SDL_MapRGB(point->format, 255, 255, 255));

    points = SDL_LoadBMP("noir.bmp");
    SDL_SetColorKey(points, SDL_SRCCOLORKEY, SDL_MapRGB(points->format, 255, 255, 255));

    positionarriere_plan.x = 0;
    positionarriere_plan.y = 0;

    while(debutparti==1) //boucle principale: (tant que le joueur veut jouer une nouvelle partie)
    {
        TTF_CloseFont(police);
        police = TTF_OpenFont("angelina.ttf", 30);
        positionscore.y=220;
        SDL_FreeSurface(score);
        sprintf(texte,"niveau : %d",niveau);
        score = TTF_RenderText_Shaded(police, texte, couleurNoire, couleurBlanche);
        positionscore.x=ecran->w/2 - score->w/2;
        SDL_BlitSurface(arriere_plan[11], NULL, ecran, &positionarriere_plan);
        SDL_BlitSurface(score, NULL, ecran, &positionscore);
        SDL_Flip(ecran);
        debutparti=2;
        while (debutparti==2) //boucle du début de la partie:
        {
              debutparti = pause(&niveau);

              sprintf(texte,"niveau : %d",niveau);
              SDL_FreeSurface(score);
              score = TTF_RenderText_Shaded(police, texte, couleurNoire, couleurBlanche);
              positionscore.x=ecran->w/2 - score->w/2;
              SDL_BlitSurface(arriere_plan[11], NULL, ecran, &positionarriere_plan);
              SDL_BlitSurface(score, NULL, ecran, &positionscore);
              SDL_Flip(ecran);
        }
        if (debutparti==1) //si le joueur a accepté de commencer la partie:
        {
            choix=rand()%11; //choix aléatoire de l'arriere plan:

            for(i=0;i<niveau;i++) init_position(&positions[i],&i);

            position.x = ecran->w / 2 - point->w / 2;
            position.y = ecran->h / 2 - point->h / 2;
            SDL_ShowCursor(SDL_DISABLE);
            SDL_WarpMouse(ecran->w / 2, ecran->h / 2);
            tempsdebut = SDL_GetTicks();
            t = 1;
            score_f=0;
            TTF_CloseFont(police);
            police = TTF_OpenFont("angelina.ttf", 20);
            positionscore.x=0;
            positionscore.y=0;
            fin = 1;
            while(fin) // boucle pendent la partie:
            {

                SDL_PollEvent(&event);
                fin = game_on(&event,&score_f,&t,&tempsdebut,&position,positions,directions,&niveau);

                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent > 20)
                    tempsPrecedent = tempsActuel;
                else
                    SDL_Delay(20 - (tempsActuel - tempsPrecedent));

                SDL_BlitSurface(arriere_plan[choix], NULL, ecran, &positionarriere_plan);

                positionscore.x=0;
                SDL_FreeSurface(score);
                sprintf(texte, " score : %d", score_f);
                score = TTF_RenderText_Blended(police, texte, couleurNoire);
                SDL_BlitSurface(score, NULL, ecran, &positionscore);

                positionscore.x=230;
                SDL_FreeSurface(score);
                sprintf(texte, "niveau : %d", niveau);
                score = TTF_RenderText_Blended(police, texte, couleurNoire);

                SDL_BlitSurface(score, NULL, ecran, &positionscore);
                SDL_BlitSurface(point, NULL, ecran, &position);
                for (i=0;i<niveau;i++) SDL_BlitSurface(points, NULL, ecran, &positions[i]);
                SDL_Flip(ecran);
            }

            position.x = position.x - 320/2;
            position.y = position.y - 240/2;

            pos_expl.x = position.x;
            pos_expl.y = position.y;
            if(pos_expl.x<0) pos_expl.x=0;
            if(pos_expl.y<0) pos_expl.y=0;

            frame=0;
            while(frame<32)
            {
                if (frame<20)
                {
                    SDL_FillRect(explosion, NULL, SDL_MapRGB(explosion->format, 0, 0, 0));
                    explode(source,explosion,&frame, position.x,position.y);
                    SDL_SetColorKey(explosion, SDL_SRCCOLORKEY, SDL_MapRGB(explosion->format, 0, 0, 0));
                }

                frame++;

                SDL_BlitSurface(arriere_plan[choix], NULL, ecran, &positionarriere_plan);

                positionscore.x=0;
                SDL_FreeSurface(score);
                sprintf(texte, "score : %d", score_f);
                score = TTF_RenderText_Blended(police, texte, couleurNoire);
                SDL_BlitSurface(score, NULL, ecran, &positionscore);

                positionscore.x=230;
                SDL_FreeSurface(score);
                sprintf(texte, "niveau : %d", niveau);
                score = TTF_RenderText_Blended(police, texte, couleurNoire);

                SDL_BlitSurface(score, NULL, ecran, &positionscore);

                for (i=0;i<niveau;i++) SDL_BlitSurface(points, NULL, ecran, &positions[i]);

                if (frame<20) SDL_BlitSurface(explosion, NULL, ecran, &pos_expl);

                SDL_Flip(ecran);

                SDL_Delay(15);
            }


            //gestion du score:
            best_score=0;
            file_score=fopen("score.txt","r");
            if (file_score!=NULL)
            {
                rewind(file_score);
                fscanf(file_score,"%s",best);
                fclose(file_score);
                best_score = strtol(best,NULL,10);
                if (score_f>best_score)
                {
                    file_score=fopen("score.txt","w+");
                    fprintf(file_score,"%d", score_f);
                    fclose(file_score);
                    sprintf(texte, "nouveau record! : %d", score_f);
                    sprintf(best1, " ");
                }
                else
                {
                    sprintf(texte, "Votre score est : %d", score_f);
                    sprintf(best1, "Meilleur score : %d",best_score);
                }
            }

            SDL_FreeSurface(score);
            SDL_FreeSurface(record);
            TTF_CloseFont(police);
            police = TTF_OpenFont("angelina.ttf", 30);
            score = TTF_RenderText_Shaded(police, texte, couleurNoire, couleurBlanche);
            record = TTF_RenderText_Shaded(police, best1, couleurNoire, couleurBlanche);
            positionscore.x=ecran->w/2 - score->w/2;
            positionscore.y=180;
            positionrecord.x=ecran->w/2 - record->w/2;
            positionrecord.y=210;

            SDL_BlitSurface(arriere_plan[12], NULL, ecran, &positionarriere_plan);
            SDL_BlitSurface(score, NULL, ecran, &positionscore);
            SDL_BlitSurface(record, NULL, ecran, &positionrecord);
            SDL_Flip(ecran);
            SDL_ShowCursor(SDL_ENABLE);

            debutparti = 2;
            while (debutparti==2) //boucle d'attente pour la fin de la partie:
            {
                debutparti = pause(&niveau);
            }
        }
    }

    TTF_CloseFont(police);
    SDL_FreeSurface(score);
    SDL_FreeSurface(record);
    for(i=0;i<13;i++) SDL_FreeSurface(arriere_plan[i]);
    SDL_FreeSurface(points);
    SDL_FreeSurface(point);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void movepoint(SDL_Rect *position1, int vitesse, direction *direction1)
{
    int choix = 0;

    //le choix aléatoire de la direction suivant l'axe x et l'axe y:
    choix = rand()%500;
    switch(choix)
    {
        case 0:
        direction1->x=0;
        break;
        case 1:
        direction1->y=0;
        break;
        case 2:
        direction1->x=1;
        break;
        case 3:
        direction1->y=1;
        break;
        default:
        break;
    }

    //déplacement du point en fonction de la direction choisi et de la vitesse:
    if ((direction1->x==0)&&(direction1->y==0))
    {
        position1->x += vitesse;
        position1->y += vitesse;
    }
    else if ((direction1->x==1)&&(direction1->y==0))
    {
        position1->x -= vitesse;
        position1->y += vitesse;
    }
    else if ((direction1->x==0)&&(direction1->y==1))
    {
        position1->y -= vitesse;
        position1->x += vitesse;
    }
    else if ((direction1->x==1)&&(direction1->y==1))
    {
        position1->x -= vitesse;
        position1->y -= vitesse;
    }

    //l'effet du rebondissement:
    if (position1->x>=295) direction1->x=1;
    if (position1->x<=0) direction1->x=0;
    if (position1->y>=295) direction1->y=1;
    if (position1->y<=0) direction1->y=0;
}

int checkcollision(SDL_Rect *position,SDL_Rect *position1)
{
    if (((((position->x<=position1->x+5)&&(position->x>=position1->x))
          ||((position->x+7>=position1->x)&&(position->x<=position1->x)))&&(((position->y<=position1->y+5)&&(position->y>=position1->y))
          ||((position->y+7>=position1->y)&&(position->y<=position1->y)))))
        return 1;

    else return 0;
}

void init_position(SDL_Rect *position, const int *i)
{
    switch(*i)
    {
    case 0:
        position->x = 20;
        position->y = 11;
        break;
    case 1:
        position->x = 280;
        position->y = 11;
        break;
    case 2:
        position->x = 20;
        position->y = 279;
        break;
    case 3:
        position->x = 280;
        position->y = 279;
        break;
    case 4:
        position->x = 140;
        position->y = 279;
        break;
    case 5:
        position->x = 280;
        position->y = 140;
        break;
    case 6:
        position->x = 20;
        position->y = 140;
        break;
    case 7:
        position->x = 20;
        position->y = 11;
        break;
    case 8:
        position->x = 20;
        position->y = 11;
        break;
    case 9:
        position->x = 280;
        position->y = 11;
        break;
    case 10:
        position->x = 20;
        position->y = 279;
        break;
    case 11:
        position->x = 280;
        position->y = 279;
        break;
    case 12:
        position->x = 140;
        position->y = 279;
        break;
    case 13:
        position->x = 280;
        position->y = 140;
        break;
    case 14:
        position->x = 20;
        position->y = 140;
        break;
    default:
        position->x = 20;
        position->y = 11;
        break;
    }
}


int pause(int *niveau)
{
    SDL_Event event;
    short debutparti=2;

    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
            case SDLK_RETURN:
            debutparti=1;
            break;
            case SDLK_ESCAPE:
            debutparti=0;
            break;
            case SDLK_UP:
            if((*niveau)<20) (*niveau)++;
            break;
            case SDLK_DOWN:
            if((*niveau)>1) (*niveau)--;
            break;
            default:
            break;
        }
        break;
        case SDL_MOUSEBUTTONUP:
        debutparti=1;
        break;
        case SDL_QUIT:
        debutparti=0;
        break;
        default:
        break;
    }

    return debutparti;
}

int game_on(SDL_Event *event,int *score_f,int *t, const int *tempsdebut, SDL_Rect *position, SDL_Rect positions[], direction directions[], int *niveau)
{
    int  fin=1,v, i=0;

    switch(event->type)
    {
    case SDL_QUIT:
        fin=0;
        break;
    case SDL_MOUSEMOTION:
        position->x = event->motion.x ;
        position->y = event->motion.y ;
        if ((position->x<=0)||(position->x>=292)||(position->y<=0)||(position->y>=292)) //verification de la collision avec les murs
            fin=0;
        break;
    default:
        break;
    }

    if ((*score_f)>=100 && (*t)==1) (*t)++; //l'incrémentation de la vitesse (t) après les 8000 premieres et deuxièmes millisecondes:
    if ((*score_f)>=200 && (*t)==2) (*t)++;
    if ((*score_f)>=300 && (*t)==3) (*t)++;

    v=(*t);
    for(i=0;i<(*niveau);i++) movepoint(&positions[i],v,&directions[i]);

    for(i=0;i<(*niveau);i++) if ((checkcollision(position,&positions[i]))) fin=0;

    if (*niveau >=7) (*score_f) = ((*niveau)/7)*(SDL_GetTicks()-(*tempsdebut))/100;
    else (*score_f) = (SDL_GetTicks()-(*tempsdebut))/((8-*niveau)*100);

    return fin;
}


void explode(SDL_Surface *source, SDL_Surface *explosion,int *frame, int x,int y)
{
    SDL_Rect clip,offset;

    offset.x=0;
    offset.y=0;


    switch(*frame)
    {
    case 0:
        if(x<0) clip.x = -x;
        else clip.x=0;
        if(y<0) clip.y = -y;
        else clip.y=0;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 1:
        if(x<0) clip.x =320 -x;
        else clip.x=320;
        if(y<0) clip.y = -y;
        else clip.y=0;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 2:
        if(x<0) clip.x =320*2 - x;
        else clip.x=320*2;
        if(y<0) clip.y = - y;
        else clip.y=0;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 3:
        if(x<0) clip.x =320*3 - x;
        else clip.x=320*3;
        if(y<0) clip.y = - y;
        else clip.y=0;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 4:
        if(x<0) clip.x = -x;
        else clip.x=0;
        if(y<0) clip.y =240 -y;
        else clip.y=240;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 5:
        if(x<0) clip.x =320 -x;
        else clip.x=320;
        if(y<0) clip.y =240 -y;
        else clip.y=240;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 6:
        if(x<0) clip.x =320*2 - x;
        else clip.x=320*2;
        if(y<0) clip.y =240 - y;
        else clip.y=240;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 7:
        if(x<0) clip.x =320*3 - x;
        else clip.x=320*3;
        if(y<0) clip.y =240 - y;
        else clip.y=240;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 8:
        if(x<0) clip.x = -x;
        else clip.x=0;
        if(y<0) clip.y =240*2-y;
        else clip.y=240*2;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 9:
        if(x<0) clip.x =320 -x;
        else clip.x=320;
        if(y<0) clip.y =240*2 -y;
        else clip.y=240*2;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 10:
        if(x<0) clip.x =320*2 - x;
        else clip.x=320*2;
        if(y<0) clip.y =240*2 - y;
        else clip.y=240*2;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 11:
        if(x<0) clip.x =320*3 - x;
        else clip.x=320*3;
        if(y<0) clip.y =240*2 - y;
        else clip.y=240*2;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 12:
        if(x<0) clip.x = -x;
        else clip.x=0;
        if(y<0) clip.y =240*3 -y;
        else clip.y=240*3;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 13:
        if(x<0) clip.x =320 -x;
        else clip.x=320;
        if(y<0) clip.y =240*3 -y;
        else clip.y=240*3;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 14:
        if(x<0) clip.x =320*2 - x;
        else clip.x=320*2;
        if(y<0) clip.y =240*3 - y;
        else clip.y=240*3;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 15:
        if(x<0) clip.x =320*3 - x;
        else clip.x=320*3;
        if(y<0) clip.y =240*3 - y;
        else clip.y=240*3;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 16:
        if(x<0) clip.x = -x;
        else clip.x=0;
        if(y<0) clip.y =240*4 -y;
        else clip.y=240*4;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 17:
        if(x<0) clip.x =320 -x;
        else clip.x=320;
        if(y<0) clip.y =240*4 -y;
        else clip.y=240*4;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 18:
        if(x<0) clip.x =320*2 - x;
        else clip.x=320*2;
        if(y<0) clip.y =240*4 - y;
        else clip.y=240*4;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    case 19:
        if(x<0) clip.x =320*3 - x;
        else clip.x=320*3;
        if(y<0) clip.y =240*4 - y;
        else clip.y=240*4;
        if(x<0) clip.w = 320 + x;
        else clip.w=320;
        if(y<0) clip.h = 240 + y;
        else clip.h=240;
        break;
    default:
        break;
    }

    SDL_BlitSurface( source, &clip, explosion, &offset );

}

