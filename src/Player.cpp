#include "../includes/runner.h"

using namespace std;

//idle 1 - 0
//idle 2 - 32
//run 1 - 128
//run 2 - 96
//run 3 - 64
//jump 1 - 160
//jump 2 - 192
//run 4 - 224
//run 5 - 256
//run 6 - 288
//jump 3 - 320
//jump 4 - 352

//128 = 316
//96 = 284
//64 = 252

Player::Player(t_sdl *sdl, string path)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
	src = {0, 0, 32, 64};
	dst = {200, 0, 32, 64};
}

void	Player::jump(int pressed)
{
	if (pressed == 1 && grounded == true)
		started_jump = SDL_GetTicks();
	if (pressed == 1 && (grounded == true || jump_state == 1))
	{
		if (SDL_GetTicks() >= started_jump + 100)
			jump_state = 0;
		else
		{
			grounded = false;
			vspeed = PLAYER_VSPEED;
			jump_state = 1;
		}
	}
	if (pressed == 0)
		jump_state = 0;
}

bool	Player::is_alive()
{
	if (life == 0)
	{
		cout << "position joueur mort -- x = " << dst.x << " et y = " << dst.y << endl;
		return (false);
	}
	return (true);
}
/*
void	Player::check_collisions(list <t_obstacle> *platform)
{
	list	<t_obstacle>::iterator i;
	SDL_Rect	plat_dst;
	int			check = 0;

	for (i = platform->begin(); i != platform->end(); i++)
	{
		plat_dst = i->dst;
		if (dst.y + dst.h > plat_dst.y && dst.y < plat_dst.y && dst.x +
				dst.w > plat_dst.x && dst.x + dst.w <= plat_dst.x + plat_dst.w && ++check)
		{
			grounded = true;
			jump_state = 0;
			dst.y = plat_dst.y - dst.h - 1;
		}
		if (dst.y > plat_dst.y && dst.y < plat_dst.y + plat_dst.h && dst.x +
				dst.w > plat_dst.x && dst.x + dst.w <= plat_dst.x + plat_dst.w && ++check)
		{
			dst.y = plat_dst.y + plat_dst.h;
		}
		if (dst.x + dst.w > plat_dst.x && dst.x < plat_dst.x && dst.y +
				dst.h > plat_dst.y && dst.y + dst.h <= plat_dst.y + plat_dst.h && ++check)
			dst.x = plat_dst.x - dst.w;
		if (dst.x > plat_dst.x && dst.x < plat_dst.x + plat_dst.w && dst.y +
				dst.h > plat_dst.y && dst.y + dst.h <= plat_dst.y + plat_dst.h && ++check)
			dst.x = plat_dst.x + plat_dst.w;
		if (check == 0)
			grounded = false;
	}
}
*/
void	Player::horizontal_move(int way, list <t_obstacle> *platform)
{
	list	<t_obstacle>::iterator i;
	SDL_Rect	plat_dst;

		dst.x += PLAYER_SPEED * way;
	if (dst.x > 720 - 32)
		dst.x = 720 - 32;
	if (dst.x < 0 - dst.w)
		life -= 1;
	if (life == 0)
		cout << "dead\n";
	if (way == 0 && grounded == true)
		dst.x -= BACKGROUND_SPEED;
	for (i = platform->begin(); i != platform->end(); i++)
	{
		plat_dst = i->dst;
		if ((dst.y < plat_dst.y + plat_dst.h && dst.y > plat_dst.y) ||
			(dst.y + dst.h > plat_dst.y && dst.y + dst.h < plat_dst.y + plat_dst.h)) //if control pb vertical
		{
			if (dst.x > plat_dst.x && dst.x < plat_dst.x + plat_dst.w) //if control gauche joueur
			{
				dst.x = plat_dst.x + plat_dst.w;
			}
			if (dst.x + dst.w > plat_dst.x && dst.x + dst.w < plat_dst.x + plat_dst.w) //if control droite joueur
			{
				dst.x = plat_dst.x - dst.w;
			}
		}
	}
}

void	Player::vertical_move(list <t_obstacle> *platform)
{
	list	<t_obstacle>::iterator i;
	SDL_Rect	plat_dst;
	int			check(0);
	
//	if (grounded == true)
//		return ;
	if (grounded == false)
	{
	dst.y += vspeed * 1.5 / 3;
	vspeed += 1;
	if (vspeed == 11)
		vspeed = 10;
	}
	for (i = platform->begin(); i != platform->end(); i++)
	{
		plat_dst = i->dst;
		if ((dst.x < plat_dst.x + plat_dst.w && dst.x > plat_dst.x) ||
			(dst.x + dst.w > plat_dst.x && dst.x + dst.w < plat_dst.x + plat_dst.w)) //if control pb vertical
		{
			if (dst.y >= plat_dst.y && dst.y <= plat_dst.y + plat_dst.h && ++check) //if control gauche joueur
			{
				dst.y = plat_dst.y + plat_dst.h;
			}
			if (dst.y + dst.h >= plat_dst.y && dst.y + dst.h <= plat_dst.y + plat_dst.h && ++check) //if control droite joueur
			{
				dst.y = plat_dst.y - dst.h;
				grounded = true;
				started_jump = 0;
				vspeed = 0;
			}
		}
	}
	if (check == 0)
		grounded = false;
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
				if (src.x == 288)
					src.x = 256;
				else if (src.x == 256)
					src.x = 224;
				else if (src.x == 224)
				{
					src.x = 256;
					forward = 1;
				}
				else
					src.x = 288;
			}
			else
			{
				if (src.x == 224)
					src.x = 256;
				else if (src.x == 288)
					src.x = 256;
				else if (src.x == 256)
				{
					src.x = 288;
					forward = 0;
				}
				else
					src.x = 288;
			}
			last_frame = current_frame;
		}
	}
	else if (grounded == false)
	{
		if (vspeed <= 0)
			src.x = 320;
		else
			src.x = 352;
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
				if (src.x == 128)
					src.x = 96;
				else if (src.x == 96)
					src.x = 64;
				else if (src.x == 64)
				{
					src.x = 96;
					forward = 1;
				}
				else
					src.x = 128;
			}
			else
			{
				if (src.x == 64)
					src.x = 96;
				else if (src.x == 128)
					src.x = 96;
				else if (src.x == 96)
				{
					src.x = 128;
					forward = 0;
				}
				else
					src.x = 128;
			}
			last_frame = current_frame;
		}
	}
	else if (grounded == false)
	{
		if (vspeed <= 0)
			src.x = 160;
		else
			src.x = 192;
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
