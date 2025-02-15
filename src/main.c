/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 01:50:06 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 15:37:54 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int pos_x = 0;
int pos_y = 0;

int render(t_cub3d *cub3d)
{
    ft_mlx_clear_image(cub3d);
    draw_map(cub3d);
    move_player(&cub3d->player);
    draw_square(cub3d->player.x, cub3d->player.x, 5, 0xFF0000, cub3d);
    mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
    return (0);
}

int main(int ac, char **av)
{
    t_cub3d *cub3d;

    if (ac != 2)
        return (ft_dprintf(2, ERR_NO_ARG, av[0]), 1);
    cub3d = empty_cub3d();
    if (!cub3d)
        return (1);
    if (init_cub3d(cub3d, av[1]))
        return (1);
    
    mlx_hook(cub3d->win, 2, 1L<<0, on_key_press, &cub3d);
    mlx_hook(cub3d->win, 3, 1L<<0, on_key_release, &cub3d);
    mlx_loop_hook(cub3d->mlx, render, cub3d);
    
    mlx_loop(cub3d->mlx);
    free_cub3d(cub3d);
    return (0);
}


