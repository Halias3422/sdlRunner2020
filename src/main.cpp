/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.cpp                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 14:44:37 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/20 15:35:45 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/runner.h"

using namespace std;

int		PLAYER_SPEED = 2;
int		BACKGROUND_SPEED = 1;
int		FRONT_BACKGROUND_SPEED = 2;
int		LVL_SPEED = 1;
int		PLAYER_VSPEED = -16;
int		TOT_OBJ = 0;
int		NB_IMG = 4;
int		OBJ_DESTROYED = 0;
int		LIFE_PLAYER = 3;
int		LIFE_PLAYER_2 = 0;
int		DEATHMATCH = 1;
int		RESOLUTION = 4;
int		SAVED_BACKGROUND_SPEED = BACKGROUND_SPEED;
int		SAVED_LIFE_PLAYER = LIFE_PLAYER;
int		SAVED_LIFE_PLAYER_2 = LIFE_PLAYER_2;
int		SAVED_DEATHMATCH = DEATHMATCH;

void	set_global_var_by_default()
{
	PLAYER_SPEED = 2;
	BACKGROUND_SPEED = 1;
	FRONT_BACKGROUND_SPEED = 2;
	LVL_SPEED = 1;
	PLAYER_VSPEED = -16;
	TOT_OBJ = 0;
	OBJ_DESTROYED = 0;
}

void	set_game_var()
{
	set_global_var_by_default();
	BACKGROUND_SPEED = SAVED_BACKGROUND_SPEED;
	LIFE_PLAYER = SAVED_LIFE_PLAYER;
	LIFE_PLAYER_2 = SAVED_LIFE_PLAYER_2;
	DEATHMATCH = SAVED_DEATHMATCH;
}

void	set_option_var()
{
	SAVED_BACKGROUND_SPEED = BACKGROUND_SPEED;
	SAVED_LIFE_PLAYER = LIFE_PLAYER;
	SAVED_LIFE_PLAYER_2 = LIFE_PLAYER_2;
	SAVED_DEATHMATCH = DEATHMATCH;
}

int		no_key(const Uint8 *state)
{
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D] || state[SDL_SCANCODE_SPACE])
		return (1);
	return (0);
}

void	create_score_textures(t_sdl *sdl, vector <SDL_Texture*> *score_texture)
{
	SDL_Texture	*tmp = NULL;

	for (int i = 0; i < 10; i++)
	{
		tmp = SDL_load_texture(sdl, sdl->renderer, tmp, "img/score" + to_string(i) + ".png");
		score_texture->push_back(tmp);
	}
}

void	clear_all_texture(vector <t_obstacle> *platform, vector <SDL_Texture*> *score_texture)
{
	SDL_Texture	*tmp;
	t_obstacle	tmp_obs;

	for (unsigned long i = 0; i < score_texture->size(); i++)
	{
		tmp = score_texture->at(i);
		SDL_DestroyTexture(tmp);
	}
	for (unsigned long i = 0; i < platform->size(); i++)
	{
		tmp_obs = platform->at(i);
		SDL_DestroyTexture(tmp_obs.texture);
	}
}

void	game_paused()
{
	SDL_Event	event;

	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RETURN)
				break ;
		}
	}
}

