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

int	sorted_arr_scan(Stack *full, Basic_info *info, int type)
{
	int	i;
	int	scan;

	scan = full->top;
	i = 0;
	printf("%d\n",type);
	while (full->data[scan] == info->sorted_array[i])
	{
		scan--;
		i ++ ;
	}
	info->sorted_number = i;
	info->head = info->sorted_array[0];
	info->tail = info->sorted_array[i - 1];
	return (i);
}


// int	btoa(Stack *a, Stack *b, int type, Basic_info *info)
// {
// 	int	pivot_value;
// 	int	b_num;
// 	int	half_pivot;
// 	int	i;

// 	i = 0;	
// 	half_pivot = (b->top - info->sorted_number)/2 + info->sorted_number;
// 	pivot_value = info->sorted_array[half_pivot];
// 	b_num = b->top; // 정렬해야 할 숫자의 갯수
// 	printf("btoa started\n");
// 	printf("sorted_number:%d",info->sorted_number);
// 	printf("\n\n@@will be applied:pivot_value = %d half_pivot = %d b_num::%d\n\n",pivot_value, half_pivot, b_num);
// 	sorted_arr_scan(b,info,type);
	
// 	if (b_num + 1 - info->sorted_number == 0)
// 		return (1);
// 	stack_check(a,b,info->sorted_array,info->argc);
// 	while (b->data[b->top] == info->sorted_array[i])
// 	{
// 		printf("sorted number ++\n");
// 		i ++ ;
// 		stack_up(b, type);
// 	}
// 	while (b_num - info->sorted_number >= 0)
// 	{
// 		printf("top::%d sorted arr:%d\n",b->data[b->top],info->sorted_array[info->sorted_number]);
// 		if (b->data[b->top] > pivot_value)
// 			element_move(a, b, type);
// 		else
// 			stack_up(b, type);
// 		b_num -- ;
// 	}
// 	stack_check(a,b,info->sorted_array,info->argc);
// 	sorted_arr_scan(b,info,type);
// 	printf("#sorted_number:%d",info->sorted_number);
// 	printf("ENDEND\n");
// 	return (0);
// }


// int	btoa(Stack *a, Stack *b, int type, Basic_info *info)
// {
// 	int	pivot_value;
// 	int	b_num;
// 	int	half_pivot;
// 	int	i;

// 	i = 0;
// 	half_pivot = (b->top - info->sorted_number)/2 + info->sorted_number;
// 	pivot_value = info->sorted_array[half_pivot];
// 	b_num = b->top; // 정렬해야 할 숫자의 갯수
// 	printf("btoa started\n");
// 	printf("sorted_number:%d",info->sorted_number);
// 	printf("\n\n@@will be applied:pivot_value = %d half_pivot = %d b_num::%d\n\n",pivot_value, half_pivot, b_num);
// 	sorted_arr_scan(b,info,type);
	
// 	if (b_num + 1 - info->sorted_number == 0)
// 		return (1);
// 	stack_check(a,b,info->sorted_array,info->argc);
// 	while (b->data[b->top] == info->sorted_array[i])
// 	{
// 		printf("sorted number ++\n");
// 		i ++ ;
// 		stack_up(b, type);
// 	}
// 	while (b_num - info->sorted_number >= 0)
// 	{
// 		printf("top::%d sorted arr:%d\n",b->data[b->top],info->sorted_array[info->sorted_number]);
// 		if (b->data[b->top] > pivot_value)
// 			element_move(a, b, type);
// 		else
// 			stack_up(b, type);
// 		b_num -- ;
// 	}
// 	stack_check(a,b,info->sorted_array,info->argc);
// 	sorted_arr_scan(b,info,type);
// 	printf("#sorted_number:%d",info->sorted_number);
// 	printf("ENDEND\n");
// 	return (0);
// }

int	atob(Stack *a, Stack *b, int type, Basic_info *info, int pivot_index)
{
	int	pivot_value;
	int	to_be_done;
	int	i;

	i = 0;
	pivot_value = info->sorted_array[pivot_index];
	to_be_done = a->top - info->sorted_number; // 정렬해야 할 숫자의 갯수
	sorted_arr_scan(a,info,type);
	printf("\n\nwill be applied:pivot_value = %d half_pivot = %d a_num::%d\n\n",pivot_value, a->top/2, to_be_done);
	printf("\n");
	stack_check(a,b,info->sorted_array,info->argc);
	printf("\n");
	printf("info->sorted_number::%d a->top::%d\n",info->sorted_number,a->top);
	printf("top:%d sorted_number:%d\n",a->top,info->sorted_number);
	if (a->top - info->sorted_number <= 1)
	{
		if (a->data[a->top] > a->data[0])
			swap(a,'a');
		if (a->top + 1 != info->sorted_number)
		{
			while(a->data[0] != info->tail)
				stack_down(a, type);
			swap(a,'a');
			while(a->data[a->top] != info->head)
				stack_up(a, type);
		}
		info->first_half ++ ;
		return (1);
	}

	while (a->data[a->top] == info->sorted_array[i])
	{
		stack_up(a, type);
		i ++ ;
	}

	while (to_be_done >= 0)
	{
		printf("3\n");
		if (a->data[a->top] <= pivot_value)
			stack_up(a, type);
		else
			element_move(b, a, type);
		to_be_done -- ;
	}
	
	stack_check(a,b,info->sorted_array,info->argc);

	while (a->data[0] != pivot_value) // 최적화필요, 위로보내아래로보내
		stack_up(a, type);
	if (a->data[0] == pivot_value)
	{
		stack_down(a, type);
		element_move(b, a, type);
	}
	atob(a,b,type,info,pivot_index/2);
	printf("\n#########################pivot_value::%d###########\n",pivot_value);
	btoa(a,b,type,info,pivot_value); 
	return (0);
}

int	btoa(Stack *a, Stack *b, int type, Basic_info *info, int pivot_value)
{
	int	pivot_index;
	static int	sent;

	sorted_arr_scan(a,info,type);
	//printf("a->top:%d sorted_number:%d!\n",a->top,info->sorted_number);
	// if (a->top + 1 == info->sorted_number)
	// 	return (0);
	printf("btoa\n");
	printf("pivot_value::%d btop::%d\n",pivot_value,b->top);
	stack_check(a,b,info->sorted_array,info->argc);
	if (b->data[b->top] > pivot_value)
		return (0);
	while (a->data[a->top] != pivot_value)
	{
		printf("ho\n");
		element_move(a, b, 'b');
		sent ++ ;
	}
	stack_check(a,b,info->sorted_array,info->argc);
	pivot_index = info->sorted_number + sent - 1; //피봇에서 씨름중이었음 스태틱센트.. 
	printf("pivot_index::%d\n",pivot_index);
	printf("$pivotindex:%d sent:%d\n",pivot_index-sent/2, sent);
	atob (a,b,type,info,pivot_index - sent/2);
	return (0);
}

int	main(int argc, char *argv[])
{
	Basic_info	info;
	Stack		a;
	Stack		b;
	int			type;

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

	type = 'a';
	atob(&a, &b, type, &info, a.top/2);
	printf("final\n");
	// atob(&a, &b, type, &info);
	// atob(&a, &b, type, &info);
	// while (atob(&a, &b, type, &info) != 1)
	// 	;
	// while (btoa(&a, &b, type, &info) != 1)
	// 	;
	stack_check(&a,&b,info.sorted_array,argc);
}