/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sdl_functions.cpp                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 10:22:57 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 16:45:57 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/runner.h"

using namespace std;

void			SDL_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
			failure_exit_program("Initialization SDL WINDOW", sdl);
}

void			SDL_create_window(t_sdl *sdl, int width, int heigth)
{
	SDL_get_desktop_display_mode(sdl, 0, &sdl->display);
	if (width == 0 && heigth == 0)
		sdl->disp = {0, 0, sdl->display.w, sdl->display.h};
	else
		sdl->disp = {0, 0, width, heigth};
	cout << "disp width = " << sdl->disp.w << " // disp height = " << sdl->disp.h << endl;
	if ((sdl->window = SDL_CreateWindow("Runner",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sdl->disp.w, sdl->disp.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == NULL)
		failure_exit_program("Creating sdl->window", sdl);
}

void			SDL_init_renderer(t_sdl *sdl)
{
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)) == NULL)
		failure_exit_program("Creating Window Renderer", sdl);
}

SDL_Texture		*SDL_create_texture(t_sdl *sdl, SDL_Texture *texture, int width,
				int height)
{
	if ((texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, width, height)) == NULL)
		failure_exit_program("Creating texture", sdl);
	return (texture);
}

void			SDL_apply_color_to_renderer(SDL_Color rgba, t_sdl *sdl)
{
	if ((SDL_SetRenderDrawColor(sdl->renderer, rgba.r, rgba.g, rgba.b, rgba.a))
			!= 0)
		failure_exit_program("Rendering Color", sdl);
}

void			SDL_init_img(void)
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		cout << "Failure Initializing IMAGES "<< IMG_GetError() << endl;
}

void			SDL_init_audio(void)
{
	if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0))
		cout << "Failure Initializing Audio " << Mix_GetError() << endl;
}

void			SDL_get_desktop_display_mode(t_sdl *sdl, int option,
				SDL_DisplayMode *display)
{
	if (SDL_GetDesktopDisplayMode(option, display) != 0)
		failure_exit_program("Getting display mode", sdl);
}

SDL_Texture		*SDL_load_texture(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, string path)
{
	if ((texture = IMG_LoadTexture(renderer, path.c_str())) == NULL)
		failure_exit_program("Loading Image on Texture", sdl);
	return (texture);
}

void			SDL_render_clear(t_sdl *sdl, SDL_Renderer *renderer)
{
	if ((SDL_RenderClear(renderer)) != 0)
		failure_exit_program("Clearing Render With Color", sdl);
}

void			SDL_render_copy(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest)
{
	if (SDL_RenderCopy(renderer, texture, src, dest) != 0)
		failure_exit_program("Rendering Copy Of Texture" , sdl);
}

void			SDL_render_target(t_sdl *sdl, SDL_Renderer *renderer,
				SDL_Texture *texture)
{
	if (SDL_SetRenderTarget(renderer, texture) != 0)
		failure_exit_program("Setting Texture as Render Target", sdl);
}

void			SDL_query_texture(t_sdl *sdl, SDL_Texture *texture, Uint32 *format,
				int *access, int *w, int *h)
{
	if (SDL_QueryTexture(texture, format, access, w, h) != 0)
		failure_exit_program("Query Texture", sdl);
}

void			SDL_init_struct(t_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
}

void			SDL_clean_struct(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

void			failure_exit_program(string error, t_sdl *sdl)
{
	cout << "ERROR " << error << " (" << SDL_GetError() << ")" << endl;
	if (!sdl)
		exit(EXIT_FAILURE);
	SDL_clean_struct(sdl);
	exit(EXIT_FAILURE);
}
