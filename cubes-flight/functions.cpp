#include <SDL/SDL.h>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <string>
#include <string.h>
#include <time.h>

#include "text3d.cpp"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 480
#define M 19
#define MAX_SIZE 6
#define SPOTS 80
#define D 20
#define RAD 0.01745329

typedef struct{double x,y,z;} Coord;

struct CUBES{
    Coord pos[M];
    int s[M];
};
typedef struct CUBES;

CUBES T[M];
FILE* score_file;
int score,full;
Coord ship_color;

void stop(){
    t3dCleanup();
    SDL_Quit();
}
void init_SDL(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Cubes Flight", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("icon32.bmp"),NULL);
    SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_OPENGL);
}
void init_OpenGL(){
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(50,(double)SCREEN_WIDTH/SCREEN_HEIGHT,0.1,1000);
    t3dInit();
    ship_color.x=100;ship_color.y=0;ship_color.z=0;
}

//--------------------------------------------------------------------------------------------

void draw_cube(int s=2,Coord pos={0,0,0}){

    glPushMatrix();
    glTranslated(pos.x,pos.y,pos.z+s);

    if(pos.x<-600) glColor3ub(0,0,0);
    else if(pos.x>=-600 && pos.x<-300) glColor3ub(pos.x*1/3+200,pos.x*1/3+200,pos.x*1/3+200);
    else glColor3ub(100,100,100);

    glBegin(GL_QUADS);

    glVertex3d(s,s,s);
    glVertex3d(s,s,-s);
    glVertex3d(-s,s,-s);
    glVertex3d(-s,s,s);

    glVertex3d(s,-s,s);
    glVertex3d(s,-s,-s);
    glVertex3d(s,s,-s);
    glVertex3d(s,s,s);

    glVertex3d(-s,-s,s);
    glVertex3d(-s,-s,-s);
    glVertex3d(s,-s,-s);
    glVertex3d(s,-s,s);

    glVertex3d(-s,s,s);
    glVertex3d(-s,s,-s);
    glVertex3d(-s,-s,-s);
    glVertex3d(-s,-s,s);

    glVertex3d(s,s,-s);
    glVertex3d(s,-s,-s);
    glVertex3d(-s,-s,-s);
    glVertex3d(-s,s,-s);

    glVertex3d(s,-s,s);
    glVertex3d(s,s,s);
    glVertex3d(-s,s,s);
    glVertex3d(-s,-s,s);

    glEnd();

    glPopMatrix();
}
void draw_ship(Coord color){
    glColor3ub(color.x,color.y,color.z);

    glBegin(GL_TRIANGLES);

    glVertex3d(-12,0,0);
    glVertex3d(0,5,0);
    glVertex3d(0,-5,0);

    glVertex3d(-12,0,5.5);
    glVertex3d(0,5,5.5);
    glVertex3d(0,-5,5.5);

    glEnd();

    glBegin(GL_QUADS);

    glVertex3d(-12,0,0);
    glVertex3d(0,5,0);
    glVertex3d(0,5,5.5);
    glVertex3d(-12,0,5.5);

    glVertex3d(-12,0,0);
    glVertex3d(0,-5,0);
    glVertex3d(0,-5,5.5);
    glVertex3d(-12,0,5.5);

    glVertex3d(0,-5,0);
    glVertex3d(0,5,0);
    glVertex3d(0,5,5.5);
    glVertex3d(0,-5,5.5);

    glEnd();
}

void random_cube_generator(int *s,Coord *pos){
    for(int j=0;j<M;j++){
        s[j]=rand()%(MAX_SIZE) + 1;
        pos[j].y=-(M/2)*(SPOTS+D)+rand()%SPOTS+j*(SPOTS+D);
        pos[j].x=-20-M/2*SPOTS+rand()%SPOTS;
    }
}
void init_cubes(){
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            T[i].s[j]=rand()%MAX_SIZE + 1;
            T[i].pos[j].z=0;
            T[i].pos[j].y=-(M/2)*(SPOTS+D)+rand()%SPOTS+j*(SPOTS+D);
            T[i].pos[j].x=-300-M*SPOTS-500+SPOTS*i+rand()%SPOTS;
        }
    }
}

void draw_text(const char* text,int x,int y,double scale,Coord Color){
    std::string stext=text;
    glColor3ub(Color.x,Color.y,Color.z);
    glPushMatrix();
    glRotated(90,0,0,1);
    glRotated(90,1,0,0);
    glTranslated(x,y,60);
    glScaled(scale,scale,scale);
    t3dDraw3D(stext, 0,0, 0, 0.2f);
    glPopMatrix();
}

