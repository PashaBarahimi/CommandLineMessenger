#include <stdlib.h>
#include "add_node.h"
#define TRUE 1

/*The process of inserting the new user node to the linked list*/
void insert_user(user_info* head, user_info* new_user)
{
	while (TRUE)
	{
		if (head->next == NULL)
		{
			head->next = new_user;
			new_user->next = NULL;
			return;
		}
		head = head->next;
	}
}

/*The process of inserting the new message node to  the linked list*/
void insert_message(message* head, message* new_message)
{
	while (TRUE)
	{
		if (head->next == NULL)
		{
			head->next = new_message;
			new_message->next = NULL;
			return;
		}
		head = head->next;
	}
}

/*The process of inserting the new group node to the linked list*/
void insert_group(group* head, group* new_group)
{
	while (TRUE)
	{
		if (head->next == NULL)
		{
			head->next = new_group;
			new_group->next = NULL;
			return;
		}
		head = head->next;
	}
}

