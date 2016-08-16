/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 21:22:11 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/16 23:46:10 by gboudrie         ###   ########.fr       */
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

int			mandelbrot(t_env env, double xc, double yc)
{
	int			i;
	double		xz;
	double		yz;
	double		tmp_xz;
	int			col;

	i = 0;
	xz = 0;
	yz = 0;
	xc = xc / env.zoom + env.x_decal - (double)(SIZE_X / 2) / env.zoom;
	yc = yc / env.zoom + env.y_decal - (double)(SIZE_Y / 2) / env.zoom;
	col = 0x00FFFFFF;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = (double)(xz * xz - yz * yz + xc);
		yz = (double)(2 * tmp_xz * yz + yc);
		col = col - env.col_set;
		if (col < 0x00000000)
			col = 0x00FFFFFF;
	}
	if (i == env.iter)
		return (0x00000000);
	else
		return (col);
}

int			julia(t_env env, double x, double y)
{
	int			i;
	double		xz;
	double		yz;
	double		tmp_xz;
	int			col;

	i = 0;
	xz = x / env.zoom + env.x_decal - (double)(SIZE_X / 2) / env.zoom;
	yz = y / env.zoom + env.y_decal - (double)(SIZE_Y / 2) / env.zoom;
	col = 0x00FFFFFF;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = (double)(xz * xz - yz * yz + env.pos_x / 1000);
		yz = (double)(2 * tmp_xz * yz + env.pos_y / 1000);
		col = col - env.col_set;
		if (col < 0x00000000)
			col = 0x00FFFFFF;
	}
	if (i == env.iter)
		return (0x00000000);
	else
		return (col);
}

void			fractals(t_env env)
{
	int		(*funct)(t_env, double, double);

	if (env.param == 0)
		funct = &mandelbrot;
	if (env.param == 1)
		funct = &julia;
//	if (env.param == 2)
//		funct = &other;
	foreach_pixel(env, funct);
}

void			foreach_pixel(t_env env, int (*funct)(t_env, double, double))
{
	int			x;
	int			y;
	x = 0;
	while (x++ < SIZE_X)
	{
		y = 0;
		while (y++ < SIZE_Y)
			img_addr(env, x, y, funct(env, (double)x, (double)y));
	}
	mlx_put_image_to_window(env.mlx, env.win, env.ig, 0, 0);
}
