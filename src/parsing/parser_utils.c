/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:34:24 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/27 05:22:45 by theaux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_finished(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < TEXTURE_AMOUNT)
	{
		if (cub3d->map.texture[i].path == NULL)
			return (false);
		i++;
	}
	if (cub3d->map.colors[FLOOR] == -1)
		return (false);
	if (cub3d->map.colors[CEILING] == -1)
		return (false);
	return (true);
}
