#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define N_STICK_FRAMES      89
#define N_ENEMY_FRAMES      30
#define N_ARRIERE_FRAMES    4
#define N_LINE_FRAMES       8
#define N_GOMME_FRAMES      7
#define N_COUNT_FRAMES      5

int init_stick(SDL_Surface **Stick, int *error)
{
    int i = 0;

    for(i = 0; i<N_STICK_FRAMES; i++)
    {
        Stick[i] = NULL;
    }

    Stick[0] = IMG_Load("arriere/stick/1.jpg");
    Stick[1] = IMG_Load("arriere/stick/2.jpg");
    Stick[2] = IMG_Load("arriere/stick/3.jpg");
    Stick[3] = IMG_Load("arriere/stick/4.jpg");
    Stick[4] = IMG_Load("arriere/stick/5.jpg");
    Stick[5] = IMG_Load("arriere/stick/6.jpg");
    Stick[6] = IMG_Load("arriere/stick/7.jpg");
    Stick[7] = IMG_Load("arriere/stick/8.jpg");
    Stick[8] = IMG_Load("arriere/stick/9.jpg");
    Stick[9] = SDL_LoadBMP("BMP/1.bmp");
    Stick[10] = SDL_LoadBMP("BMP/2.bmp");
    Stick[11] = SDL_LoadBMP("BMP/3.bmp");
    Stick[12] = SDL_LoadBMP("BMP/4.bmp");
    Stick[13] = SDL_LoadBMP("BMP/5.bmp");
    Stick[14] = SDL_LoadBMP("BMP/6.bmp");
    Stick[15] = SDL_LoadBMP("BMP/7.bmp");
    Stick[16] = SDL_LoadBMP("BMP/down1.bmp");
    Stick[17] = SDL_LoadBMP("BMP/down3.bmp");
    Stick[18] = SDL_LoadBMP("BMP/down5.bmp");
    Stick[19] = SDL_LoadBMP("BMP/down7.bmp");
    Stick[20] = SDL_LoadBMP("BMP/down8.bmp");
    Stick[21] = SDL_LoadBMP("BMP/down9.bmp");
    Stick[22] = SDL_LoadBMP("BMP/down10.bmp");
    Stick[23] = SDL_LoadBMP("BMP/down11.bmp");
    Stick[24] = SDL_LoadBMP("BMP/down12.bmp");
    Stick[25] = SDL_LoadBMP("BMP/jump2.bmp");
    Stick[26] = SDL_LoadBMP("BMP/jump4.bmp");
    Stick[27] = SDL_LoadBMP("BMP/jump5.bmp");
    Stick[28] = SDL_LoadBMP("BMP/jump6.bmp");
    Stick[29] = SDL_LoadBMP("BMP/jump7.bmp");
    Stick[30] = SDL_LoadBMP("BMP/jump8.bmp");
    Stick[31] = SDL_LoadBMP("BMP/jump9.bmp");
    Stick[32] = SDL_LoadBMP("BMP/jump10.bmp");
    Stick[33] = SDL_LoadBMP("BMP/jump11.bmp");
    Stick[34] = SDL_LoadBMP("BMP/jump12.bmp");
    Stick[35] = SDL_LoadBMP("BMP/jump13.bmp");
    Stick[36] = SDL_LoadBMP("BMP/jump14.bmp");
    Stick[37] = SDL_LoadBMP("BMP/front1.bmp");
    Stick[38] = SDL_LoadBMP("BMP/front2.bmp");
    Stick[39] = SDL_LoadBMP("BMP/front3.bmp");
    Stick[40] = SDL_LoadBMP("BMP/front4.bmp");
    Stick[41] = SDL_LoadBMP("BMP/front5.bmp");
    Stick[42] = SDL_LoadBMP("BMP/front6.bmp");
    Stick[43] = SDL_LoadBMP("BMP/front7.bmp");
    Stick[44] = SDL_LoadBMP("BMP/front8.bmp");
    Stick[45] = SDL_LoadBMP("BMP/front9.bmp");
    Stick[46] = SDL_LoadBMP("BMP/front10.bmp");
    Stick[47] = SDL_LoadBMP("BMP/front11.bmp");
    Stick[48] = SDL_LoadBMP("BMP/front12.bmp");
    Stick[49] = SDL_LoadBMP("BMP/front13.bmp");
    Stick[50] = SDL_LoadBMP("BMP/front14.bmp");
    Stick[51] = SDL_LoadBMP("BMP/hit1.bmp");
    Stick[52] = SDL_LoadBMP("BMP/hit2.bmp");
    Stick[53] = SDL_LoadBMP("BMP/hit3.bmp");
    Stick[54] = SDL_LoadBMP("BMP/hit4.bmp");
    Stick[55] = SDL_LoadBMP("BMP/hit5.bmp");
    Stick[56] = SDL_LoadBMP("BMP/hit6.bmp");
    Stick[57] = SDL_LoadBMP("BMP/hit7.bmp");
    Stick[58] = SDL_LoadBMP("BMP/hit8.bmp");
    Stick[59] = SDL_LoadBMP("BMP/hit9.bmp");
    Stick[60] = SDL_LoadBMP("BMP/hit10.bmp");
    Stick[61] = SDL_LoadBMP("BMP/hit11.bmp");
    Stick[62] = SDL_LoadBMP("BMP/hit12.bmp");
    Stick[63] = SDL_LoadBMP("BMP/hit13.bmp");
    Stick[64] = SDL_LoadBMP("BMP/hit14.bmp");
    Stick[65] = SDL_LoadBMP("BMP/fall1.bmp");
    Stick[66] = SDL_LoadBMP("BMP/fall2.bmp");
    Stick[67] = SDL_LoadBMP("BMP/fall3.bmp");
    Stick[68] = SDL_LoadBMP("BMP/fall4.bmp");
    Stick[69] = SDL_LoadBMP("BMP/fall5.bmp");
    Stick[70] = SDL_LoadBMP("BMP/fall6.bmp");
    Stick[71] = SDL_LoadBMP("BMP/fall7.bmp");
    Stick[72] = SDL_LoadBMP("BMP/fall8.bmp");
    Stick[73] = SDL_LoadBMP("BMP/fall9.bmp");
    Stick[74] = SDL_LoadBMP("BMP/fallcliff1.bmp");
    Stick[75] = SDL_LoadBMP("BMP/fallcliff2.bmp");
    Stick[76] = SDL_LoadBMP("BMP/fallcliff3.bmp");
    Stick[77] = SDL_LoadBMP("BMP/fallcliff4.bmp");
    Stick[78] = SDL_LoadBMP("BMP/fallcliff5.bmp");
    Stick[79] = SDL_LoadBMP("BMP/fallhit1.bmp");
    Stick[80] = SDL_LoadBMP("BMP/fallhit2.bmp");
    Stick[81] = SDL_LoadBMP("BMP/fallhit3.bmp");
    Stick[82] = SDL_LoadBMP("BMP/fallhit4.bmp");
    Stick[83] = SDL_LoadBMP("BMP/fallhit5.bmp");
    Stick[84] = SDL_LoadBMP("BMP/fallhit6.bmp");
    Stick[85] = SDL_LoadBMP("BMP/fallhit7.bmp");
    Stick[86] = SDL_LoadBMP("BMP/stick.bmp");
    Stick[87] = SDL_LoadBMP("BMP/front15.bmp");
    Stick[88] = SDL_LoadBMP("BMP/front16.bmp");

    for(i=0;i<N_STICK_FRAMES;i++)
    {
        if (Stick[i]==NULL)
            (*error)=1;

    }

    return 1;
}

