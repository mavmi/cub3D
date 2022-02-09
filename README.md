sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev


#ifdef __linux__
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
#endif


#ifdef __linux__
  mlx_mouse_hide();
#endif
