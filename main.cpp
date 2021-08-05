#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <SDL2/SDL_mixer.h>
using namespace std;
struct ajor
{
    bool ex;
    int streng;
};
int main( int argc, char * argv[] )
{
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music * background;
    Mix_Chunk * jumpEfect=Mix_LoadWAV("tagh.wav");
    short int i,j,qum;

    cout<<"che ahangi pakhsh beshe? \n 1.Shadow \t 2.Journey \t 3.Flight \t 4.Council \t 5.None"<<endl;
    cin>>qum;
    if(qum==1) background=Mix_LoadMUS("Shadow.mp3");
    else if(qum==2) background=Mix_LoadMUS("Journey.mp3");
    else if(qum==3) background=Mix_LoadMUS("Flight.mp3");
    else if(qum==4) background=Mix_LoadMUS("Council.mp3");
    else if(qum==5) background=NULL;

//1.present adad ha roye safhe  2.esm vared kardan v save kardan  3.seda gozari(wav)   4.aks pas zamine
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    Mix_PlayMusic(background,-1);

    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1240, 700, WND_flags, &m_window, &m_renderer ); //zarib arz safhe 0.75 shode
    SDL_RaiseWindow(m_window);
    //define parameters
    bool partab=false,p=false,o=false,k=false,pus=false;
    int x=0,v=40,x0,l=60,kom=0,r=15,h,score=0;
    double t=0,theta=M_PI/2,theta0;
    ajor a[5][5];
    SDL_Event *e = new SDL_Event();
    int level=1,damage,xt,yt,brok=0;
    short int lives=3;


    for(i=1;i<5;i++) for(j=0;j<5;j++) a[i][j].ex=false;
    //tolid randim agor ha v streng
    for(i=0;i<5;i++)
    {
        a[0][i].ex=rand()%3;
        a[0][i].streng=rand()%level+1;
        if(!a[0][0].ex && !a[0][1].ex && !a[0][2].ex && !a[0][3].ex && !a[0][4].ex) a[0][3].ex=true;
        else if(a[0][0].ex && a[0][1].ex && a[0][2].ex && a[0][3].ex && a[0][4].ex) a[0][3].ex=false;
    }
    damage=level;
    while(true)
    {
        SDL_SetRenderDrawColor( m_renderer, 225, 225, 225, 255 );
        SDL_RenderClear( m_renderer );
        if(partab)
        {
            xt=700+x0+v*cos(theta0)*t;
            yt=kom+650-v*sin(theta0)*t;
            /*baztab ofoghi*/ if(xt<=r-2 || xt>=1240-r+2){
                Mix_PlayChannel(-1,jumpEfect,0);
                x0+=2*v*cos(theta0)*t;
                theta0=M_PI-theta0;
            }
            /*baztab amoodi*/ else if(yt<=r){
                Mix_PlayChannel(-1,jumpEfect,0);
                kom-=2*v*sin(theta0)*t;
                theta0*=-1;
            }
            /*baztab racket*/ else if(xt>600+x && xt<800+x && yt==652 && t>1){
                Mix_PlayChannel(-1,jumpEfect,0);
                kom-=2*v*sin(theta0)*t;
                theta0*=-1;
            }
            /*khareg shodan toop*/ else if(yt>710){
                lives--;
                cout<<"Lives:"<<lives<<endl;
                if(lives==0)
                    return 0;
                partab=false;
            }
            else //barkhord be agor ha
            {
                for(i=0;i<5;i++)
                {
                    for(j=0;j<5;j++)
                    {
                        if(( ((xt==40+240*j-r || xt==40+240*j-r+1) && cos(theta0)>=0) || (xt==240*(j+1)+r && cos(theta0)<=0)) && yt<=110*(i+1) && yt>=110*(i+1)-70 && a[i][j].ex)
                        {
                            Mix_PlayChannel(-1,jumpEfect,0);
                            x0+=2*v*cos(theta0)*t;
                            theta0=M_PI-theta0;
                            h=damage;
                            damage-=a[i][j].streng;
                            a[i][j].streng-=h;
                            if(a[i][j].streng<=0)
                            {
                                brok++;
                                a[i][j].ex=false;
                            }
                            if(damage<=0)
                            {
                                level++;
                                score+=level*brok;
                                cout<<"level:"<<level<<endl<<"score:"<<score<<endl;
                                partab=false;
                                //radif akhar
                                for(j=0;j<5;j++)
                                    if(a[4][j].ex)
                                    {SDL_Delay(1000); SDL_DestroyWindow( m_window );SDL_DestroyRenderer( m_renderer );SDL_Quit();return 0;}
                                for(i=4;i>0;i--)//shift agorha
                                {
                                    for(j=0;j<5;j++)
                                        a[i][j]=a[i-1][j];
                                }
                                for(j=0;j<5;j++)//tolid again line1
                                {
                                    a[0][j].ex=rand()%2;
                                    a[0][j].streng=rand()%level+1;
                                    if(!a[0][0].ex && !a[0][1].ex && !a[0][2].ex && !a[0][3].ex && !a[0][4].ex) a[0][3].ex=true;else if(a[0][0].ex && a[0][1].ex && a[0][2].ex && a[0][3].ex && a[0][4].ex) a[0][3].ex=false;
                                }
                            }
                        }
                        else if(( (yt==110*(i+1)+r && sin(theta0)>=0) || (yt==110*(i+1)-70-r && sin(theta0)<=0) ) && xt<=240*(j+1) && xt>=40+240*j && a[i][j].ex)
                        {
                            Mix_PlayChannel(-1,jumpEfect,0);
                            kom-=2*v*sin(theta0)*t;
                            theta0*=-1;
                            h=damage;
                            damage-=a[i][j].streng;
                            a[i][j].streng-=h;
                            if(a[i][j].streng<=0){
                                brok++;
                                a[i][j].ex=false;}
                            if(damage<=0)
                            {
                                level++;
                                score+=level*brok;
                                cout<<"level:"<<level<<endl<<"score:"<<score<<endl;
                                partab=false;
                                //radif akhar
                                for(j=0;j<5;j++)
                                    if(a[4][j].ex)
                                    {SDL_Delay(1000); SDL_DestroyWindow( m_window );SDL_DestroyRenderer( m_renderer );SDL_Quit();return 0;}
                                for(i=4;i>0;i--)//shift agorha
                                {
                                    for(j=0;j<5;j++)
                                        a[i][j]=a[i-1][j];
                                }
                                for(j=0;j<5;j++)//tolid again line1
                                {
                                    a[0][j].ex=rand()%3;
                                    a[0][j].streng=rand()%level+1;
                                    if(!a[0][0].ex && !a[0][1].ex && !a[0][2].ex && !a[0][3].ex && !a[0][4].ex) a[0][3].ex=true;else if(a[0][0].ex && a[0][1].ex && a[0][2].ex && a[0][3].ex && a[0][4].ex) a[0][3].ex=false;
                                }
                            }
                        }
                    }
                }
            }
            filledEllipseRGBA(m_renderer,700+x0+v*cos(theta0)*t,kom+650-v*sin(theta0)*t,15,15,20,100,100,255*damage/level);
        }
        else
        {
            filledEllipseRGBA(m_renderer,700+x,650,15,15,20,100,100,255);
            aalineRGBA(m_renderer,700+x,650,700+x+l*cos(theta),650-l*sin(theta),100,100,100,255);
        }
        if(k && p && o) //code taghal
        {
            for(i=1;i<3;i++)
            {
                for(j=0;j<5;j++)
                    a[i][j].ex=false;
            }
        }
        //present agor ha
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                if(a[i][j].ex)
                    boxRGBA(m_renderer,40+240*j,110*(i+1),240*(j+1),110*(i+1)-70,200,10,20,255*(a[i][j].streng)/level);
            }
        }

        boxRGBA(m_renderer,600+x,665,800+x,690,50,100,200,255);//racket
        t+=0.01;
