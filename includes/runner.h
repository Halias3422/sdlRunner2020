#ifndef RUNNER_H
# define RUNNER_H

#include <unistd.h>
#include <iostream>
//#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include <list>
#include <ctime>

static int	PLAYER_SPEED = 3;
static int	BACKGROUND_SPEED = 1;
static int	LVL_SPEED = 1;
static int	PLAYER_VSPEED = -15;
static int	NB_OBJ = 3;

// STRUCT

typedef struct		s_sdl
{
			SDL_Window		*window;
			SDL_Renderer	*renderer;
			SDL_DisplayMode	display;
			SDL_Rect		disp;
			SDL_Texture		*buffer;
			SDL_Rect		buffer_rect;
}					t_sdl;



// FUNCTIONS

void			SDL_init_window(t_sdl *sdl);
void			SDL_init_renderer(t_sdl *sdl);
SDL_Texture		*SDL_create_texture(t_sdl *sdl, SDL_Texture *texture, int width,
					int height);
void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl);
void			SDL_init_img(void);
void			SDL_init_audio(void);
void			SDL_get_desktop_display_mode(t_sdl *sdl, int option,
					SDL_DisplayMode *display);
SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
					SDL_Texture *texture, std::string path);
void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer);
void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
					SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture);
void			SDL_query_texture(t_sdl *sdl, SDL_Texture *texture, Uint32 *format,
					int *access, int *w, int *h);
void			SDL_init_struct(t_sdl *sdl);
void			SDL_clean_struct(t_sdl *sdl);
void			failure_exit_program(std::string error, t_sdl *sdl);

#endif
