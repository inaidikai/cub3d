/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:31:51 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/10 02:04:33 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <ctype.h>
# include <limits.h>
# include <ctype.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// # define SKY_COLOR 0x87CEEB
// # define FLOOR_COLOR 0x8B4513

// # define ROTATE_SPEED 0.05

# define PI 3.14159265

typedef struct s_vars		t_vars;
typedef struct s_rays		t_rays;
typedef struct s_texture	t_texture;

typedef struct s_texture
{
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
    int txt;
    float pix_x;
    float pix_y;
} t_texture;
typedef struct s_player
{
	double				cam_height;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				speed;
	//t_line				line;
	double				camera_x;
	char				direction;

}						t_player;

typedef struct s_image
{
        t_texture *no;
    t_texture *so;
    t_texture *we;
    t_texture *ea;
    int f;
    int c;
    int init;
	void				*img;
	char				*address;
	int					bits_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

enum	e_key
{
	UP = 13,
	DOWN = 1,
	LEFT = 0,
	RIGHT = 2,
	ESC = 53,
	ARROW_L = 123,
	ARROW_R = 124,
	MAP = 46,
	LOOK_LEFT = 123,
	LOOK_RIGHT = 124,
};

enum	e_mouse
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
};

typedef struct s_vtable_rays{
	void	(*reset_values)(t_rays *self);
	void	(*wall_collision)(t_rays *self);
	void	(*get_distance)(t_rays *self);
	void	(*get_wall_height)(t_rays *self);
	void	(*select_sprite)(t_rays *self, float i, float i2);
	void	(*print)(t_rays *self);
	void	(*increment_angle)(t_rays *self);
	void	(*free)(t_rays *self);

}t_vtable_rays;
typedef struct s_vars
{
    void *mlx;
    void *win;
    t_img *textures;          // Pointer to texture structure
    t_img image; 
	char *img;
	int endian;
	char		*addr;
	int line_length;  
	int			bits_per_pixel;         // Image for rendering
    char **map;   
	int width;
    int height;            // Map grid
    int map_x;                // Map width in cells
    int map_y;                // Map height in cells
    float pos_x;              // Player x position
    float pos_y;              // Player y position
	t_player			player;
    int player_side;          // Player's starting direction
    float player_cos;         // Cosine of player's direction
    float player_sin;         // Sine of player's direction
    float radius;             // Camera radius
    double speed;             // Movement speed
    int rotation;     
	int pos;
	int player_angle;
    t_img north_texture;    // North wall texture
    t_img south_texture;    // South wall texture
    t_img west_texture;     // West wall texture
    t_img east_texture;     // East wall texture
    int floor_color;  
	int map_on;        // Floor color (hex)
    int ceiling_color;        // Ceiling color (hex)
    int init;                 // Initialization flag
    t_rays				*rays;
} t_vars;
typedef struct s_rays
{
	t_vtable_rays	*operations;
	t_vars			*vars;
	t_texture		*texture;
	double			half_h;
	double			increment_angle;
	double			half_fov;
	double			ray_angle;
	int				ray_count;
	double			ray_x;
	double			ray_y;
	double			ray_cos;
	double			ray_sin;
	int				wall;
	double			distance;
	int				wall_h;
	int				init;
	double			difx;
	double			dify;
	int				tmp;
	int				pix;
}	t_rays;


typedef struct s_line
{
	int					x;
	int					y;
	int					y0;
	int					y1;
	int					tex_x;
	int					tex_y;
}						t_line;



typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}					t_color;

typedef struct s_stack_node
{
	char				*val;
	struct s_stack_node	*next;
}						t_stack_node;

typedef struct s_stack
{
	t_stack_node		*front;
	t_stack_node		*back;
}						t_stack;
typedef struct s_map_infos
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;

	t_color				floor_color;
	t_color				ceiling_color;

	t_stack				stack;

	int					no_path_parsed;
	int					so_path_parsed;
	int					we_path_parsed;
	int					ea_path_parsed;
	int					floor_color_parsed;
	int					ceiling_color_parsed;

}						t_map_infos;

