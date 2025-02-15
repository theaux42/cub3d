/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:15:30 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/16 00:03:51 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    empty_player(t_player *player)
{
    player->x = 0.0;
    player->y = 0.0;
    player->dir = PI / 2;
    player->fov = 1.0;
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
    else if (key == A)
        player->rotate_left = true;
    else if (key == D)
        player->rotate_right = true;
    else if (key == MINUS)
        player->fov -= 0.1;
    else if (key == PLUS)
        player->fov += 0.1;
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
    else if (key == A)
        player->rotate_left = false;
    else if (key == D)
        player->rotate_right = false;
    return (0);
}

void    move_player(float cos_dir, float sin_dir, int speed, t_player *player, char **map)
{
    float new_x;
    float new_y;

    if (player->up)
    {
        new_x = player->x + cos_dir * speed;
        new_y = player->y + sin_dir * speed;
        if (!is_touching_wall(new_x, new_y, map))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->down)
    {
        new_x = player->x - cos_dir * speed;
        new_y = player->y - sin_dir * speed;
        if (!is_touching_wall(new_x, new_y, map))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->left)
    {
        new_x = player->x - sin_dir * speed;
        new_y = player->y + cos_dir * speed;
        if (!is_touching_wall(new_x, new_y, map))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->right)
    {
        new_x = player->x + sin_dir * speed;
        new_y = player->y - cos_dir * speed;
        if (!is_touching_wall(new_x, new_y, map))
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
}

void player_key_handler(t_player *player, char **map)
{
    int SPEED;
    float cos_dir;
    float sin_dir;
    cos_dir = cos(player->dir);
    sin_dir = sin(player->dir);
    (void)map;
    if (player->rotate_left)
        player->dir -= (CAMERA_SPEED + player->fov / 50);
    if (player->rotate_right)
        player->dir += (CAMERA_SPEED + player->fov / 50);
    SPEED = PLAYER_SPEED;
    if (!player->sprint)
        SPEED /= 2;
    move_player(cos_dir, sin_dir, SPEED, player, map);
}
