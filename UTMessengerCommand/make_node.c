#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "structs.h"
#include "add_node.h"
#include "make_node.h"
#define FALSE 0
#define TRUE 1
#define PHONE_NUMBER_LENGTH 11

/*This function makes a new struct date_time*/
date_time* date(void)
{
	time_t now;
	time(&now);
	struct tm* my_time = localtime(&now);
	date_time* new_date = (date_time*)malloc(sizeof(date_time));
	if (new_date == NULL)
	{
		printf("\tOops! Memory error!\n");
		return NULL;
	}
	new_date->year = my_time->tm_year + 1900;
	new_date->month = my_time->tm_mon + 1;
	new_date->day = my_time->tm_mday;
	new_date->hour = my_time->tm_hour;
	new_date->min = my_time->tm_min;
	return new_date;
}

/*This function returns the message earmark*/
int get_earmark(message* head)
{
	if (head->next == NULL)
		return 0;
	while (TRUE)
	{
		head = head->next;
		if (head->next == NULL)
			return head->earmark + 1;
	}
}

/*This function makes a new user_info node*/
int add_user(user_info* head, char* username, char* password, char* phone_number, date_time* sign_up_date)
{
	user_info* new_user = (user_info*)malloc(sizeof(user_info));
	if (new_user == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	new_user->username = username;
	new_user->password = password;
	new_user->phone_number = (char*)malloc(PHONE_NUMBER_LENGTH + 1);
	if (new_user->phone_number == NULL) return FALSE;
	strcpy_s(new_user->phone_number, PHONE_NUMBER_LENGTH + 1, phone_number);
	new_user->sign_up_date = sign_up_date;
	insert_user(head, new_user);
	return TRUE;
}

/*This function makes a new message node*/
int add_message(message* head, char* sender_username, char* receiver_username, char* input_message, date_time* message_date)
{
	message* new_message = (message*)malloc(sizeof(message));
	if (new_message == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	new_message->sender_username = sender_username;
	new_message->receiver_username = receiver_username;
	new_message->content = input_message;
	new_message->message_date = message_date;
	new_message->read_check = FALSE;
	new_message->earmark = get_earmark(head);
	insert_message(head, new_message);
	return TRUE;
}

/*This function makes a new group node*/
int create_group(group* head, char* name, char* admin_username)
{
	group* new_group = (group*)malloc(sizeof(group));
	if (new_group == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	new_group->name = name;
	new_group->admin_username = admin_username;
	new_group->users = NULL;
	new_group->user_num = 0;
	insert_group(head, new_group);
	return TRUE;
}

