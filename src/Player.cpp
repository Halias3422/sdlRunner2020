#include "../includes/runner.h"

using namespace std;

int IDLE_1 = 0;
int IDLE_2 = 32;
int RUN_RIGHT_1 = 64;
int RUN_RIGHT_2 = 96;
int RUN_RIGHT_3 = 128;
int RUN_RIGHT_4 = 160;
int RUN_RIGHT_5 = 192;
int RUN_RIGHT_6 = 224;
int RUN_LEFT_1 = 256;
int RUN_LEFT_2 = 288;
int RUN_LEFT_3 = 320;
int RUN_LEFT_4 = 352;
int RUN_LEFT_5 = 384;
int RUN_LEFT_6 = 416;
int JUMP_RIGHT_1 = 448;
int JUMP_RIGHT_2 = 480;
int JUMP_RIGHT_3 = 512;
int JUMP_RIGHT_4 = 544;
int JUMP_RIGHT_5 = 576;
int JUMP_LEFT_1 = 608;
int JUMP_LEFT_2 = 640;
int JUMP_LEFT_3 = 672;
int JUMP_LEFT_4 = 704;
int JUMP_LEFT_5 = 736;

Player::Player(t_sdl *sdl, string path, int nb, string heart_path)
{
	texture = SDL_load_texture(sdl, sdl->renderer, texture, path);
	src = {0, 0, 32, 64};
	if (nb == 1)
		dst = {200, 0, 32, 64};
	else if (nb == 2)
		dst = {250, 0, 32, 64};
	heart = SDL_load_texture(sdl, sdl->renderer, heart, heart_path);
	player_nb = nb;
}

void	Player::reset_dst()
{
	if (player_nb == 1)
		dst = {72 + 36, 100 - 64, 32, 64};
	else if (player_nb == 2)
		dst = {72 + 36, 100 - 64, 32, 64};
}

