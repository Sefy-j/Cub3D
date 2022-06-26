/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:34:43 by pvillena          #+#    #+#             */
/*   Updated: 2022/06/17 18:39:11 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <errno.h>
# include <sys/time.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# define SYMBOLS "RDO0F1 NSWE"
# define COLLIS "1FRD"
# define LOOK "NSWE"
# define SQMIN 16
# define MINIMAP 256
# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159
# define DOOR "./texs/wood.xpm"
# define STATSPR "./texs/pillar.xpm"
# define ANIMSPR1 "./texs/frank01.xpm"
# define ANIMSPR2 "./texs/frank02.xpm"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_wall {
	int		wallheight;
	int		startdraw;
	int		enddraw;
	double	exacthit;
	double	stepy;
	int		y;
	int		xwall;
	int		ywall;
}			t_wall;

typedef struct s_paint {
	int	sp_width;
	int	sp_height;
	int	sp_posx;
	int	start_drawy;
	int	end_drawy;
	int	start_drawx;
	int	end_drawx;
	int	stripe;
	int	tex_x;
	int	tex_y;
	int	color;
	int	y;
}		t_paint;

typedef struct s_sprite {
	double			x;
	double			y;
	double			rel_x;
	double			rel_y;
	double			sp_x;
	double			sp_z;
	double			distance;
	char			*path;
	char			*path2;
	t_data			tex;
	t_data			tex2;
	int				h;
	int				w;
	int				h2;
	int				w2;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_map {
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	int		*f_color;
	int		*c_color;
	char	**map;
}			t_map;

typedef struct s_texs {
	t_data	wn;
	t_data	ws;
	t_data	we;
	t_data	ww;
	t_data	door;
	int		width;
	int		height;
}	t_texs;

typedef struct s_ray {
	t_data		img;
	t_map		*map;
	t_texs		texs;
	t_sprite	*sprites;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	double		play_x;
	double		play_y;
	double		vel;
	double		velgiro;
	double		velstraf;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		delta_x;
	double		delta_y;
	double		distperpwall;
	double		*distance;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			mouse;
}			t_ray;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	SPW = 0,
	SPH = 1
};

enum {
	ERRGEN = 1,
	ERRMAP = 2,
	ERRTEX = 3
};

enum {
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

t_map				*all_the_parsing_is_here_part_two(char **argv);
t_map				*get_map_textures_and_color(int fd);
char				*get_texture(int fd, char *p);
int					*get_color(int fd, char *p);
int					count_strs(char **arr);
char				**get_map(int fd);
char				**ft_free(char **result);
char				**append_str(char **origin, char *append);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					my_pixel_get(t_data *data, int x, int y);
int					key_hooks(int keycode, t_ray *ray);
void				cub3d(t_map *map);
t_ray				*load_textures(t_ray *ray);
int					create_trgb(int t, int r, int g, int b);
t_ray				print_wall(t_ray ray, int x);
int					key_release(int keycode, t_ray *ray);
void				rotate_vector(double *x, double *y, double angle);
int					ft_destroywindow(t_ray *ray);
int					stop_automove(t_ray *ray);
void				create_minimap(t_ray *ray);
void				get_mouse_pos(t_ray *ray);
int					check_extension(char *str);
void				calc_sprites(t_ray *ray);
t_sprite			*new_sprite(int x, int y, char mode);
void				add_sprite_back(t_sprite **sprites, t_sprite *new);
void				print_sprites(t_sprite *sprite);
t_sprite			*init_sprites(char **map);
void				load_sprite_textures(t_ray *ray);
void				load_north_tex(t_ray *ray);
void				load_east_tex(t_ray *ray);
void				load_south_tex(t_ray *ray);
void				load_west_tex(t_ray *ray);
char				*skip_empty_lines(int fd);
int					ft_destroywindow(t_ray *ray);
void				create_minimap(t_ray *ray);
int					check_minmap(t_ray *ray, int x, int y);
void				paint_hero(t_ray *ray);
void				set_player(t_ray *ray, int i, int j);
t_ray				single_ray(t_ray ray, char **map, int xsweep);
unsigned long int	c_time(unsigned long int time_start);
t_ray				*open_close_doors(t_ray *ray);
void				ft_exit(int status);

#endif