int init_enemy(SDL_Surface **enemy, int *error)
{
    int i =0;

    for (i=0;i<N_ENEMY_FRAMES;i++)
    {
        enemy[i]=NULL;
    }

    enemy[0] = SDL_LoadBMP("enemies/0.bmp");
    enemy[1] = SDL_LoadBMP("enemies/1.bmp");
    enemy[2] = SDL_LoadBMP("enemies/2.bmp");
    enemy[3] = SDL_LoadBMP("enemies/3.bmp");
    enemy[4] = SDL_LoadBMP("enemies/4.bmp");
    enemy[5] = SDL_LoadBMP("enemies/5.bmp");
    enemy[6] = SDL_LoadBMP("enemies/6.bmp");
    enemy[7] = SDL_LoadBMP("enemies/7.bmp");
    enemy[8] = SDL_LoadBMP("enemies/sword1.bmp");
    enemy[9] = SDL_LoadBMP("enemies/9.bmp");
    enemy[10] = SDL_LoadBMP("enemies/10.bmp");
    enemy[11] = SDL_LoadBMP("enemies/11.bmp");
    enemy[12] = SDL_LoadBMP("enemies/12.bmp");
    enemy[13] = SDL_LoadBMP("enemies/13.bmp");
    enemy[14] = SDL_LoadBMP("enemies/14.bmp");
    enemy[15] = SDL_LoadBMP("enemies/sword1.bmp");
    enemy[16] = SDL_LoadBMP("enemies/sword2.bmp");
    enemy[17] = SDL_LoadBMP("enemies/sword3.bmp");
    enemy[18] = SDL_LoadBMP("enemies/sword4.bmp");
    enemy[19] = SDL_LoadBMP("enemies/sword5.bmp");
    enemy[20] = SDL_LoadBMP("enemies/sword6.bmp");
    enemy[21] = SDL_LoadBMP("enemies/sword7.bmp");
    enemy[22] = SDL_LoadBMP("enemies/fall1.bmp");
    enemy[23] = SDL_LoadBMP("enemies/fall2.bmp");
    enemy[24] = SDL_LoadBMP("enemies/fall3.bmp");
    enemy[25] = SDL_LoadBMP("enemies/fall4.bmp");
    enemy[26] = SDL_LoadBMP("enemies/fall5.bmp");
    enemy[27] = SDL_LoadBMP("enemies/fall6.bmp");
    enemy[28] = SDL_LoadBMP("enemies/fall7.bmp");
    enemy[29] = SDL_LoadBMP("enemies/fall8.bmp");

    for(i=0;i<N_ENEMY_FRAMES;i++)
    {
        if (enemy[i]==NULL)
            (*error)=1;

    }

    return 1;
}

