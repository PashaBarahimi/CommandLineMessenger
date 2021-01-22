#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "add_group.h"
#include "make_node.h"
#include "existence_check.h"
#include "get_input.h"
#define ENTER (-1)
#define FALSE 0
#define TRUE 1

/*This function executes when the user wants to create a new group*/
int new_group(user_info* head_user, user_info* admin, group* head_group)
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
	if (group_name_existence_check(head_group, input) != NULL || username_existence_check(head_user, input) != NULL)
	{
		printf("\tThis name already exists.\n");
		return FALSE;
	}
	printf("\tGroup created successfully.\n");
	return create_group(head_group, input, admin->username);
}

/*This function executes when the group's admin wants to add a new user to the group*/
int add_to(user_info* head_user, user_info* user, group* head_group)
{
	char* group_name = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&group_name)) == FALSE) return FALSE;
	if (enter_check == ENTER)
	{
		printf("\tWrong command format.\n");
		return FALSE;
	}
	group* gp;
	if ((gp = group_name_existence_check(head_group, group_name)) == NULL)
	{
		printf("\tThis group doesn't exist.\n");
		if (enter_check != ENTER) clear_buffer();
		return FALSE;
	}
	if (strcmp(user->username, gp->admin_username) != 0) /*Checking if the user is the group's admin*/
	{
		printf("\tYou are not this group's admin.\n");
		if (enter_check != ENTER) clear_buffer();
		return FALSE;
	}
	char* input_user = (char*)malloc(0);
	if ((enter_check = get_username(&input_user)) == FALSE) return FALSE;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		return FALSE;
	}
	user_info* new_member;
	if ((new_member = username_existence_check(head_user, input_user)) == NULL)
	{
		printf("\tThis username doesn't exist.\n");
		return FALSE;
	}
	return add_user_to_group(gp, new_member);
}

/*This function is the process of adding a new member to the group's node*/
int add_user_to_group(group* gp, user_info* user)
{
	if (!strcmp(gp->admin_username, user->username))
	{
		printf("\tThis username is yours.\n");
		return FALSE;
	}
	for (int i = 0; i < gp->user_num; i++)
		if (!strcmp(gp->users[i], user->username))
		{
			printf("\tThis user is already a member of this group.\n");
			return FALSE;
		}
	char** new_users = (char**)realloc(gp->users, (gp->user_num + 1) * sizeof(char*));
	if (new_users == NULL)
	{
		printf("\tOops! Memory error.\n");
		return FALSE;
	}
	new_users[gp->user_num] = user->username;
	gp->users = new_users;
	gp->user_num++;
	printf("\tUser added successfully.\n");
	return TRUE;
}
