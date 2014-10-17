

#include<SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character;
SDL_Rect rect_background,rect_character;



int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0; rect_character.y = 125; rect_character.w = w; rect_character.h = h;

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
            /*Aqui se valida la posicion del personaje para ver en que punto se
            encuentra dentro del mapa de bits y si se encuentra dentro de los limites
            de la pantalla, procede a moverse*/
            if((rect_character.x>=0 && rect_character.x<=(rect_background.w-rect_character.w)) && (rect_character.y>=0 && rect_character.y<=(rect_background.h-rect_character.h))){
                if(Event.key.keysym.sym == SDLK_d || Event.key.keysym.sym == SDLK_RIGHT)
                    rect_character.x+=5;
                /*Movimiento hacia la derecha*/
                if(Event.key.keysym.sym == SDLK_a || Event.key.keysym.sym == SDLK_LEFT)
                    rect_character.x-=5;
                /*Movimiento hacia la izquierda*/
                if(Event.key.keysym.sym == SDLK_w || Event.key.keysym.sym == SDLK_UP)
                    rect_character. y-=5;
                /*Movimiento hacia la arriba*/
                if(Event.key.keysym.sym == SDLK_s || Event.key.keysym.sym == SDLK_DOWN)
                    rect_character.y+=5;
                /*Movimiento hacia la abajo*/
                }
            }else{
            /*Esto es cuando se sale de las dimensiones de la imagen tomando en cuenta
            el tamaño del personaje*/
            if(rect_character.x < 0)
                rect_character.x=0;
            if(rect_character.y < 0)
                rect_character.y=0;
            if(rect_character.x > (rect_background.w-rect_character.w))
                rect_character.x=468;
            if(rect_character.y > (rect_background.h-rect_character.h))
                rect_character.y=218;

            /*Estas validaciones lo que hacen es regresar al personaje
            al borde de la pantalla dependiendo de su ubicacion en x
            o en y*/
            }
            /*Esto se hace en la validacion del KeyDown para que se haga de
            inmediato para asi no tener que tocar otra tecla para que el
            personaje regrese dentro de los limites de la pantalla*/
        }



        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderPresent(renderer);
    }

	return 0;
}
