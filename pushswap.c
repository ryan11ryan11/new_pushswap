/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:59:30 by junhhong          #+#    #+#             */
/*   Updated: 2024/04/16 16:31:09 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

// void	stack_check(Stack *a, Stack *b, int *s, int argc)
// {
// 	int	j;
// 	int	i;
// 	int	k;

// 	k = 0;
// 	i = a->top;
// 	j = b->top;
// 	printf("sorted int arr::");
// 	while (k < argc - 1)
// 	{
// 		printf("%d,", s[k]);
// 		k ++ ;
// 	}
// 	printf("\n");
// 	while (j >= 0 || i >= 0)
// 	{
// 		while (i > j && i >= 0)
// 		{
// 			printf("1a[%d]%d		b[%d]-\n",i, a->data[i],i);
// 			i -- ;
// 		}
// 		while (j > i && j >= 0)
// 		{
// 			printf("2a[%d]-		b[%d]%d\n",i,j,b->data[j]);
// 			j -- ;
// 		}
// 		while(i >= 0 && j >= 0)
// 		{
// 			printf("3a[%d]%d		b[%d]%d\n",i,a->data[i],j,b->data[j]);
// 			i -- ;
// 			j -- ;
// 		}
// 	}
// }

// void	first_three(int argc, Stack *a, Stack *b)
// {
// 	int	piv1;
// 	int	piv2;
// 	int	set;

// 	set = a->top;
// 	piv1 = (argc - 1) / 3;
// 	piv2 = (argc - 1) / 3 * 2;
// 	while (set != 0)
// 	{
// 		if (a->data[a->top] < piv1)
// 			stack_up(a, 'a');
// 		if (a->data[a->top] >= piv1 && a->data[a->top] <= piv2)
// 			element_move(b, a, 'b');
// 		if (a->data[a->top] > piv2)
// 		{
// 			element_move(b, a, 'b');
// 			stack_up(b, 'b');
// 		}
// 		set -- ;
// 	}
// }

void	start(t_Basic_info *info, t_Stack *a, t_Stack *b, char *argv[])
{
	stack_init(a);
	stack_init(b);
	info->first_half = 0;
	info->a = a;
	info->b = b;
	info->sorted_number = 0;
	info->sorted_array = arr_maker(info->argc, argv);
	info->pivot_index = (info->argc - 1) / 4 * 3;
	stack_maker(info->argc, info->a, info->sorted_array);
	quicksort(info->sorted_array, 0, info->argc - 2);
}

void	main_sort(t_Basic_info *info)
{
	atob(info, info->pivot_index, info->a->data[0]);
	sorted_arr_scan(info->a, info);
	while (info->b->top > 1)
	{
		info->pivot_index = (info->argc - info->sorted_number) / 2 \
		+ info->sorted_number - 1;
		simple_btoa(info->a, info->b, info);
		info->pivot_index = info->sorted_array[info->sorted_number \
		+ (info->a->top - info->sorted_number) / 2];
		atob(info, info->pivot_index, info->a->data[0]);
		sorted_arr_scan(info->a, info);
	}
}

int	max_checker(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_new_atoi(argv[i]) > 2147483647 || \
			ft_new_atoi(argv[i]) < -2147483647)
			return (0);
		i ++ ;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_Basic_info	info;
	t_Stack			a;
	t_Stack			b;

	info.argc = argc;
	if (is_non_digit(argv) == 0 || dup_check(argv) == 0 || \
		max_checker(argv) == 0)
	{
		ft_putstr_fd("ERROR\n", 1);
		return (0);
	}
	if (argc <= 2)
		return (0);
	start(&info, &a, &b, argv);
	if (argc == 4 || argc == 6)
		case_five(&a, &b, &info, argc);
	main_sort(&info);
	final(&a, &b);
	free(info.sorted_array);
}
