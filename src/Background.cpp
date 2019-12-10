#include "../includes/runner.h"

using namespace std;

Background::Background(t_sdl *sdl, string path)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
	src = {0, 0, 720, 480};
	dst = {0, 0, 720, 480};
	tmp_src = {0, 0, 720, 480};
	tmp_dst = {0, 0, 720, 480};
}

void Background::fillbuffer(t_sdl *sdl)
{
	int		delta(0);

	if (src.x + 720 >= 10000)
	{
		delta = (src.x + 720) - 10000;
		src.w = 720 - delta;
		dst.w = 720 - delta;
		tmp_src.w = delta;
		tmp_dst.w = delta;
		tmp_dst.x = 720 - delta;
		SDL_render_copy(sdl, sdl->renderer, texture, &tmp_src, &tmp_dst);
	}
	SDL_render_copy(sdl, sdl->renderer, texture, &src, &dst);
	if (src.x >= 10000)
	{
		src.w = 720;
		dst.w = 720;
		src.x = 0;
	}
	src.x += 100;
}

Background::~Background()
{
	SDL_DestroyTexture(texture);
}
