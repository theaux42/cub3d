/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:00:52 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/24 14:41:18 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_valid(t_cub3d *cub3d)
{
	if (check_player_amount(cub3d->map))
		return (true);
	if (check_map_chars(cub3d->map))
		return (true);
	if (is_map_closed(cub3d))
		return (true);
	return (false);
}
