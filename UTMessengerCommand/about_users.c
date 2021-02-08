#include <stdio.h>
#include <stdlib.h>
#include "about_users.h"
#include "get_input.h"
#include "existence_check.h"
#define ENTER (-1)
#define FALSE 0
#define TRUE 1

/*This function shows users' info if the command is "info"*/
void info(user_info* head_user)
{
	while ((head_user = head_user->next) != NULL)
		printf("\t%s\n", head_user->username);
}

/*This function shows a specific user's info*/
int about(user_info* head)
{
	char* input = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&input)) == FALSE) return FALSE;
	user_info* about_user;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		return FALSE;
	}
	if ((about_user = username_existence_check(head, input)) == NULL)
	{
		printf("\tThis username doesn't exist.\n");
		return FALSE;
	}
	printf("\t%s->%s Joined %02d/%02d/%d at %02d:%02d\n", about_user->username, about_user->phone_number, about_user->sign_up_date->month, about_user->sign_up_date->day, about_user->sign_up_date->year, about_user->sign_up_date->hour, about_user->sign_up_date->min);
	return TRUE;
}