void move_cubes(int v){
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++) T[i].pos[j].x+=v;
        if(T[i].pos[0].x>M/2*SPOTS){
            T[i].pos[0].x=M/2*SPOTS;
            random_cube_generator(T[i].s,T[i].pos);
        }
    }
}
void draw_cubes_ship(double teta,int pause=0){
    glPushMatrix();
    glRotated(teta*0.4,1,0,0);
    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++){
            if(!pause)T[i].pos[j].y+=teta*0.25;
            draw_cube(T[i].s[j],T[i].pos[j]);
        }

    glPopMatrix();
    glPushMatrix();
    glRotated(-teta*0.1,0,0,1);
    glRotated(teta*0.4,1,0,0);
    glTranslated(200,0,0);
    draw_ship(ship_color);
    glPopMatrix();

}
void draw_score(){
    char s[5];
    sprintf(s,"%5d",score);

    draw_text("score: ",-20,100,10,{200,200,200});
    draw_text(s,20,100,10,{200,200,200});
}

double line(Coord A,Coord B,double x){
    if(B.x!=A.x) return (x-A.x)*(B.y-A.y)/(B.x-A.x) + A.y;
    else return 0;
}

int check_collision(double teta){
    Coord v[3];
    double x,y1,y2,a,b,c;

    v[0].x=188*cos(teta*RAD*0.1);
    v[0].y=188*sin(-teta*RAD*0.1);
    v[1].x=5*sin(-teta*RAD*0.1)+200*cos(-teta*RAD*0.1);
    v[1].y=-5*cos(-teta*RAD*0.1)+200*sin(-teta*RAD*0.1);
    v[2].x=-5*sin(-teta*RAD*0.1)+200*cos(-teta*RAD*0.1);
    v[2].y=5*cos(-teta*RAD*0.1)+200*sin(-teta*RAD*0.1);

    if(v[1].x==v[2].x)
        for(int i=0;i<M;i++)
            for(int j=0;j<M;j++){
                x=T[i].pos[j].x+T[i].s[j];
                y1=T[i].pos[j].y+T[i].s[j];
                y2=T[i].pos[j].y-T[i].s[j];
                a=line(v[0],v[1],x);
                b=line(v[0],v[2],x);
                if(x>=v[0].x && x<=v[0].x+12){
                    if(y1>=a && y1<=b) return 1;
                    else if(y2>=a && y2<=b) return 1;
                }
                x=T[i].pos[j].x-T[i].s[j];
                if(x>=v[0].x && x<=v[0].x+12){
                    if(y1>=a && y1<=b) return 1;
                    else if(y2>=a && y2<=b) return 1;
                }
            }
    else if(v[1].x>v[2].x)
        for(int i=0;i<M;i++)
            for(int j=0;j<M;j++){
                x=T[i].pos[j].x+T[i].s[j];
                y1=T[i].pos[j].y+T[i].s[j];
                y2=T[i].pos[j].y-T[i].s[j];
                a=line(v[0],v[1],x);
                b=line(v[0],v[2],x);
                c=line(v[1],v[2],x);
                if(x>=v[0].x && x<=v[2].x){
                    if(y1>=a && y1<=b) return 1;
                    else if(y2>=a && y2<=b) return 1;
                }
                else if(x>v[2].x && x<=v[1].x){
                    if(y1>=a && y1<=c) return 1;
                    else if(y2>=a && y2<=c) return 1;
                }
                x=T[i].pos[j].x-T[i].s[j];
                if(x>=v[0].x && x<=v[2].x){
                    if(y1>=a && y1<=b ) return 1;
                    else if(y2>=a && y2<=b) return 1;
                }
                else if(x>v[2].x && x<=v[1].x){
                    if(y1>=a && y1<=c) return 1;
                    else if(y2>=a && y2<=c) return 1;
                }

            }
    else if(v[1].x<v[2].x)
        for(int i=0;i<M;i++)
            for(int j=0;j<M;j++){
                x=T[i].pos[j].x+T[i].s[j];
                y1=T[i].pos[j].y+T[i].s[j];
                y2=T[i].pos[j].y-T[i].s[j];
                a=line(v[0],v[1],x);
                b=line(v[0],v[2],x);
                c=line(v[1],v[2],x);
                if(x>=v[0].x && x<= v[1].x){
                    if(y1>=a && y1<=b) return 1;
                    else if(y2>=a && y2<=b) return 1;
                }
                else if(x>v[1].x && x<= v[2].x){
                    if(y1>=c && y1<=b) return 1;
                    else if(y2>=c && y2<=b) return 1;
                }
                x=T[i].pos[j].x-T[i].s[j];
                if(x>=v[0].x && x<= v[1].x){
                    if(y1>=a && y1<=b) return 1;
                    else if(y2>=a && y2<=b) return 1;
                }
                else if(x>v[1].x && x<= v[2].x){
                    if(y1>=c && y1<=b) return 1;
                    else if(y2>=c && y2<=b) return 1;
                }
            }

    for(int i=0;i<M;i++)
        for(int j=0;j<M;j++){
            x=T[i].pos[j].x+T[i].s[j];
            y1=T[i].pos[j].y+T[i].s[j];
            y2=T[i].pos[j].y-T[i].s[j];
            if(v[0].x<=x && v[0].x>=x-T[i].s[j] &&
               v[0].y>=y1 && v[0].y<=y2) return 1;
            else if(v[1].x<=x && v[1].x>=x-T[i].s[j] &&
                    v[1].y>=y1 && v[1].y<=y2) return 1;
            else if(v[2].x<=x && v[2].x>=x-T[i].s[j] &&
                    v[2].y>=y1 && v[2].y<=y2) return 1;
            x=T[i].pos[j].x-T[i].s[j];
            if(v[0].x<=x && v[0].x>=x-T[i].s[j] &&
               v[0].y>=y1 && v[0].y<=y2) return 1;
            else if(v[1].x<=x && v[1].x>=x-T[i].s[j] &&
                    v[1].y>=y1 && v[1].y<=y2) return 1;
            else if(v[2].x<=x && v[2].x>=x-T[i].s[j] &&
                    v[2].y>=y1 && v[2].y<=y2) return 1;

        }

    return 0;
}

