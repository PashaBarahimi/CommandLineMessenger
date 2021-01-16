#pragma once
#include "structs.h"

int send_message(user_info* head_user, user_info* sender, group* head_group, message* head_message);
int show_sent_messages(user_info* head_user, user_info* sender, group* head_group, message* head_message);
int group_sent_messages(user_info* sender, char* group_name, message* head_message, group* head_group);
int show_received_messages(user_info* head_user, user_info* receiver, group* head_group, message* head_message);
int group_message_check(group* head_group, message* head_message, user_info* sender, char* group_name, int enter_check);
int send_message_to_group(group* receiver, message* head_message, char* input_message, user_info* sender);
int print_sent_messages(char* sender, char* receiver, message* head);
int print_received_messages(char* sender, char* receiver, message* head);
int group_received_messages(user_info* receiver, char* group_name, message* head_message, group* head_group);
void message_info_print(user_info* user, message* head);
