#include <SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SDL tutorial lesson 1";

void initSDL(SDL_Window* &window, SDL_Surface* &surface);

void logSDLError(ostream& os, const string &msg, bool fatal = false);

void quitSDL(SDL_Window* &window, SDL_Surface* &surface);

void waitUntilKeyPressed();

void loadMedia(SDL_Surface* &hello);

int main(int argc, char* argv[]){
        SDL_Window* window = NULL;
        SDL_Surface* surface = NULL;
        SDL_Surface* hello = NULL;

        initSDL(window, surface);
        loadMedia(hello);

        SDL_Event e;
        bool quit = false;
        while(!quit){
              while(SDL_PollEvent(&e)){
                     if(e.type == SDL_QUIT){
                            quit = true;
                            break;
                     }
              }
              SDL_BlitSurface(hello, NULL, surface, NULL);
              SDL_UpdateWindowSurface(window);
        }

        quitSDL(window, surface);
       return 0;
}

void logSDLError(ostream& os, const string &msg, bool fatal){
       os << msg << " Error: " << SDL_GetError() << endl;
       if(fatal){
              SDL_Quit();
              exit(1);
       }
}

void initSDL(SDL_Window* &window, SDL_Surface* &surface)
{
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
              logSDLError(std::cout, "SDL_Init", true);
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

        surface = SDL_GetWindowSurface(window);

        if (surface == nullptr) logSDLError(std::cout, "CreateSurface", true);
}

void quitSDL(SDL_Window* &window, SDL_Surface* &surface){
       SDL_FreeSurface(surface);
       surface = NULL;
       SDL_DestroyWindow(window);
       window = NULL;
       SDL_Quit();
}

void waitUntilKeyPressed(){
        SDL_Event e;
        while (true) {
               if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) return;
               SDL_Delay(100);
        }
}

void loadMedia(SDL_Surface* &hello){
       hello = SDL_LoadBMP( "x.bmp" );
       if(hello == NULL ) logSDLError(std::cout, "loadMedia", true);
}
