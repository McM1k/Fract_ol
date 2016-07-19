/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 21:22:11 by gboudrie          #+#    #+#             */
/*   Updated: 2016/07/19 21:04:05 by gboudrie         ###   ########.fr       */
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

static void		mandelbrot(t_env env, double xc, double yc)
{
	int		i;
	double	xz;
	double	yz;
	double	tmp_xz;
	int		col;

	i = 0;
	xz = 0;
	yz = 0;
	col = 0x00FFFFFF;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = xz * xz - yz * yz + (xc / env.zoom - 2.1 + env.x_decal);
		yz = 2 * tmp_xz * yz + (yc / env.zoom - 1.2 + env.y_decal);
		col = col - 150000;
		if (col % (255 * 255 * 255) == 0)
			col = 0;
	}
	if (i == env.iter)
		img_addr(env, xc, yc, 0x00000000);
	else
		img_addr(env, xc, yc, col);
}

static void		julia(t_env env, double x, double y)
{
	int		i;
	double	xz;
	double	yz;
	double	tmp_xz;
	int		col;

	i = 0;
	xz = (double)(x / (double)env.zoom);
	yz = (double)(y / (double)env.zoom);
	col = 0;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = (double)(xz * xz - yz * yz + (double)(env.pos_x));
		yz = (double)(2 * tmp_xz * yz + (double)(env.pos_y));
		col = col - 150000;
		if (col % (255 * 255 * 255) == 0)
			col = 0;
	}
	if (i == env.iter)
		img_addr(env, x, y, 0x00000000);
	else
		img_addr(env, x, y, col);
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
				mandelbrot(env, x, y);
			else if (env.param == 1)
				julia(env, x, y);
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
