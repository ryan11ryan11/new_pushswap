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

void	init_organize(Stack *a, Stack *b, Basic_info *info)
{
	int	rewind;
	int	set;

	set = a->top;
	rewind = 0;
	printf("init started\n");
	while (set >= 0)
	{
		if (a->data[a->top] > info->sorted_array[1])
		{
			element_move(b,a,'a');
			rewind ++ ;
		}
		else
			stack_up(a,'a');
		set -- ;
	}
	while (rewind > 0)
	{
		element_move(a,b,'b');
		rewind -- ;
	}
	if (a->data[a->top] > a->data[a->top - 1])
		swap(a,'a');
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
		if (a->data[a->top] == info->sorted_array[info->sorted_number]) // a의 꼭대기가 다음 수라면 리스트 업해서 밑으로 보내
		{
			stack_up(a, 'a');
			sorted_arr_scan(a,info);
			unorganized = (a->top + 1) + rewind - info->sorted_number;
		}
		while (a->data[a->top] != info->sorted_array[0]) // 제일 작은수 위의 정렬되지 않은 숫자가 다 b로 넘어갈 때까지
		{
			element_move(b, a, 'a'); // a에서 b로 넘겨
			rewind ++ ;
			if (a->data[a->top] == info->sorted_array[info->sorted_number]) // a의 꼭대기가 다음 수라면 리스트 업해서 밑으로 보내
			{
				stack_up(a, 'a');
				sorted_arr_scan(a,info);
				unorganized = (a->top + 1) + rewind - info->sorted_number;
			}
		}
		if (a->data[a->top] == info->sorted_array[info->sorted_number])
		{
			stack_up(a, 'a');
			sorted_arr_scan(a,info);
			unorganized = (a->top + 1) + rewind - info->sorted_number;
		}
		while (rewind > 0) // 리와인드 0 될때까지 b에서 a로 옮겨
		{
			element_move(a, b, 'b');
			rewind -- ;
			if (a->data[a->top] == info->sorted_array[info->sorted_number])
			{
				stack_up(a, 'a');
				sorted_arr_scan(a,info);
				unorganized = (a->top + 1) + rewind - info->sorted_number;
			}
		}
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

int	atob(Stack *a, Stack *b, Basic_info *info, int pivot_index, int start, int end)
{
	int	pivot_value;
	int	flag;

	printf("atob 도입\n");
	flag = 0;
	pivot_value = info->sorted_array[pivot_index];
	sorted_arr_scan(a,info);
	printf("\n\n1 sortednumber:%d pivot value:%d end:%d\n\n",info->sorted_number,pivot_value,end);	
	stack_check(a,b,info->sorted_array,info->argc);

	if (a->top + 1 - info->sorted_number <= 20)
	{
		printf("미정렬된 값이 %d 개 이하입니다. 정렬합니다\n", a->top + 1 - info->sorted_number);
		printf("atob returned a->top:%d sortnum:%d\n",a->top, info->sorted_number);
		sorted_arr_scan(a,info);
		organize (a, b, a->top + 1 - info->sorted_number, info);
		printf("정렬후::\n");
		stack_check(a,b,info->sorted_array,info->argc);
		return (0);
	}
	
	printf("피봇밸류:%d 보다 작으면 밑으로 보내고 크면 스택 b로 보냅니다\n", pivot_value);
	while (flag == 0) // 피봇밸류보다 작으면 밑으로 보내고 크면 스택b로 옮긴다
	{
		sorted_arr_scan(a,info);
		if (a->data[a->top] == end)
			flag = 1;
		if (a->data[a->top] <= pivot_value)
			stack_up(a, 'a');
		else
			element_move (b, a, 'a');
	}
	printf("\n\n2 sortednumber:%d pivot value:%d end:%d\n\n",info->sorted_number,pivot_value,end);	
	stack_check(a,b,info->sorted_array,info->argc);

	printf("피봇밸류:%d 을 맨 밑으로 보내고 스택b로 이동시킴\n", pivot_value);
	if (a->data[0] != pivot_value && a->top + 1 != info->sorted_number) // 피봇값을 맨 밑으로 보낸다, 최적화필요, 위로보내아래로보내
		pivot_buttom(a,pivot_value);
	if (a->data[0] == pivot_value && a->top + 1 != info->sorted_number) // 피봇값을 맨 위로 보낸 뒤 스택b로 이동시킨다
	{
		stack_down(a, 'a');
		element_move(b, a, 'a');
	}
	sorted_arr_scan(a,info);
	printf("리와인드, 정렬된 수열의 갯수는 %d 개이며, 수열 마지막 숫자 %d 가 맨 밑으로 오도록 합니다. \n", info->sorted_number, info->tail);
	while (info -> sorted_number > 1 && info -> tail != a->data[0]) // 리와인드
		stack_down(a,'a');
	printf("\n\n3 sortednumber:%d pivot value:%d end:%d\n\n",info->sorted_number,pivot_value,end);
	stack_check(a,b,info->sorted_array,info->argc);
	printf("atob 끝\n");
	atob(a,b,info,info->sorted_number - 1 + (a->top - info->sorted_number + 1)/2,a->data[a->top],a->data[0]);
	printf("###pivot_value:%d###\n",pivot_value);
	btoa(a,b,info,pivot_value);
	printf("%d",start);
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
	if (b->data[b->top] > pivot_value) // btop의 밸류가 피봇밸류 이상일경우 종료
		return (0);
	while (a->data[a->top] != pivot_value) // 피봇밸류만큼 b에서 a로 끌어옴
	{
		printf("ho\n");
		element_move(a, b, 'b');
		sent ++ ;
	}
	if (sent/2 == 0)
		sent = 2;
	pivot_index = info->sorted_array[info->sorted_number] + sent/2 - 1; // 피봇 재설정
	printf("btoa finished\n");
	printf("sent to atob:pivot_index:%d a->data[a->top]:%d prv_btop:%d\n",pivot_index, a->data[a->top], prv_btop);
	atob (a,b,info,pivot_index, a->data[a->top],prv_btop);
	return (0);
}

void	simple_btoa(Stack *a, Stack *b, Basic_info *info)
{
	int	times;

	times = b->top;
	while (times >= 0)
	{
		if (b->data[b->top] < info->sorted_array[info->pivot_index])
			element_move(a, b, 'b');
		else
			stack_up(b, 'b');
		times -- ;
	}
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

	atob(&a, &b, &info,info.pivot_index, a.data[a.top], a.data[0]); // 일단 b로 다 보낸다
	sorted_arr_scan(&a,&info);
	printf("					####onemore####\n");
	while(b.top > 1)
	{
		info.pivot_index = (argc - info.sorted_number) / 2 + info.sorted_number - 1; // 
		simple_btoa(&a,&b,&info);
		printf("new_pivot:%d					####onemore####\n",info.pivot_index);
		stack_check(&a,&b,info.sorted_array,argc);
		info.pivot_index = info.sorted_array[info.sorted_number + (a.top - info.sorted_number) / 2];
		atob(&a, &b, &info,info.pivot_index, a.data[a.top], a.data[0]);
		sorted_arr_scan(&a,&info);
	}
	
	printf("final\n");
	// atob(&a, &b, type, &info);
	// atob(&a, &b, type, &info);
	// while (atob(&a, &b, type, &info) != 1)
	// 	;
	// while (btoa(&a, &b, type, &info) != 1)
	// 	;
	stack_check(&a,&b,info.sorted_array,argc);
}