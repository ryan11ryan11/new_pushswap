/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:50:56 by junhhong          #+#    #+#             */
/*   Updated: 2024/03/13 18:47:26 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	swap(Stack *s, int type)
{
	int	temp;

	if (s->top < 1)
		return ;
	temp = s->data[s->top];
	s->data[s->top] = s->data[s->top - 1];
	s->data[s->top - 1] = temp;
	if (type == 'a')
		ft_putstr_fd("sa\n",1);
	if (type == 'b')
		ft_putstr_fd("sb\n",1);
}

void	element_move(Stack *a, Stack *b, int type)
{
	push(a, b->data[b->top]);
	pop(b);
	if (type == 'a')
		ft_putstr_fd("pa\n",1);
	if (type == 'b')
		ft_putstr_fd("pb\n",1);
}

void	stack_up(Stack *s, int type)
{
	int	i;
	int	temp;

	if (s->top < 1)
		return ;
	i = s->top;
	temp = s->data[s->top];
	while(i > 0)
	{
		s->data[i] = s->data[i - 1];
		i -- ;
	}
	s->data[0] = temp;
	if (type == 'a')
		ft_putstr_fd("ra\n",1);
	if (type == 'b')
		ft_putstr_fd("rb\n",1);
}

void	stack_down(Stack *s, int type)
{
	int	i;
	int	temp;

	if (s->top < 1)
		return ;
	i = 0;
	temp = s->data[0];
	while(i <= s->top - 1)
	{
		s->data[i] = s->data[i + 1];
		i ++ ;
	}
	s->data[s->top] = temp;
	if (type == 'a')
		ft_putstr_fd("rra\n",1);
	if (type == 'b')
		ft_putstr_fd("rrb\n",1);
}
