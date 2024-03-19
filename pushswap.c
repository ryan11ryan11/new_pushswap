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

int	ans_check(Stack *full, Stack *empty, int *s, int type)
{
	static int	i;

	while (s[i] == full->data[full->top])
	{
		element_move(empty, full, type); // full 꼭대기 있는걸 empty에 박음
		i ++ ;
		printf("1a->data[a->top] :: %d		s[%d] :: %d\n", full->data[full->top],i, s[i]);
	}
	printf("2a->data[a->top] :: %d		s[%d] :: %d\n", full->data[full->top],i, s[i]);
	return (i);
}

int	complete_move(Stack *full, Basic_info *info, int type)
{
	int	i;

	i = 0;
	while (full->data[full->top] == info->sorted_array[i])
	{
		stack_up(full, type);
		i ++ ;
	}
	info->sorted_number = i;
	return (i);
}


int	btoa(Stack *a, Stack *b, int type, Basic_info *info)
{
	int	pivot_value;
	int	b_num;
	int	half_pivot;
	
	half_pivot = (b->top - info->sorted_number)/2 + info->sorted_number;
	pivot_value = info->sorted_array[half_pivot];
	b_num = b->top; // 정렬해야 할 숫자의 갯수
	printf("btoa started\n");
	printf("sorted_number:%d",info->sorted_number);
	printf("\n\nwill be applied:pivot_value = %d half_pivot = %d b_num::%d\n\n",pivot_value, half_pivot, b_num);
	stack_check(a,b,info->sorted_array,info->argc);
	while (b_num - info->sorted_number >= 0)
	{
		printf("btop:%d\n", b->data[b->top]);
		if (b->data[b->top] == info->sorted_array[info->sorted_number])
		{
			info->sorted_number ++ ;
			stack_up(b, type);
		}
		if (b->data[b->top] > pivot_value)
			element_move(a, b, type);
		else
			stack_up(b, type);
		b_num -- ;
	}
	return (0);
}


int	atob(Stack *a, Stack *b, int type, Basic_info *info)
{
	int	pivot_value;
	int	a_num;
	int	half_pivot;
	
	half_pivot = a->top/2;
	pivot_value = info->sorted_array[half_pivot];
	a_num = a->top; // 정렬해야 할 숫자의 갯수
	printf("\n\nwill be applied:pivot_value = %d half_pivot = %d a_num::%d\n\n",pivot_value, half_pivot, a_num);
	stack_check(a,b,info->sorted_array,info->argc);
	if (half_pivot == 0)
	{
		element_move(b, a, type); // type = b 이면 pb, a면 pa
		printf("##FINISHED##\n");
		return (1);
	}
	while (a_num >= 0)
	{
		if (a->data[a->top] < pivot_value)
			stack_up(a, type);
		else
			element_move(b, a, type);
		// if (b->data[b->top] > b->data[b->top - 1])
		// 	swap(b, 'b');
		a_num -- ;
	}
	return (0);
}


// typedef struct	basic_info
// {
// 	int	*sorted_array;
// 	Stack *a;
// 	Stack *b;
// 	int	argc;
// 	int pivot_index;
// }Basic_info;

int	main(int argc, char *argv[])
{
	Basic_info	info;
	Stack	a;
	Stack	b;
	int		sorted_until;
	int		type;

	if (argc <= 1) // 나중에 숫자 아닌 다른거 들어올 때 규칙 제정하기
		return (0);
	stack_init(&a);
	stack_init(&b);
	info.a = &a;
	info.b = &b;
	info.sorted_array = arr_maker(argc, argv);
	info.pivot_index = (argc - 1) / 2;
	info.argc = argc;
	printf("pivot_index = %d\n", info.pivot_index);
	stack_maker(info.argc, info.a, info.sorted_array);
	quicksort(info.sorted_array, 0, info.argc - 2); 
	stack_check(info.a,info.b,info.sorted_array,info.argc);

	type = 'a';
	while (atob(&a, &b, type, &info) != 1)
		;
	stack_check(info.a,info.b,info.sorted_array,info.argc);
	printf("here\n");
	sorted_until = complete_move(&b, &info, 'b');
	btoa(&a, &b, type, &info);
	// while (btoa(&a, &b, type, &info) != 1)
	// 	;
	printf("sorted_until:%d\n",sorted_until);
	stack_check(&a,&b,info.sorted_array,argc);

	// make하고
	// cc돌리고
	
}