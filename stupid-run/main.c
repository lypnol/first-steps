#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>

#include "animation.c"

int main(int argc, char** argv)
{
    SDL_Surface *ecran = NULL;
    SDL_Surface *Stick[N_STICK_FRAMES];
    SDL_Surface *arriere_plan[N_ARRIERE_FRAMES];
    SDL_Surface *Score = NULL;
    SDL_Surface *Best_Score = NULL;
    SDL_Surface *enemy[N_ENEMY_FRAMES];
    SDL_Surface *line[N_LINE_FRAMES];
    SDL_Surface *gomme[N_GOMME_FRAMES];
    SDL_Surface *count[N_COUNT_FRAMES];
    SDL_Surface *erreur = NULL;
    SDL_Surface *load = NULL;
    SDL_Rect position, position_enemy, position_line, position_best_score;
    SDL_Rect position_arriere_plan, position_score, position_gomme, position_count;
    SDL_Event event;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurVerte = {0, 55,0};
    SDL_Color couleurBleu = {0, 0, 60};
    TTF_Font *police = NULL;
    FILE *file_score=NULL;
    int frame_sit = 0, frame_right = 9, frame_up=27, frame_down = 16, frame_front = 37,
        frame_hit = 51, pos_bas = 0, pos_haut = 0, statut = 0, fin = 1, debut = 1,
        frame_line = 0, fall= 0,frame_sword = 15, frame_fall = 65, frame_gomme = 0, score = 0,
        best_score = 0, compteur = 1, choice = 0, en_bas = 0, enemy_chosen = 0,
        vitesse = 0, hit0 = 0, error = 0, frame_count = 0, delay = 0;
    char text_score[100];
    char text_best_score[100];

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(500, 350, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    erreur = IMG_Load("arriere/erreur.jpg");
    load = IMG_Load("arriere/chargement.jpg");

    SDL_WM_SetCaption("Stupid Run", NULL);

    position_line.x=0;
    position_line.y=297;
    position_count.x=215;
    position_count.y=0;
    position_gomme.y=0;
    position_gomme.x=0;
    position_arriere_plan.x = 0;
    position_arriere_plan.y = 0;
    position_enemy.y = 0;

    //chargement des images:
    SDL_BlitSurface(load, NULL, ecran, &position_arriere_plan);
    SDL_Flip(ecran);

    init_stick(Stick, &error);
    init_arriere_plan(arriere_plan, &error);
    init_enemy(enemy, &error);
    init_line(line, &error);
    init_gomme(gomme, &error);
    init_count(count, &error);

    if (error==0)
    {
        while(debut!=0) // boucle principale
        {
            if (debut==1) // ecran d'acceuil:
            {
                position.x = 404;
                position.y = 81;
                fin = 1;
                while(fin)
                {
                    SDL_PollEvent(&event);
                    switch(event.type)
                    {
                    case SDL_QUIT:
                        TTF_CloseFont(police);
                        SDL_FreeSurface(load);
                        SDL_FreeSurface(erreur);
                        Free_Surfaces(Stick, enemy, arriere_plan, line, gomme, count);
                        SDL_FreeSurface(Score);
                        SDL_FreeSurface(Best_Score);
                        SDL_FreeSurface(ecran);
                        TTF_Quit();
                        SDL_Quit();
                        exit(0);
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                        case SDLK_RETURN:
                            debut = 2;
                            fin = 0;
                            break;
                        case SDLK_h:
                            debut = 3;
                            fin = 0;
                            break;
                        case SDLK_ESCAPE:
                            debut = 0;
                            fin = 0;
                            break;
                        }
                        break;
                    }

                    sit(&frame_sit);
                    SDL_Delay(55);
                    SDL_SetColorKey(Stick[frame_sit], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_sit]->format, 255, 255, 255));
                    SDL_BlitSurface(arriere_plan[0], NULL, ecran, &position_arriere_plan);
                    SDL_BlitSurface(Stick[frame_sit], NULL, ecran, &position);
                    SDL_Flip(ecran);
                }
            }

            else if (debut==2) // debut de la partie:
            {
                // inisialization des param�tres:
                TTF_CloseFont(police);
                police = TTF_OpenFont("angelina.ttf", 25);
                position_enemy.x = 500;
                position_score.x = 60;
                position_score.y = 10;
                choice = 0;
                pos_bas = 0;
                pos_haut = 0;
                score = 0;
                statut = 0;
                fin = 1;
                vitesse = 20;
                hit0 = 0;
                frame_fall = 65;
                delay = 0;
                frame_count = 0;
                position.x = 90;
                position.y = 0;
                enemy_chosen=0;
                compteur = 1;
                frame_right = 9;
                frame_sword = 15;
                while(fin) //boucle pendant la partie
                {
                    SDL_BlitSurface(arriere_plan[1], NULL, ecran, &position_arriere_plan);
                    SDL_PollEvent(&event);
                    switch(event.type)
                    {
                    case SDL_QUIT:
                        TTF_CloseFont(police);
                        SDL_FreeSurface(load);
                        SDL_FreeSurface(erreur);
                        Free_Surfaces(Stick, enemy, arriere_plan, line, gomme, count);
                        SDL_FreeSurface(Score);
                        SDL_FreeSurface(Best_Score);
                        SDL_FreeSurface(ecran);
                        TTF_Quit();
                        SDL_Quit();
                        exit(0);
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            TTF_CloseFont(police);
                            SDL_FreeSurface(load);
                            SDL_FreeSurface(erreur);
                            Free_Surfaces(Stick, enemy, arriere_plan, line, gomme, count);
                            SDL_FreeSurface(Score);
                            SDL_FreeSurface(Best_Score);
                            SDL_FreeSurface(ecran);
                            TTF_Quit();
                            SDL_Quit();
                            exit(0);
                            break;
                        case SDLK_UP:
                            statut = 1;
                            break;
                        case SDLK_DOWN:
                            statut = 2;
                            break;
                        case SDLK_RIGHT:
                            statut = 3;
                            break;
                        case SDLK_LEFT:
                            statut = 4;
                            break;
                        default:
                            statut = 0;
                            break;
                        }
                        break;
                    case SDL_KEYUP:
                        switch(event.key.keysym.sym)
                        {
                        case SDLK_DOWN:
                            if (check_down(&frame_down)==1)
                                en_bas=1;
                            break;
                        default:
                            break;
                        }

                    default:
                        break;
                    }

                    move_line(&frame_line);
                    SDL_SetColorKey(line[frame_line], SDL_SRCCOLORKEY, SDL_MapRGB(line[frame_line]->format, 255, 255, 255));
                    move_gomme(&frame_gomme);
                    SDL_SetColorKey(gomme[frame_gomme], SDL_SRCCOLORKEY, SDL_MapRGB(gomme[frame_gomme]->format, 255, 255, 255));
                    move_count(&frame_count,&delay);
                    SDL_SetColorKey(count[frame_count], SDL_SRCCOLORKEY, SDL_MapRGB(count[frame_count]->format, 255, 255, 255));
                    SDL_BlitSurface(count[frame_count], NULL, ecran, &position_count);

                    SDL_Delay(50);
                    if (score==(33)*compteur) // choix de l'enemie:
                    {
                        compteur++;
                        enemy_chosen=1;
                        if (((compteur%5)==0)&&(vitesse<=55))
                            vitesse += 4;

                        choice = rand()%16;
                        fall = enemy_type(&choice);

                        SDL_SetColorKey(enemy[choice], SDL_SRCCOLORKEY, SDL_MapRGB(enemy[choice]->format, 255, 255, 255));
                        position_enemy.x=500;
                    }

                    score++;
                    sprintf(text_score, "score : %d", score);
                    SDL_FreeSurface(Score);
                    Score = TTF_RenderText_Blended(police, text_score, couleurNoire);

                    SDL_BlitSurface(line[frame_line], NULL, ecran, &position_line);

                    if(enemy_chosen) // si l'enemie a �t� choisi:
                    {
                        if (position_enemy.x >0)
                        {
                            if(fall!=4)
                            {
                                frame_sword = 15;
                                position_enemy.x -= vitesse;
                                SDL_BlitSurface(enemy[choice], NULL, ecran, &position_enemy);
                            }
                            else if(fall==4)
                            {
                                position_enemy.x -= 20;
                                if(position_enemy.x >=150)
                                {
                                    move_sword(&frame_sword);
                                    SDL_SetColorKey(enemy[frame_sword], SDL_SRCCOLORKEY, SDL_MapRGB(enemy[frame_sword]->format, 255, 255, 255));
                                    SDL_BlitSurface(enemy[frame_sword], NULL, ecran, &position_enemy);
                                }
                                else
                                {
                                    fall_sword(&frame_sword);
                                    SDL_SetColorKey(enemy[frame_sword], SDL_SRCCOLORKEY, SDL_MapRGB(enemy[frame_sword]->format, 255, 255, 255));
                                    SDL_BlitSurface(enemy[frame_sword], NULL, ecran, &position_enemy);
                                }

                            }

                        }
                        else
                        {
                            enemy_chosen = 0;
                        }

                        if(fall!=4)
                        {
                            if ((position_enemy.x <=125)&&(position_enemy.x>=60))
                            {
                                if(check_collision(&pos_haut,&pos_bas,&hit0,&choice)==1)
                                {
                                    fin = 0;
                                }
                            }
                        }
                        else
                        {
                            if ((position_enemy.x <=150)&&(position_enemy.x>=140))
                            {
                                if(check_collision(&pos_haut,&pos_bas,&hit0,&choice)==1)
                                {
                                    fin = 0;
                                }
                            }
                        }
                    }

                    // gestion des animations:
                    if (statut==0)
                    {
                        frame_front=37;
                        pos_bas = 0;
                        pos_haut = 0;
                        frame_hit=51;
                        frame_down=16;
                        frame_up=27;
                        hit0 = 0;
                        en_bas=0;
                        run(&frame_right);
                        SDL_SetColorKey(Stick[frame_right], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_right]->format, 255, 255, 255));
                        SDL_BlitSurface(Stick[frame_right], NULL, ecran, &position);
                    }
                    else if (statut==1)
                    {
                        frame_front=37;
                        frame_down=16;
                        frame_right=9;
                        frame_hit=51;
                        hit0 = 0;
                        en_bas=0;
                        if(check_complete_jump(&frame_up)==0)
                        {
                            pos_bas = jump(&frame_up);
                            SDL_SetColorKey(Stick[frame_up], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_up]->format, 255, 255, 255));
                            SDL_BlitSurface(Stick[frame_up], NULL, ecran, &position);
                        }
                        else
                        {
                            statut=0;
                            SDL_BlitSurface(Stick[frame_right], NULL, ecran, &position);
                            frame_up = 25;
                        }
                    }
                    else if (statut==2)
                    {
                        frame_front=37;
                        frame_up=27;
                        frame_right=9;
                        frame_hit=51;
                        hit0 = 0;
                        if (en_bas!=1)
                        {
                            pos_haut = down(&frame_down);
                            SDL_SetColorKey(Stick[frame_down], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_down]->format, 255, 255, 255));
                            SDL_BlitSurface(Stick[frame_down], NULL, ecran, &position);
                            en_bas = 0;
                        }
                        else if(en_bas==1)
                        {
                            if (!check_complete_down(&frame_down))
                            {
                                pos_haut = complete_down(&frame_down);
                                SDL_SetColorKey(Stick[frame_down], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_down]->format, 255, 255, 255));
                                SDL_BlitSurface(Stick[frame_down], NULL, ecran, &position);
                            }
                            else
                            {
                                SDL_BlitSurface(Stick[frame_right], NULL, ecran, &position);
                                frame_down = 16;
                                statut=0;
                                en_bas=0;
                            }
                        }
                    }
                    else if (statut==3)
                    {
                        frame_up=27;
                        frame_right=9;
                        frame_down=16;
                        frame_hit=51;
                        hit0 = 0;
                        en_bas=0;
                        if(check_complete_front(&frame_front)==0)
                        {
                            pos_haut = front(&frame_front);
                            SDL_SetColorKey(Stick[frame_front], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_front]->format, 255, 255, 255));
                            SDL_BlitSurface(Stick[frame_front], NULL, ecran, &position);
                        }
                        else
                        {
                            SDL_BlitSurface(Stick[frame_right], NULL, ecran, &position);
                            statut=0;
                            frame_front = 37;
                        }
                    }
                    else if (statut==4)
                    {
                        frame_up=27;
                        frame_right=9;
                        frame_down=16;
                        frame_front=37;
                        en_bas=0;
                        if(check_complete_hit(&frame_hit)==0)
                        {
                            pos_bas = hit(&frame_hit, &hit0);
                            SDL_SetColorKey(Stick[frame_hit], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_hit]->format, 255, 255, 255));
                            SDL_BlitSurface(Stick[frame_hit], NULL, ecran, &position);
                        }
                        else
                        {
                            SDL_BlitSurface(Stick[frame_right], NULL, ecran, &position);
                            statut=0;
                            frame_hit = 51;
                        }
                    }

                    SDL_BlitSurface(gomme[frame_gomme], NULL, ecran, &position_gomme);
                    SDL_BlitSurface(Score, NULL, ecran, &position_score);
                    SDL_Flip(ecran);

                }

                // animation apr�s la collision:
                if (fall==1)
                {
                    while(check_complete_fall(&frame_fall)!=1)
                    {
                        position.x += 11;
                        position_enemy.x -= 11;
                        SDL_BlitSurface(arriere_plan[1],NULL,ecran, &position_arriere_plan);
                        SDL_BlitSurface(line[frame_line], NULL, ecran, &position_line);
                        SDL_BlitSurface(enemy[choice], NULL, ecran, &position_enemy);
                        fall_down(&frame_fall);
                        SDL_SetColorKey(Stick[frame_fall], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_fall]->format, 255, 255, 255));
                        SDL_BlitSurface(Stick[frame_fall], NULL, ecran, &position);
                        SDL_BlitSurface(gomme[frame_gomme], NULL, ecran, &position_gomme);
                        SDL_BlitSurface(Score, NULL, ecran, &position_score);
                        SDL_Flip(ecran);
                        SDL_Delay(55);
                    }
                }

                else if (fall==2)
                {
                    while(check_complete_fall(&frame_fall)!=1)
                    {
                        position.x += 11;
                        position_enemy.x -= 11;
                        SDL_BlitSurface(arriere_plan[1],NULL,ecran, &position_arriere_plan);
                        SDL_BlitSurface(line[frame_line], NULL, ecran, &position_line);
                        SDL_BlitSurface(enemy[choice], NULL, ecran, &position_enemy);
                        fall_up(&frame_fall);
                        SDL_SetColorKey(Stick[frame_fall], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_fall]->format, 255, 255, 255));
                        SDL_BlitSurface(Stick[frame_fall], NULL, ecran, &position);
                        SDL_BlitSurface(gomme[frame_gomme], NULL, ecran, &position_gomme);
                        SDL_BlitSurface(Score, NULL, ecran, &position_score);
                        SDL_Flip(ecran);
                        SDL_Delay(55);
                    }
                }

                else if (fall==3)
                {
                    while(check_complete_fall(&frame_fall)!=1)
                    {
                        position.x += 11;
                        position_enemy.x -= 11;
                        SDL_BlitSurface(arriere_plan[1],NULL,ecran, &position_arriere_plan);
                        SDL_BlitSurface(line[frame_line], NULL, ecran, &position_line);
                        SDL_BlitSurface(enemy[choice], NULL, ecran, &position_enemy);
                        fall_cliff(&frame_fall);
                        SDL_SetColorKey(Stick[frame_fall], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_fall]->format, 255, 255, 255));
                        SDL_BlitSurface(Stick[frame_fall], NULL, ecran, &position);
                        SDL_BlitSurface(gomme[frame_gomme], NULL, ecran, &position_gomme);
                        SDL_BlitSurface(Score, NULL, ecran, &position_score);
                        SDL_Flip(ecran);
                        SDL_Delay(55);
                    }
                }

                else if (fall==4)
                {
                    while(check_complete_fall(&frame_fall)!=1)
                    {
                        position.x += 11;
                        position_enemy.x -= 11;
                        SDL_BlitSurface(arriere_plan[1],NULL,ecran, &position_arriere_plan);
                        SDL_BlitSurface(line[frame_line], NULL, ecran, &position_line);
                        SDL_BlitSurface(enemy[choice], NULL, ecran, &position_enemy);
                        fall_up(&frame_fall);
                        SDL_SetColorKey(Stick[frame_fall], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_fall]->format, 255, 255, 255));
                        SDL_BlitSurface(Stick[frame_fall], NULL, ecran, &position);
                        SDL_BlitSurface(gomme[frame_gomme], NULL, ecran, &position_gomme);
                        SDL_BlitSurface(Score, NULL, ecran, &position_score);
                        SDL_Flip(ecran);
                        SDL_Delay(55);
                    }
                }

                //gestion du score � la fin de la partie:
                TTF_CloseFont(police);
                police = TTF_OpenFont("angelina.ttf", 35);
                position_score.x = 150;
                position_score.y = 268;
                position_best_score.x = 150;
                position_best_score.y = 300;

                best_score=0;
                file_score=fopen("score.sce","r");
                if (file_score!=NULL)
                {
                    rewind(file_score);
                    fscanf(file_score,"%s",text_best_score);
                    best_score = strtol(text_best_score,NULL,10);
                    fclose(file_score);
                    if (score>best_score)
                    {
                        file_score=fopen("score.sce","w+");
                        fprintf(file_score,"%d", score);
                        fclose(file_score);
                        sprintf(text_score, "nouveau record! : %d", score);
                        sprintf(text_best_score, " ");
                    }
                    else
                    {
                        sprintf(text_score, "Votre score est : %d", score);
                        sprintf(text_best_score, "Meilleur score : %d",best_score);
                    }
                }

                SDL_FreeSurface(Score);
                Score = TTF_RenderText_Blended(police, text_score, couleurBleu);
                SDL_FreeSurface(Best_Score);
                Best_Score = TTF_RenderText_Blended(police, text_best_score, couleurVerte);

                fin = 1;
                position.x = 404;
                position.y = 81;
                while(fin) //boucle: fin de partie:
                {

                    SDL_PollEvent(&event);
                    switch(event.type)
                    {
                    case SDL_QUIT:
                        TTF_CloseFont(police);
                        SDL_FreeSurface(load);
                        SDL_FreeSurface(erreur);
                        Free_Surfaces(Stick, enemy, arriere_plan, line, gomme, count);
                        SDL_FreeSurface(Score);
                        SDL_FreeSurface(Best_Score);
                        SDL_FreeSurface(ecran);
                        TTF_Quit();
                        SDL_Quit();
                        exit(0);
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                        case SDLK_RETURN:
                            debut = 1;
                            fin = 0;
                            break;
                        case SDLK_ESCAPE:
                            exit(0);
                            break;
                        }
                        break;
                    }
                    SDL_Delay(50);
                    sit(&frame_sit);
                    SDL_SetColorKey(Stick[frame_sit], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_sit]->format, 255, 255, 255));
                    SDL_BlitSurface(arriere_plan[2], NULL, ecran, &position_arriere_plan);
                    SDL_BlitSurface(Stick[frame_sit], NULL, ecran, &position);
                    SDL_BlitSurface(Score, NULL, ecran, &position_score);
                    SDL_BlitSurface(Best_Score, NULL, ecran, &position_best_score);
                    SDL_Flip(ecran);
                }
            }

            else if (debut==3)// ecran d'aide:
            {
                position.x = 404;
                position.y = 81;
                fin = 1;
                while(fin)
                {
                    SDL_PollEvent(&event);
                    switch(event.type)
                    {
                    case SDL_QUIT:
                        TTF_CloseFont(police);
                        SDL_FreeSurface(load);
                        SDL_FreeSurface(erreur);
                        Free_Surfaces(Stick, enemy, arriere_plan, line, gomme, count);
                        SDL_FreeSurface(Score);
                        SDL_FreeSurface(Best_Score);
                        SDL_FreeSurface(ecran);
                        TTF_Quit();
                        SDL_Quit();
                        exit(0);
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                        case SDLK_RETURN:
                            debut = 1;
                            fin = 0;
                            break;
                        case SDLK_ESCAPE:
                            debut = 1;
                            fin = 0;
                            break;
                        }
                        break;
                    }

                    sit(&frame_sit);
                    SDL_Delay(55);
                    SDL_SetColorKey(Stick[frame_sit], SDL_SRCCOLORKEY, SDL_MapRGB(Stick[frame_sit]->format, 255, 255, 255));
                    SDL_BlitSurface(arriere_plan[3], NULL, ecran, &position_arriere_plan);
                    SDL_BlitSurface(Stick[frame_sit], NULL, ecran, &position);
                    SDL_Flip(ecran);
                }
            }
        }
    }

    else if (error==1)
    {
        SDL_BlitSurface(erreur, NULL, ecran, &position_arriere_plan);
        SDL_Flip(ecran);
        fin = 1;
        while(fin)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
            case SDL_QUIT:
                fin = 0;
                break;
            }
        }
    }

    SDL_FreeSurface(load);
    SDL_FreeSurface(erreur);
    Free_Surfaces(Stick, enemy, arriere_plan, line, gomme, count);
    SDL_FreeSurface(Score);
    SDL_FreeSurface(Best_Score);
    SDL_FreeSurface(ecran);

    return EXIT_SUCCESS;
}