void	Player::jump(int pressed)
{
	(void)extra_horizontal_force;
	(void)extra_vertical_force;
	if (pressed == 1 && grounded == true)
		started_jump = SDL_GetTicks();
	if (pressed == 1 && (grounded == true || jump_state == 1))
	{
		if (SDL_GetTicks() >= started_jump + 100)
			jump_state = 0;
		else
		{
			extra_horizontal_force = 0;
			PLAYER_SPEED = 2;
			last_boost = 0;
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
	//	return (true);
	if (life <= 0)
	{
		//		cout << "position joueur mort -- x = " << dst.x << " et y = " << dst.y << endl;
		return (false);
	}
	return (true);
}

void	Player::reborn(vector <t_obstacle> *platform, Platform obj_list[NB_IMG])
{
	t_obstacle	new_obj;

	reset_dst();
	extra_horizontal_force = -BACKGROUND_SPEED;
	fill_obstacle(&new_obj, obj_list, 0, 1, 72, 100, -BACKGROUND_SPEED, 0, 1);
	platform->push_back(new_obj);
}

void	Player::reset_last_boost()
{
	PLAYER_SPEED = 2;
	last_boost = 0;
}

void	Player::horizontal_move(int way, vector <t_obstacle> *platform, Platform obj_list[NB_IMG])
{
	vector		<t_obstacle>::iterator i;
	SDL_Rect	plat_dst;

	//	cout << "player speed = " << PLAYER_SPEED << endl;
	if (way != 0 && way != -1 && grounded == true && last_boost == 0)
		last_boost = SDL_GetTicks();
	if (way != 0 && way != -1  && last_boost + 2000 < SDL_GetTicks())
	{
		//		PLAYER_SPEED += PLAYER_SPEED < 3 ? 1 : 0;
		last_boost = SDL_GetTicks();
	}
	else if (way == -1)
	{
		PLAYER_SPEED = 2;
	}
	dst.x += PLAYER_SPEED * way;
	if (dst.x > 720 - 32)
		dst.x = 720 - 32;
	if (dst.x < 0 - dst.w)
	{
		life -= 1;
		if (life > 0)
			reborn(platform, obj_list);
	}
	if (way == 0 && grounded == true)
		dst.x -= BACKGROUND_SPEED + extra_horizontal_force;
	for (i = platform->begin(); i != platform->end(); i++)
	{
		plat_dst = i->dst;
		if (i->box_collide == 1 && ((dst.y < plat_dst.y && dst.y + dst.h > plat_dst.y) || (dst.y < plat_dst.y + plat_dst.h && dst.y > plat_dst.y) ||
					(dst.y + dst.h > plat_dst.y && dst.y + dst.h < plat_dst.y + plat_dst.h))) //if control pb vertical
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

void	Player::vertical_move(vector <t_obstacle> *platform, Platform obj_list[NB_IMG])
{
	vector	<t_obstacle>::iterator i;
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
		if (direction == 1)
		{
			if (vspeed == -20)
				src.x = JUMP_RIGHT_1;
			else if (vspeed <= -2)
				src.x = JUMP_RIGHT_2;
			else if (vspeed > -2 && vspeed <= 2)
				src.x = JUMP_RIGHT_3;
			else if (vspeed > 2 && vspeed <= 18)
				src.x = JUMP_RIGHT_4;
			else if (vspeed > 18 && vspeed <= 20)
				src.x = JUMP_RIGHT_5;
		}
		else
		{
			if (vspeed == -20)
				src.x = JUMP_LEFT_1;
			else if (vspeed <= -2)
				src.x = JUMP_LEFT_2;
			else if (vspeed > -2 && vspeed <= 2)
				src.x = JUMP_LEFT_3;
			else if (vspeed > 2 && vspeed <= 18)
				src.x = JUMP_LEFT_4;
			else if (vspeed > 18 && vspeed <= 20)
				src.x = JUMP_LEFT_5;
		}
	}
	for (i = platform->begin(); i != platform->end(); i++)
	{
		plat_dst = i->dst;
		if (i->box_collide == 1 && ((dst.x < plat_dst.x && dst.x + dst.w > plat_dst.x) || (dst.x < plat_dst.x + plat_dst.w && dst.x > plat_dst.x) ||
					(dst.x + dst.w > plat_dst.x && dst.x + dst.w < plat_dst.x + plat_dst.w))) //if control pb vertical
		{
			if (dst.y >= plat_dst.y && dst.y <= plat_dst.y + plat_dst.h && ++check) //if control gauche joueur
			{
				dst.y = plat_dst.y + plat_dst.h;
			}
			if (dst.y + dst.h >= plat_dst.y && dst.y + dst.h <= plat_dst.y + plat_dst.h && ++check) //if control droite joueur
			{
				dst.y = plat_dst.y - dst.h;
				if (i->type == 2 || i->type == 3)
				{
					life -= 1;
					if (life > 0)
						reborn(platform, obj_list);
				}
				grounded = true;
				started_jump = 0;
				vspeed = 0;
			}
		}
	}
	if (check == 0)
	{
		extra_horizontal_force = 0;
		last_boost = 0;
		grounded = false;
	}
	if (dst.y > 480)
	{
		life -= 1;
		if (life > 0)
			reborn(platform, obj_list);
	}
}

void	Player::left()
{
	current_frame = SDL_GetTicks();
	direction = -1;
	if (grounded == true)
	{
		if (last_frame + 16 * 4 < current_frame)
		{
			if (src.x == RUN_LEFT_1)
				src.x = RUN_LEFT_2;
			else if (src.x == RUN_LEFT_2)
				src.x = RUN_LEFT_3;
			else if (src.x == RUN_LEFT_3)
				src.x = RUN_LEFT_4;
			else if (src.x == RUN_LEFT_4)
				src.x = RUN_LEFT_5;
			else if (src.x == RUN_LEFT_5)
				src.x = RUN_LEFT_6;
			else if (src.x == RUN_LEFT_6)
				src.x = RUN_LEFT_1;
			else
				src.x = RUN_LEFT_1;
			last_frame = current_frame;
		}
	}
}

void	Player::right()
{
	current_frame = SDL_GetTicks();
	direction = 1;
	if (grounded == true)
	{
		if (last_frame + 16 * 4 < current_frame)
		{
			if (src.x == RUN_RIGHT_1)
				src.x = RUN_RIGHT_2;
			else if (src.x == RUN_RIGHT_2)
				src.x = RUN_RIGHT_3;
			else if (src.x == RUN_RIGHT_3)
				src.x = RUN_RIGHT_4;
			else if (src.x == RUN_RIGHT_4)
				src.x = RUN_RIGHT_5;
			else if (src.x == RUN_RIGHT_5)
				src.x = RUN_RIGHT_6;
			else if (src.x == RUN_RIGHT_6)
				src.x = RUN_RIGHT_1;
			else
				src.x = RUN_RIGHT_1;
			last_frame = current_frame;
		}
	}
}

void	Player::print_score(t_sdl *sdl, vector <SDL_Texture*> *score_texture)
{
	SDL_Rect	dst = {0, 10, 32, 64};
	SDL_Texture	*tmp;
	int			div;
	int			res;
	int			diff_dst;
	string		score_tot;
	int			length;

	score_tot = to_string(score);
	length = score_tot.length() - 1;
	if (player_nb == 2)
		diff_dst = 720 - 52;
	else
		diff_dst = 52 - 32 + length * 32;
	div = score;
	while (div > 0)
	{
		res = div % 10;
		div = div / 10;
		dst.x = diff_dst;
		tmp = score_texture->at(res);
		SDL_render_copy(sdl, sdl->renderer, tmp, NULL, &dst);
		diff_dst -= 32;
	}
}

void	Player::print_heart(t_sdl *sdl)
{
	if (player_nb == 1)
		heart_dst.x = 20;
	else if (player_nb == 2)
		heart_dst.x = 700 - 32;
	for (int i = 0; i < life; i++)
	{
		SDL_render_copy(sdl, sdl->renderer, heart, NULL, &heart_dst);
		if (player_nb == 1)
			heart_dst.x += 36;
		else if (player_nb == 2)
			heart_dst.x -= 36;
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

void	Player::set_score()
{
	if (life >= 1)
		score = OBJ_DESTROYED;
}

void	Player::menu_animation(t_sdl *sdl)
{
	dst.y = 125;
	dst.w = 32 * 5;
	dst.h = 64 * 5;
	if (player_nb == 1)
	{
		if (menu_right == RUN_RIGHT_1)
			src.x = RUN_RIGHT_2;
		else if (menu_right == RUN_RIGHT_2)
			src.x = RUN_RIGHT_3;
		else if (menu_right == RUN_RIGHT_3)
			src.x = RUN_RIGHT_4;
		else if (menu_right == RUN_RIGHT_4)
			src.x = RUN_RIGHT_5;
		else if (menu_right == RUN_RIGHT_5)
			src.x = RUN_RIGHT_6;
		else if (menu_right == RUN_RIGHT_6)
			src.x = RUN_RIGHT_1;
		else
			src.x = RUN_RIGHT_1;
		dst.x = 50;
		fill_buffer(sdl);
		menu_right = src.x;
	}
	else
	{
		if (menu_left == RUN_LEFT_1)
			src.x = RUN_LEFT_2;
		else if (menu_left == RUN_LEFT_2)
			src.x = RUN_LEFT_3;
		else if (menu_left == RUN_LEFT_3)
			src.x = RUN_LEFT_4;
		else if (menu_left == RUN_LEFT_4)
			src.x = RUN_LEFT_5;
		else if (menu_left == RUN_LEFT_5)
			src.x = RUN_LEFT_6;
		else if (menu_left == RUN_LEFT_6)
			src.x = RUN_LEFT_1;
		else
			src.x = RUN_LEFT_1;
		dst.x = 490;
		fill_buffer(sdl);
		menu_left = src.x;
	}
	src = {0, 0, 32, 64};
	dst = {200, 0, 32, 64};
}

void	Player::set_life(int lifeuh)
{
	if (player_nb == 2 && LIFE_PLAYER_2 == 0)
		life = 0;
	else
		life = lifeuh;
}

void	Player::fill_buffer(t_sdl *sdl)
{
	SDL_render_copy(sdl, sdl->renderer, texture, &src, &dst);
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}
