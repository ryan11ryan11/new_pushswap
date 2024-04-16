/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:39:28 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/16 15:39:20 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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
		stack_up(a, 'a');
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

void	case_five(t_Stack *a, t_Stack *b, t_Basic_info *info, int argc)
{
	int	i;

	i = 5;
	if (argc == 4)
	{
		case_three(a);
		return ;
	}
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
