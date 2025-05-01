/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:02:50 by tbabou            #+#    #+#             */
/*   Updated: 2025/03/29 15:02:50 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_parsing(t_cub3d *cub3d)
{
	if (parse_settings(cub3d))
		return (true);
	if (settings_checker(cub3d))
		return (true);
	if (parse_map(cub3d))
		return (true);
	if (init_player(cub3d->map.map, &cub3d->player))
		return (true);
	if (init_textures(cub3d))
		return (true);
	if (is_map_valid(cub3d))
		return (true);
	return (false);
}
