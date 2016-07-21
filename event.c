/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:54:05 by gboudrie          #+#    #+#             */
/*   Updated: 2016/07/21 18:06:26 by gboudrie         ###   ########.fr       */
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
			(double)-10 / env->zoom : (double)10 / env->zoom);
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

void		ft_quit(void)
{
	ft_putendl("Closing program.");
	exit(0);
}
