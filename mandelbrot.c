/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 21:22:11 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/16 18:27:55 by gboudrie         ###   ########.fr       */
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

static int		mandelbrot(t_env env, double xc, double yc)
{
	int		i;
	double	xz;
	double	yz;
	double	tmp_xz;
	int		col;

	i = 0;
	xz = 0;
	yz = 0;
	xc = (double)(xc / env.zoom + env.x_decal - (double)(SIZE_X / 2) / env.zoom);
	yc = (double)(yc / env.zoom + env.y_decal - (double)(SIZE_Y / 2) / env.zoom);
	col = 0x00FFFFFF;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = (double)(xz * xz - yz * yz + xc);
		yz = (double)(2 * tmp_xz * yz + yc);
		col = col - 135000;
		if (col < 0x00000000)
			col = 0x00FFFFFF;
	}
	if (i == env.iter)
		return (0x00000000);
	else
		return (col);
}

static int		julia(t_env env, double x, double y)
{
	int		i;
	double	xz;
	double	yz;
	double	tmp_xz;
	int		col;

	i = 0;
	xz = (double)(x / env.zoom + env.x_decal - (double)(SIZE_X / 2) / env.zoom);
	yz = (double)(y / env.zoom + env.y_decal - (double)(SIZE_Y / 2) / env.zoom);
	col = 0x00FFFFFF;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = (double)(xz * xz - yz * yz + env.pos_x / 1000);
		yz = (double)(2 * tmp_xz * yz + env.pos_y / 1000);
		col = col - 135000;
		if (col < 0x00000000)
			col = 0x00FFFFFF;
	}
	if (i == env.iter)
		return (0x00000000);
	else
		return (col);
}

void			foreach_pixel(t_env env)
{
	double		x;
	double		y;
	x = 0;
	while (x++ < SIZE_X)
	{
		y = 0;
		while (y++ < SIZE_Y)
		{
			if (env.param == 0)
				img_addr(env, x, y, mandelbrot(env, x, y));
			else if (env.param == 1)
				img_addr(env, x, y, julia(env, x, y));
		}
	}
	mlx_put_image_to_window(env.mlx, env.win, env.ig, 0, 0);
}
