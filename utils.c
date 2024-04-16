/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:27:22 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/16 16:01:17 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	is_non_digit(char *argv[])
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '+' || argv[i][j] == '-')
				j ++ ;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j ++ ;
		}
		j = 0;
		i ++ ;
	}
	return (1);
}

int	dup_check(char *argv[])
{
	int	i;
	int	j;
	int	target;
	int	match;

	match = 0;
	j = 1;
	i = 1;
	while (argv[j] != NULL)
	{
		target = ft_new_atoi(argv[j]);
		while (argv[i] != NULL)
		{
			if (ft_new_atoi(argv[i]) == target)
				match ++ ;
			if (match > 1)
				return (0);
			i ++ ;
		}
		match = 0;
		i = 1;
		j ++ ;
	}
	return (1);
}

void	pivot_buttom(t_Stack *a, int pivot_value)
{
	int	loc_pivot_value;

	loc_pivot_value = where_is(a, pivot_value);
	if (loc_pivot_value > a->top / 2)
	{
		while (a->data[0] != pivot_value)
			stack_up(a, 'a');
	}
	if (loc_pivot_value <= a->top / 2 && a->data[0] != pivot_value)
	{
		while (a->data[0] != pivot_value)
			stack_down(a, 'a');
	}
}

void	down_or_b(t_Basic_info *info, int end, int pivot_value)
{
	int	flag;

	flag = 0;
	while (flag == 0)
	{
		sorted_arr_scan(info->a, info);
		if (info->a->data[info->a->top] == end)
			flag = 1;
		if (info->a->data[info->a->top] <= pivot_value)
			stack_up(info->a, 'a');
		else
			element_move (info->b, info->a, 'b');
	}
	if (info->a->data[0] != pivot_value && \
		info->a->top + 1 != info->sorted_number)
		pivot_buttom(info->a, pivot_value);
	if (info->a->data[0] == pivot_value && \
		info->a->top + 1 != info->sorted_number)
	{
		stack_down(info->a, 'a');
		element_move(info->b, info->a, 'b');
	}
}