int init_arriere_plan(SDL_Surface **arriere_plan, int *error)
{
    int  i = 0;

    for(i=0;i<N_ARRIERE_FRAMES;i++)
    {
        arriere_plan[i]=NULL;
    }

    arriere_plan[0] = IMG_Load("arriere/acceuil.jpg");
    arriere_plan[1] = IMG_Load("arriere/jeu.jpg");
    arriere_plan[2] = IMG_Load("arriere/fin.jpg");
    arriere_plan[3] = IMG_Load("arriere/tuto.jpg");

    for(i=0;i<N_ARRIERE_FRAMES;i++)
    {
        if (arriere_plan[i]==NULL)
            (*error)=1;

    }

    return 1;
}

int init_line(SDL_Surface **line, int *error)
{
    int i = 0;

    for(i=0;i<N_LINE_FRAMES;i++)
    {
        line[i]=NULL;
    }

    line[0] = SDL_LoadBMP("arriere/ligne1.bmp");
    line[1] = SDL_LoadBMP("arriere/ligne1.bmp");
    line[2] = SDL_LoadBMP("arriere/ligne2.bmp");
    line[3] = SDL_LoadBMP("arriere/ligne2.bmp");
    line[4] = SDL_LoadBMP("arriere/ligne3.bmp");
    line[5] = SDL_LoadBMP("arriere/ligne3.bmp");
    line[6] = SDL_LoadBMP("arriere/ligne4.bmp");
    line[7] = SDL_LoadBMP("arriere/ligne4.bmp");

    for(i=0;i<N_LINE_FRAMES;i++)
    {
        if (line[i]==NULL)
            (*error)=1;

    }

    return 1;
}

