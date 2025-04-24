/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 01:50:06 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/24 20:23:29 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// todo add la map
int	render(t_cub3d *cub3d)
{
	raycast(cub3d);
	player_key_handler(&cub3d->player, cub3d->map.map);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
	return (0);
}

int	exit_game(t_cub3d *cub3d)
{
	free_cub3d(cub3d);
	exit(0);
}

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;

	if (ac != 2)
		return (ft_dprintf(2, ERR_NO_ARG, av[0]), 1);
	cub3d = empty_cub3d();
	if (!cub3d)
		return (1);
	if (init_cub3d(cub3d, av[1]))
		return (free_cub3d(cub3d), 1);
	mlx_hook(cub3d->win, 17, 1L << 17, exit_game, cub3d);
	mlx_hook(cub3d->win, 2, 1L << 0, on_key_press, cub3d);
	mlx_hook(cub3d->win, 3, 1L << 1, on_key_release, &cub3d->player);
	mlx_loop_hook(cub3d->mlx, render, cub3d);
	mlx_loop(cub3d->mlx);
	free_cub3d(cub3d);
	return (0);
}
