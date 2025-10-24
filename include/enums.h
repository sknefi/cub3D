/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkarika <fkarika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:30:55 by fkarika           #+#    #+#             */
/*   Updated: 2025/10/24 16:30:56 by fkarika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef enum s_textures_dir
{
	NO = 0,
	EA,
	SO,
	WE,
	ERROR = -1,
}	t_textures_dir;

typedef enum s_color_types
{
	CEILING = 0,
	FLOOR
}	t_color_types;
