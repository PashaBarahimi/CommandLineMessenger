#pragma once
#include "structs.h"

int edit_username(user_info* user, user_info* head_user, group* head_group, message* head_message);
int edit_password(user_info* user);
void edit_username_in_groups(user_info* user, group* head_group, char* input);
void edit_username_in_messages(user_info* user, message* head_message, char* input);
