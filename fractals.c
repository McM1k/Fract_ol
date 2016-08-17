/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 18:11:41 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/17 19:46:46 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "math.h"

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

int			sinusoida(t_env env, double x, double y)
{
	int			i;
	double		xz;
	double		yz;
	double		tmp_xz;
	int			col;

	i = 0;
	xz = 0;
	yz = 0;
	x = x / env.zoom + env.x_decal - (double)(SIZE_X / 2) / env.zoom;
	y = y / env.zoom + env.y_decal - (double)(SIZE_Y / 2) / env.zoom;
	col = 0x00FFFFFF;
	while (xz * xz + yz * yz < 4 && ++i < env.iter)
	{
		tmp_xz = xz;
		xz = (double)(sin(xz) * sin(xz) - sin(yz) * sin(yz) + x);
		yz = (double)(2 * sin(tmp_xz) * sin(yz) + y);
		col = col - env.col_set;
		if (col < 0)
			col = 0x00FFFFFF;
	}
	if (i == env.iter)
		return (0);
	else
		return (col);
}
