#ifndef RUNNER_H
# define RUNNER_H

#include <unistd.h>
#include <iostream>
//#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "Background.h"
#include "Player.h"
#include "Platform.h"
#include <vector>
#include <list>
#include <ctime>

extern int	PLAYER_SPEED;
extern int	BACKGROUND_SPEED;
extern int	FRONT_BACKGROUND_SPEED;
extern int	LVL_SPEED;
extern int	PLAYER_VSPEED;
extern int	TOT_OBJ;
extern const int	NB_IMG;
extern int	OBJ_DESTROYED;

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

class Player;
class Background;
class Platform;

// FUNCTIONS

//main.cpp

int		no_key(const Uint8 *state);


//print.cpp

void	print_score_menu(t_sdl *sdl);
void	print_obstacle(t_sdl *sdl, std::vector <t_obstacle> *platform);
void	print_runner(t_sdl *sdl, Background *background, Background *front_background, Player *player, Player *player2, std::vector <t_obstacle> *platform, std::vector <SDL_Texture*> *score_texture);
void	print_menu(t_sdl *sdl, int menu, SDL_Texture *img_menu, SDL_Texture *img_arrow, Player *player, Player *player2);

//generation.cpp

void	fill_obstacle(t_obstacle *new_obj, Platform obj_list[3], int type, int box_collide, int dst_x, int dst_y);
void	create_lvl(t_sdl *sdl, std::vector <t_obstacle> *platform, Platform obj_list[3]);
void	generation_only_ground(Platform obj_list[3], std::vector <t_obstacle> *platform);

//sdl_functions.cpp

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
