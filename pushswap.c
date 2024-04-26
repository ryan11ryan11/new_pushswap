/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:59:30 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/26 18:22:12 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	start(t_Basic_info *info, t_Stack *a, t_Stack *b, char *argv[])
{
	stack_init(a);
	stack_init(b);
	info->first_half = 0;
	info->a = a;
	info->b = b;
	info->sorted_number = 0;
	info->sorted_array = arr_maker(info->argc, argv);
	info->pivot_index = (info->argc - 1) / 4 * 3;
	stack_maker(info->argc, info->a, info->sorted_array);
	quicksort(info->sorted_array, 0, info->argc - 2);
}

int	main_sort(t_Basic_info *info, t_Stack *a)
{
	if (sorted_arr_scan(info->a, info) == a->top + 1)
		return (0);
	atob(info, info->pivot_index, info->a->data[0]);
	while (info->b->top > 1)
	{
		info->pivot_index = (info->argc - info->sorted_number) / 2 \
		+ info->sorted_number - 1;
		simple_btoa(info->a, info->b, info);
		atob(info, info->pivot_index, info->a->data[0]);
		sorted_arr_scan(info->a, info);
	}
	return (1);
}

char	**argc_2(t_Basic_info *info, char *argv[])
{
	char	**arr;
	int		i;

	i = 0;
	info->tmp_arr = ft_strjoin("junhhong ", argv[1]);
	arr = ft_split(info->tmp_arr, ' ');
	while (arr[i] != NULL)
		i ++ ;
	if (i <= 2)
	{
		if (is_non_digit(argv) == 0 || max_checker(argv) == 0)
			write(2, "Error\n", 6);
		freedom(arr);
		free(info->tmp_arr);
		return (NULL);
	}
	info->argc = i;
	return (arr);
}

void	freedom(char *argv[])
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i ++ ;
	while (i >= 0)
	{
		free(argv[i]);
		i -- ;
	}
	free (argv);
}

int	main(int argc, char *argv[])
{
	t_Basic_info	info;
	t_Stack			a;
	t_Stack			b;
	int				flag;

	flag = 0;
	info.argc = argc;
	if (argc == 2)
	{
		argv = argc_2(&info, argv);
		flag ++ ;
		if (!argv || info.argc <= 2)
			return (0);
	}
	if (error_case(argv, flag, &info) == 0)
		return (0);
	start(&info, &a, &b, argv);
	if (small_case(&info, flag, argv) == 0)
		return (0);
	main_sort(&info, &a);
	final(&a, &b);
	if (flag != 0)
		free_tmp_argv(argv, &info);
	free(info.sorted_array);
}
