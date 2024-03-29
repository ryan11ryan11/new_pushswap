/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:39:45 by junhhong          #+#    #+#             */
/*   Updated: 2024/03/12 16:47:57 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PUSHSWAP_H_
#define _PUSHSWAP_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100


typedef struct stack
{
	int	data[100];
	int	top;
}Stack;

typedef struct stackstructure
{
	int	target;
	int	standard;
	int	prv_target;
	int	mid;
	int	target_location;
}Stackstructure;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

typedef struct	basic_info
{
	int	*sorted_array;
	Stack *a;
	Stack *b;
	int	argc;
	int pivot_index;
	int	sorted_number;
	int	head;
	int	tail;
	int	first_half;
}Basic_info;


int		is_empty(Stack *a);
int		is_full(Stack *a);
int		push(Stack *a, int i);
int		pop(Stack *a);
void	stack_init(Stack *a);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	a_sort(Stack *a, int *s, int argc);
int		where_is(Stack *a, int target);
void	stack_check(Stack *a, Stack *b, int *s, int argc);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);

void	swap(Stack *s, int type);
void	element_move(Stack *a, Stack *b, int type);
void	stack_up(Stack *s, int type);
void	stack_down(Stack *s, int type);
int	btoa(Stack *a, Stack *b, Basic_info *info, int pivot_value);
int	organize(Stack *a, int how_many);

#endif