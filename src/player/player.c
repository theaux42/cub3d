/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:15:30 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 18:51:21 by theaux           ###   ########.fr       */
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

int	on_key_press(int key, t_player *player)
{
    if (key == LEFT)
        player->left = true;
    else if (key == RIGHT)
        player->right = true;
    else if (key == UP)
        player->up = true;
    else if (key == DOWN)
        player->down = true;
    else if (key == SHIFT)
        player->sprint = true;
    return (0);
}

int	on_key_release(int key, t_player *player)
{
    if (key == LEFT)
        player->left = false;
    else if (key == RIGHT)
        player->right = false;
    else if (key == UP)
        player->up = false;
    else if (key == DOWN)
        player->down = false;
    else if (key == SHIFT)
        player->sprint = false;
    return (0);
}

void move_player(t_player *player)
{
    int SPEED = PLAYER_SPEED;
    if (!player->sprint)
        SPEED /= 1.25;
    if (player->up)
        player->y -= SPEED;
    if (player->down)
        player->y += SPEED;
    if (player->left)
        player->x -= SPEED;
    if (player->right)
        player->x += SPEED;
}