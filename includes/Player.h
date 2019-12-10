#include "runner.h"

class Player
{
	public:
	
	Player(t_sdl *sdl, std::string path);

void	fill_buffer(t_sdl *sdl);
void	right();
void	jump();
void	left();
void	idle();
void	vertical_move();
void	horizontal_move(int way);

	~Player();

	private:

	SDL_Texture	*texture;
	SDL_Rect	src;
	SDL_Rect	dst;
	std::string	state = "idle";
	Uint32		last_frame = 0;
	Uint32		current_frame = 0;
	int			forward = 0;
	bool		grounded = true;
	int			vspeed = 0;
};
