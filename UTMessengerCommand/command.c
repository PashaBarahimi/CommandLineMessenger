#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"
#include "get_input.h"
#define ENTER (-1)
#define TRUE 1
#define MAIN_MENU 2
#define SIGNED_IN 3
#define LOGIN 4
#define SIGN_UP 5
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
#define HELP 17

/*This function prints all the valid commands*/
void help(int section)
{
	switch (section)
	{
	case MAIN_MENU:
		printf("login <Username> <Password>\n");
		printf("signup <Username> <Password> <Phone Number>\n");
		printf("close\n");
		break;
	case SIGNED_IN:
		printf("logout\n");
		printf("edit_username <New Username>\n");
		printf("edit_pass <New Password>\n");
		printf("send <Username/Group Name> <Content>\n");
		printf("info\n");
		printf("about <Username>\n");
		printf("show_sent <Username/Group Name>\n");
		printf("show_received <Username/Group Name>\n");
		printf("close\n");
		printf("create_group <Group Name>\n");
		printf("add_to <Group Name> <Username>\n");
		break;
	default:
		break;
	}
}

/*The process of checking the entered command*/
int command(int section, int* enter_check)
{
	while (TRUE)
	{
		printf(">> ");
		char* input = (char*)malloc(0);
		int cmd;
		if ((*enter_check = get_command(&input)))
		{
			if (!strcmp(input, "login")) cmd = LOGIN;
			else if (!strcmp(input, "signup")) cmd = SIGN_UP;
			else if (!strcmp(input, "close")) cmd = CLOSE;
			else if (!strcmp(input, "logout")) cmd = LOG_OUT;
			else if (!strcmp(input, "edit_username")) cmd = EDIT_USERNAME;
			else if (!strcmp(input, "edit_pass")) cmd = EDIT_PASS;
			else if (!strcmp(input, "send")) cmd = SEND;
			else if (!strcmp(input, "info")) cmd = INFO;
			else if (!strcmp(input, "about")) cmd = ABOUT;
			else if (!strcmp(input, "show_sent")) cmd = SHOW_SENT;
			else if (!strcmp(input, "show_received")) cmd = SHOW_RECEIVED;
			else if (!strcmp(input, "create_group")) cmd = CREATE_GROUP;
			else if (!strcmp(input, "add_to")) cmd = ADD_TO;
			else if (!strcmp(input, "help")) cmd = HELP;
			else
			{
				printf("\tInvalid command! Type help to see the valid commands.\n");
				if (*enter_check != ENTER) clear_buffer();
				continue;
			}
			if ((cmd == CLOSE || cmd == LOG_OUT || cmd == INFO || cmd == HELP) && *enter_check != ENTER)
			{
				printf("\tWrong command format.\n");
				clear_buffer();
				continue;
			}
			if (cmd == HELP) help(section);
			else return cmd;
		}
	}
}
