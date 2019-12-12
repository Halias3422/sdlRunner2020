#include "../includes/runner.h"

using namespace std;

int		TOT_OBJ = 0;

void	print_obstacle(t_sdl *sdl, list <t_obstacle> *platform)
{
	list <t_obstacle>::iterator i;

	for (i = platform->begin(); i != platform->end(); i++)
		SDL_render_copy(sdl, sdl->renderer, i->texture, NULL, &i->dst);
}

void	print_runner(t_sdl *sdl, Background *background, Player *player, list <t_obstacle> *platform)
{
	(void)platform;
	SDL_render_clear(sdl, sdl->renderer);
//	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
//	SDL_render_clear(sdl, sdl->renderer);
	
	background->fillbuffer(sdl);
//	player->check_collisions(platform);
	player->vertical_move(platform);
	player->horizontal_move(0, platform);
	player->fill_buffer(sdl);
	print_obstacle(sdl, platform);
	
//	SDL_render_target(sdl, sdl->renderer, NULL);
//	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, &sdl->disp);
	SDL_RenderPresent(sdl->renderer);
}

int		no_key(const Uint8 *state)
{
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_D] || state[SDL_SCANCODE_SPACE])
		return (1);
	return (0);
}

void	fill_obstacle(t_obstacle *new_obj, Platform obj_list[3], int type, int box_collide, int dst_x, int dst_y)
{
	new_obj->type = type;
	new_obj->nb_obstacle = TOT_OBJ++;
	new_obj->box_collide = box_collide;
	new_obj->texture = obj_list[new_obj->type].get_texture();
	new_obj->dst = obj_list[new_obj->type].get_dst();
	new_obj->dst.x = dst_x;
	new_obj->dst.y = dst_y;
}

void	create_lvl(t_sdl *sdl, list <t_obstacle> *platform, Platform obj_list[3])
{
	int			i = 0;
	t_obstacle	new_obj;

	(void)obj_list;
	(void)sdl;
	(void)platform;
	while (i < 8)
	{
		fill_obstacle(&new_obj, obj_list, 0, 1, 72 * i, 460);
		platform->push_back(new_obj);
		i++;
		if (i == 8)
		{
			fill_obstacle(&new_obj, obj_list, 1, 1, 72 * i + 72, 350);
			platform->push_back(new_obj);
		}
	}
	fill_obstacle(&new_obj, obj_list, 0, 1, 72 * 4, 395);
	platform->push_back(new_obj);
	fill_obstacle(&new_obj, obj_list, 0, 1, 72 * 2, 350);
	platform->push_back(new_obj);
	fill_obstacle(&new_obj, obj_list, 0, 1, 72 * 7, 440);
	platform->push_back(new_obj);

}

void	runner_loop(t_sdl *sdl, const Uint8 *state)
{
	Uint32		last_frame(0), current_frame(0);
	list		<t_obstacle> platform;

	Platform obj_list[3];
	obj_list[0].create_platform(sdl, "img/ground0.png");
	obj_list[1].create_platform(sdl, "img/ground1.png");
	obj_list[2].create_platform(sdl, "img/ground2.png");
	sdl->buffer = SDL_create_texture(sdl, sdl->buffer, 720, 480);
	sdl->buffer_rect = {0, 0, 720, 480};
	Background background(sdl, "img/background.png");
	Player player(sdl, "img/runnerdebug.png");
	create_lvl(sdl, &platform, obj_list);
	while (1)
	{
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (state[SDL_SCANCODE_A])
		{
			player.left();
			player.horizontal_move(-1, &platform);
		}
		if (state[SDL_SCANCODE_D])
		{
			player.right();
			player.horizontal_move(1, &platform);
		}
		if (state[SDL_SCANCODE_SPACE])
			player.jump(1);
		else
			player.jump(0);
		if (state[SDL_SCANCODE_ESCAPE] || player.is_alive() == false)
			break ;
		if (no_key(state) == 0 || (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_D]))
			player.idle();
		current_frame = SDL_GetTicks();
		if (last_frame + 16 >= current_frame)
			SDL_Delay(last_frame + 16 - current_frame);
		last_frame = current_frame;
		print_runner(sdl, &background, &player, &platform);
	}
}

void	print_menu(t_sdl *sdl, int menu, SDL_Texture *img_menu, SDL_Texture *img_arrow)
{
	SDL_Rect	dst;
	SDL_Rect	menu_dst;

	SDL_render_clear(sdl, sdl->renderer);
//	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
//	SDL_render_clear(sdl, sdl->renderer);

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
//	SDL_render_target(sdl, sdl->renderer, NULL);
//	SDL_render_copy(sdl, sdl->renderer, sdl->buffer, NULL, &sdl->disp);
	SDL_RenderPresent(sdl->renderer);
}

int		main()
{
	t_sdl		sdl;
	const Uint8	*state;
	int			menu(0);
	SDL_Texture	*img_menu(nullptr), *img_arrow(nullptr);

	SDL_init_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	SDL_init_img();
	img_menu = SDL_load_texture(&sdl, sdl.renderer, img_menu, "img/menu.png");
	img_arrow = SDL_load_texture(&sdl, sdl.renderer, img_arrow, "img/menu_arrow.png");
	while (1)
	{
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
		if (state[SDL_SCANCODE_RETURN])
		{
			if (menu == 0)
				runner_loop(&sdl, state);
			if (menu == 1)
				runner_loop(&sdl, state);
			if (menu == 2)
				break ;
		}
		if (state[SDL_SCANCODE_UP])
		{
			menu -= menu == 0 ? 0 : 1;
			SDL_Delay(100);
		}
		if (state[SDL_SCANCODE_DOWN])
		{
			menu += menu == 2 ? 0 : 1;
			SDL_Delay(100);
		}
		print_menu(&sdl, menu, img_menu, img_arrow);
	}
	SDL_DestroyTexture(img_menu);
	SDL_DestroyTexture(img_arrow);
	SDL_clean_struct(&sdl);
	return (0);
}
