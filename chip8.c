#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "SDL.h"

typedef struct {
	SDL_Window *window;
} sdl_t;

typedef struct { 
	uint32_t window_width;
	uint32_t window_height;
} config_t;

// intialize SDL
bool init_sdl(sdl_t *sdl, const config_t config){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		SDL_Log("Could not intialize SDL subsystem! %s\n", SDL_GetError());
	 	return false;   
    }
	sdl->window = SDL_CreateWindow("CHIP 8", SDL_WINDOWPOS_CENTERED, 
							SDL_WINDOWPOS_CENTERED, config.window_width, 
			       			config.window_height, 0);
	
	if(!sdl->window){
		SDL_Log("Could not create SDL window %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void final_cleanup(const sdl_t sdl){
	SDL_DestroyWindow(sdl.window);
	SDL_Quit(); // Shut down SDL subsystem
}

bool set_config_from_args(config_t *config, const int argc, char **argv){
	
	*config = (config_t){
		.window_width = 64,  	//CHIP8 original x resolution
		.window_height = 32,	//CHIP8 original y resolution
	};

	for(int i=1; i<argc; i++){
		(void) argv[i]; //prevent compiler error from unused variables argc/argv
	}
	return true;
}

int main(int argc, char **argv){
	(void) argc;
	(void) argv;
	// initialize emulator config options
	config_t config = {0};
	if (!set_config_from_args(&config, argc, argv)) exit(EXIT_FAILURE);
	
	// initialize SDL
	sdl_t sdl = {0};
	if(!init_sdl(&sdl, config)) exit(EXIT_FAILURE);
	

	// Final cleanup
	final_cleanup(sdl);

	exit(EXIT_SUCCESS);
} 

