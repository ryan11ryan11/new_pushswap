/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:17:43 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/16 15:26:17 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	sorted_arr_scan(t_Stack *full, t_Basic_info *info)
{
	int	i;
	int	scan;

	scan = full->top;
	i = 0;
	while (full->data[scan] != info->sorted_array[i] && scan >= 0)
		scan -- ;
	while (full->data[scan] == info->sorted_array[i] && scan >= 0)
	{
		scan -- ;
		i ++ ;
	}
	if (i <= 1)
	{
		info->sorted_number = 0;
		return (0);
	}
	info->sorted_number = i;
	info->head = info->sorted_array[0];
	info->tail = info->sorted_array[i - 1];
	return (i);
}

void	init_organize(t_Stack *a, t_Stack *b, t_Basic_info *info)
{
	int	rewind;
	int	set;

	set = a->top;
	rewind = 0;
	while (set >= 0)
	{
		if (a->data[a->top] > info->sorted_array[1])
			stack_up(a, 'a');
		else
		{
			element_move(b, a, 'b');
			rewind ++ ;
		}
		set -- ;
	}
	while (rewind > 0)
	{
		element_move (a, b, 'a');
		rewind -- ;
	}
	if (a->data[a->top] > a->data[a->top - 1])
		swap (a, 'a');
	while (a->data[0] != info->sorted_array[1])
		stack_up (a, 'a');
}

int	is_at_a(t_Stack *a, int target)
{
	int	i;

	i = a->top;
	while (i >= 0)
	{
		if (a->data[i] == target)
			return (1);
		i -- ;
	}
	return (0);
}

void	organize(t_Stack *a, t_Stack *b, int unorganized, t_Basic_info *info)
{
	int	rewind;

	rewind = 0;
	if (unorganized == a->top + 1)
		init_organize(a, b, info);
	sorted_arr_scan(a, info);
	unorganized = (a->top + 1) + rewind - info->sorted_number;
	while (unorganized != 0)
	{
		if (is_at_a(a, info->sorted_array[info->sorted_number]) == 1)
		{
			while (a->data[a->top] != info->sorted_array[info->sorted_number])
				element_move(b, a, 'b');
		}
		if (is_at_a(a, info->sorted_array[info->sorted_number]) == 0)
		{
			while (a->data[a->top] != info->sorted_array[info->sorted_number])
				element_move(a, b, 'a');
		}
		if (a->data[a->top] == info->sorted_array[info->sorted_number])
			stack_up(a, 'a');
		sorted_arr_scan(a, info);
		unorganized -- ;
	}
	return ;
}

int	where_is(t_Stack *a, int target)
{
	int	i;

	i = 0;
	while (a->data[i] != target)
		i++;
	return (i);
}
