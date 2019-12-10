#ifndef BACKGROUND_H
# define BACKGROUND_H

#include "runner.h"

typedef struct s_sdl t_sdl;

class Background
{
	public:
	Background(t_sdl *sdl, std::string path);

	void fillbuffer(t_sdl *sdl);

	~Background();

	private:
	SDL_Texture	*texture;
	SDL_Rect	src;
	SDL_Rect	dst;
	SDL_Rect	tmp_src;
	SDL_Rect	tmp_dst;
};

#endif
