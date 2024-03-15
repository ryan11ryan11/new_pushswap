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

void	pivot_quicksort(Stack *full, Stack *empty, int pivot_index, int *s, int type, int argc)
{
	int	pivot_value;
	int	a_num;
	
	pivot_value = s[pivot_index];
	a_num = full->top; // 정렬해야 할 숫자의 갯수
	printf("\n\nwill be applied:pivot_value = %d pivot_index = %d a_num::%d\n\n",pivot_value, pivot_index, a_num);
	stack_check(full,empty,s,argc);
	if (pivot_index == 1)
	{
		printf("##FINISHED##\n");
		pivot_index ++ ;
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
	printf("1\n");
	pivot_quicksort(full, empty, pivot_index/2, s, type, argc);
	printf("\n\n@will be applied:pivot_value = %d pivot_index = %d a_num::%d\n\n",s[(pivot_index)], (pivot_index), a_num);
	printf("2\n");
	pivot_quicksort(empty, full, (pivot_index + full->top)/2, s, type, argc);
}

int	main(int argc, char *argv[])
{
	Stack	a;
	Stack	b;
	int		*s;
	int		pivot_index;

	if (argc <= 1) // 나중에 숫자 아닌 다른거 들어올 때 규칙 제정하기
		return (0);
	s = arr_maker(argc, argv);
	pivot_index = (argc - 1) / 2;
	printf("pivot_index = %d\n", pivot_index);
	stack_init(&a);
	stack_maker(argc, &a, s);
	quicksort(s, 0, argc - 2); 
	stack_init(&b);

	pivot_quicksort(&a, &b, pivot_index, s, 'a', argc);
	//stack_check(&a, &b ,s ,argc);
	// printf("dd\n");
	// //element_move(&b, &a, 'a');
	// printf("xx\n");
	// pivot_index = (argc - 1 - ans_check(&b, &a, s,'b'))/2;
	// printf("new pivot index : %d\n", pivot_index);
	// stack_check(&a,&b,s,argc);
	// printf("atop::%d	btop::%d\n", a.top, b.top);
	// pivot_quicksort(&b, &a, pivot_index, s, 'b', argc);
	// printf("second\n");
	// stack_check(&a,&b,s,argc);
	// element_move(&a, &b, 'b');
	pivot_index = (argc - 1 - ans_check(&a, &b, s,'a'))/2;
	stack_check(&a,&b,s,argc);
	// printf("atop::%d	btop::%d\n", a.top, b.top);
}