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

void	test(t_list *a_order)
{
	int	i;

	i = 0;
	// while(a_order != NULL)
	// {
	// 	printf("%s\n", a_order->content);
	// 	a_order = a_order->next;
	// }
	while(a_order != NULL)
	{
		a_order = a_order->next;
		i ++ ;
	}
	printf("order number :: %d\n", i);
}

void	center(char *order, int type) /// 나중에 메모리 누수 관리
{
	static t_list *a_order;
	static t_list *b_order;
	
	if (type == 'a')
	{
		//printf("%s\n", order);
		ft_lstadd_back(&a_order, ft_lstnew(order));
		ft_lstadd_back(&b_order, ft_lstnew("skip"));
	}
	if (type == 'b')
	{
		//printf("%s\n", order);
		ft_lstadd_back(&a_order, ft_lstnew("skip"));
		ft_lstadd_back(&b_order, ft_lstnew(order));
	}
	test(a_order);
}

void	swap(Stack *s, int type)
{
	int	temp;

	printf("swap\n");
	if (s->top < 1)
		return ;
	temp = s->data[s->top];
	s->data[s->top] = s->data[s->top - 1];
	s->data[s->top - 1] = temp;
	if (type == 'a')
		center("sa",'a');
	if (type == 'b')
		center("sb",'b');
}

void	element_move(Stack *a, Stack *b, int type)
{
	push(a, b->data[b->top]); // 뒤에있는 b 를 빼서 a에 꼭대기에 넣음
	printf("elementmove %d is moved\n", b->data[b->top]);
	pop(b);
	if (type == 'a')
		center("pa",'a');
	if (type == 'b')
		center("pb",'b');
}

void	stack_up(Stack *s, int type)
{
	int	i; // ra
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
	    center("ra",'a');
    if (type == 'b')
        center("rb",'b');
}


void	stack_down(Stack *s, int type)
{
	int	i; // rra
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
	    center("rra",'a');
    if (type == 'b')
        center("rrb",'b');
}
