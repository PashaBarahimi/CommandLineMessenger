#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "add_node.h"
#include "make_node.h"
#define FALSE 0
#define TRUE 1
#define USERS_FILE_ADDRESS "user.txt"
#define MESSAGES_FILE_ADDRESS "message.txt"
#define GROUP_FILE_ADDRESS "group.txt"

/*This function handles saving data in the file*/
void save_process(user_info* head_user, message* head_message, group* head_group)
{
	if (!save_users(head_user))
		printf("\tError saving data.\n");
	if (!save_messages(head_message))
		printf("\tError saving data.\n");
	if (!save_groups(head_group))
		printf("\tError saving data.\n");
	exit(0);
}

/*This function saves users' info in the file*/
int save_users(user_info* head)
{
	FILE* output = fopen(USERS_FILE_ADDRESS, "w");
	if (output == NULL)
		return FALSE;
	while ((head = head->next) != NULL)
		fprintf(output, "%s\n%s\n%s\n%d %d %d %d %d\n", head->username, head->password, head->phone_number, head->sign_up_date->month, head->sign_up_date->day, head->sign_up_date->year, head->sign_up_date->hour, head->sign_up_date->min);
	fclose(output);
	return TRUE;
}

/*This function saves messages in the file*/
int save_messages(message* head)
{
	FILE* output = fopen(MESSAGES_FILE_ADDRESS, "w");
	if (output == NULL)
		return FALSE;
	while ((head = head->next) != NULL)
		fprintf(output, "%s\n%s\n%s\n%d\n%d %d %d %d %d\n", head->sender_username, head->receiver_username, head->content, head->read_check, head->message_date->month, head->message_date->day, head->message_date->year, head->message_date->hour, head->message_date->min);
	fclose(output);
	return TRUE;
}

/*This function saves groups in the file*/
int save_groups(group* head)
{
	FILE* output = fopen(GROUP_FILE_ADDRESS, "w");
	if (output == NULL)
		return FALSE;
	while ((head = head->next) != NULL)
	{
		fprintf(output, "%s\n%s\n%d\n", head->name, head->admin_username, head->user_num);
		for (int i = 0; i < head->user_num; i++)
			fprintf(output, "%s\n", head->users[i]);
	}
	fclose(output);
	return TRUE;
}

/*This function handles reading data from file*/
void read_process(user_info* head_user, message* head_message, group* head_group)
{
	read_users(head_user);
	read_messages(head_message);
	read_groups(head_group);
}

/*This function reads users' data from file*/
int read_users(user_info* head)
{
	FILE* input = fopen(USERS_FILE_ADDRESS, "r");
	if (input == NULL)
		return FALSE;
	while (TRUE)
	{
		user_info* new_user = (user_info*)malloc(sizeof(user_info));
		date_time* new_date = (date_time*)malloc(sizeof(date_time));
		if (new_user == NULL || new_date == NULL)
		{
			printf("\tOops! Memory error.\n");
			return FALSE;
		}
		new_user->username = read_from_file(input, '\n');
		if (feof(input))
		{
			free(new_user);
			free(new_date);
			fclose(input);
			return TRUE;
		}
		new_user->password = read_from_file(input, '\n');
		new_user->phone_number = read_from_file(input, '\n');
		new_date->month = atoi(read_from_file(input, ' '));
		new_date->day = atoi(read_from_file(input, ' '));
		new_date->year = atoi(read_from_file(input, ' '));
		new_date->hour = atoi(read_from_file(input, ' '));
		new_date->min = atoi(read_from_file(input, '\n'));
		new_user->sign_up_date = new_date;
		insert_user(head, new_user);
	}
}

/*This function reads messages from the file*/
int read_messages(message* head)
{
	FILE* input = fopen(MESSAGES_FILE_ADDRESS, "r");
	if (input == NULL)
		return FALSE;
	while (TRUE)
	{
		message* new_message = (message*)malloc(sizeof(message));
		date_time* new_date = (date_time*)malloc(sizeof(date_time));
		if (new_message == NULL || new_date == NULL)
		{
			printf("\tOops! Memory error.\n");
			return FALSE;
		}
		new_message->sender_username = read_from_file(input, '\n');
		if (feof(input))
		{
			free(new_message);
			free(new_date);
			fclose(input);
			return TRUE;
		}
		new_message->receiver_username = read_from_file(input, '\n');
		new_message->content = read_from_file(input, '\n');
		new_message->read_check = atoi(read_from_file(input, '\n'));
		new_date->month = atoi(read_from_file(input, ' '));
		new_date->day = atoi(read_from_file(input, ' '));
		new_date->year = atoi(read_from_file(input, ' '));
		new_date->hour = atoi(read_from_file(input, ' '));
		new_date->min = atoi(read_from_file(input, '\n'));
		new_message->message_date = new_date;
		new_message->earmark = get_earmark(head);
		insert_message(head, new_message);
	}
}

/*This function reads groups from the file*/
int read_groups(group* head)
{
	FILE* input = fopen(GROUP_FILE_ADDRESS, "r");
	if (input == NULL)
		return FALSE;
	while (TRUE)
	{
		group* new_group = (group*)malloc(sizeof(group));
		if (new_group == NULL)
		{
			printf("\tOops! Memory error.\n");
			return FALSE;
		}
		new_group->name = read_from_file(input, '\n');
		if (feof(input))
		{
			free(new_group);
			fclose(input);
			return TRUE;
		}
		new_group->admin_username = read_from_file(input, '\n');
		new_group->user_num = atoi(read_from_file(input, '\n'));
		new_group->users = groups_users(new_group->user_num);
		if (new_group->users == NULL)
		{
			printf("\tOops! Memory error.\n");
			return FALSE;
		}
		for (int i = 0; i < new_group->user_num; i++)
			new_group->users[i] = read_from_file(input, '\n');
		insert_group(head, new_group);
	}
}

/*This function reads a line from file and returns it to the reading functions*/
char* read_from_file(FILE* input, char sep)
{
	char* line = (char*)malloc(0);
	int n = 0;
	while (TRUE)
	{
		char* new_pointer = (char*)realloc(line, n + 1);
		if (new_pointer == NULL)
		{
			printf("\tOops! Memory error.\n");
			return NULL;
		}
		n++;
		const char temp = (char)fgetc(input);
		if (temp == EOF)
			return NULL;
		if (temp == sep)
		{
			new_pointer[n - 1] = '\0';
			line = new_pointer;
			return line;
		}
		new_pointer[n - 1] = temp;
		line = new_pointer;
	}
}

/*This function is only separated from read_groups to remove warning*/
char** groups_users(int num)
{
	char** users = (char**)malloc(num * sizeof(char*));
	return users;
}