int init_gomme(SDL_Surface **gomme, int *error)
{
    int i = 0;

    for(i=0;i<N_GOMME_FRAMES;i++)
    {
        gomme[i]=NULL;
    }

    gomme[0] = SDL_LoadBMP("arriere/gomme1.bmp");
    gomme[1] = SDL_LoadBMP("arriere/gomme2.bmp");
    gomme[2] = SDL_LoadBMP("arriere/gomme3.bmp");
    gomme[3] = SDL_LoadBMP("arriere/gomme4.bmp");
    gomme[4] = SDL_LoadBMP("arriere/gomme5.bmp");
    gomme[5] = SDL_LoadBMP("arriere/gomme6.bmp");
    gomme[6] = SDL_LoadBMP("arriere/gomme1.bmp");

    for(i=0;i<N_GOMME_FRAMES;i++)
    {
        if (gomme[i]==NULL)
            (*error)=1;

    }

    return 1;
}

int init_count(SDL_Surface **count, int *error)
{
    int i = 0;

    for(i=0;i<N_COUNT_FRAMES;i++)
    {
        count[i]=NULL;
    }

    count[0] = SDL_LoadBMP("arriere/count3.bmp");
    count[1] = SDL_LoadBMP("arriere/count2.bmp");
    count[2] = SDL_LoadBMP("arriere/count1.bmp");
    count[3] = SDL_LoadBMP("arriere/countgo.bmp");
    count[4] = SDL_LoadBMP("blank.bmp");
    for(i=0;i<N_COUNT_FRAMES;i++)
    {
        if (count[i]==NULL)
            (*error)=1;

    }

    return 1;
}

void Free_Surfaces(SDL_Surface **Stick, SDL_Surface **enemy, SDL_Surface **arriere_plan, SDL_Surface **line, SDL_Surface **gomme, SDL_Surface **count)
{
    int i = 0;

    for (i=0; i<N_STICK_FRAMES; i++)
    {
        SDL_FreeSurface(Stick[i]);
    }
    for (i=0; i<N_ENEMY_FRAMES; i++)
    {
        SDL_FreeSurface(enemy[i]);
    }
    for (i=0; i<N_ARRIERE_FRAMES; i++)
    {
        SDL_FreeSurface(arriere_plan[i]);
    }
    for (i=0; i<N_LINE_FRAMES; i++)
    {
        SDL_FreeSurface(line[i]);
    }
    for (i=0; i<N_GOMME_FRAMES; i++)
    {
        SDL_FreeSurface(gomme[i]);
    }
    for (i=0; i<N_COUNT_FRAMES; i++)
    {
        SDL_FreeSurface(count[i]);
    }
}



void move_line(int *frame_line)
{
    (*frame_line) = ((*frame_line) + 1)%N_LINE_FRAMES;
}

void move_gomme(int *frame_gomme)
{
    (*frame_gomme) = ((*frame_gomme) + 1)%N_GOMME_FRAMES;
}

void move_count(int *frame_count, int *delay)
{
    if((*delay)<10)
    {
        (*delay)++;
    }
    else
    {
        (*delay) = 0;
        if ((*frame_count)<N_COUNT_FRAMES-1)
            (*frame_count)++;
    }
}

void sit(int *frame_sit)
{
    if ((*frame_sit)<8)
        (*frame_sit)++;
    else
        (*frame_sit)=0;
}

void run(int *frame_run)
{
    if ((*frame_run)<15)
        (*frame_run)++;
    else
        (*frame_run) = 9;
}

void fall_down(int *frame_fall)
{
    if ((*frame_fall)<65)
        (*frame_fall)=65;

    if ((*frame_fall)<73)
        (*frame_fall)++;
    else
        (*frame_fall)=65;
}

void fall_up(int *frame_fall)
{
    if ((*frame_fall)<72)
        (*frame_fall)=79;

    if (((*frame_fall)<85)&&((*frame_fall)>=79))
        (*frame_fall)++;

    else if ((*frame_fall)==85)
        (*frame_fall)=72;

    else if ((*frame_fall)==72)
        (*frame_fall)=73;

    else if((*frame_fall)==73)
        (*frame_fall) = 79;
}

