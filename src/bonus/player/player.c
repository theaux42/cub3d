/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:05:40 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/25 19:29:56 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	empty_player(t_player *player)
{
	player->pos = (t_dvec2){0.0, 0.0};
	player->spawn_pos = (t_vec2){0, 0};
	player->plane = (t_dvec2){0.0, 0.66};
	player->angle = PI / 2;
	player->speed = PLAYER_SPEED;
	player->left = false;
	player->interact = false;
	player->right = false;
	player->up = false;
	player->down = false;
	player->sprint = false;
	player->rotate_left = false;
	player->rotate_right = false;
	player->pitch = 0;
	player->look_up = false;
	player->look_down = false;
}

void	update_camera_plane(t_player *player)
{
	player->plane.x = sin(player->angle);
	player->plane.y = -cos(player->angle);
}

void	player_key_handler(t_player *player, char **map)
{
	float	current_speed;

	current_speed = player->speed;
	if (player->rotate_left)
		player->angle -= CAMERA_SPEED;
	if (player->rotate_right)
		player->angle += CAMERA_SPEED;
	player->angle = fmod(player->angle, 2 * PI);
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->sprint)
		current_speed *= 1.5;
	else
		current_speed = PLAYER_SPEED / 2;
	update_camera_plane(player);
	if (player->look_up)
		player->pitch += 20;
	if (player->look_down)
		player->pitch -= 20;
	if (player->pitch < -HEIGHT / 2)
		player->pitch = -HEIGHT / 2;
	if (player->pitch > HEIGHT / 2)
		player->pitch = HEIGHT / 2;
	move_player(player->angle, current_speed, player, map);
}
