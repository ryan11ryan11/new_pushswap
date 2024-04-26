/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:50:56 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/26 18:28:36 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	swap(t_Stack *s, int type)
{
	int	temp;

	if (s->top < 1)
		return ;
	temp = s->data[s->top];
	s->data[s->top] = s->data[s->top - 1];
	s->data[s->top - 1] = temp;
	if (type == 'a')
		write(1, "sa\n", 3);
	if (type == 'b')
		write(1, "sb\n", 3);
}

void	element_move(t_Stack *a, t_Stack *b, int type)
{
	push(a, b->data[b->top]);
	pop(b);
	if (type == 'a')
		write(1, "pa\n", 3);
	if (type == 'b')
		write(1, "pb\n", 3);
}

void	stack_up(t_Stack *s, int type)
{
	int	i;
	int	temp;

	if (s->top < 1)
		return ;
	i = s->top;
	temp = s->data[s->top];
	while (i > 0)
	{
		s->data[i] = s->data[i - 1];
		i -- ;
	}
	s->data[0] = temp;
	if (type == 'a')
		write(1, "ra\n", 3);
	if (type == 'b')
		write(1, "rb\n", 3);
}

void	stack_down(t_Stack *s, int type)
{
	int	i;
	int	temp;

	if (s->top < 1)
		return ;
	i = 0;
	temp = s->data[0];
	while (i <= s->top - 1)
	{
		s->data[i] = s->data[i + 1];
		i ++ ;
	}
	s->data[s->top] = temp;
	if (type == 'a')
		write(1, "rra\n", 4);
	if (type == 'b')
		write(1, "rrb\n", 4);
}
