#include "runner.h"
#include <list>

typedef struct s_obstacle	t_obstacle;
class	Platform;
extern int NB_IMG;

class Player
{
	public:
	
	Player(t_sdl *sdl, std::string path, int nb, std::string heart_path);

void	reset_dst();
void	fill_buffer(t_sdl *sdl);
void	right();
void	reborn(std::vector <t_obstacle> *platform, Platform obj_list[NB_IMG]);
void	jump(int pressed);
void	left();
void	idle();
void	set_score();
void	print_score(t_sdl *sdl, std::vector <SDL_Texture*> *score_texture);
void	print_heart(t_sdl *sdl);
void	menu_animation(t_sdl *sdl);
void	set_life(int lifeuh);
void	reset_last_boost();
void	vertical_move(std::vector <t_obstacle> *platform, Platform obj_list[NB_IMG]);
void	horizontal_move(int way, std::vector <t_obstacle> *platform, Platform obj_list[NB_IMG]);
bool	is_alive();

	~Player();

	private:

	SDL_Texture	*texture = NULL;
	SDL_Texture	*heart = NULL;
	SDL_Rect	heart_dst = {0, 85, 32, 32};
	SDL_Rect	src;
	SDL_Rect	dst;
	std::string	state = "idle";
	Uint32		last_frame = 0;
	Uint32		current_frame = 0;
	Uint32		last_boost = 0;
	bool		grounded = false;
	int			vspeed = 0;
	int			life = 1;
	int			jump_state = 0;
	Uint32		started_jump = 0;
	int			menu_left = 0;
	int			menu_right = 0;
	int			score = 0;
	int			player_nb = 1;
	int			extra_horizontal_force = 0;
	int			extra_vertical_force = 0;
	int			direction = 1;
};
