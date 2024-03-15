/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:45:20 by junhhong          #+#    #+#             */
/*   Updated: 2024/02/09 15:08:28 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	stack_init(Stack *a)
{
	a->top = -1;
}

int	pop(Stack *a)
{
	if (is_empty(a) == 1)
		return (0);
	else
	{
		a->top --;
		return (a->data[a->top]);
	}
}

int	push(Stack *a, int i)
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

int	is_empty(Stack *a)
{
	if (a->top == -1)
		return (1);
	else
		return (0);
}

int	is_full(Stack *a)
{
	if (a->top > MAX - 1)
		return (1);
	else
		return (0);
}
