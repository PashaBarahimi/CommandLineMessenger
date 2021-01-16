#pragma once
#include "structs.h"

int new_group(user_info* head_user, user_info* admin, group* head_group);
int add_to(user_info* head_user, user_info* user, group* head_group);
int add_user_to_group(group* gp, user_info* user);
