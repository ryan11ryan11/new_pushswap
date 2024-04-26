/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:32:08 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/26 18:26:36 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	atob(t_Basic_info *info, int pivot_index, int end)
{
	int	pivot_value;

	pivot_value = info->sorted_array[pivot_index];
	if (sorted_arr_scan(info->a, info) == info->a->top + 1)
		return (0);
	if (info->a->top + 1 - info->sorted_number <= 33)
	{
		sorted_arr_scan(info->a, info);
		organize (info->a, info->b, info->a->top + 1 \
		- info->sorted_number, info);
		return (0);
	}
	if (sorted_arr_scan(info->a, info) < 1)
		end = info->a->data[0];
	else
		end = info->a->data[where_is(info->a, info->sorted_array[0]) + 1];
	down_or_b(info, end, pivot_value);
	sorted_arr_scan(info->a, info);
	while (info -> sorted_number > 1 && info -> tail != info->a->data[0])
		stack_down(info->a, 'a');
	sorted_arr_scan(info->a, info);
	atob(info, info->sorted_number + (info->a->top + 1 - info->sorted_number) \
		/ 2 - 1, info->a->data[0]);
	btoa(info->a, info->b, info, pivot_index);
	return (0);
}

int	btoa(t_Stack *a, t_Stack *b, t_Basic_info *info, int pivot_index)
{
	int	sent;
	int	prv_btop;

	sent = 0;
	prv_btop = b->data[b->top];
	sorted_arr_scan(a, info);
	if (b->data[b->top] > info->sorted_array[pivot_index])
	{
		return (0);
	}
	while (a->data[a->top] != info->sorted_array[pivot_index])
	{
		element_move(a, b, 'a');
		sent ++ ;
	}
	if (sent / 2 == 0)
		sent = 2;
	atob (info, info->sorted_number + (sent / 2 - 1), prv_btop);
	return (0);
}

void	simple_btoa(t_Stack *a, t_Stack *b, t_Basic_info *info)
{
	int	times;
	int	rewind;

	rewind = 0;
	times = b->top;
	while (times >= 0)
	{
		if (b->data[b->top] < info->sorted_array[info->pivot_index])
			element_move(a, b, 'a');
		else
			stack_up(b, 'b');
		times -- ;
		rewind ++ ;
	}
	info->pivot_index = info->sorted_number + \
	(a->top + 1 - info->sorted_number) / 2;
}

void	final(t_Stack *a, t_Stack *b)
{
	int	i;

	i = 0;
	if (b->top >= 1 && b->data[b->top] < b->data[b->top - 1])
		swap(b, 'b');
	while (b->top != -1)
	{
		element_move (a, b, 'a');
		i ++ ;
	}
	while (i > 0)
	{
		stack_up(a, 'a');
		i -- ;
	}
}
