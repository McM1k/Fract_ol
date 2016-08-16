/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:54:05 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/16 19:50:39 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

void		events(int keycode, t_env *env)
{
	if (keycode == 53)
		destroy_funct(env);
	if (keycode == 123 || keycode == 124)
		env->x_decal += (keycode == 123 ?
			-10.0 / env->zoom : 10.0 / env->zoom);
	if (keycode == 75 || keycode == 67)
	{
		env->iter += (keycode == 67 ? 1 : -1);
		if (env->iter < 1)
			env->iter = 1;
	}
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

int		clic_funct(int button, int x, int y, t_env *env)
{
	if ((button == 1) || (button == 4))
	{
		env->x_decal += (x - (SIZE_X / 2)) / (env->zoom * 1.5);
		env->y_decal += (y - (SIZE_Y / 2)) / (env->zoom * 1.5);
		events(69, env);
	}
	if ((button == 2) || (button == 5))
	{
		env->x_decal -= (x - (SIZE_X / 2)) / (env->zoom * 1.5);
		env->y_decal -= (y - (SIZE_Y / 2)) / (env->zoom * 1.5);
		events(78, env);
	}
	foreach_pixel(*env);
	return (0);
}

void		ft_quit(void)
{
	ft_putendl("Closing program.");
	exit(0);
}
