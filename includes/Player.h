#include "runner.h"
#include <list>

typedef struct s_obstacle	t_obstacle;

class Player
{
	public:
	
	Player(t_sdl *sdl, std::string path);

void	fill_buffer(t_sdl *sdl);
void	right();
void	jump(int pressed);
void	left();
void	idle();
void	vertical_move(std::list <t_obstacle> *platform);
void	horizontal_move(int way, std::list <t_obstacle> *platform);
bool	is_alive();

	~Player();

	private:

	SDL_Texture	*texture = NULL;
	SDL_Rect	src;
	SDL_Rect	dst;
	std::string	state = "idle";
	Uint32		last_frame = 0;
	Uint32		current_frame = 0;
	int			forward = 0;
	bool		grounded = false;
	int			vspeed = 0;
	int			life = 1;
	int			jump_state = 0;
	Uint32		started_jump = 0;
};
