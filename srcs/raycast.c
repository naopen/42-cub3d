/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:11:08 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:13:15 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_column(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	if (start < 0)
		start = 0;
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	while (y <= end)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}

/*
  簡略化したレイキャスト例。テクスチャまでは反映せず、壁に当たったら単色で描画する。
  テクスチャを貼る場合は、壁のヒット面に応じて X 座標を計算し、さらに描画する Y 座標ごとに
  テクスチャ座標を補間する必要があります。
*/
void	render_frame(t_game *game)
{
	// 1. 背景塗りつぶし
	draw_background(game);

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		// カメラ空間での x座標(-1.0 ~ 1.0)
		double cameraX = 2.0 * x / (double)WIN_WIDTH - 1.0;
		double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;

		// レイのマップ上のマス座標
		int mapX = (int)game->player.x;
		int mapY = (int)game->player.y;

		// レイの長さ
		double sideDistX;
		double sideDistY;

		// ΔDist (1マス進むのに必要な距離)
		double deltaDistX = fabs(1.0 / rayDirX);
		double deltaDistY = fabs(1.0 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;
		int hit = 0;
		int side;

		// 初期 stepX / stepY と sideDistX / sideDistY を計算
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
		}

		// DDA ループ
		while (hit == 0)
		{
			// x方向と y方向、どちらが小さいかで次の区切りまで進む
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// 壁に当たったかチェック
			if (game->map.grid[mapY][mapX] == '1')
				hit = 1;
		}

		// レイが壁に当たった距離を計算
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// 壁の高さを計算
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		// 描画範囲
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;

		// 壁面の色 (side で若干暗くするなど演出可能)
		int color = 0x00FF00; // 仮に緑

		if (side == 1)
			color = color / 2; // ちょっと暗く
		draw_column(game, x, drawStart, drawEnd, color);
	}

	// 最後にイメージをウィンドウへ反映
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}