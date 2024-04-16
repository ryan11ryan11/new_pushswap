/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:45:20 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/16 15:27:08 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	stack_init(t_Stack *a)
{
	a->top = -1;
}

int	pop(t_Stack *a)
{
	if (is_empty(a) == 1)
		return (0);
	else
	{
		a->top --;
		return (a->data[a->top]);
	}
}

int	push(t_Stack *a, int i)
{
	if (is_full(a) == 1)
		return (0);
	else
	{
		a->top ++ ;
		a->data[a->top] = i;
		return (a->data[a->top]);
	}
}

int	is_empty(t_Stack *a)
{
	if (a->top == -1)
		return (1);
	else
		return (0);
}

int	is_full(t_Stack *a)
{
	if (a->top > 1000 - 1)
		return (1);
	else
		return (0);
}
