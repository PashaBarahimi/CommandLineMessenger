#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include "message_process.h"
#include "get_input.h"
#include "existence_check.h"
#include "make_node.h"
#define ENTER (-1)
#define FALSE 0
#define TRUE 1

/*Process of sending a message to another user*/
int send_message(user_info* head_user, user_info* sender, group* head_group, message* head_message)
{
	int enter_check;
	char* input = (char*)malloc(0);
	if ((enter_check = get_username(&input)) == FALSE) return FALSE;
	user_info* receiver = username_existence_check(head_user, input);
	if (receiver != NULL)
	{
		if (!strcmp(sender->username, input))
		{
			printf("\tThis username is yours!\n");
			if (enter_check != ENTER) clear_buffer();
			free(input);
			return FALSE;
		}
		char* input_message = (char*)malloc(0);
		if (!get_message(&input_message)) return FALSE;
		printf("\tMessage sent successfully.\n");
		return add_message(head_message, sender->username, receiver->username, input_message, date());
	}
	return group_message_check(head_group, head_message, sender, input, enter_check);
}

/*This function checks if the entered name belongs to a group to send the message*/
int group_message_check(group* head_group, message* head_message, user_info* sender, char* group_name, int enter_check)
{
	group* receiver = group_name_existence_check(head_group, group_name);
	if (receiver == NULL)
	{
		printf("\tThe username or the group name you entered doesn't exist.\n");
		if (enter_check != ENTER) clear_buffer();
		return FALSE;
	}
	int exist_check = FALSE;
	for (int i = 0; i < receiver->user_num; i++)
	{
		if (!strcmp(receiver->users[i], sender->username))
		{
			exist_check = TRUE;
			break;
		}
	}
	if (!strcmp(receiver->admin_username, sender->username))
		exist_check = TRUE;
	if (!exist_check)
	{
		printf("\tYou are not a member of this group.\n");
		if (enter_check != ENTER) clear_buffer();
		return FALSE;
	}
	char* input_message = (char*)malloc(0);
	if (!get_message(&input_message)) return FALSE;
	return send_message_to_group(receiver, head_message, input_message, sender);
}

/*This function sends message to the group*/
int send_message_to_group(group* receiver, message* head_message, char* input_message, user_info* sender)
{
	int check = TRUE;
	date_time* send_date = date();
	for (int i = 0; i < receiver->user_num; i++)
		if (strcmp(receiver->users[i], sender->username) != 0)
			check = add_message(head_message, receiver->name, receiver->users[i], input_message, send_date);
	if (!check) return FALSE;
	if (strcmp(sender->username, receiver->admin_username) != 0)
	{
		check = add_message(head_message, receiver->name, receiver->admin_username, input_message, send_date);
		if (!check) return FALSE;
	}
	check = add_message(head_message, sender->username, receiver->name, input_message, send_date);
	if (!check) return FALSE;
	printf("\tMessage sent successfully.\n");
	return TRUE;
}

/*This function is the process of showing sent messages*/
int show_sent_messages(user_info* head_user, user_info* sender, group* head_group, message* head_message)
{
	char* input = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&input)) == FALSE) return FALSE;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		free(input);
		return FALSE;
	}
	user_info* receiver = username_existence_check(head_user, input);
	if (receiver != NULL)
	{
		if (!strcmp(sender->username, input))
		{
			printf("\tThis username is yours!\n");
			free(input);
			return FALSE;
		}
		return print_sent_messages(sender->username, receiver->username, head_message);
	}
	return group_sent_messages(sender, input, head_message, head_group);
}

/*This function prints the sent messages*/
int print_sent_messages(char* sender, char* receiver, message* head)
{
	int check = FALSE;
	while ((head = head->next) != NULL)
	{
		if (strcmp(sender, head->sender_username) == 0 && strcmp(receiver, head->receiver_username) == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), head->read_check == FALSE ? FOREGROUND_RED : FOREGROUND_GREEN); /*Changing foreground color dependent to the reading status*/
			check = TRUE;
			printf("\tMessage to @%s in %02d/%02d/%d at %02d:%02d -> %s\n", receiver, head->message_date->month, head->message_date->day, head->message_date->year, head->message_date->hour, head->message_date->min, head->content);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); /*Resetting foreground color*/
		}
	}
	if (!check)
		printf("\tNo message to show!\n");
	return check;
}

