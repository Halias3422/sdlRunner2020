#include "../includes/runner.h"

using namespace std;

//idle 1 - 0
//idle 2 - 32
//run 1 - 128
//run 2 - 96
//run 3 - 64
//jump 1 - 188
//jump 2 - 220

Player::Player(t_sdl *sdl, string path)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
	src = {0, 0, 32, 64};
	dst = {0, 0, 32, 64};
}

void	Player::jump()
{
	if (grounded == true)
	{
		grounded = false;
		vspeed = -30;
	}
}

void	Player::horizontal_move(int way)
{
		dst.x += 10 * way;
	if (dst.x > 720 - 32)
		dst.x = 720 - 32;
	if (dst.x < 0)
		dst.x = 0;
}

void	Player::vertical_move()
{
	if (grounded == false)
	{
	dst.y += vspeed * 1.5 / 3;
	vspeed += 1;
	if (vspeed == 31)
		vspeed = 30;
	}
	if (dst.y >= 416)
	{
		dst.y = 416;
		grounded = true;
	}
}

void	Player::left()
{
	current_frame = SDL_GetTicks();
	if (grounded == true)
	{
		if (last_frame + 16 * 6 < current_frame)
		{
			if (forward == 0)
			{
				if (src.x == 0 || src.x == 32)
					src.x = 128;
				else if (src.x == 128)
					src.x = 96;
				else if (src.x == 96)
					src.x = 64;
				else if (src.x == 64)
				{
					src.x = 96;
					forward = 1;
				}
			}
			else
			{
				if (src.x == 0 || src.x == 32)
					src.x = 128;
				else if (src.x == 64)
					src.x = 96;
				else if (src.x == 128)
					src.x = 96;
				else if (src.x == 96)
				{
					src.x = 128;
					forward = 0;
				}
			}
			last_frame = current_frame;
		}
	}
}

void	Player::right()
{
	current_frame = SDL_GetTicks();
	if (grounded == true)
	{
		if (last_frame + 16 * 6 < current_frame)
		{
			if (forward == 0)
			{
				if (src.x == 0 || src.x == 32)
					src.x = 128;
				else if (src.x == 128)
					src.x = 96;
				else if (src.x == 96)
					src.x = 64;
				else if (src.x == 64)
				{
					src.x = 96;
					forward = 1;
				}
			}
			else
			{
				if (src.x == 0 || src.x == 32)
					src.x = 128;
				else if (src.x == 64)
					src.x = 96;
				else if (src.x == 128)
					src.x = 96;
				else if (src.x == 96)
				{
					src.x = 128;
					forward = 0;
				}
			}
			last_frame = current_frame;
		}
	}
}
void	Player::idle()
{
	current_frame = SDL_GetTicks();
	if (grounded == true)
	{
		last_frame = 0;
		if (current_frame % 600 > 300)
			src.x = 32;
		else
			src.x = 0;
	}
}

void	Player::fill_buffer(t_sdl *sdl)
{
	SDL_render_copy(sdl, sdl->renderer, texture, &src, &dst);
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}
