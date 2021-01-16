#pragma once
#include "structs.h"

void save_process(user_info* head_user, message* head_message, group* head_group);
int save_users(user_info* head);
int save_messages(message* head);
int save_groups(group* head);
void read_process(user_info* head_user, message* head_message, group* head_group);
int read_users(user_info* head);
int read_messages(message* head);
int read_groups(group* head);
char* read_from_file(FILE* input, char sep);
char** groups_users(int num);