void	runner_loop(t_sdl *sdl, const Uint8 *state, Player *player, Player *player2)
{
	Uint32		last_frame(0), current_frame(0);
	vector		<t_obstacle> platform;
	vector		<SDL_Texture*> score_texture;
	int			lvl_cap_speed(100);
	SDL_Event	event;

	player->set_life(LIFE_PLAYER);
	player2->set_life(LIFE_PLAYER);
	player->reset_dst();
	player2->reset_dst();
	cout << "joueur 1 = " << ((player->is_alive() == true) ? "VIVANT" : "MORT") << " // joueur 2 = " << ((player2->is_alive() == true) ? "VIVANT" : "MORT") << endl;
	create_score_textures(sdl, &score_texture);
	Platform obj_list[NB_IMG];
	obj_list[0].create_platform(sdl, "img/ground0.png");
	obj_list[1].create_platform(sdl, "img/ground1.png");
	obj_list[2].create_platform(sdl, "img/ground2.png");
	obj_list[3].create_platform(sdl, "img/ground3.png");
	Background background(sdl, "img/background.png");
	Background front_background(sdl, "img/forest.png");
	create_lvl(sdl, &platform, obj_list);
	while (1)
	{
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_p)
			{
				if (BACKGROUND_SPEED < 10)
				{
					FRONT_BACKGROUND_SPEED += 1;
					BACKGROUND_SPEED += 1;
				}
			}
			if (event.key.keysym.sym == SDLK_o)
			{
				FRONT_BACKGROUND_SPEED = 0;
				BACKGROUND_SPEED = 0;
			}
			if (event.key.keysym.sym == SDLK_l)
				player->reborn(&platform, obj_list);
			if (event.key.keysym.sym == SDLK_i)
			{
				FRONT_BACKGROUND_SPEED = -1;
				BACKGROUND_SPEED = -1;
			}
			if ((player->is_alive() == true || player2->is_alive() == true) && event.key.keysym.sym == SDLK_RETURN)
				game_paused();
		}
		if (state[SDL_SCANCODE_A])
		{
			player->left();
			player->horizontal_move(-1, &platform, obj_list);
		}
		if (state[SDL_SCANCODE_LEFT])
		{
			player2->left();
			player2->horizontal_move(-1, &platform, obj_list);
		}
		if (state[SDL_SCANCODE_D])
		{
			player->right();
			player->horizontal_move(1, &platform, obj_list);
		}
		if (state[SDL_SCANCODE_RIGHT])
		{
			player2->right();
			player2->horizontal_move(1, &platform, obj_list);
		}
		if (state[SDL_SCANCODE_SPACE])
			player->jump(1);
		else
			player->jump(0);
		if (state[SDL_SCANCODE_KP_0])
			player2->jump(1);
		else
			player2->jump(0);
		if (state[SDL_SCANCODE_ESCAPE])
			break ;
		if ((DEATHMATCH == 1 && (player->is_alive() == false && player2->is_alive() == false)) || (DEATHMATCH == 0 && (player->is_alive() == false || player2->is_alive() == false)))
		{
			print_score_menu(sdl);
			while (1)
			{
				if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_RETURN)
						break ;
				}
			}
			break ;
		}
		if (OBJ_DESTROYED > (lvl_cap_speed * BACKGROUND_SPEED) / 2)
		{
			if (BACKGROUND_SPEED > 0)
			{
				FRONT_BACKGROUND_SPEED += 1;
				BACKGROUND_SPEED += 1;
				lvl_cap_speed += 100;
			}
		}
		if (!state[SDL_SCANCODE_D])
			player->reset_last_boost();
		if ((!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_SPACE]) || (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D]))
			player->idle();
		if ((!state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_KP_0]) || (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT]))
			player2->idle();
		player->set_score();
		player2->set_score();
		current_frame = SDL_GetTicks();
		if (last_frame + 16 >= current_frame)
			SDL_Delay(last_frame + 16 - current_frame);
		last_frame = current_frame;
		generation_only_ground(obj_list, &platform);
		print_runner(sdl, &background, &front_background, player, player2, &platform, &score_texture, obj_list);
	}
	clear_all_texture(&platform, &score_texture);
}

