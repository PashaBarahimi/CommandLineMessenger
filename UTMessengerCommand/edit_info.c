#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "edit_info.h"
#include "get_input.h"
#include "existence_check.h"
#define ENTER (-1)
#define FALSE 0
#define TRUE 1

int edit_username(user_info* user, user_info* head_user, group* head_group, message* head_message)
{
	char* input = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&input)) == FALSE) return FALSE;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		return FALSE;
	}
	if (!strcmp(input, user->username))
	{
		printf("\tThis username is already yours.\n");
		return FALSE;
	}
	if (username_existence_check(head_user, input) != NULL || group_name_existence_check(head_group, input) != NULL)
	{
		printf("\tThis username already exists.\n");
		return FALSE;
	}
	edit_username_in_groups(user, head_group, input);
	edit_username_in_messages(user, head_message, input);
	user->username = input;
	printf("\tUsername edited successfully.\n");
	return TRUE;
}

int edit_password(user_info* user)
{
	char* input = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_password(&input)) == FALSE) return FALSE;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		return FALSE;
	}
	if (!strcmp(input, user->password))
	{
		printf("\tThis password is already yours.\n");
		return FALSE;
	}
	user->password = input;
	printf("\tPassword edited successfully.\n");
	return TRUE;
}

void edit_username_in_groups(user_info* user, group* head_group, char* input)
{
	while ((head_group = head_group->next) != NULL)
		if (!strcmp(head_group->admin_username, user->username))
			head_group->admin_username = input;
		else
			for (int i = 0; i < head_group->user_num; i++)
				if (!strcmp(head_group->users[i], user->username))
					head_group->users[i] = input;
}

void edit_username_in_messages(user_info* user, message* head_message, char* input)
{
	while ((head_message = head_message->next) != NULL)
		if (!strcmp(head_message->sender_username, user->username))
			head_message->sender_username = input;
		else if (!strcmp(head_message->receiver_username, user->username))
			head_message->receiver_username = input;
}
