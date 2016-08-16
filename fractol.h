/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:27:05 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/16 23:49:42 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# define SIZE_X 750
# define SIZE_Y 600

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*ig;
	char		*img;
	int			siz;
	int			bit;
	int			end;
	double		zoom;
	double		x_decal;
	double		y_decal;
	int			param;
	int			iter;
	double		pos_x;
	double		pos_y;
	int			col_set;
}				t_env;

void			foreach_pixel(t_env env, int (*funct)(t_env, double, double));
void			img_addr(t_env env, int x, int y, int color);
void			events(int keycode, t_env *env);
int				destroy_funct(void *param);
int				mouse_funct(int x, int y, t_env *env);
int				clic_funct(int button, int x, int y, t_env *env);
void			ft_quit();
void			fractals(t_env env);
int				mandelbrot(t_env env, double xc, double yc);
int				julia(t_env env, double x, double y);

#endif
