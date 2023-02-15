#include <SDL.h>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SDL tutorial lesson 5";

void initSDL(SDL_Window* &window, SDL_Surface* &screenSurface);

void logSDLError(ostream& os, const string &msg, bool fatal = false);

void quitSDL(SDL_Window* &window, SDL_Surface* &screenSurface);

void waitUntilKeyPressed();

SDL_Surface* loadSurface(std::string path){
       SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL ) logSDLError(std::cout, "Load Image", true);
	optimizedSurface = SDL_LoadBMP(path.c_str());
	if(optimizedSurface == NULL) logSDLError(std::cout, "Optimizing Image", true);
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}

int main(int argc, char* argv[]){
        SDL_Window* window = NULL;
        SDL_Surface* screenSurface = NULL;

        initSDL(window, screenSurface);
        SDL_Surface* gStretchedSurface = loadSurface("picture.bmp");

        SDL_Rect stretchRect;
        stretchRect.x = stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;

        SDL_Event e;
        bool quit = false;
        while(!quit){
              while(SDL_PollEvent(&e)){
                     if(e.type == SDL_QUIT){
                            quit = true;
                            break;
                     }
              }
              SDL_BlitScaled(gStretchedSurface, NULL, screenSurface, &stretchRect);
              SDL_UpdateWindowSurface(window);
        }

        quitSDL(window, screenSurface);
       return 0;
}

void logSDLError(ostream& os, const string &msg, bool fatal){
       os << msg << " Error: " << SDL_GetError() << endl;
       if(fatal){
              SDL_Quit();
              exit(1);
       }
}

void initSDL(SDL_Window* &window, SDL_Surface* &screenSurface)
{
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
              logSDLError(std::cout, "SDL_Init", true);
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

        screenSurface = SDL_GetWindowSurface(window);

        if (screenSurface == nullptr) logSDLError(std::cout, "CreateSurface", true);
}

void quitSDL(SDL_Window* &window, SDL_Surface* &screenSurface){
       SDL_FreeSurface(screenSurface);
       screenSurface = NULL;
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


