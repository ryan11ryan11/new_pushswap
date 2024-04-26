/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:14:18 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/26 18:29:18 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	free_tmp_argv(char *argv[], t_Basic_info *info)
{
	free(info->tmp_arr);
	freedom(argv);
}

int	error_case(char *argv[], int flag, t_Basic_info *info)
{
	if (is_non_digit(argv) == 0 || \
		dup_check(argv) == 0 || max_checker(argv) == 0)
	{
		if (flag != 0)
			free_tmp_argv(argv, info);
		write(2, "Error\n", 6);
		return (0);
	}
	return (1);
}

int	small_case(t_Basic_info *info, int flag, char *argv[])
{
	if (info->argc <= 6)
	{
		small_center(info->a, info->b, info);
		if (flag != 0)
			free_tmp_argv(argv, info);
		free(info->sorted_array);
		return (0);
	}
	return (1);
}
