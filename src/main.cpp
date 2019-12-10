#include "../includes/runner.h"

using namespace std;

void	print_runner(t_sdl *sdl, Background *background, Player *player)
{
	SDL_render_clear(sdl, sdl->renderer);
//	SDL_render_target(sdl, sdl->renderer, sdl->buffer);
//	SDL_render_clear(sdl, sdl->renderer);
	
	background->fillbuffer(sdl);
	player->vertical_move();
	player->fill_buffer(sdl);
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

void	runner_loop(t_sdl *sdl, const Uint8 *state)
{
//	SDL_Event	event;
	Uint32		last_frame(0), current_frame(0);

	sdl->buffer = SDL_create_texture(sdl, sdl->buffer, 720, 480);
	sdl->buffer_rect = {0, 0, 720, 480};
	Background background(sdl, "img/background.png");
	Player player(sdl, "img/runner.png");
	while (1)
	{
		state = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();
//		if (SDL_PollEvent(&event) && event.type != SDL_KEYDOWN)
//			player.changestate("idle");
		if (state[SDL_SCANCODE_A])
		{
			player.left();
			player.horizontal_move(-1);
		}
		if (state[SDL_SCANCODE_D])
		{
			player.right();
			player.horizontal_move(1);
		}
		if (state[SDL_SCANCODE_SPACE])
			player.jump();
		if (state[SDL_SCANCODE_ESCAPE])
			break ;
		if (no_key(state) == 0)
			player.idle();
		current_frame = SDL_GetTicks();
		if (last_frame + 16 >= current_frame)
			SDL_Delay(last_frame + 16 - current_frame);
		last_frame = current_frame;
		print_runner(sdl, &background, &player);
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
