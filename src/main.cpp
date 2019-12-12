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
	fill_obstacle(&new_obj, obj_list, 0, 1, 72 * 2, 400);
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
	Player player(sdl, "img/runner.png");
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

int		main()
{
	t_sdl		sdl;
	const Uint8	*state;

	SDL_init_struct(&sdl);
	SDL_init_window(&sdl);
	SDL_init_renderer(&sdl);
	SDL_init_img();
	runner_loop(&sdl, state);
	SDL_clean_struct(&sdl);
	return (0);
}
