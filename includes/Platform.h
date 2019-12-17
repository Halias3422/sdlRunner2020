#ifndef PLATFORM_H
#define PLATFORM_H

#include "runner.h"

class Platform
{
	public:

	Platform();
	void		create_platform(t_sdl *sdl, std::string path);
	SDL_Rect	get_dst();
	SDL_Texture	*get_texture();
	~Platform();

	private:

	SDL_Texture	*texture = NULL;
	SDL_Rect	dst;
};

typedef struct		s_obstacle
{
		int			type;
		int			nb_obstacle;
		int			box_collide;
		SDL_Texture	*texture;
		SDL_Rect	dst;
		int			extra_horizontal_force;
		int			extra_vertical_force;
		int			ignore;
}					t_obstacle;

#endif
