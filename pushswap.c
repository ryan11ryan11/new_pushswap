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

int	complete_move(Stack *empty, Stack *full, int *s, int type)
{
	int	i;

	i = 0;
	while (full->data[full->top] == s[i])
	{
		element_move(empty, full, type);
		i ++ ;
	}
	return (i);
}

void	pivot_quicksort(Stack *full, Stack *empty, int pivot_index, int *s, int type, int argc)
{
	int	pivot_value;
	int	a_num;
	
	pivot_value = s[pivot_index];
	a_num = full->top; // 정렬해야 할 숫자의 갯수
	printf("\n\nwill be applied:pivot_value = %d pivot_index = %d a_num::%d\n\n",pivot_value, pivot_index, a_num);
	stack_check(full,empty,s,argc);
	if (pivot_index == 0)
	{
		element_move(empty, full, type); // type = b 이면 pb, a면 pa
		printf("##FINISHED##\n");
		return ;
	}
	while (a_num >= 0)
	{
		if (full->data[full->top] < pivot_value)
			stack_up(full, type);
		else
			element_move(empty, full, type);
		if (empty->data[empty->top] > empty->data[empty->top - 1])
			swap(empty, 'b');
		a_num -- ;
	}
	pivot_quicksort(full, empty, pivot_index/2, s, type, argc);
	//pivot_quicksort(empty, full, (pivot_index + full->top)/2, s, type, argc);
}

int	main(int argc, char *argv[])
{
	Basic_info	info;
	int		sorted_until;
	int		type;

	if (argc <= 1) // 나중에 숫자 아닌 다른거 들어올 때 규칙 제정하기
		return (0);
	info.sorted_array = arr_maker(argc, argv);
	info.pivot_index = (argc - 1) / 2;
	info.argc = argc;
	printf("pivot_index = %d\n", info.pivot_index);
	stack_init(info.a);
	stack_init(info.b);
	stack_maker(info.argc, info.a, info.sorted_array);
	quicksort(info.sorted_array, 0, info.argc - 2); 
	stack_check(info.a,info.b,info.sorted_array,info.argc);

	// type = 'a';
	// pivot_quicksort(&a, &b, pivot_index, s, type, argc);
	// sorted_until = complete_move(&a, &b, s, 'b');
	// printf("%d\n", sorted_until);
	// stack_check(&a,&b,s,argc);
}