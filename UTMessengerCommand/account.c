#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"
#include "get_input.h"
#include "command.h"
#include "existence_check.h"
#include "make_node.h"
#include "edit_info.h"
#include "message_process.h"
#include "about_users.h"
#include "add_group.h"
#include "file.h"
#define ENTER (-1)
#define FALSE 0
#define TRUE 1
#define SIGNED_IN 3
#define CLOSE 6
#define LOG_OUT 7
#define EDIT_USERNAME 8
#define EDIT_PASS 9
#define SEND 10
#define INFO 11
#define ABOUT 12
#define SHOW_SENT 13
#define SHOW_RECEIVED 14
#define CREATE_GROUP 15
#define ADD_TO 16
#define PHONE_NUMBER_LENGTH 11

void sign_in_interface(user_info* head_user, group* head_group, message* head_message, user_info* user)
{
	printf("Welcome @%s\n", user->username);
	message_info_print(user, head_message);
	while (TRUE)
	{
		int enter_check;
		const int cmd = command(SIGNED_IN, &enter_check);
		if (cmd == LOG_OUT)
		{
			printf("\tLogged out successfully.\n");
			return;
		}
		if (cmd == CLOSE) save_process(head_user, head_message, head_group);
		if (cmd == INFO) info(head_user);
		else
		{
			if ((cmd == EDIT_USERNAME || cmd == EDIT_PASS || cmd == ABOUT || cmd == SHOW_SENT || cmd == SHOW_RECEIVED || cmd == CREATE_GROUP || cmd == ADD_TO) && (enter_check == ENTER))
			{
				printf("\tWrong command format.\n");
				continue;
			}
			if (cmd == EDIT_USERNAME) edit_username(user, head_user, head_group, head_message);
			else if (cmd == EDIT_PASS) edit_password(user);
			else if (cmd == SEND) send_message(head_user, user, head_group, head_message);
			else if (cmd == ABOUT) about(head_user);
			else if (cmd == SHOW_SENT) show_sent_messages(head_user, user, head_group, head_message);
			else if (cmd == SHOW_RECEIVED) show_received_messages(head_user, user, head_group, head_message);
			else if (cmd == CREATE_GROUP) new_group(head_user, user, head_group);
			else if (cmd == ADD_TO) add_to(head_user, user, head_group);
			else
			{
				printf("\tThis command is not valid here. You should first log out to use this command.\n");
				if (enter_check != ENTER) clear_buffer();
			}
		}
	}
}

void sign_in(user_info* head_user, group* head_group, message* head_message)
{
	char* input_username = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&input_username)) == FALSE) return;
	if (enter_check == ENTER)
	{
		printf("\tWrong command format.\n");
		return;
	}
	user_info* user;
	if ((user = username_existence_check(head_user, input_username)) == NULL)
	{
		printf("\tThis username doesn't exist.\n");
		if (enter_check != ENTER) clear_buffer();
		return;
	}
	char* input_password = (char*)malloc(0);
	enter_check = get_password(&input_password);
	if (enter_check == FALSE) return;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		return;
	}
	if (strcmp(input_password, user->password) != 0)
	{
		printf("\tThe password doesn't match.\n");
		return;
	}
	printf("\tSign in successful.\n");
	sign_in_interface(head_user, head_group, head_message, user);
}

void sign_up(user_info* head_user, group* head_group, message* head_message)
{
	char* input_username = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&input_username)) == FALSE) return;
	if (enter_check == ENTER)
	{
		printf("\tWrong command format.\n");
		return;
	}
	if (username_existence_check(head_user, input_username) != NULL)
	{
		printf("\tThis username already exists.\n");
		if (enter_check != ENTER) clear_buffer();
		return;
	}
	char* input_password = (char*)malloc(0);
	if ((enter_check = get_password(&input_password)) == FALSE) return;
	if (enter_check == ENTER)
	{
		printf("\tWrong command format.\n");
		return;
	}
	char input_phone[PHONE_NUMBER_LENGTH + 1];
	if (!get_phone_number(input_phone)) return;
	if (phone_number_existence_check(head_user, input_phone) != NULL)
	{
		printf("\tPhone number already exists.\n");
		return;
	}
	add_user(head_user, input_username, input_password, input_phone, date());
	user_info* user = username_existence_check(head_user, input_username);
	printf("\tSign up successful.\n");
	sign_in_interface(head_user, head_group, head_message, user);
}

