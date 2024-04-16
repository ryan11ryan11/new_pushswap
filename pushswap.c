/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:59:30 by junhhong          #+#    #+#             */
/*   Updated: 2024/03/13 19:04:37 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	ab_swap(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	quicksort(int s[], int start, int end)
{
	int	left;
	int	right;
	int	pivot;

	pivot = start;
	left = pivot + 1;
	right = end ;
	if (start == end)
		return ;
	while (left <= right)
	{
		while (s[left] < s[pivot] && left <= end)
			left ++ ;
		while (s[right] > s[pivot] && right >= start)
			right -- ;
		if (left < right)
			ab_swap(&s[left], &s[right]);
	}
	if (left > right)
		ab_swap(&s[right], &s[pivot]);
	if (start < right)
		quicksort(s, start, right - 1);
	if (left < end)
		quicksort(s, right + 1, end);
}

int	*arr_maker(int argc, char *argv[]) // 나중에 free 필수!
{
	int	*arr;
	int	j;

	j = 0;
	arr = (int *)malloc(sizeof(int) * (argc - 1)); // argc = 10
	while(j <= argc - 2) // j <= 8
	{
		arr[j] = ft_atoi(argv[j + 1]);
		j ++ ;
	}
	return	arr;
}

void	stack_maker(int argc, Stack *a, int *arr)
{
	while(argc > 1)
	{
		push(a, arr[argc - 2]);
		argc -- ;	
	}
}

void	stack_check(Stack *a, Stack *b, int *s, int argc)
{
	int	j;
	int	i;
	int	k;

	k = 0;
	i = a->top;
	j = b->top;
	printf("sorted int arr::");
	while(k < argc - 1)
	{
		printf("%d,", s[k]);
		k ++ ;
	}
	printf("\n");
	while (j >= 0 || i >= 0)
	{
		while(i > j && i >= 0)
		{
			printf("1a[%d]%d		b[%d]-\n",i, a->data[i],i);
			i -- ;
		}
		while (j > i && j >= 0)
		{
			printf("2a[%d]-		b[%d]%d\n",i,j,b->data[j]);
			j -- ;
		}
		while(i >= 0 && j >= 0)
		{
			printf("3a[%d]%d		b[%d]%d\n",i,a->data[i],j,b->data[j]);
			i -- ;
			j -- ;
		}
	}
}

int	sorted_arr_scan(Stack *full, Basic_info *info)
{
	int	i;
	int	scan;

	scan = full->top;
	i = 0;
	while (full->data[scan] != info->sorted_array[i] && scan >= 0)
		scan -- ;
	while (full->data[scan] == info->sorted_array[i] && scan >= 0)
	{
		scan -- ;
		i ++ ;
	}
	if (i <= 1)
	{
		info->sorted_number = 0;
		return (0);
	}
	info->sorted_number = i;
	info->head = info->sorted_array[0];
	info->tail = info->sorted_array[i - 1];
	return (i);
}

void	init_organize(Stack *a, Stack *b, Basic_info *info)
{
	int	rewind;
	int	set;

	set = a->top;
	rewind = 0;
	while (set >= 0)
	{
		if (a->data[a->top] > info->sorted_array[1])
			stack_up(a,'a');
		else
		{
			element_move(b,a,'b');
			rewind ++ ;
		}
		set -- ;
	}
	while (rewind > 0)
	{
		element_move(a,b,'a');
		rewind -- ;
	}
	if (a->data[a->top] > a->data[a->top - 1])
		swap(a,'a');
	while (a->data[0] != info->sorted_array[1])

		stack_up(a,'a');
}

int	is_at_a(Stack *a, int target)
{
	int	i;

	i = a->top;
	while (i >= 0)
	{
		if (a->data[i] == target)
			return (1);
		i -- ; 
	}
	return (0);
}

void	organize(Stack *a, Stack *b, int unorganized, Basic_info *info)
{
	int	rewind;

	rewind = 0;
	if (unorganized == a->top + 1)
		init_organize(a,b,info);
	sorted_arr_scan(a,info);
	unorganized = (a->top + 1) + rewind - info->sorted_number;
	while (unorganized != 0)
	{
		if (is_at_a(a,info->sorted_array[info->sorted_number]) == 1)
		{
			while (a->data[a->top] != info->sorted_array[info->sorted_number])
				element_move(b,a,'b');
		}
		if (is_at_a(a,info->sorted_array[info->sorted_number]) == 0)
		{
			while (a->data[a->top] != info->sorted_array[info->sorted_number])
				element_move(a,b,'a');
		}
		if (a->data[a->top] == info->sorted_array[info->sorted_number])
			stack_up(a,'a');
		sorted_arr_scan(a,info);
		unorganized -- ;
	}
	return ;
}

int	where_is(Stack *a, int target)
{
	int	i;

	i = 0;
	while (a->data[i] != target)
		i++;
	return (i);
}

void	pivot_buttom(Stack *a, int pivot_value)
{
	int	loc_pivot_value;

	loc_pivot_value = where_is(a, pivot_value);
	if (loc_pivot_value > a->top/2)
	{
		while (a->data[0] != pivot_value)
			stack_up(a,'a');
	}
	if (loc_pivot_value <= a->top/2 && a->data[0] != pivot_value)
	{
		while (a->data[0] != pivot_value)
			stack_down(a,'a');
	}
}

void first_three(int argc, Stack *a, Stack *b)
{
	int	piv1;
	int	piv2;
	int	set;

	set = a->top;
	piv1 = (argc - 1) / 3;
	piv2 = (argc - 1) / 3 * 2;
	while (set != 0)
	{
		if (a->data[a->top] < piv1)
			stack_up(a,'a');
		if (a->data[a->top] >= piv1 && a->data[a->top] <= piv2)
			element_move(b,a,'b');
		if (a->data[a->top] > piv2)
		{
			element_move(b,a,'b');
			stack_up(b,'b');
		}
		set -- ;
	}
}

void	down_or_b(Stack *a, Stack *b, Basic_info *info, int end, int pivot_value)
{
	int flag;

	flag = 0;
	while (flag == 0) // 피봇밸류보다 작으면 밑으로 보내고 크면 스택b로 옮긴다
	{
		sorted_arr_scan(a,info);
		if (a->data[a->top] == end)
			flag = 1;
		if (a->data[a->top] <= pivot_value)
			stack_up(a, 'a');
		else
			element_move (b, a, 'b');
	}
	if (a->data[0] != pivot_value && a->top + 1 != info->sorted_number) // 피봇값을 맨 밑으로 보낸다, 최적화필요, 위로보내아래로보내
		pivot_buttom(a,pivot_value);
	if (a->data[0] == pivot_value && a->top + 1 != info->sorted_number) // 피봇값을 맨 위로 보낸 뒤 스택b로 이동시킨다
	{
		stack_down(a, 'a');
		element_move(b, a, 'b');
	}
}

int	atob(Stack *a, Stack *b, Basic_info *info, int pivot_index, int end)
{
	int	pivot_value;

	pivot_value = info->sorted_array[pivot_index];
	if(sorted_arr_scan(a,info) == a->top + 1)
		return (0);
	if (a->top + 1 - info->sorted_number <= 30)
	{
		sorted_arr_scan(a,info);
		organize (a, b, a->top + 1 - info->sorted_number, info);
		return (0);
	}
	if (sorted_arr_scan(a,info) < 1)
		end = a->data[0];
	else
		end = a->data[where_is(a,info->sorted_array[0]) + 1];
	down_or_b(a,b,info,end,pivot_value);
	sorted_arr_scan(a,info);
	while (info -> sorted_number > 1 && info -> tail != a->data[0]) // 리와인드
		stack_down(a,'a');
	atob(a,b,info,info->sorted_number - 1 + (a->top - info->sorted_number + 1)/2,a->data[0]);
	btoa(a,b,info,pivot_value);
	return (0);
}

int	btoa(Stack *a, Stack *b, Basic_info *info, int pivot_value)
{
	int	pivot_index;
	int	sent;
	int	prv_btop;

	sent = 0;
	prv_btop = b->data[b->top];
	sorted_arr_scan(a,info);
	if (b->data[b->top] > pivot_value) // btop의 밸류가 피봇밸류 이상일경우 종료
		return (0);
	while (a->data[a->top] != pivot_value) // 피봇밸류만큼 b에서 a로 끌어옴
	{
		element_move(a, b, 'a');
		sent ++ ;
	}
	if (sent/2 == 0)
		sent = 2;
	pivot_index = info->sorted_array[info->sorted_number] + sent/2 - 1; // 피봇 재설정
	atob (a,b,info,pivot_index,prv_btop);
	return (0);
}

void	simple_btoa(Stack *a, Stack *b, Basic_info *info)
{
	int	times;

	times = b->top;
	while (times >= 0)
	{
		if (b->data[b->top] < info->sorted_array[info->pivot_index])
			element_move(a, b, 'a');
		else
			stack_up(b, 'b');
		times -- ;
	}
}

void	start(Basic_info *info, Stack *a, Stack *b,int argc,char *argv[])
{
	stack_init(a);
	stack_init(b);
	info->first_half = 0;
	info->a = a;
	info->b = b;
	info->sorted_number = 0;
	info->sorted_array = arr_maker(argc, argv);
	info->pivot_index = (argc - 1) / 4 * 3;
	info->argc = argc;
	stack_maker(info->argc, info->a, info->sorted_array);
	quicksort(info->sorted_array, 0, info->argc - 2); 
}

int	is_non_digit(char *argv[])
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '+' || argv[i][j] == '-')
				j ++ ;
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j ++ ;
		}
		j = 0;
		i ++ ;
	}
	return (1);
}

int	dup_check(char *argv[])
{
	int	i;
	int	j;
	int	target;
	int	match;

	match = 0;
	j = 1;
	i = 1;
	while (argv[j] != NULL)
	{
		target = ft_atoi(argv[j]);
		while (argv[i] != NULL)
		{
			if (ft_atoi(argv[i]) == target)
				match ++ ;
			if (match > 1)
				return (0);
			i ++ ;
		}
		match = 0;
		i = 1;
		j ++ ;
	}
	return (1);
}

int	max_check(char *argv[])
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < -2147483647)
		{
			return (0);
		}
		i ++ ;
	}
	return (1);
}

void	case_three(Stack *a)
{
	if (a->data[2] < a->data[1] && a->data[1] > a->data[0] && a->data[2] < a->data[0])
	{
		stack_down(a,'a');
		swap(a,'a');
	}
	else if (a->data[2] < a->data[1] && a->data[1] > a->data[0] && a->data[2] > a->data[0])
		stack_up(a,'a');
	else if (a->data[2] > a->data[1] && a->data[1] < a->data[0] && a->data[2] < a->data[0])
		swap(a,'a');
	else if (a->data[2] > a->data[1] && a->data[1] > a->data[0] && a->data[2] > a->data[0])
	{
		swap(a,'a');
		stack_down(a,'a');
	}
	else if (a->data[2] > a->data[1] && a->data[1] < a->data[0] && a->data[2] > a->data[0])
		stack_up(a,'a');
}

void	case_five(Stack *a, Stack *b, Basic_info *info, int argc)
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
		if (a->data[a->top] == info->sorted_array[0] || a->data[a->top] == info->sorted_array[1])
			element_move (b,a,'b');
		else
			stack_up(a,'a');
		i -- ;
	}
	if (b->data[b->top] < b->data[b->top - 1])
		swap(b,'b');
	case_three(a);
	element_move (a,b,'a');
	element_move (a,b,'a');
}

void	final(Stack *a, Stack *b)
{
	int	i;

	i = 0;
	if (b->top >= 1 && b->data[b->top] < b->data[b->top - 1])
		swap(b,'b');
	while(b->top != -1)
	{
		element_move (a,b,'a');
		i ++ ;
	}
	while (i > 0)
	{
		stack_up(a,'a');
		i -- ;
	}
}

int	main(int argc, char *argv[])
{
	Basic_info	info;
	Stack		a;
	Stack		b;

	if (is_non_digit(argv) == 0 || dup_check(argv) == 0)
	{
		ft_putstr_fd("ERROR\n",1);
		return (0);
	}
	if (argc <= 2)
		return (0);
	start(&info, &a, &b, argc, argv);
	if (argc == 4 || argc == 6)
		case_five(&a,&b,&info,argc);
	atob(&a, &b, &info,info.pivot_index,a.data[0]);
	sorted_arr_scan(&a,&info);
	while(b.top > 1)
	{
		info.pivot_index = (argc - info.sorted_number) / 2 + info.sorted_number - 1;
		simple_btoa(&a,&b,&info);
		info.pivot_index = info.sorted_array[info.sorted_number + (a.top - info.sorted_number) / 2];
		atob(&a, &b, &info,info.pivot_index,a.data[0]);
		sorted_arr_scan(&a,&info);
	}
	final(&a,&b);
}