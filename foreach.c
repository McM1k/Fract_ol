/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 18:12:36 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/17 19:42:42 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	texts(t_env env)
{
	mlx_string_put(env.mlx, env.win, 9, 9, 0, "Arrows to move    |");
	mlx_string_put(env.mlx, env.win, 10, 10, 0x00F0F0F0, "Arrows to move    |");
	mlx_string_put(env.mlx, env.win, 9, 24, 0, "Clics to zoom     |");
	mlx_string_put(env.mlx, env.win, 10, 25, 0x00F0F0F0, "Clics to zoom     |");
	mlx_string_put(env.mlx, env.win, 9, 39, 0, "* | / for iters   |");
	mlx_string_put(env.mlx, env.win, 10, 40, 0x00F0F0F0, "* | / for iters   |");
	mlx_string_put(env.mlx, env.win, 9, 54, 0, "1 | 2 for colours |");
	mlx_string_put(env.mlx, env.win, 10, 55, 0x00F0F0F0, "1 | 2 for colours |");
	mlx_string_put(env.mlx, env.win, 9, 69, 0, "__________________|");
	mlx_string_put(env.mlx, env.win, 10, 70, 0x00F0F0F0, "__________________|");
	mlx_string_put(env.mlx, env.win, 9, SIZE_Y - 21, 0, "Iterations :");
	mlx_string_put(env.mlx, env.win, 10, SIZE_Y - 20, 0x00E08080,
				   "Iterations :");
	mlx_string_put(env.mlx, env.win, 139, SIZE_Y - 21, 0,ft_itoa(env.iter));
	mlx_string_put(env.mlx, env.win, 140, SIZE_Y - 20, 0x00E08080,
				   ft_itoa(env.iter));
	mlx_string_put(env.mlx, env.win, 9, SIZE_Y - 36, 0, "Colours :");
	mlx_string_put(env.mlx, env.win, 109, SIZE_Y - 36, 0, ft_itoa(env.col_set));
	mlx_string_put(env.mlx, env.win, 10, SIZE_Y - 35, 0x00E0E080, "Colours :");
	mlx_string_put(env.mlx, env.win, 110, SIZE_Y - 35, 0x00E0E080,
				   ft_itoa(env.col_set));
}

void		fractals(t_env env)
{
	int		(*funct)(t_env, double, double);

	if (env.param == 0)
		funct = &mandelbrot;
	if (env.param == 1)
		funct = &julia;
	if (env.param == 2)
		funct = &sinusoida;
	foreach_pixel(env, funct);
}

void		foreach_pixel(t_env env, int (*funct)(t_env, double, double))
{
	int		x;
	int		y;

	x = 0;
	while (x++ < SIZE_X)
	{
		y = 0;
		while (y++ < SIZE_Y)
			img_addr(env, x, y, funct(env, (double)x, (double)y));
	}
	mlx_put_image_to_window(env.mlx, env.win, env.ig, 0, 0);
	texts(env);
}

void		img_addr(t_env env, int x, int y, int color)
{
		if (!(x > env.siz - 1 || x <= 0 || y <= 0 ||
			x > SIZE_X || y > SIZE_Y))
		ft_memcpy(&env.img[(x - 1) * 4 + (y - 1) * env.siz], &color, 4);
}
