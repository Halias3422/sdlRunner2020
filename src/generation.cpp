#include "../includes/runner.h"

using namespace std;

void	fill_obstacle(t_obstacle *new_obj, Platform obj_list[NB_IMG], int type, int box_collide, int dst_x, int dst_y, int	extra_horizontal_force, int extra_vertical_force, int ignore)
{
	new_obj->type = type;
	new_obj->nb_obstacle = TOT_OBJ++;
	new_obj->box_collide = box_collide;
	new_obj->texture = obj_list[new_obj->type].get_texture();
	new_obj->dst = obj_list[new_obj->type].get_dst();
	new_obj->dst.x = dst_x;
	new_obj->dst.y = dst_y;
	new_obj->extra_horizontal_force = extra_horizontal_force;
	new_obj->extra_vertical_force = extra_vertical_force;
	new_obj->ignore = ignore;
}

void	create_lvl(t_sdl *sdl, vector <t_obstacle> *platform, Platform obj_list[NB_IMG])
{
	int			i = 0;
	t_obstacle	new_obj;

	(void)sdl;
	while (i < 11)
	{
		fill_obstacle(&new_obj, obj_list, 0, 1, 72 * i, 460, 0, 0, 0);
		platform->push_back(new_obj);
		i++;
	}
}

void	generation_only_ground(Platform obj_list[NB_IMG], vector <t_obstacle> *platform)
{
	vector <t_obstacle>::iterator begin = platform->begin();
	vector <t_obstacle>::iterator end = platform->end();
	t_obstacle	new_plat;
	int			box_collide;
	int			altitude;
	static int	check_invisible_items = 10;
	int			nb_obj_impossible = 0;
	int			min;
	int			type;

	srand(time(NULL));
	while (begin->ignore == 1)
	{
		platform->erase(begin);
		begin = platform->begin();
	}
	if (platform && begin->dst.x + begin->dst.w < 0)
	{
		OBJ_DESTROYED += 1;
		platform->erase(begin);
	}
	end--;

	while (platform && end->dst.x < 792)
	{
		box_collide = rand() % 100 < 100 - check_invisible_items ? 1 : 0;
		while (end->box_collide == 0 || end->type == 2 || end->type == 3 || end->ignore == 1)
		{
			end--;
			if (end->ignore == 0)
				nb_obj_impossible += 1;
		}
		if (box_collide == 1)
			check_invisible_items += 20;
		else
			check_invisible_items = 10;

		type = rand() % 2;
		if ((end->dst.y - 100 + nb_obj_impossible * 150) > 460)
		{
			box_collide = 1;
			nb_obj_impossible = 0;
		}
		else
		{
		if (type == 0 && rand() % 10 == 9)
			type = 3;
		else if (type == 1 && rand() % 10 == 9)
			type = 2;
		}
		min = (end->dst.y - 100 + nb_obj_impossible * 150);
		altitude = rand() % (460 - min + 1) + min;
		if (altitude < 65)
			altitude = 48 * 2;
		while (altitude % 20 != 0)
			altitude--;
		end = platform->end();
		end--;
		while (end->ignore == 1)
			end--;
		if (rand() % 100 < 2)
		{
			for (int i = 0; i != 16; i++)
			{
				fill_obstacle(&new_plat, obj_list, rand() % 2, 1, end->dst.x + end->dst.w, altitude, 0, 0, 0);
				platform->push_back(new_plat);
				end = platform->end();
				end--;
			}
		}
		else
		{
			fill_obstacle(&new_plat, obj_list, type, box_collide, end->dst.x + end->dst.w, altitude, 0, 0, 0);
			platform->push_back(new_plat);
			end = platform->end();
			end--;
			while (end->ignore == 1)
				end--;
		}
		nb_obj_impossible = 0;
	}
	for (begin = platform->begin(); begin != platform->end(); begin++)
		begin->dst.x -= BACKGROUND_SPEED + begin->extra_horizontal_force;
}