void draw_sceen(double teta){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(300,0,0,0,0,0,0,0,1);

    glPushMatrix();
    glRotated(10,0,1,0);
    draw_cubes_ship(teta);
    draw_score();
    glPopMatrix();
    glFlush();
    SDL_GL_SwapBuffers();
}
void draw_pause(double teta){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(300,0,0,0,0,0,0,0,1);

    glPushMatrix();
    glRotated(10,0,1,0);
    draw_cubes_ship(teta,1);
    draw_score();
    glPopMatrix();

    draw_text("PAUSE",0,40,15,{200,200,0});

    glFlush();
    SDL_GL_SwapBuffers();
}

void change_ship_color(){
    if (ship_color.y!=0 && ship_color.z!=0){ship_color.z=0;ship_color.x=100;ship_color.y=0;}
    else if(ship_color.x!=0 && ship_color.z!=0){ship_color.z=100;ship_color.x=0;ship_color.y=100;}
    else if(ship_color.x!=0 && ship_color.y!=0) {ship_color.y=0;ship_color.x=100;ship_color.z=100;}
    else if(ship_color.x!=0) {ship_color.y=100;ship_color.x=0;}
    else if(ship_color.y!=0) {ship_color.y=0;ship_color.z=100;}
    else if(ship_color.z!=0) {ship_color.z=0;ship_color.x=100;ship_color.y=100;}
}

void draw_rotating_ship(int *t,SDL_Event event){
    glPushMatrix();
    glTranslated(200,35,0);
    glPushMatrix();
    glRotated(30,1,1,0);
    glPushMatrix();
    glRotated(*t,0,0,0.2);*t+=2;
    if(event.motion.x>450 && event.motion.x<600 && event.motion.y>180 && event.motion.y<280)
        draw_ship({ship_color.x*2,ship_color.y*2,ship_color.z*2});
    else draw_ship(ship_color);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

}

//--------------------------------------------------------------------------------------------

