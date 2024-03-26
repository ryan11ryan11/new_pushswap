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
	while (full->data[scan] == info->sorted_array[i])
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

int	organize(Stack *a, int how_many)
{
	if (how_many > 2)
		return (0);
	if (how_many == 0)
		return(2);
	if (how_many == 1)
	{
		stack_up(a, 'a');
		return (2);
	}
	if (how_many == 2)
	{
		if (a->data[a->top] < a->data[a->top - 1])
		{
			stack_up(a, 'a');
			stack_up(a, 'a');
			return (2);
		}
		else
		{
			swap(a, 'a');
			stack_up(a, 'a');
			stack_up(a, 'a');
			return (2);
		}
	}
	return(0);
}

int	atob(Stack *a, Stack *b, Basic_info *info, int pivot_index, int start, int end)
{
	int	pivot_value;
	int	flag;

	printf("atob start\n");
	flag = 0;
	pivot_value = info->sorted_array[pivot_index];
	sorted_arr_scan(a,info);
	printf("pivot_index:%d start:%d end:%d\n",pivot_index,start,end);
	stack_check(a,b,info->sorted_array,info->argc);

	if (a->top + 1 - info->sorted_number <= 2) // btoa에서 당겨온 수가 2개 이하이면 organize하고 종결
	{
		printf("a->top:%d sortnum:%d\n",a->top, info->sorted_number);
		sorted_arr_scan(a,info);
		organize (a, a->top + 1 - info->sorted_number);
		return (0);
	}

	printf("sortednumber::%d pivot value:%d end:%d \n",info->sorted_number,pivot_value,end);
	while (flag == 0)
	{
		sorted_arr_scan(a,info);
		if (a->data[a->top] == end)
			flag = 1;
		if (a->data[a->top] <= pivot_value)
			stack_up(a, 'a');
		else
			element_move(b, a, 'a');
	}
	organize (a, a->top - info->sorted_number);
	while (a->data[0] != pivot_value && a->top + 1 != info->sorted_number) // 최적화필요, 위로보내아래로보내
	{
		//printf("here\n");
		stack_up(a, 'a');
	}
	if (a->data[0] == pivot_value && a->top + 1 != info->sorted_number)
	{
		stack_down(a, 'a');
		element_move(b, a, 'a');
	}
	printf("atob end\n");
	atob(a,b,info,pivot_index/2+info->sorted_number-1,a->data[a->top],a->data[0]);
	printf("###pivot_value:%d###\n",pivot_value);
	btoa(a,b,info,pivot_value); 
	return (0);
}

int	btoa(Stack *a, Stack *b, Basic_info *info, int pivot_value)
{
	int	pivot_index;
	int	sent;
	int	prv_btop;

	printf("btoa started\n");
	sent = 0;
	prv_btop = b->data[b->top];
	sorted_arr_scan(a,info);
	if (b->data[b->top] > pivot_value)
		return (0);
	while (a->data[a->top] != pivot_value)
	{
		printf("ho\n");
		element_move(a, b, 'b');
		sent ++ ;
	}
	// if (a->top + 1 - info->sorted_number == 0)
	// 	return (0);
	//stack_check(a,b,info->sorted_array,info->argc);
	if (sent/2 == 0)
		sent = 2;
	pivot_index = info->sorted_array[info->sorted_number] + sent/2 - 1;
	printf("btoa finished\n");
	printf("sent to atob:pivot_index:%d a->data[a->top]:%d prv_btop:%d\n",pivot_index, a->data[a->top], prv_btop);
	atob (a,b,info,pivot_index, a->data[a->top],prv_btop);
	return (0);
}

int	main(int argc, char *argv[])
{
	Basic_info	info;
	Stack		a;
	Stack		b;

	if (argc <= 1) // 나중에 숫자 아닌 다른거 들어올 때 규칙 제정하기
		return (0);
	stack_init(&a);
	stack_init(&b);
	info.first_half = 0;
	info.a = &a;
	info.b = &b;
	info.sorted_number = 0;
	info.sorted_array = arr_maker(argc, argv);
	info.pivot_index = (argc - 1) / 2;
	info.argc = argc;
	printf("pivot_index = %d\n", info.pivot_index);
	stack_maker(info.argc, info.a, info.sorted_array);
	quicksort(info.sorted_array, 0, info.argc - 2); 

	atob(&a, &b, &info,info.pivot_index, a.data[a.top], a.data[0]);
	printf("final\n");
	// atob(&a, &b, type, &info);
	// atob(&a, &b, type, &info);
	// while (atob(&a, &b, type, &info) != 1)
	// 	;
	// while (btoa(&a, &b, type, &info) != 1)
	// 	;
	stack_check(&a,&b,info.sorted_array,argc);
}