//        SDL_Texture * m_texture;
//        textColor1(m_renderer,100,650,"level:",gFont,text_color,m_texture);
//        textColor1(m_renderer,600,650,"score:",gFont,text_color,m_texture);
//        textColor1(m_renderer,1000,650,"lives:",gFont,text_color,m_texture);
        SDL_RenderPresent(m_renderer);
        while(pus)
        {
            //aks pause bezar
            while(SDL_PollEvent(e))
            {
                if(e->type==SDL_KEYDOWN)
                {
                    if(e->key.keysym.sym==SDLK_0)
                    {
                        pus=false;
                        break;
                    }
                }
            }
        }
        while(SDL_PollEvent(e))
        {
            if(e->type==SDL_KEYDOWN)
            {
                switch (e->key.keysym.sym)
                {
                    case SDLK_0:
                        Mix_PlayChannel(-1,jumpEfect,0);
                        pus=true;
                        break;
                    case SDLK_d:
                        x+=5;
                        break;
                    case SDLK_a:
                        x-=5;
                        break;
                    case SDLK_w:
                        theta+=0.1;
                        break;
                    case SDLK_x:
                        theta-=0.1;
                        break;
                    case SDLK_p:
                        p=true;
                        break;
                    case SDLK_o:
                        o=true;
                        break;
                    case SDLK_k:
                        k=true;
                        break;
                    case SDLK_SPACE:
                        if(!partab)
                        {
                            partab=true;
                            damage=level;
                            x0=x;
                            kom=0;
                            theta0=theta;
                            t=0;
                        }
                        break;
                    case SDLK_q:
                        SDL_DestroyWindow( m_window );
                        SDL_DestroyRenderer( m_renderer );
                        SDL_Quit();
                        return 0;
                }
            }
            else if(e->type==SDL_KEYUP)
            {
                switch(e->key.keysym.sym)
                {
                    case SDLK_p:
                        p=false;
                        break;
                    case SDLK_o:
                        o=false;
                        break;
                    case SDLK_k:
                        k=false;
                        break;
                }
            }
        }
    }
}

