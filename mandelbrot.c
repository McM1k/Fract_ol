/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 21:22:11 by gboudrie          #+#    #+#             */
/*   Updated: 2016/06/16 21:28:27 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			img_addr(t_env env, int x, int y, int color)
{
	if (!(x > env.siz - 1 || x <= 0 || y <= 0
		  || x > SIZE_X || y > SIZE_Y))
		ft_memcpy(&env.img[(x - 1) * 4 + (y - 1) * env.siz], &color, 4);
}

/*
**	Zn = (Zn-1)^2                          + C
**	Zn = (xZ + yZ * i)^2                   + xC + yC * i
**	Zn = (xZ)^2 - (yZ)^2 + 2 * xZ * yZ * i + xC + yC * i
**	x = xZ * xZ - yZ * yZ + xC	    y = 2 * xZ * yZ + yC
*/
static void		mandelbrot(t_env env, double xC, double yC, int iter)
{
	int		i;
	double	xZ;
	double	yZ;
	double	tmp_xZ;

	i = 0;
	xZ = 0;
	yZ = 0;
	while (xZ * xZ + yZ * yZ < 4 && ++i < iter)
	{
		tmp_xZ = xZ;
		xZ = xZ * xZ - yZ * yZ + (xC / env.zoom + env.pos_x - 2.1 + env.x_decal);
		yZ = 2 * tmp_xZ * yZ + (yC / env.zoom + env.pos_y - 1.2 + env.y_decal);
	}
	if (i == iter)
		img_addr(env, xC, yC, 0x00000000);
	else
		img_addr(env, xC, yC, 0x00FFFFFF * pow(i, 1.998) / iter);
}

static void		julia(t_env env, double x, double y, int iter)
{
	int		i;
	double	xZ;
	double	yZ;
	double	tmp_xZ;

	i = 0;
	xZ = (x / env.zoom);
	yZ = (y / env.zoom);
	while (xZ * xZ + yZ * yZ < 4 && ++i < iter)
	{
		tmp_xZ = xZ;
		xZ = xZ * xZ - yZ * yZ + env.pos_x;
		yZ = 2 * tmp_xZ * yZ + env.pos_y;
	}
	if (i == iter)
		img_addr(env, x, y, 0x00000000);
	else
		img_addr(env, x, y, 0x00FFFFFF * pow(i, 1.998) / iter);
}

void			foreach_pixel(t_env env)
{
	double		x;
	double		y;
	double		iter;

	iter = 30 + (env.zoom / 500);
	x = 0;
	while (x++ < SIZE_X)
	{
		y = 0;
		while (y++ < SIZE_Y)
		{
			if (env.param == 0)
				mandelbrot(env, x, y, iter);
			else if (env.param == 1)
				julia(env, x, y, iter);
		}
	}
	x = SIZE_X - 30;
	while (x++ < SIZE_X)
	{
		y = SIZE_Y - 30;
		while (y++ < SIZE_Y)
			img_addr(env, x, y, 0x00FF0000);
	}
}
