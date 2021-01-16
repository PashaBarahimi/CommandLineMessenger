#pragma once
#include "structs.h"

int add_user(user_info* head, char* username, char* password, char* phone_number, date_time* sign_up_date);
int add_message(message* head, char* sender_username, char* receiver_username, char* message, date_time* message_date);
int create_group(group* head, char* name, char* admin_username);
date_time* date(void);
int get_earmark(message* head);
