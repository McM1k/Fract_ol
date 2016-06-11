/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/11 15:54:05 by gboudrie          #+#    #+#             */
/*   Updated: 2016/06/11 21:20:02 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

void		events(int keycode, t_env *env)
{
	if (keycode == 53)
		destroy_funct(env);
	if (keycode == 123 || keycode == 124)
		env->x_decal += (keycode == 123 ? -10 : 10);
	if (keycode == 125 || keycode == 126)
		env->y_decal += (keycode == 125 ? 10 : -10);
	if (keycode == 78 || keycode == 69)
	{
		env->zoom += (keycode == 69 ? 2 : -2);
		if (env->zoom <= 250)
			env->zoom = 250;
	}
}

void		ft_quit()
{
	ft_putendl("Closing program.");
	exit(0);
}