/*This function searches for group messages that the user has sent*/
int group_sent_messages(user_info* sender, char* group_name, message* head_message, group* head_group)
{
	group* receiver = group_name_existence_check(head_group, group_name);
	if (receiver == NULL)
	{
		printf("\tThe username or the group name you entered doesn't exist.\n");
		return FALSE;
	}
	int exist_check = FALSE;
	for (int i = 0; i < receiver->user_num; i++)
	{
		if (!strcmp(receiver->users[i], sender->username))
		{
			exist_check = TRUE;
			break;
		}
	}
	if (!strcmp(sender->username, receiver->admin_username))
		exist_check = TRUE;
	if (!exist_check)
	{
		printf("\tYou are not a member of this group.\n");
		return FALSE;
	}
	return print_sent_messages(sender->username, receiver->name, head_message);
}

/*This function is the process of showing received messages*/
int show_received_messages(user_info* head_user, user_info* receiver, group* head_group, message* head_message)
{
	char* input = (char*)malloc(0);
	int enter_check;
	if ((enter_check = get_username(&input)) == FALSE) return FALSE;
	if (enter_check != ENTER)
	{
		printf("\tWrong command format.\n");
		clear_buffer();
		free(input);
		return FALSE;
	}
	user_info* sender = username_existence_check(head_user, input);
	if (sender != NULL)
	{
		if (!strcmp(receiver->username, input))
		{
			printf("\tThis username is yours!\n");
			free(input);
			return FALSE;
		}
		return print_received_messages(sender->username, receiver->username, head_message);
	}
	return group_received_messages(receiver, input, head_message, head_group);
}

/*This function prints the received messages*/
int print_received_messages(char* sender, char* receiver, message* head)
{
	int check = FALSE;
	while ((head = head->next) != NULL)
	{
		if (strcmp(sender, head->sender_username) == 0 && strcmp(receiver, head->receiver_username) == 0)
		{
			check = TRUE;
			printf("\tMessage from @%s in %02d/%02d/%d at %02d:%02d -> %s\n", sender, head->message_date->month, head->message_date->day, head->message_date->year, head->message_date->hour, head->message_date->min, head->content);
			head->read_check = TRUE;
		}
	}
	if (!check)
		printf("\tNo message to show!\n");
	return check;
}

/*This function searches for group messages that the user has received*/
int group_received_messages(user_info* receiver, char* group_name, message* head_message, group* head_group)
{
	group* sender = group_name_existence_check(head_group, group_name);
	if (sender == NULL)
	{
		printf("\tThe username or the group name you entered doesn't exist.\n");
		return FALSE;
	}
	int exist_check = FALSE;
	for (int i = 0; i < sender->user_num; i++)
	{
		if (!strcmp(sender->users[i], receiver->username))
		{
			exist_check = TRUE;
			break;
		}
	}
	if (!strcmp(receiver->username, sender->admin_username))
		exist_check = TRUE;
	if (!exist_check)
	{
		printf("\tYou are not a member of this group.\n");
		return FALSE;
	}
	return print_received_messages(sender->name, receiver->username, head_message);
}

/*This function prints the unread messages' info when the user login*/
void message_info_print(user_info* user, message* head_message)
{
	printf("\tUnread messages:\n");
	while ((head_message = head_message->next) != NULL)
		if (!strcmp(user->username, head_message->receiver_username) && head_message->read_check == FALSE)
			printf("\tMessage from @%s in %02d/%02d/%d at %02d:%02d\n", head_message->sender_username, head_message->message_date->month, head_message->message_date->day, head_message->message_date->year, head_message->message_date->hour, head_message->message_date->min);
}

