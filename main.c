/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:24:47 by gboudrie          #+#    #+#             */
/*   Updated: 2016/06/11 21:18:23 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			destroy_funct(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	mlx_destroy_image(env->mlx, env->ig);
	mlx_destroy_window(env->mlx, env->win);
	ft_quit();
	return (1);
}

int			my_key_func(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	events(keycode, env);
	ft_bzero(env->img, SIZE_X * SIZE_Y * 4);
	foreach_pixel(*env);
	mlx_put_image_to_window(env->mlx, env->win, env->ig, 0, 0);
	return (1);
}


int			main(int ac, char **av)
{
    t_env   env;

	if (ac != 2 || (ft_strcmp(av[1], "Mandelbrot") != 0 &&
					ft_strcmp(av[1], "Julia") != 0 &&
					ft_strcmp(av[1], "Other") != 0) ||
		!(env.mlx = mlx_init()) ||
		!(env.win = mlx_new_window(env.mlx, SIZE_X, SIZE_Y, "Fractol")) ||
		!(env.ig = mlx_new_image(env.mlx, SIZE_X, SIZE_Y)))
		ft_putendl("Accepted parameters :\n\t-Mandelbrot\n\t-Julia\n\t-Other");
	else
	{
		env.zoom = 250;
		env.img = mlx_get_data_addr(env.ig, &(env.bit), &(env.siz), &(env.end));
		foreach_pixel(env);
		mlx_put_image_to_window(env.mlx, env.win, env.ig, 0, 0);
		mlx_hook(env.win, 2, 0, my_key_func, &env);
		mlx_hook(env.win, 17, 0, destroy_funct, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
