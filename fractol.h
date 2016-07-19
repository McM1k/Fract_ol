/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:27:05 by gboudrie          #+#    #+#             */
/*   Updated: 2016/07/17 15:09:36 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# define SIZE_X 750
# define SIZE_Y 650

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*ig;
	char		*img;
	int			siz;
	int			bit;
	int			end;
	int			zoom;
	double		x_decal;
	double		y_decal;
	int			param;
	int			iter;
	int			pos_x;
	int			pos_y;
}				t_env;

void			foreach_pixel(t_env env);
void			img_addr(t_env env, int x, int y, int color);
void			events(int keycode, t_env *env);
int				destroy_funct(void *param);
int				mouse_funct(int x, int y, t_env *env);
void			ft_quit();

#endif
