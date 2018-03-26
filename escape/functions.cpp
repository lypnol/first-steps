#include <SDL/SDL.h>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <string>
#include <string.h>
#include <time.h>

#include "text3d.cpp"

#define SW 400
#define SH 400
#define G 40
#define PI 3.14159
#define DEG 57.2957

typedef struct{double x,y;} POINT;
typedef struct{POINT r,v;double m;} CELL;
typedef struct{int r,g,b;} COLOR;

int N,Hscore,score;
FILE *F_score;
CELL *P,V;

void add_cell(){
    if(N<99)N++;
    if(N!=100){
        CELL *NP=(CELL*)malloc(N*sizeof(CELL));
        for(int i=0;i<N-1;i++) NP[i]=P[i];
        free(P);
        P=NP;
        P[N-1].r.x= (SW/2) - rand()%(SW);
        P[N-1].r.y= (SH/2) - rand()%(SH);
        P[N-1].v.x=0;
        P[N-1].v.y=0;
        P[N-1].m=rand()%6+4;
    }
}
void del_cell(int i){
    if(N>0)N--;
    if(N!=0){
        CELL *NP=(CELL*)malloc(N*sizeof(CELL));
        for(int j=0;j<i && j<N;j++) NP[j]=P[j];
        for(int j=i;j<N;j++) NP[j]=P[j+1];
        free(P);
        P=NP;
    }
}

void stop(){
    t3dCleanup();
    SDL_Quit();
    free(P);
}
void init_SDL(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Escape", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"),NULL);
    SDL_SetVideoMode(SW, SH, 32, SDL_OPENGL);
}
void init_OpenGL(){
    t3dInit();
}

void generate_cells(){
    P=(CELL*)malloc(sizeof(CELL)*N);
    for(int i=0;i<N;i++){
        P[i].r.x=SW/2 - rand()%SW;
        P[i].r.y=SH/2 - rand()%SH;
        P[i].v.x=0;
        P[i].v.y=0;
        P[i].m=rand()%6+4;
    }
}
void randomize_cells(){
    for(int i=0;i<N;i++){
        P[i].v.x=3 - rand()%6+0.5;
        P[i].v.y=3 - rand()%6+0.5;
    }
}