void	menu_option_function(t_sdl *sdl, SDL_Texture *menu_option, SDL_Texture *menu_check, SDL_Texture *img_arrow)
{
	SDL_Event	event;
	int			last_resolution;
	int			first_menu = 1;

	last_resolution = RESOLUTION;
	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_DOWN)
				first_menu += first_menu == 6 ? 0 : 1;
			if (event.key.keysym.sym == SDLK_UP)
				first_menu -= first_menu == 1 ? 0 : 1;
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				if (first_menu == 6)
					break ;
				else
				{
					while (1)
					{
						if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
						{
							if (event.key.keysym.sym == SDLK_RETURN)
							{
								if (RESOLUTION != last_resolution)
								{
									last_resolution = RESOLUTION;
									SDL_SetWindowFullscreen(sdl->window, 0);
									SDL_SetWindowPosition(sdl->window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
									if (RESOLUTION == 1)
									{
										sdl->disp = {0, 0, 1920, 1080};
										SDL_SetWindowSize(sdl->window, 1920, 1080);
									}
									if (RESOLUTION == 2)
									{
										sdl->disp = {0, 0, 1600, 900};
										SDL_SetWindowSize(sdl->window, 1600, 900);
									}
									if (RESOLUTION == 3)
									{
										sdl->disp = {0, 0, 720, 480};
										SDL_SetWindowSize(sdl->window, 720, 480);
									}
									if (RESOLUTION == 4)
									{
										SDL_get_desktop_display_mode(sdl, 0, &sdl->display);
										sdl->disp = {0, 0, sdl->display.w, sdl->display.h};
										SDL_SetWindowSize(sdl->window, sdl->disp.w, sdl->disp.h);
										SDL_SetWindowFullscreen(sdl->window, 1);
									}
								}
								break ;
							}
							if (event.key.keysym.sym == SDLK_LEFT)
							{
								if (first_menu == 1)
									LIFE_PLAYER_2 = 0;
								if (first_menu == 2)
									LIFE_PLAYER -= LIFE_PLAYER == 1 ? 0 : 1;
								if (first_menu == 3 && LIFE_PLAYER_2 > 0)
									DEATHMATCH -= DEATHMATCH == 0 ? 0 : 1;
								if (first_menu == 4)
									BACKGROUND_SPEED -= BACKGROUND_SPEED == 1 ? 0 : 1;
								if (first_menu == 5)
									RESOLUTION -= RESOLUTION == 1 ? 0 : 1;
							}
							if (event.key.keysym.sym == SDLK_RIGHT)
							{
								if (first_menu == 1)
									LIFE_PLAYER_2 = 1;
								if (first_menu == 2)
									LIFE_PLAYER += LIFE_PLAYER == 9 ? 0 : 1;
								if (first_menu == 3)
									DEATHMATCH += DEATHMATCH == 1 ? 0 : 1;
								if (first_menu == 4)
									BACKGROUND_SPEED += BACKGROUND_SPEED == 9 ? 0 : 1;
								if (first_menu == 5)
									RESOLUTION += RESOLUTION == 4 ? 0 : 1;
							}
						}
						SDL_Delay(72);
						print_menu_option(sdl, menu_option, menu_check, img_arrow, first_menu, 1);
					}
				}
			}
		}
		SDL_Delay(72);
		print_menu_option(sdl, menu_option, menu_check, img_arrow, first_menu, 0);
	}
	set_option_var();
}

int		main()
{
	t_sdl		sdl;
	const Uint8	*state;
	int			menu(0);
	SDL_Event	event;
	SDL_Texture	*img_menu(nullptr), *img_arrow(nullptr), *menu_check(nullptr), *menu_option(nullptr);

	SDL_init_struct(&sdl);
	SDL_init(&sdl);
	SDL_create_window(&sdl, 0, 0);
	SDL_SetWindowFullscreen(sdl.window, 1);
	SDL_init_renderer(&sdl);
	SDL_init_img();
	sdl.buffer = SDL_create_texture(&sdl, sdl.buffer, 720, 480);
	sdl.buffer_rect = {0, 0, 720, 480};
	img_menu = SDL_load_texture(&sdl, sdl.renderer, img_menu, "img/menu.png");
	img_arrow = SDL_load_texture(&sdl, sdl.renderer, img_arrow, "img/menu_arrow.png");
	menu_check = SDL_load_texture(&sdl, sdl.renderer, menu_check, "img/menu_check.png");
	menu_option = SDL_load_texture(&sdl, sdl.renderer, menu_option, "img/menu_options.png");
	Player	player(&sdl, "img/runner1.png", 1, "img/heart1.png");
	Player	player2(&sdl, "img/runner2.png", 2, "img/heart2.png");
	set_global_var_by_default();
	while (1)
	{
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				if (menu == 0)
				{
					set_game_var();
					runner_loop(&sdl, state, &player, &player2);
					set_game_var();
				}
				if (menu == 1)
					menu_option_function(&sdl, menu_option, menu_check, img_arrow);
				if (menu == 2)
					break ;
			}
			if (event.key.keysym.sym == SDLK_UP)
				menu -= menu == 0 ? 0 : 1;
			if (event.key.keysym.sym == SDLK_DOWN)
				menu += menu == 2 ? 0 : 1;
		}
		print_menu(&sdl, menu, img_menu, img_arrow, &player, &player2);
		SDL_Delay(72);
	}
	SDL_DestroyTexture(img_menu);
	SDL_DestroyTexture(img_arrow);
	SDL_clean_struct(&sdl);
	return (0);
}