void fall_cliff(int *frame_fall)
{
    if ((*frame_fall)<70)
        (*frame_fall)=74;

    if(((*frame_fall)<78)&&((*frame_fall)>=74))
        (*frame_fall)++;

    else if((*frame_fall)==78)
        (*frame_fall)=70;

    else if((*frame_fall)==70)
        (*frame_fall)=71;

    else if((*frame_fall)==71)
        (*frame_fall)=72;

    else if((*frame_fall)==72)
        (*frame_fall)=73;

    else if((*frame_fall)==73)
        (*frame_fall)=74;
}

int check_complete_fall(int const *frame_fall)
{
    if ((*frame_fall)==73)
        return 1;
    else
        return 0;
}



int jump(int *frame_up)
{
    int position_y = 0;

    switch((*frame_up))
        {
        case 25:
            position_y = 34;
            break;
        case 26:
            position_y = 34;
            break;
        case 27:
            position_y = 34;
            break;
        case 28:
            position_y = 62;
            break;
        case 29:
            position_y = 89;
            break;
        case 30:
            position_y = 91;
            break;
        case 31:
            position_y = 91;
            break;
        case 32:
            position_y = 91;
            break;
        case 33:
            position_y = 82;
            break;
        case 34:
            position_y = 66;
            break;
        case 35:
            position_y = 33;
            break;
        case 36:
            position_y = 0;
            break;
        }

    (*frame_up)++;

    return position_y;

}

int check_complete_jump(int *frame_up)
{
    if ((*frame_up)>=36)
        return 1;
    else
        return 0;
}



int down(int *frame_down)
{
    int position_y;

    switch((*frame_down))
        {
        case 16:
            position_y = 0;
            (*frame_down)++;
            break;
        case 17:
            position_y = 15;
            (*frame_down)++;
            break;
        case 18:
            position_y = 30;
            (*frame_down)++;
            break;
        case 19:
            position_y = 35;
            (*frame_down)++;
            break;
        case 20:
            position_y = 35;
            break;
        }

    return position_y;
}

int complete_down(int *frame_down)
{
    int position_y = 0;

    switch((*frame_down))
    {
    case 20:
        position_y = 18;
        break;
    case 21:
        position_y = 8;
        break;
    case 22:
        position_y = 0;
        break;
    case 23:
        position_y = 0;
        break;
    }

    (*frame_down)++;

    return position_y;
}

int check_complete_down(int *frame_down)
{
    if ((*frame_down)>=24)
        return 1;
    else
        return 0;
}

int check_down(int *frame_down)
{
    if ((*frame_down)==20)
        return 1;
    else
        return 0;
}



int front(int *frame_front)
{
    int position_y;

    switch((*frame_front))
        {

        case 37:
            position_y=38;
            break;
        case 38:
            position_y = 45;
            break;
        case 39:
            position_y = 52;
            break;
        case 40:
            position_y = 52;
            break;
        case 41:
            position_y = 55;
            break;
        case 42:
            position_y = 55;
            break;
        case 43:
            position_y = 50;
            break;
        case 44:
            position_y = 50;
            break;
        case 45:
            position_y = 27;
            break;
        case 46:
            position_y = 53;
            break;
        case 47:
            position_y = 65;
            break;
        case 48:
            position_y = 34;
            break;
        case 49:
            position_y = 10;
            break;
        case 50:
            position_y = 10;
            break;
        }

    if((*frame_front)==50)
        (*frame_front)=86;

    (*frame_front)++;

    return position_y;
}

int check_complete_front(int *frame_front)
{
    if ((*frame_front)>=88)
        return 1;
    else
        return 0;
}