//--------------------------------------------------------------------------------------------
double dist(POINT a,POINT b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void draw_text(const char* text,POINT p,double scale,COLOR C){
    std::string stext=text;
    glColor3ub(C.r,C.g,C.b);
    glPushMatrix();
    glScaled(scale/100*SH/SW,scale/100,1);
    glTranslated(p.x,p.y,0);
    t3dDraw2D(stext, 0,0, 0.2f);
    glPopMatrix();
}
void draw_dot(POINT C,COLOR Co,double s){
    if(s!=0){
        glColor3ub(Co.r,Co.g,Co.b);
        glBegin(GL_POLYGON);
        for(int a=0;a<ceil(s*2);a++)
            glVertex2d((C.x+s*cos(a*2*PI/ceil(s*2)))/(SW/2),(C.y+s*sin(a*2*PI/ceil(s*2)))/(SH/2));

        glEnd();
    }
}
void draw_line(POINT a,POINT b,COLOR Co){
    glColor3ub(Co.r,Co.g,Co.b);
    glPushMatrix();
    glTranslated(a.x/(SW/2),a.y/(SH/2),0);
    double d=dist(a,b);
    if((b.y-a.y)!=0){
        if(b.y-a.y>0) glRotated(-atan((b.x-a.x)/(b.y-a.y))*DEG,0,0,1);
        else glRotated((PI-atan((b.x-a.x)/(b.y-a.y)))*DEG,0,0,1);
    }
    else{
        if(b.x>a.x) glRotated(-90,0,0,1);
        else glRotated(90,0,0,1);
    }
    glBegin(GL_QUADS);
    glVertex2d(-0.75/(SW/2),0);
    glVertex2d(-0.75/(SW/2),d/(SH/2));
    glVertex2d(0.75/(SW/2),d/(SH/2));
    glVertex2d(0.75/(SW/2),0);
    glEnd();
    glPopMatrix();
}

void draw_score(){
    char s[5];
    sprintf(s,"%d",score);
    draw_text("score: ",{-10,11},8,{200,200,200});
    draw_text(s,{-6.5,11},8,{200,200,200});
}
void draw_life(){
    char s[10];
    sprintf(s,"%2.1f",abs(V.m-2)*100/8.0);
    draw_text("life: ",{6.7,11},8,{200,200,200});
    draw_text(s,{10,11},8,{200,200,200});
}

void move_cells(){
    POINT a;
    double d;
    for(int i=0;i<N;i++){
        a={0,0};
        d=dist(P[i].r,V.r);
        if(d>=(P[i].m+V.m)){
            a.x = G*8*((V.r.x-P[i].r.x))/(d*d*d);
            a.y = G*8*((V.r.y-P[i].r.y))/(d*d*d);
        }
        else{
            P[i].v.x= -(P[i].m*P[i].v.x)/(5+P[i].m);
            P[i].v.y= -(P[i].m*P[i].v.y)/(5+P[i].m);
            if(V.m>0) V.m -= P[i].m/40.0;
        }
        P[i].r.x += P[i].v.x+0.5*a.x;
        P[i].r.y += P[i].v.y+0.5*a.y;
        if(abs(P[i].v.x)<10) P[i].v.x += a.x;
        if(abs(P[i].v.y)<10) P[i].v.y += a.y;
        if(P[i].r.x+P[i].m>=(SW/2) || P[i].r.x-P[i].m<=-(SW/2)){
            if(P[i].r.x>0) P[i].r.x=((SW/2)-P[i].m);
            else P[i].r.x=-((SW/2)-P[i].m);
            P[i].v.x = -P[i].v.x;
        }
        if(P[i].r.y+P[i].m>=(SH/2) || P[i].r.y-P[i].m<=-(SH/2)){
            if(P[i].r.y>0) P[i].r.y=((SH/2)-P[i].m);
            else P[i].r.y=-((SH/2)-P[i].m);
            P[i].v.y = -P[i].v.y;
        }
    }
}
void show_cells(){
    for(int i=0;i<N;i++){
        P[i].r.x += P[i].v.x;
        P[i].r.y += P[i].v.y;
        if(P[i].r.x+P[i].m>=(SW/2) || P[i].r.x-P[i].m<=-(SW/2)){
            if(P[i].r.x>0) P[i].r.x=((SW/2)-P[i].m);
            else P[i].r.x=-((SW/2)-P[i].m);
            P[i].v.x = -P[i].v.x;
        }
        if(P[i].r.y+P[i].m>=(SH/2) || P[i].r.y-P[i].m<=-(SH/2)){
            if(P[i].r.y>0) P[i].r.y=((SH/2)-P[i].m);
            else P[i].r.y=-((SH/2)-P[i].m);
            P[i].v.y = -P[i].v.y;
        }
    }
}

void draw_sceen(int pause){
    char n[3];
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<N;i++) draw_dot(P[i].r,{0,200,200},P[i].m);
    draw_dot(V.r,{200,0,0},V.m);
    draw_score();
    sprintf(n,"%d",N);
    draw_text(n,{0,11},8,{0,200,200});
    draw_life();
    if(pause) draw_text("PAUSE",{0,0},18,{200,200,200});
    glFlush();
    SDL_GL_SwapBuffers();
}


//--------------------------------------------------------------------------------------------

