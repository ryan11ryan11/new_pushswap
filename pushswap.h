/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:39:45 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/16 16:07:42 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct stack
{
	int	data[500];
	int	top;
}	t_Stack;

typedef struct stackstructure
{
	int	target;
	int	standard;
	int	prv_target;
	int	mid;
	int	target_location;
}	t_Stackstructure;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct basic_info
{
	int		*sorted_array;
	t_Stack	*a;
	t_Stack	*b;
	int		argc;
	int		pivot_index;
	int		sorted_number;
	int		head;
	int		tail;
	int		first_half;
}	t_Basic_info;

// presort.c
void		ab_swap(int *a, int *b);
void		quicksort(int s[], int start, int end);
int			*arr_maker(int argc, char *argv[]);
void		stack_maker(int argc, t_Stack *a, int *arr);

//organizer.c
int			sorted_arr_scan(t_Stack *full, t_Basic_info *info);
void		init_organize(t_Stack *a, t_Stack *b, t_Basic_info *info);
int			is_at_a(t_Stack *a, int target);
void		organize(t_Stack *a, t_Stack *b, \
				int unorganized, t_Basic_info *info);
int			where_is(t_Stack *a, int target);

//stack_movement
int			atob(t_Basic_info *info, int pivot_index, int end);
int			btoa(t_Stack *a, t_Stack *b, t_Basic_info *info, int pivot_value);
void		simple_btoa(t_Stack *a, t_Stack *b, t_Basic_info *info);
void		final(t_Stack *a, t_Stack *b);

//utils
void		pivot_buttom(t_Stack *a, int pivot_value);
void		down_or_b(t_Basic_info *info, int end, int pivot_value);
int			dup_check(char *argv[]);
int			is_non_digit(char *argv[]);

//small_argc
void		case_three(t_Stack *a);
void		case_five(t_Stack *a, t_Stack *b, t_Basic_info *info, int argc);

//new_atoi
long long	ft_new_atoi(const char *nptr);

int			is_empty(t_Stack *a);
int			is_full(t_Stack *a);
int			push(t_Stack *a, int i);
int			pop(t_Stack *a);
void		stack_init(t_Stack *a);
void		ft_putstr_fd(char *s, int fd);
void		a_sort(t_Stack *a, int *s, int argc);
void		stack_check(t_Stack *a, t_Stack *b, int *s, int argc);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);

void		swap(t_Stack *s, int type);
void		element_move(t_Stack *a, t_Stack *b, int type);
void		stack_up(t_Stack *s, int type);
void		stack_down(t_Stack *s, int type);

#endif