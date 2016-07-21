/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:24:47 by gboudrie          #+#    #+#             */
/*   Updated: 2016/07/21 19:02:48 by gboudrie         ###   ########.fr       */
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

int			mouse_funct(int x, int y, t_env *env)
{
	env->pos_x = (double)x;
	env->pos_y = (double)y;
	foreach_pixel(*env);
	mlx_put_image_to_window(env->mlx, env->win, env->ig, 0, 0);
	return (1);
}

int			my_key_func(int keycode, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	events(keycode, env);
	foreach_pixel(*env);
	mlx_put_image_to_window(env->mlx, env->win, env->ig, 0, 0);
	return (1);
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac != 2 || (ft_strcmp(av[1], "Mandelbrot") != 0 &&
					ft_strcmp(av[1], "Julia") != 0 &&
					ft_strcmp(av[1], "Other") != 0) ||
		!(env.mlx = mlx_init()) ||
		!(env.win = mlx_new_window(env.mlx, SIZE_X, SIZE_Y, "Fractol")) ||
		!(env.ig = mlx_new_image(env.mlx, SIZE_X, SIZE_Y)))
		ft_putendl("Accepted parameters :\n\t-Mandelbrot\n\t-Julia\n\t-Other");
	else
	{
		env.param = (ft_strcmp(av[1], "Mandelbrot") == 0 ? 0 : 1);
		if (env.param == 1)
			env.param = (ft_strcmp(av[1], "Julia") == 0 ? 1 : 2);
		env.pos_x = 0;
		env.pos_y = 0;
		env.x_decal = 0;
		env.y_decal = 0;
		env.zoom = 200;
		env.iter = 50;
		env.img = mlx_get_data_addr(env.ig, &(env.bit), &(env.siz), &(env.end));
		foreach_pixel(env);
		mlx_put_image_to_window(env.mlx, env.win, env.ig, 0, 0);
		mlx_hook(env.win, 6, 0, mouse_funct, &env);
		mlx_hook(env.win, 2, 0, my_key_func, &env);
		mlx_hook(env.win, 17, 0, destroy_funct, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
