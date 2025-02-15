/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:03:55 by tbabou            #+#    #+#             */
/*   Updated: 2025/02/15 18:44:32 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PLAYER_H
# define PLAYER_H

#include "structs.h"

void    empty_player(t_player *player);
bool    init_player(char **map, t_player *player);

int     on_key_press(int key, t_player *player);
int     on_key_release(int key, t_player *player);
void    move_player(t_player *player);

#endif