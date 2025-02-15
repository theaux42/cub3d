/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:15:30 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 15:42:46 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    empty_player(t_player *player)
{
    player->left = false;
    player->right = false;
    player->up = false;
    player->down = false;
    player->rotate_left = false;
    player->rotate_right = false;
}

int	on_key_press(int key, t_cub3d *cub3d)
{
    if (key == LEFT)
        cub3d->player.left = true;
    else if (key == RIGHT)
        cub3d->player.right = true;
    else if (key == UP)
        cub3d->player.up = true;
    else if (key == DOWN)
        cub3d->player.down = true;
    if (key == UP)
    {
    }
    return (0);
}

int	on_key_release(int key, t_cub3d *cub3d)
{
    ft_printf("key has been released : %i\n", key);
    if (key == LEFT)
        cub3d->player.left = false;
    else if (key == RIGHT)
        cub3d->player.right = false;
    else if (key == UP)
        cub3d->player.up = false;
    else if (key == DOWN)
        cub3d->player.down = false;
    return (0);
}

void move_player(t_player *player)
{
    if (player->up)
        ft_printf("player is going to move");
    if (player->up)
        player->y -= PLAYER_SPEED;
    if (player->down)
        player->y += PLAYER_SPEED;
    if (player->left)
        player->x -= PLAYER_SPEED;
    if (player->right)
        player->x += PLAYER_SPEED;
    
}