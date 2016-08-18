/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 17:24:47 by gboudrie          #+#    #+#             */
/*   Updated: 2016/08/18 19:47:25 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init(t_env *env, char *param)
{
	env->param = (ft_strcmp(param, "Mandelbrot") == 0 ? 0 : 1);
	if (env->param == 1)
		env->param = (ft_strcmp(param, "Julia") == 0 ? 1 : 2);
	if (env->param == 2)
		env->param = (ft_strcmp(param, "Burning") == 0 ? 2 : 3);
	env->pos_x = 0;
	env->pos_y = 0;
	env->x_decal = 0;
	env->y_decal = 0;
	env->zoom = 200;
	env->iter = 100;
	env->col_set = 150000;
	env->img = mlx_get_data_addr(env->ig, &(env->bit), &(env->siz),
								&(env->end));
}

int				main(int ac, char **av)
{
	t_env	env;

	if (ac != 2 || (ft_strcmp(av[1], "Mandelbrot") != 0 &&
					ft_strcmp(av[1], "Julia") != 0 &&
					ft_strcmp(av[1], "Burning") != 0) ||
		!(env.mlx = mlx_init()) ||
		!(env.win = mlx_new_window(env.mlx, SIZE_X, SIZE_Y, "Fractol")) ||
		!(env.ig = mlx_new_image(env.mlx, SIZE_X, SIZE_Y)))
		ft_putendl("Accepted params :\n\t-Mandelbrot\n\t-Julia\n\t-Burning");
	else
	{
		init(&env, av[1]);
		fractals(env);
		mlx_hook(env.win, 6, 0, mouse_funct, &env);
		mlx_hook(env.win, 4, 0, clic_funct, &env);
		mlx_hook(env.win, 2, 0, key_funct, &env);
		mlx_hook(env.win, 17, 0, destroy_funct, &env);
		mlx_loop(env.mlx);
	}
	return (0);
}