void new_game(){
    SDL_Event event;
    int e=0,p=0;
    char C_Hscore[100];

    F_score=fopen("score","r");
    if (F_score!=NULL){
        rewind(F_score);
        fscanf(F_score,"%s",C_Hscore);
        Hscore=strtol(C_Hscore,NULL,10);
        sprintf(C_Hscore, "High Score : %d", Hscore);
        fclose(F_score);
    }
    SDL_ShowCursor(SDL_ENABLE);
    SDL_WarpMouse(SW/2,SH/2-25);
    N=7; generate_cells(); randomize_cells();
    while(!e){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
            exit(0);
            break;
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                exit(0);
                break;
                case SDLK_RETURN:
                e=1;
                break;
                default: e=0; break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN: p=1; break;
            case SDL_MOUSEBUTTONUP:
                if(p){
                    p=0;
                    if(event.motion.x>90*SW/400 && event.motion.x<310*SW/400
                    && event.motion.y>150*SH/400 && event.motion.y<200*SH/400)
                        if(event.button.button == SDL_BUTTON_LEFT) e=1;
                }
            break;
            default: e=0; break;
        }

        glClear( GL_COLOR_BUFFER_BIT);
        show_cells();
        for(int i=0;i<N;i++) draw_dot(P[i].r,{0,200,200},P[i].m);

        if(event.motion.x>90*SW/400 && event.motion.x<310*SW/400
            && event.motion.y>150*SH/400 && event.motion.y<200*SH/400)
                draw_text("New Game",{0,1},16,{0,250,250});
        else    draw_text("New Game",{0,1},16,{0,100,100});

        draw_text("Escape",{0,3.3},20,{200,200,200});
        draw_line({-90,95},{-50,95},{200,200,200});
        draw_line({-90,95},{-90,105},{200,200,200});
        draw_line({50,155},{90,155},{200,200,200});
        draw_line({90,155},{90,145},{200,200,200});
        draw_text(C_Hscore,{0,-4},10,{200,200,200});
        draw_text("by ayoub sbai",{9.5,-13},7,{200,200,200});

        glFlush();
        SDL_GL_SwapBuffers();

        SDL_Delay(20);
    }
}
void game_on(){
    SDL_Event event;
    int game=1,pause=0,p=0,t=0,N0=N;

    V.r={0,0}; V.v={0,0}; V.m=10;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouse(SW/2, SH/2);
    while(game){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
            exit(0);
            break;
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                exit(0);
                break;
                default: game=1; break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN: p=1; break;
            case SDL_MOUSEBUTTONUP:
            if(p){
                p=0;
                switch(event.button.button){
                    case SDL_BUTTON_LEFT:
                        if(pause){
                            SDL_ShowCursor(SDL_DISABLE);
                            SDL_WarpMouse(V.r.x+(SW/2),(SH/2)-V.r.y);
                            pause=0;
                        }
                        else{
                            SDL_WarpMouse(SW/2,SH/2);
                            SDL_ShowCursor(SDL_ENABLE);
                            pause=1;
                        }
                    default: break;
                }
            }
            break;
            case SDL_MOUSEMOTION:
            if(!pause){
                V.r.x=event.motion.x-(SW/2);
                V.r.y=(SH/2)-event.motion.y;
            }
            break;
            default: game=1; break;
        }

        if(!pause){
            move_cells();
            t++;
            if(t==500){
                t=0;
                if(N<99) add_cell();
            }
            score = ((N-N0)*500+t)/10;
        }
        if(V.m<=2) game=0;
        draw_sceen(pause);

        SDL_Delay(20);
    }
}
void game_over(){
    SDL_Event event;
    int e=0,p=0,H,N0=N;
    char C_Hscore[100],C_score[100];

    F_score=fopen("score","r");
    if (F_score!=NULL){
        rewind(F_score);
        fscanf(F_score,"%s",C_Hscore);
        Hscore=strtol(C_Hscore,NULL,10);
        fclose(F_score);
        sprintf(C_Hscore, "High Score : %d", Hscore);
        if (score>Hscore){
            F_score=fopen("score","w+");
            fprintf(F_score,"%d", score);
            fclose(F_score);
            sprintf(C_score, "New Record! : %d", score);
        }
        else sprintf(C_score, "Score : %d", score);
    }
    SDL_ShowCursor(SDL_ENABLE);
    SDL_WarpMouse(SW/2,SH/2-25);
    randomize_cells();
    while(!e){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
            exit(0);
            break;
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                exit(0);
                break;
                case SDLK_RETURN:
                e=1;
                break;
                default: e=0; break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN: p=1; break;
            case SDL_MOUSEBUTTONUP:
                if(p){
                    p=0;
                    if(event.motion.x>90*SW/400 && event.motion.x<310*SW/400
                        && event.motion.y>150*SH/400 && event.motion.y<200*SH/400)
                        if(event.button.button == SDL_BUTTON_LEFT) e=1;
                }
            break;
            default: e=0; break;
        }

        glClear( GL_COLOR_BUFFER_BIT);

        show_cells();
        for(int i=0;i<N;i++) draw_dot(P[i].r,{0,200,200},P[i].m);
        if(event.motion.x>90*SW/400 && event.motion.x<310*SW/400
            && event.motion.y>150*SH/400 && event.motion.y<200*SH/400)
                draw_text("Play again",{0,1},16,{0,250,250});
        else    draw_text("Play again",{0,1},16,{0,100,100});

        draw_text("Game Over",{0,3.3},20,{200,0,0});
        draw_line({-150,95},{-100,95},{200,0,0});
        draw_line({-150,95},{-150,115},{200,0,0});
        draw_line({100,155},{150,155},{200,0,0});
        draw_line({150,155},{150,135},{200,0,0});
        draw_text(C_score,{0,-1.3},10,{200,200,200});
        draw_text(C_Hscore,{0,-4},10,{200,200,200});
        draw_text("by ayoub sbai",{9.5,-13},7,{200,200,200});

        glFlush();
        SDL_GL_SwapBuffers();

        SDL_Delay(20);
    }
    for(int i=0;i<N0-7;i++) del_cell(rand()%(N-1));
}

