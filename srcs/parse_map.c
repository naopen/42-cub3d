/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:01:56 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:03:49 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_map(t_game *game)
{
	// ここではサンプルとして固定的にマップを与える例
	// 実際は、parse_config.c 側で読み込んだ行を使って動的に 2次元配列を確保し、下記のように格納
	static char *sample_map[] = {"111111", "100001", "1000W1", "100001",
		"111111", NULL};

	int height = 0;
	while (sample_map[height])
		height++;
	game->map.height = height;
	game->map.width = 6; // サンプル固定

	game->map.grid = malloc(sizeof(char *) * (height + 1));
	if (!game->map.grid)
		return (-1);

	for (int i = 0; i < height; i++)
	{
		game->map.grid[i] = strdup(sample_map[i]);
		if (!game->map.grid[i]) // strdupのエラーチェックを追加
		{
			// 既に割り当て済みのメモリを解放
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			return (-1);
		}
	}
	game->map.grid[height] = NULL;

	// プレイヤー開始位置と向きの探索 (サンプル)
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < game->map.width; x++)
		{
			if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S'
				|| game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				// 方角に応じて dir_x, dir_y をセット(例: W の場合は(-1,0))
				game->player.dir_x = -1;
				game->player.dir_y = 0;
				// 同様に plane_x, plane_y も方向に応じて設定
				game->player.plane_x = 0;
				game->player.plane_y = 0.66;

				// 開始位置の文字を'0'に置き換える (複数開始位置を防ぐ)
				game->map.grid[y][x] = '0';
				return (0); // 開始位置を見つけたらループを抜ける
			}
		}
	}
	return (-1); // 開始位置が見つからない場合のエラー処理
}