int hit(int *frame_hit, int *hit)
{
    int position_y;

    switch((*frame_hit))
        {
        case 51:
            position_y = 0;
            (*hit)=0;
            break;
        case 52:
            position_y = 0;
            (*hit)=0;
            break;
        case 53:
            position_y = 34;
            (*hit)=0;
            break;
        case 54:
            position_y = 78;
            (*hit)=0;
            break;
        case 55:
            position_y = 83;
            (*hit)=0;
            break;
        case 56:
            position_y = 86;
            (*hit)=1;
            break;
        case 57:
            position_y = 86;
            (*hit)=1;
            break;
        case 58:
            position_y = 55;
            (*hit)=1;
            break;
        case 59:
            position_y = 23;
            (*hit)=1;
            break;
        case 60:
            position_y = 30;
            (*hit)=1;
            break;
        case 61:
            position_y = 30;
            (*hit)=1;
            break;
        case 62:
            position_y = 30;
            (*hit)=1;
            break;
        case 63:
            position_y = 12;
            (*hit)=0;
            break;
        case 64:
            position_y = 0;
            (*hit)=0;
            break;
        }
    (*frame_hit)++;

    return position_y;
}

int check_complete_hit(int *frame_hit)
{
    if ((*frame_hit)>=64)
        return 1;
    else
        return 0;
}



int enemy_type(int const *choice)
{
    switch((*choice))
    {
    case 0:
        return 3;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 1;
        break;
    case 4:
        return 1;
        break;
    case 5:
        return 1;
        break;
    case 6:
        return 3;
        break;
    case 7:
        return 3;
        break;
    case 8:
        return 4;
        break;
    case 9:
        return 2;
        break;
    case 10:
        return 2;
        break;
    case 11:
        return 2;
        break;
    case 12:
        return 2;
        break;
    case 13:
        return 2;
        break;
    case 14:
        return 2;
        break;
    case 15:
        return 4;
        break;
    }
}

void move_sword(int *frame_sword)
{
    if((*frame_sword)<15)
        (*frame_sword)=15;

    if ((*frame_sword)<21)
        (*frame_sword)++;
    else
        (*frame_sword) = 15;
}

void fall_sword(int *frame_sword)
{
    if ((*frame_sword)<22)
        (*frame_sword)=22;

    if ((*frame_sword)<29)
        (*frame_sword)++;
    else
        (*frame_sword) = 29;
}

int check_collision(int const *pos_haut,int const *pos_bas,int const *hit, int const *choice)
{
    switch((*choice))
    {
    case 0:
        if ((*pos_bas)>=1)
            return 0;
        else
            return 1;
        break;
    case 1:
        if ((*pos_bas)>=35)
            return 0;
        else
            return 1;
        break;
    case 2:
        if ((*pos_bas)>=35)
            return 0;
        else
            return 0;
        break;
    case 3:
        if ((*pos_bas)>=35)
            return 0;
        else
            return 1;
        break;
    case 4:
        if ((*pos_bas)>=35)
            return 0;
        else
            return 1;
        break;
    case 5:
        if ((*pos_bas)>=35)
            return 0;
        else
            return 1;
        break;
    case 6:
        if ((*pos_bas)>=2)
            return 0;
        else
            return 1;
        break;
    case 7:
        if ((*pos_bas)>=2)
            return 0;
        else
            return 1;
        break;
    case 8:
        if ((*hit)==1)
            return 0;
        else
            return 1;
        break;
    case 9:
        if ((*pos_haut)>=10)
            return 0;
        else
            return 1;
        break;
    case 10:
        if ((*pos_haut)>=10)
            return 0;
        else
            return 1;
        break;
    case 11:
        if ((*pos_haut)>=10)
            return 0;
        else
            return 1;
        break;
    case 12:
        if ((*pos_haut)>=10)
            return 0;
        else
            return 1;
        break;
    case 13:
        if ((*pos_haut)>=10)
            return 0;
        else
            return 1;
        break;
    case 14:
        if ((*pos_haut)>=10)
            return 0;
        else
            return 1;
        break;
    case 15:
        if ((*hit)==1)
            return 0;
        else
            return 1;
        break;
    }
}
