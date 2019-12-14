#include "../includes/runner.h"

using namespace std;

void	print_obstacle(t_sdl *sdl, vector <t_obstacle> *platform)
{
	vector <t_obstacle>::iterator i;

	for (i = platform->begin(); i != platform->end(); i++)
	{
		if (i->box_collide == 1)
		{
			SDL_render_copy(sdl, sdl->renderer, i->texture, NULL, &i->dst);
		}
	}
}

void	print_runner(t_sdl *sdl, Background *background, Background *front_background, Player *player, Player *player2, vector <t_obstacle> *platform, vector <SDL_Texture*> *score_texture)
{
	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
	SDL_render_clear(sdl, sdl->renderer);
	
	background->fillbuffer(sdl, "background");
	front_background->fillbuffer(sdl, "front_background");
	player->horizontal_move(0, platform);
	player2->horizontal_move(0, platform);
	player->vertical_move(platform);
	player2->vertical_move(platform);

	if (player->is_alive() == true)
		player->fill_buffer(sdl);
	if (player2->is_alive() == true)
	player2->fill_buffer(sdl);
	print_obstacle(sdl, platform);

	player->print_score(sdl, score_texture);
	player2->print_score(sdl, score_texture);
	player->print_heart(sdl);
	player2->print_heart(sdl);


	SDL_render_target(sdl, sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, &sdl->disp);
	SDL_RenderPresent(sdl->renderer);
}

void	print_menu(t_sdl *sdl, int menu, SDL_Texture *img_menu, SDL_Texture *img_arrow, Player *player, Player *player2)
{
	SDL_Rect	dst;
	SDL_Rect	menu_dst;

	SDL_render_clear(sdl, sdl->renderer);
	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
	SDL_render_clear(sdl, sdl->renderer);

	menu_dst = {0, 0, 0, 0};
	SDL_query_texture(sdl, img_menu, NULL, NULL, &menu_dst.w, &menu_dst.h);

	if (menu == 0)
		dst = {261, 214, 0, 0};
	if (menu == 1)
		dst = {221, 293, 0, 0};
	if (menu == 2)
		dst = {257, 379, 0, 0};
	SDL_render_copy(sdl, sdl->renderer, img_menu, NULL, &menu_dst);
	SDL_query_texture(sdl, img_arrow, NULL, NULL, &dst.w, &dst.h);
	SDL_render_copy(sdl, sdl->renderer, img_arrow, NULL, &dst);
	player->menu_animation(sdl);
	player2->menu_animation(sdl);
	SDL_render_target(sdl, sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, &sdl->disp);
	SDL_RenderPresent(sdl->renderer);
}

void	print_score_menu(t_sdl *sdl)
{
	SDL_Texture	*loose(nullptr);
	SDL_Rect	dst = {0, 0, 720, 480};

	PLAYER_SPEED = 0;
	BACKGROUND_SPEED = 0;
	FRONT_BACKGROUND_SPEED = 0;
	LVL_SPEED = 0;
	PLAYER_VSPEED = 0;

	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
	loose = SDL_load_texture(sdl, sdl->renderer, loose, "img/loose.png");
	SDL_render_copy(sdl, sdl->renderer, loose, NULL, &dst);
	SDL_render_target(sdl, sdl->renderer, NULL);
	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, &sdl->disp);
	SDL_RenderPresent(sdl->renderer);
	SDL_DestroyTexture(loose);
}
