#pragma once

typedef struct date_time
{
	int year;
	int month;
	int day;
	int hour;
	int min;
}date_time;

typedef struct user_info
{
	char* username;
	char* password;
	char* phone_number;
	date_time* sign_up_date;
	struct user_info* next;
}user_info;

typedef struct message
{
	char* sender_username;
	char* receiver_username;
	char* content;
	date_time* message_date;
	int read_check;
	int earmark;
	struct message* next;
}message;

typedef struct group
{
	char* name;
	char* admin_username;
	int user_num;
	char** users;
	struct group* next;
}group;
