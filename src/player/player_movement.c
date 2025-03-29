/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:13:21 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/29 15:14:09 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	try_move(float new_x, float new_y, char **map)
{
	float	collision_buffer;

	collision_buffer = 0.2;
	if (is_touching_wall(new_x + collision_buffer, new_y, map)
		|| is_touching_wall(new_x - collision_buffer, new_y, map)
		|| is_touching_wall(new_x, new_y + collision_buffer, map)
		|| is_touching_wall(new_x, new_y - collision_buffer, map))
		return (false);
	return (true);
}

void	move_player(double angle, float speed, t_player *player, char **map)
{
	t_vec2	movement;
	t_dvec2	new;
	double	mangle;

	movement = (t_vec2){player->right - player->left, player->up
		- player->down};
	mangle = angle + atan2(movement.x, movement.y);
	if (!(player->up - player->down) && !(player->right - player->left))
		return ;
	new.x = player->pos.x + cos(mangle) * speed;
	new.y = player->pos.y + sin(mangle) * speed;
	if (try_move(new.x, player->pos.y, map))
		player->pos.x = new.x;
	if (try_move(player->pos.x, new.y, map))
		player->pos.y = new.y;
}