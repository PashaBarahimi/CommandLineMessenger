#include <string.h>
#include "existence_check.h"

user_info* phone_number_existence_check(user_info* head, char* phone_number)
{
	while ((head = head->next))
		if (!strcmp(head->phone_number, phone_number))
			return head;
	return NULL;
}

user_info* username_existence_check(user_info* head, char* username)
{
	while ((head = head->next))
		if (!strcmp(head->username, username))
			return head;
	return NULL;
}

group* group_name_existence_check(group* head, char* name)
{
	while ((head = head->next))
		if (!strcmp(head->name, name))
			return head;
	return NULL;
}
