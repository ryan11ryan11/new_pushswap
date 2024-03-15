/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:50:56 by junhhong          #+#    #+#             */
/*   Updated: 2024/02/27 16:31:41 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	a_sorting(Stack *a, Stackstructure *astruc, int *s)
{
	while(a->data[a->top] == s[astruc->target_location + 1])
	{
		printf("	yosi\n");
		stack_up(a,'a');
		astruc->target_location ++ ;
		astruc->prv_target = astruc->target;
		astruc->target = s[astruc->target_location];
	}
}

void	a_low_target(Stack *a, Stackstructure *astruc, int *s)
{
	int target_loc_a;

	target_loc_a = where_is(a, astruc->target);
	printf("	low_target\n");
	while (1)
	{
		while (a->data[a->top] != astruc->target)
			stack_down(a,'a');
		swap(a,'a');
		stack_up(a,'a');
		if (a->data[a->top] == astruc->target && a->data[0] == astruc->prv_target)
			break ;
	}
	stack_up(a,'a');
	a_sorting(a,astruc,s);
}

void	a_high_target(Stack *a, Stackstructure *astruc, int *s)
{
	int target_loc_a;

	target_loc_a = where_is(a, astruc->target);
	printf("	high_target\n");
	while(1)
	{
		while (a->data[a->top - 1] != astruc->target)
			stack_up(a,'a');
		swap(a,'a');
		if(a->data[a->top] == astruc->target && a->data[0] == astruc->prv_target)
			break;
		stack_down(a,'a');
	}
	stack_up(a,'a');
	a_sorting(a,astruc,s);
}

void	a_linking(Stack *a, Stackstructure *astruc, int *s, int argc)
{
	int	prv_location;
	int	target_loc_a;

	printf("	a_linking start\n");
	//stack_check(a,a,s,argc);
	prv_location = where_is(a, astruc->prv_target);
	target_loc_a = where_is(a, astruc->target);
	printf("\nstandard:%d\ntarget:%d\nprv_target:%d\nmid:%d\ntarget_location:%d\nprv_location:%d\na->data[a->top]:%d\n\n",astruc->standard,astruc->target,astruc->prv_target,astruc->mid,astruc->target_location,prv_location,a->data[a->top]);
	printf("s[prv_location]:%d\nprv_location:%d\n",s[prv_location],prv_location);
	if (target_loc_a >= a->top / 2)
		a_high_target(a,astruc,s);
	if (target_loc_a < a->top / 2)
		a_low_target(a,astruc,s);
	astruc->target_location ++ ;
	astruc->prv_target = astruc->target;
	astruc->target = s[astruc->target_location];
	stack_check(a,a,s,argc);
}

void	a_target_buttom(Stack *a, Stackstructure *astruc, int *s)
{
	int	target_location;
	int	prv_location;

	printf("	target_buttom\n");
	prv_location = where_is(a, astruc->prv_target);
	target_location = where_is(a, astruc->target);
	while (a->data[0] != astruc->target)
	{
		if (target_location <= astruc->mid)
			stack_down(a,'a');
		else
			stack_up(a,'a');
		if (a->data[a->top] > a->data[a->top - 1])
		 	swap(a,'a');
	}
	astruc->target_location ++ ;
	astruc->prv_target = astruc->target;
	astruc->target = s[astruc->target_location];
}

void	a_sort_init(Stackstructure *astruc, int *s, int argc, Stack *a)
{
	astruc->standard = (argc - 1) / 2;
	astruc->target = s[astruc->standard];
	astruc->prv_target = a->data[0];
	astruc->mid = (a->top)/2;
	astruc->target_location = (argc - 1) / 2;
}

int		checker(Stack *a)
{
	int	i;
	int	j;

	i = 0;
	j = a->top;
	while (i == 0 && j > 1)
	{	
		if(a->data[j] > a->data[j-1])
			i -- ;
		j -- ;
	}
	return (i);
}

void	lineup(Stack *a)
{
	int i;

	i = a->top;
	while (i > 0)
	{
		if (a->data[a->top] > a->data[a->top--])
			swap(a,'a');
		else
			stack_up(a,'a');
		i -- ;
	}
}

void	a_sort(Stack *a, int *s, int argc)
{
	Stackstructure	astruc;
	t_list *a_order;
	t_list *b_order;

	a_order = NULL;
	b_order = NULL;
	a_sort_init(&astruc, s, argc, a);
	a_target_buttom(a, &astruc, s); // 어떠한 경우에도 타겟은 스탠다드이다.
	while (1)
	{
		if (checker(a) == 0)
			break;
		a_linking(a, &astruc, s, argc);
	}
	lineup(a);
	printf("$$$$$$$$$$FINAL$$$$$$$$$$$$$$$$");
	stack_check(a,a,s,argc);
}