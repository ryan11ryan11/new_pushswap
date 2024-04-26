/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:39:28 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/22 11:17:19 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	case_two(t_Stack *a)
{
	if (a->data[1] > a->data[0])
		swap(a, 'a');
}

void	case_three(t_Stack *a)
{
	if (a->data[2] < a->data[1] && a->data[1] > a->data[0] \
		&& a->data[2] < a->data[0])
	{
		stack_down(a, 'a');
		swap(a, 'a');
	}
	else if (a->data[2] < a->data[1] && a->data[1] > a->data[0] \
		&& a->data[2] > a->data[0])
		stack_down(a, 'a');
	else if (a->data[2] > a->data[1] && a->data[1] < a->data[0] \
		&& a->data[2] < a->data[0])
		swap(a, 'a');
	else if (a->data[2] > a->data[1] && a->data[1] > a->data[0] \
		&& a->data[2] > a->data[0])
	{
		swap(a, 'a');
		stack_down(a, 'a');
	}
	else if (a->data[2] > a->data[1] && a->data[1] < a->data[0] \
		&& a->data[2] > a->data[0])
		stack_up(a, 'a');
}

void	case_four(t_Stack *a, t_Stack *b, t_Basic_info *info)
{
	int	i;

	i = 4;
	while (i > 0)
	{
		if (a->data[a->top] <= info->sorted_array[1])
			element_move(b, a, 'b');
		else
			stack_up(a, 'a');
		i -- ;
	}
	if (a->data[a->top] > a->data[a->top - 1])
		swap(a, 'a');
	if (b->data[b->top] < b->data[b->top - 1])
		swap(b, 'b');
	i = 2;
	while (i > 0)
	{
		element_move(a, b, 'a');
		i -- ;
	}
}

void	case_five(t_Stack *a, t_Stack *b, t_Basic_info *info)
{
	int	i;

	i = 5;
	while (i > 0)
	{
		if (a->data[a->top] == info->sorted_array[0] || \
			a->data[a->top] == info->sorted_array[1])
			element_move (b, a, 'b');
		else
			stack_up(a, 'a');
		i -- ;
	}
	if (b->data[b->top] < b->data[b->top - 1])
		swap(b, 'b');
	case_three(a);
	element_move (a, b, 'a');
	element_move (a, b, 'a');
}

void	small_center(t_Stack *a, t_Stack *b, t_Basic_info *info)
{
	if (sorted_arr_scan(a, info) == a->top + 1)
		return ;
	if (info->argc == 6)
		case_five(a, b, info);
	if (info->argc == 4)
		case_three(a);
	if (info->argc == 5)
		case_four(a, b, info);
	if (info->argc == 3)
		case_two(a);
}