typedef struct s_vars		t_vars;
typedef struct s_rays		t_rays;
typedef struct s_texture	t_texture;

void			ft_reset_sprite(void);
void			ray_casting(t_vars *vars);
void			ft_reset_values(t_rays *self);
void			ft_hit_wall(t_rays *self);
void			ft_calculate_distance(t_rays *self);
void			ft_calculate_wall_height(t_rays *self);
void			ft_increment_angle(t_rays *self);
t_vtable_rays	*ft_init_vtable(void);
t_rays			*get_raycaster(void);
float			degreetoradian(double degree);
void			ft_get_sprite(t_rays *self, float i, float i2);
void			ft_print_walls(t_rays *self);
void			free_table(t_rays *self);

enum e_element
{
    NO = 1,
    SO = 2,
    WE = 3,
    EA = 4,
    F = 5,
    C = 6,
};


char					*get_next_line(int fd);
int	close_game(t_vars *vars);
size_t					ft_strlen(char const *str);

char					*ft_strch(char const *str, int c);
char					*ft_strcpy(char *dest, char *src);
char					*ft_strdup(char const *src);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_free_pp(void **argv);
char					cube3d(char *c);
void					free_cube3d(t_vars *vars);
int						perror_cube3d(char *str, int flag);
t_vars					*ft_t_vars(void);
int						path_struct(t_vars *map);
int						ft_array_length(char **array);
void					validate_file_format(char *filename);
void frey(t_vars *map);


int		read_key(int keycode, t_vars *vars);
int		get_keycode(int keycode);
void	ft_up(t_vars *vars);
void	ft_down(t_vars *vars);
void	ft_left(t_vars *vars);
void	ft_right(t_vars *vars);
void	ft_esc(t_vars *vars);
int		ft_mouse(int button, int x, int y, t_vars *vars);
void	ft_look_right(t_vars *vars);
void	ft_look_left(t_vars *vars);

int						is_valid_config_line(const char *line);
int						is_valid_map_line(const char *line);

void					element_hunter(char *filename);

t_img					*ft_t_img(void);
void					init_texture(t_vars *vars, t_texture *txt,
							char *element, int val);
void					init_color(int *color, char *element);
int						invisible_yes_no(char c);
int						val_chk(t_img *img, char *temp);

int						fill(t_vars *map, char *filename);
int						ft_stronlyspaces(const char *line);

void					store(t_vars *map, char *filename);

int						check_isclosed(int i, t_vars *map);
int						is_pace(char c);



void game();
void player_info(t_vars *vars);
void data_info(t_vars *vars);
size_t ft_strlen(char const *str);
char *ft_strch(char const *str, int c);
char *ft_strcpy(char *dest, char *src);
char *ft_strdup(char const *src);
char *ft_strjoin(char const *s1, char const *s2);
void ft_free_pp(void **argv);
char cube3d(char *filename);
void free_cube3d(t_vars *vars);
int perror_cube3d(char *str, int flag);
void	size_map(void);
t_vars *ft_t_vars(void);
void	call_mlx(t_vars *vars);
t_img *ft_t_img(void);
int path_struct(t_vars *map);
int	check_map(void);
void	free_stack(t_stack *s);
int ft_array_length(char **array);
char **ft_dup_cpp(char **src, int len);
void validate_file_format(char *filename);
int is_valid_config_line(const char *line);
int is_valid_map_line(const char *line);

void			ft_reset_sprite(void);
void			ft_reset_values(t_rays *self);
void			ft_hit_wall(t_rays *self);
void			ft_calculate_distance(t_rays *self);
void			ft_calculate_wall_height(t_rays *self);
void			ft_increment_angle(t_rays *self);
t_vtable_rays	*ft_init_vtable(void);
t_rays			*get_raycaster(void);
float			degreetoradian(double degree);
void			ft_get_sprite(t_rays *self, float i, float i2);
void			ft_print_walls(t_rays *self);
void			free_table(t_rays *self);

void    put_pixel(t_vars *data, int x, int y, int color);
void	check_fill(t_vars *vars, int y, int x, int *i);
int	ft_str_len(char *s);
long long	ft_len_pp(void **argv);

#endif
