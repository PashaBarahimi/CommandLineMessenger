#include <string.h>
#include "existence_check.h"

/*This function checks if the number already exists and returns the user_info if it exists and null if it doesn't*/
user_info* phone_number_existence_check(user_info* head, char* phone_number)
{
	while ((head = head->next))
		if (!strcmp(head->phone_number, phone_number))
			return head;
	return NULL;
}

/*This function checks if the username already exists and returns the user_info if it exists and null if it doesn't*/
user_info* username_existence_check(user_info* head, char* username)
{
	while ((head = head->next))
		if (!strcmp(head->username, username))
			return head;
	return NULL;
}

/*This function checks if the group already exists and returns the group if it exists and null if it doesn't*/
group* group_name_existence_check(group* head, char* name)
{
	while ((head = head->next))
		if (!strcmp(head->name, name))
			return head;
	return NULL;
}
