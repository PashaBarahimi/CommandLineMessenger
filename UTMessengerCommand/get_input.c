#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_input.h"
#define ENTER (-1)
#define FALSE 0
#define TRUE 1
#define PHONE_NUMBER_LENGTH 11
#define MIN_PASS_LENGTH 6

/*This function reads phone number from console*/
int get_phone_number(char* phone_number)
{
	for (int i = 0; i <= PHONE_NUMBER_LENGTH; i++)
	{
		const char temp = (char)getchar();
		if ((i == 0 && temp != '0') || (i == PHONE_NUMBER_LENGTH && temp != '\n') || (temp == '\n' && i != PHONE_NUMBER_LENGTH) || ((temp < '0' || temp > '9') && temp != '\n'))
		{
			printf("\tWrong phone number format! The correct format is 0xxxxxxxxxx.\n");
			if (temp != '\n') clear_buffer();
			return FALSE;
		}
		if (temp == '\n') break;
		phone_number[i] = temp;
	}
	phone_number[PHONE_NUMBER_LENGTH] = '\0';
	return TRUE;
}

/*This function reads username from console*/
int get_username(char** username)
{
	*username = NULL;
	char* tmp;
	char temp;
	int n = 0;
	while ((temp = (char)getchar()) != ' ' && temp != '\n')
	{
		tmp = (char*)realloc(*username, n + 1);
		n++;
		if (tmp == NULL)
		{
			printf("\tOops! Memory error!\n");
			return FALSE;
		}
		tmp[n - 1] = temp;
		*username = tmp;
	}
	tmp = (char*)realloc(*username, n + 1);
	if (tmp == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	tmp[n] = '\0';
	*username = tmp;
	if (strlen(*username) == 0)
	{
		if (temp != '\n') clear_buffer();
		printf("\tWrong format! No characters entered.\n");
		return FALSE;
	}
	if (temp == '\n') return ENTER;
	return TRUE;
}

/*This function reads password from console*/
int get_password(char** password)
{
	*password = NULL;
	char* tmp;
	char temp;
	int n = 0;
	while ((temp = (char)getchar()) != ' ' && temp != '\n')
	{
		tmp = (char*)realloc(*password, n + 1);
		n++;
		if (tmp == NULL)
		{
			printf("\tOops! Memory error!\n");
			return FALSE;
		}
		tmp[n - 1] = temp;
		*password = tmp;
	}
	tmp = (char*)realloc(*password, n + 1);
	if (tmp == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	tmp[n] = '\0';
	*password = tmp;
	if (strlen(*password) < MIN_PASS_LENGTH)
	{
		if (temp != '\n') clear_buffer();
		printf("\tWrong password format! Password should at least contain %d characters.\n", MIN_PASS_LENGTH);
		return FALSE;
	}
	if (temp == '\n') return ENTER;
	return TRUE;
}

/*This function reads message from console*/
int get_message(char** message)
{
	*message = NULL;
	char* tmp;
	char temp;
	int n = 0;
	while ((temp = (char)getchar()) != '\n')
	{
		tmp = (char*)realloc(*message, n + 1);
		n++;
		if (tmp == NULL)
		{
			printf("\tOops! Memory error!\n");
			return FALSE;
		}
		tmp[n - 1] = temp;
		*message = tmp;
	}
	tmp = (char*)realloc(*message, n + 1);
	if (tmp == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	tmp[n] = '\0';
	*message = tmp;
	if (strlen(*message) == 0)
	{
		printf("\tWrong message format! No characters entered.\n");
		return FALSE;
	}
	return TRUE;
}

/*This function reads command from console*/
int get_command(char** input)
{
	*input = NULL;
	char* tmp;
	char temp;
	int n = 0;
	while ((temp = (char)getchar()) != '\n' && temp != ' ')
	{
		tmp = (char*)realloc(*input, n + 1);
		n++;
		if (tmp == NULL)
		{
			printf("\tOops! Memory error!\n");
			return FALSE;
		}
		tmp[n - 1] = temp;
		*input = tmp;
	}
	tmp = (char*)realloc(*input, n + 1);
	if (tmp == NULL)
	{
		printf("\tOops! Memory error!\n");
		return FALSE;
	}
	tmp[n] = '\0';
	*input = tmp;
	if (strlen(*input) == 0)
	{
		printf("\tWrong command format! No characters entered.\n");
		if (temp != '\n') clear_buffer();
		return FALSE;
	}
	if (temp == '\n') return ENTER;
	return TRUE;
}

/*This function clears the std out buffer if needed*/
void clear_buffer()
{
	while (getchar() != '\n');
}

