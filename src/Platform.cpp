#include "../includes/Platform.h"

using namespace std;

Platform::Platform()
{
}

void	Platform::create_platform(t_sdl *sdl, string path)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
	SDL_query_texture(sdl, texture, NULL, NULL, &dst.w, &dst.h);
	dst = {0, 0, dst.w, dst.h};
}

SDL_Texture	*Platform::get_texture()
{
	return (texture);
}

SDL_Rect	Platform::get_dst()
{
	return (dst);
}

Platform::~Platform()
{
	SDL_DestroyTexture(texture);
}