void new_game(){
    SDL_Event event;
    int e=0,t=0,p=0,Hi_Score;
    char text_Hi_score[100];;
    score_file=fopen("score","r");
    glDisable(GL_DEPTH_TEST);
    if (score_file!=NULL){
        rewind(score_file);
        fscanf(score_file,"%s",text_Hi_score);
        Hi_Score=strtol(text_Hi_score,NULL,10);
        sprintf(text_Hi_score, "High Score : %d", Hi_Score);
        fclose(score_file);
    }
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
                default: e=0; break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN: p=1; break;
            case SDL_MOUSEBUTTONUP:
                if(p){
                    p=0;
                    if(event.motion.x>70 && event.motion.x<290 && event.motion.y>139 && event.motion.y<173)
                        e=1;
                    else if(event.motion.x>450 && event.motion.x<600 && event.motion.y>180 && event.motion.y<280)
                        change_ship_color();
                }
            break;
            default: e=0; break;
        }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt(300,0,0,0,0,0,0,0,1);

        move_cubes(6);
        glPushMatrix();
        glRotated(10,0,1,0);
        for(int i=0;i<M;i++)
            for(int j=0;j<M;j++){
                draw_cube(T[i].s[j],T[i].pos[j]);
            }
        glPopMatrix();

        if(event.motion.x>70 && event.motion.x<290 && event.motion.y>139 && event.motion.y<173)
                draw_text("New Game",-80,40,15,{0,250,250});
        else    draw_text("New Game",-80,40,15,{0,100,100});

        draw_text("Cubes Flight",0,80,20,{200,200,200});
        draw_text(text_Hi_score,0,-40,15,{20,20,200});

        draw_rotating_ship(&t,event);

        glFlush();
        SDL_GL_SwapBuffers();

        SDL_Delay(20);
    }
}
void game_on(){
    SDL_Event event;
    int v=11,game=1,pause=0,p=0;
    double teta;
    score=0;
    init_cubes();
    glEnable(GL_DEPTH_TEST);
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
                default: game=1;break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN: p=1; break;
            case SDL_MOUSEBUTTONUP:
            if(p){
                p=0;
                if(pause) pause=0;
                else pause=1;
            }
            break;
            case SDL_MOUSEMOTION:
            if((event.motion.x - SCREEN_WIDTH/2)/4.0<22 && (event.motion.x - SCREEN_WIDTH/2)/4.0>-22)
                teta = -(event.motion.x - SCREEN_WIDTH/2)/4.0;
            break;
            default: break;
        }

        if(!pause){
            score++;
            if(v<=20 && score%500==0) v+=1;
            move_cubes(v);
            draw_sceen(teta);
            if(check_collision(teta)) game=0;
        }
        else{
            move_cubes(0);
            draw_pause(teta);
        }
        SDL_Delay(20);
    }
}
void game_over(){
    SDL_Event event;
    int e=0,p=0,Hi_Score;
    char text_score[100],text_Hi_score[100];
    glDisable(GL_DEPTH_TEST);
    score_file=fopen("score","r");
    if (score_file!=NULL){
        rewind(score_file);
        fscanf(score_file,"%s",text_Hi_score);
        Hi_Score=strtol(text_Hi_score,NULL,10);
        fclose(score_file);
        sprintf(text_Hi_score, "High Score : %d", Hi_Score);
        if (score>Hi_Score){
            score_file=fopen("score","w+");
            fprintf(score_file,"%d", score);
            fclose(score_file);
            sprintf(text_score, "New Record! : %d", score);
        }
        else sprintf(text_score, "Score : %d", score);
    }

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
                default: e=0; break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN: p=1; break;
            case SDL_MOUSEBUTTONUP:
                if(p){
                    p=0;
                    if(event.motion.x>70 && event.motion.x<280 && event.motion.y>139 && event.motion.y<173)
                        e=1;
                }
            break;
            default: e=0; break;
        }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt(300,0,0,0,0,0,0,0,1);

        move_cubes(6);
        glPushMatrix();
        glRotated(10,0,1,0);
        for(int i=0;i<M;i++)
            for(int j=0;j<M;j++){
                draw_cube(T[i].s[j],T[i].pos[j]);
            }
        glPopMatrix();

        if(event.motion.x>70 && event.motion.x<280 && event.motion.y>139 && event.motion.y<173)
                draw_text("Play Again",-80,40,15,{0,250,250});
        else    draw_text("Play Again",-80,40,15,{0,100,100});


        draw_text(text_Hi_score,53,0,12,{0,0,200});
        draw_text(text_score,65,39,12,{0,0,200});
        draw_text("GAME OVER",0,-50,20,{170,0,0});
        draw_text("Cubes Flight",0,80,20,{200,200,200});

        glFlush();
        SDL_GL_SwapBuffers();

        SDL_Delay(20);
    }
}


