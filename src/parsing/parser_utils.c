/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theaux <theaux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:34:24 by tbabou            #+#    #+#             */
/*   Updated: 2025/04/29 11:20:05 by theaux           ###   ########.fr       */
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
	return (true);
}
