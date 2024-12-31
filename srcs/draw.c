/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:13:17 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:13:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "cub3d.h"

void	draw_background(t_game *game)
{
	int	floor_color;
	int	ceiling_color;

	int x, y;
	floor_color = create_trgb(0, game->floor_color.r, game->floor_color.g,
			game->floor_color.b);
	ceiling_color = create_trgb(0, game->ceiling_color.r, game->ceiling_color.g,
			game->ceiling_color.b);
	for (y = 0; y < WIN_HEIGHT; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(game, x, y, ceiling_color);
			else
				put_pixel(game, x, y, floor_color);
		}
	}
}

void	draw_walls(t_game *game)
{
	// 必要に応じて壁描画専用ロジックを追加
	// ここでは raycast.c のほうで壁を描画しているので空実装
	(void)game;
}