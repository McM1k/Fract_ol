/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:54:05 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/17 19:16:23 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

int		key_funct(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	events(keycode, env);
	fractals(*env);
	return (1);
}

void	events(int keycode, t_env *env)
{
	if (keycode == 53)
		destroy_funct(env);
	if (keycode == 123 || keycode == 124)
		env->x_decal += (keycode == 123 ?
			-30.0 / env->zoom : 30.0 / env->zoom);
	if (keycode == 75 || keycode == 67)
	{
		env->iter += (keycode == 67 ? 20 : -20);
		if (env->iter < 1)
			env->iter = 1;
	}
	if (keycode == 83 || keycode == 84)
		env->col_set += (keycode == 84 ? 5000 : -5000);
	if (keycode == 125 || keycode == 126)
		env->y_decal += (keycode == 125 ?
			(double)10 / env->zoom : (double)-10 / env->zoom);
	if (keycode == 78 || keycode == 69)
	{
		env->zoom *= (keycode == 69 ? 2 : 0.5);
		if (env->zoom <= 1)
			env->zoom = 1;
	}
}

int		mouse_funct(int x, int y, t_env *env)
{
	env->pos_x = (double)x;
	env->pos_y = (double)y;
	if (env->param == 1)
	{
		fractals(*env);
	}
	return (1);
}

int		clic_funct(int button, int x, int y, t_env *env)
{
	if ((button == 1) || (button == 4))
	{
		env->x_decal += (x - (SIZE_X / 2)) / env->zoom;
		env->y_decal += (y - (SIZE_Y / 2)) / env->zoom;
		events(69, env);
	}
	if ((button == 2) || (button == 5))
	{
		env->x_decal -= (x - (SIZE_X / 2)) / env->zoom;
		env->y_decal -= (y - (SIZE_Y / 2)) / env->zoom;
		events(78, env);
	}
	fractals(*env);
	return (0);
}

int		destroy_funct(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	mlx_destroy_image(env->mlx, env->ig);
	mlx_destroy_window(env->mlx, env->win);
	ft_putendl("Closing program.");
	exit(0);
	return (1);
}
