#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "command.h"
#include "get_input.h"
#include "account.h"
#include "file.h"
#define ENTER (-1)
#define TRUE 1
#define MAIN_MENU 2
#define LOGIN 4
#define SIGN_UP 5
#define CLOSE 6

/*Program starts here*/
int main()
{
	user_info* head_user = (user_info*)malloc(sizeof(user_info));
	message* head_message = (message*)malloc(sizeof(message));
	group* head_group = (group*)malloc(sizeof(group));
	if (head_user == NULL || head_message == NULL || head_group == NULL) exit(1);
	head_user->next = NULL;
	head_message->next = NULL;
	head_group->next = NULL;
	read_process(head_user, head_message, head_group);
	printf("Welcome To UT Messenger\n\nEnter your command:\n");
	while (TRUE)
	{
		int enter_check;
		const int cmd = command(MAIN_MENU, &enter_check);
		if (cmd == CLOSE) save_process(head_user, head_message, head_group);
		if ((cmd == LOGIN || cmd == SIGN_UP) && (enter_check == ENTER))
		{
			printf("\tWrong command format.\n");
			continue;
		}
		if (cmd == LOGIN) sign_in(head_user, head_group, head_message);
		else if (cmd == SIGN_UP) sign_up(head_user, head_group, head_message);
		else
		{
			printf("\tThis command is not valid here, you should sign in first.\n");
			if (enter_check != ENTER) clear_buffer();
		}
	}
}
