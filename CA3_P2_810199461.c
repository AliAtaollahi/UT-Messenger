#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "Header.h"
#pragma warning(disable : 4996)
#define MIN_LENGTH_PASSWORD 6
#define LENGTH_PHONENUMBER 11
#define LENGTH_MESSAGE_TEXT 30
#define USERDATA "DATAUSER.txt"
#define MESSAGEDATA "DATAMESSAGE.txt"
#define GROUPDATA "DATAGROUP.txt"
int main()
{
	USER* head = malloc(sizeof(USER));                            //ijad ettelat va motghaiier haye avvalieh
	MESSAGE* head_message = malloc(sizeof(MESSAGE));
	GROUP* head_group = malloc(sizeof(GROUP));
	head->next = NULL;
	head_message->next = NULL;
	head_group->next = NULL;
	FILE *information;
	if (information = fopen(USERDATA, "r"))                  //chek boodan ya naboodan ettelaat az ghabl
	{
		LOADING_INFORMATION_OF_USERS(head);
		LOADING_INFORMATION_OF_GROUPS(head, head_message, head_group);
		LOADING_INFORMATION_OF_MESSAGES(head, head_message, head_group);
		fclose(information);
	}
	printf("WELCOME TO MY MESSANGER NOT UT :) \n	ALI ATAOLLAHI \nPLEASE ENTER COMMAND :\n**************************\n>> ");
	MAIN_MENU(head, head_message, head_group);         //hedayat be samt list asli
	return 0;
}
short set_Text_Color(const ConsoleColors foreground)
{
	Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	BufferInfo bufferInfo;
	if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
		return 0;
	Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
	SetConsoleTextAttribute(consoleHandle, color);
	return 1;
}
char* GET_IN_LOAD(FILE *information)
{
	char c;                  //khat be khat khandane file
	char* read = malloc(sizeof(char));
	int last = 0;
	while ((c = fgetc(information)) != '\n')
	{
		read[last] = c;
		last++;
		read = (char*)realloc(read, (last + 1) * sizeof(char));
	}
	read[last] = '\0';
	return read;
}
int CHECK_LENGHT(char* entry)
{
	int l = 0;                      //andaze girie tool har reshteh
	while (entry[l] != '\0')
		l++;
	l++;
	return (l);
}
int CHECK_USERNAME_EXIST(char* USERNAME, USER* head, GROUP* head_group)
{
	int check = 1;
	USER* alternative = malloc(sizeof(USER));
	USER* first = malloc(sizeof(USER));
	alternative = head;
	GROUP* find = head_group;
	while (find->next != NULL)
	{
		find = find->next;                                  //chek kardane inke gorohi ba in nam hast
		if (strcmp(find->G_NAME, USERNAME) == 0)
		{
			printf("	THERE IS THIS GROUPNAME . TRY ANOTHER ONE :\n");
			return 0;
		}
	}
	int i = 0;
	while ((alternative->next) != NULL)
	{
		alternative = (alternative->next);
		if (strcmp(USERNAME, alternative->USERNAME) == 0) check = 0;
		i++;
	}
	if (i != 0)
		if (strcmp(USERNAME, alternative->USERNAME) == 0) check = 0;                     //check kardane inke yoozery ba in nam hast
	if (check == 0)
		printf("	THERE IS THIS USERNAME . TRY ANOTHER ONE :\n");
	return check;
}
int CHECK_PASSWORD_IN_SIGNUP(char* PASSWORD)
{
	if ((CHECK_LENGHT(PASSWORD) - 1) >= MIN_LENGTH_PASSWORD)             //check karadne entebagh rams
		return 1;
	else
	{
		printf("	MIN OF PASSWORD LEGTH IS %d , TRY AGAIN :\n", MIN_LENGTH_PASSWORD);
		return 0;
	}
}
int CHECK_PHONE_NUMBER_IN_SIGNUP(char* PHONE_NUMBER, USER* head)
{
	int check = 1;
	for (int i = 0; i<(CHECK_LENGHT(PHONE_NUMBER) - 1); i++)                 //chek kardane phormate shomareh voroodi
		if (((PHONE_NUMBER[i] - '0')>9) || ((PHONE_NUMBER[i] - '0')<0))
			check = 0;
	if (check == 0)
		printf("	DON'T USE CARECTER IN PHONE NUMBER :\n");
	if (PHONE_NUMBER[0] != '0')
	{
		printf("	ENTER 0 IN FIRST OF PHONE NUMBER :\n");
		check = 0;
	}
	if ((CHECK_LENGHT(PHONE_NUMBER) - 1) != LENGTH_PHONENUMBER)
	{
		printf("	LENGTH OF PHONE NUMBER IS %d NOT %d :\n", LENGTH_PHONENUMBER, (CHECK_LENGHT(PHONE_NUMBER) - 1));
		check = 0;
	}
	return check;
}
int CHECK_PHONE_NUMBER_EXIST(char* PHONE_NUMBER, USER* head)
{
	{
		int check = 1;                                       //check kardane naboodan shomare vorodi dar shomareh haye ghabli
		USER* alternative = malloc(sizeof(USER));
		USER* first = malloc(sizeof(USER));
		alternative = head;
		int i = 0;
		while ((alternative->next) != NULL)
		{
			alternative = (alternative->next);
			if (strcmp(PHONE_NUMBER, alternative->PHONE_NUMBER) == 0) check = 0;
			i++;
		}
		if (i != 0)
			if (strcmp(PHONE_NUMBER, alternative->PHONE_NUMBER) == 0) check = 0;
		if (check == 0)
			printf("	THERE IS THIS PHONE_NUMBER . TRY ANOTHER ONE :\n");
		return check;
	}
}
int CHECK_GROUP_NAME_EXIST(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group, char* CHECK_NAME)
{
	USER* find_user = head;                            //chek kardane nabood nam grooh
	GROUP* find_group = head_group;
	while (find_user->next != NULL)
	{
		find_user = find_user->next;
		if (strcmp(find_user->USERNAME, CHECK_NAME) == 0)
		{
			printf("	THERE IS THIS NAME IN USERNAMES !!!\n>> ");
			return 0;
		}
	}
	while (find_group->next != NULL)
	{
		find_group = find_group->next;
		if (strcmp(find_group->G_NAME, CHECK_NAME) == 0)
		{
			printf("	THERE IS THIS NAME IN GROUP NAMES !!!\n>> ");
			return 0;
		}
	}
	return 1;
}
char* RECIVE()
{
	char* recive;                  //daryaft reshteh
	char c;
	recive = (char*)malloc(sizeof(char));
	int last = 0;
	while (((c = getchar()) != ' ') && (c != '\n'))
	{
		recive[last] = c;
		last++;
		recive = (char*)realloc(recive, (last + 1) * sizeof(char));
	}
	recive[last] = '\0';
	return recive;
}
char* RECIVE_IN_MAIN(int* p_checking)
{
	char* recive;                  //daryaft reshteh dar menu
	char c;
	recive = (char*)malloc(sizeof(char));
	int last = 0;
	while (((c = getchar()) != ' ') && (c != '\n'))
	{
		recive[last] = c;
		last++;
		recive = (char*)realloc(recive, (last + 1) * sizeof(char));
	}
	recive[last] = '\0';
	if (c == '\n') *p_checking = 1;
	return recive;
}
void EQUIVALEN_TWO_STRUCT(USER* a, USER* b)
{
	a->NUM_OF_USER = b->NUM_OF_USER;        //barabar sazi do esteract
	a->PASSWORD = b->PASSWORD;
	a->PHONE_NUMBER = b->PHONE_NUMBER;
	a->USERNAME = b->USERNAME;
	a->next = NULL;
}
int FIND_WHO_ENTERED1(USER* head, USER* WHO_ENTERED)
{
	int check = 0, check_sum = 1;                         //peyda kardane shomare yoozere voroodi ke dar login estefadeh mikonim
	WHO_ENTERED = head;
	char* CHECK_USERNAME = RECIVE();
	char* CHECK_PASS = RECIVE();
	while ((WHO_ENTERED->next) != NULL) {
		WHO_ENTERED = (WHO_ENTERED->next);
		if (strcmp(WHO_ENTERED->USERNAME, CHECK_USERNAME) == 0) {
			check = 1;
			break;
		}
	}
	if (strcmp(WHO_ENTERED->USERNAME, CHECK_USERNAME) == 0) check = 1;
	if (check == 1) check = strcmp(WHO_ENTERED->PASSWORD, CHECK_PASS);
	else {
		printf("	THERE ISN'T THIS USERNAME !!!\n>> ");
		check_sum = 0;
	}
	if ((check == 0) && (check_sum == 1)) check_sum = (WHO_ENTERED->NUM_OF_USER + 1);
	else if (check_sum == 1) {
		printf("	PASSWORD IS NOT MATCHED !!!\n>> ");                     //chek entebagh rams
		check_sum = 0;
	}
	if (check_sum == 0) {
		free(CHECK_USERNAME);
		free(CHECK_PASS);
	}
	return check_sum;
}
USER* FIND_WHO_ENTERED2(USER* head, int num)
{
	USER* find = malloc(sizeof(USER));    //peyda kardane user ba shomare
	find = head;
	while ((find->NUM_OF_USER) != (num - 1))
		find = (find->next);
	return find;
}
USER* FIND_WHO_ENTERED_NORMAL(USER* head, char* CHECK_USER)
{
	USER* finding = head;          //peyda kardane yoozer bedoon shomre tartib yoozer
	while (finding->next != NULL)
	{
		finding = finding->next;
		if (strcmp(finding->USERNAME, CHECK_USER) == 0) return finding;
	}
	printf("	THERE IS NOT THIS USERNAME!!!\n>> ");
	return NULL;
}
GROUP* FIND_GROUP(USER* head, GROUP* head_group, char* CHECK_GROUP, int special)
{
	GROUP* find = head_group;               //peyda kardane yek goroh
	while (find->next != NULL)
	{
		find = find->next;
		if (strcmp(find->G_NAME, CHECK_GROUP) == 0) return find;
	}
	if (special) printf("	THERE IS NOT THIS GROUP!!!\n>> ");
	return NULL;
}
GROUP* FIND_GROUP_WHIT_NUMBER(USER* head, GROUP* head_group, int num)
{
	GROUP* finding = head_group;          //peyda kardan goroh ba shomare an
	while (finding->next != NULL)
	{
		finding = finding->next;
		if (finding->NUM_OF_GROUP == num) return finding;
	}
	return NULL;
}
int FIND_WHO_RECIEVE(USER* head, char* CHECK_USERNAME)
{
	int i = 0;                       //peyda kardane yek yoozer dar halet kolli
	int check = 0;
	USER* find = malloc(sizeof(USER));
	find = head;
	while ((find->next) != NULL)
	{
		find = (find->next);
		i++;
		if (strcmp(find->USERNAME, CHECK_USERNAME) == 0)
		{
			check = 1;
			break;
		}
	}
	if (check == 1)
		return i;
	else
	{
		printf("	THERE ISN'T THIS USERNAME !!! \n>> ");
		return 0;
	}
}
void EDIT_USERNAME(USER* WHO_ENTERED, USER* head, GROUP* head_group)
{
	int check = 0;
	USER* finding = malloc(sizeof(USER));              //edit kardane username
	char* CHECK_USERNAME = RECIVE();
	finding = head;
	while (finding->next != NULL)
	{
		finding = finding->next;
		if (strcmp(finding->USERNAME, CHECK_USERNAME) == 0)            //chek tekrari ba username haye ghabli naboodan
		{
			if (strcmp(WHO_ENTERED->USERNAME, CHECK_USERNAME) == 0)printf("		YOU ENTER YOUR LAST USERNAME !!!\n>> ");
			else printf("	YOU ENTER OTHER USERS USERNAME !!!\n>> ");
			free(CHECK_USERNAME);
			return;
		}
	}
	check = CHECK_USERNAME_EXIST(CHECK_USERNAME, head, head_group);
	if (check)
	{
		WHO_ENTERED->USERNAME = CHECK_USERNAME;
		printf("	YOU EDIT YOUR USERNAME SUCCESSFULLY !!! :\n");
	}
	else free(CHECK_USERNAME);
	printf(">> ");
}
void EDIT_PASSWORD(USER* WHO_ENTERED)
{
	char* CHECK_PASSWORD;              //edit password
	CHECK_PASSWORD = RECIVE();
	if ((CHECK_PASSWORD_IN_SIGNUP(CHECK_PASSWORD)) == 1)
	{
		if (strcmp(CHECK_PASSWORD, WHO_ENTERED->PASSWORD) == 0)                       //chek tekrari naboodan
		{
			printf("	EDIT FAILED !!! YOU ENTERED PREVIOUS PASSWORD !!! \n>> ");
			free(CHECK_PASSWORD);
		}
		else
		{
			printf("	YOU EDIT YOUR PASSWORD SUCCESSFULLY !!! \n>> ");
			int i = 0;
			for (i = 0; CHECK_PASSWORD[i] != '\0'; i++)
				WHO_ENTERED->PASSWORD[i] = CHECK_PASSWORD[i];
			WHO_ENTERED->PASSWORD[i] = '\0';
		}

	}
	else
	{
		free(CHECK_PASSWORD);
		return;
	}
}
char* RECIEVE_NOW_TIME()
{
	int i;                    //daryaft zaman hal
	char* time_now;
	time_t currenttime;
	time(&currenttime);
	time_now = malloc(sizeof(char) * 26);
	strcpy(time_now, ctime(&currenttime));
	for (i = 0; time_now[i] != '\n'; i++) {}
	time_now[i] = '\0';
	return time_now;
}
void FREE_USER(USER* user)
{
	free(user->date_of_signup);
	free(user->next);
	free(user->PASSWORD);
	free(user->PHONE_NUMBER);
	free(user->USERNAME);
	free(user);
}
int SIGNUP(USER* head, GROUP* head_group) {
	int CHECK_PASSWORD = 1, CHECK_PHONE_NUMBER = 1, CHECK_USERNAME = 1, i = 0;
	USER* new_information = malloc(sizeof(USER));                  //gereftan etelaat az karbar va gharar dadan dar struct
	USER* alternative = head;
	USER* first = alternative;
	for (i = 0; (alternative->next) != NULL; i++) alternative = (alternative->next);
	new_information->USERNAME = RECIVE();
	CHECK_USERNAME = CHECK_USERNAME_EXIST(new_information->USERNAME, head, head_group);
	new_information->PASSWORD = RECIVE();
	CHECK_PASSWORD = CHECK_PASSWORD_IN_SIGNUP(new_information->PASSWORD);
	new_information->PHONE_NUMBER = RECIVE();
	CHECK_PHONE_NUMBER = CHECK_PHONE_NUMBER_IN_SIGNUP(new_information->PHONE_NUMBER, head);
	if (CHECK_PHONE_NUMBER == 1) CHECK_PHONE_NUMBER = CHECK_PHONE_NUMBER_EXIST(new_information->PHONE_NUMBER, head);
	new_information->NUM_OF_USER = i;
	new_information->date_of_signup = RECIEVE_NOW_TIME();
	new_information->next = NULL;
	if ((CHECK_PASSWORD == 1) && (CHECK_PHONE_NUMBER == 1) && (CHECK_USERNAME == 1)) {
		alternative->next = new_information;
		head = first;
		printf("	YOU REGISTERED SUCESSFULLY AND LOGIN AUTOMATICALY !!!\n>> ");
		return 1;
	}
	else {
		FREE_USER(new_information);
		printf(">> ");
		return 0;
	}
}
void INFO(USER* head, GROUP* head_group)
{
	USER* info = malloc(sizeof(USER));         //namayesh etelaat karbaran
	info = head;
	if (info->next == NULL)
	{
		printf("	THERE ISN'T ANY USERNAME !!!\n>> ");
		return;
	}
	while ((info->next) != NULL)
	{
		info = (info->next);
		printf("	USER %d IS %s\n", (info->NUM_OF_USER + 1), (info->USERNAME));
	}
	GROUP* find = malloc(sizeof(GROUP));
	find = head_group;
	while (find->next != NULL)		 //namayesh etelaat gorooh ha
	{
		find = find->next;
		printf("	GROUP %d IS %s\n", (find->NUM_OF_GROUP) + 1, find->G_NAME);
	}
	printf(">> ");
}
void ABOUT(USER* head)
{
	USER* WHO_ENTERED = malloc(sizeof(USER));                //namayesh etelaat karbar
	WHO_ENTERED = head;
	char* CHECK_USERNAME;
	CHECK_USERNAME = RECIVE();
	int check = 0;
	while ((WHO_ENTERED->next) != NULL)
	{
		WHO_ENTERED = (WHO_ENTERED->next);
		if (strcmp(WHO_ENTERED->USERNAME, CHECK_USERNAME) == 0)
		{
			check = 1;
			break;
		}
	}
	if (check)
		printf("	USER %d HIS USERNAME IS %s\n	date of signup is %s \n	HIS PHONE NUMBER IS %s\n>> ", (WHO_ENTERED->NUM_OF_USER + 1), WHO_ENTERED->USERNAME, WHO_ENTERED->date_of_signup, WHO_ENTERED->PHONE_NUMBER);
	else
		printf("	THERE IS NOT THIS USERNAME !!! \n>> ");
}
void SEND_MESSAGE_TO_GROUP(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group, GROUP* GROUP_TARGETED, char* CHECK_TEXT, int i)
{
	USER* circle_in_members = GROUP_TARGETED->head_of_members;             //ijad chand payam be teadad azaye gorooh
	while (circle_in_members->next != NULL)
	{
		i = 0;
		circle_in_members = circle_in_members->next;
		MESSAGE* NEW_LIST_MESSAGES = head_message;
		MESSAGE* first = NEW_LIST_MESSAGES;
		while (NEW_LIST_MESSAGES->next != NULL) {
			NEW_LIST_MESSAGES = NEW_LIST_MESSAGES->next;
			i++;
		}
		MESSAGE* new_information = malloc(sizeof(MESSAGE));
		new_information->next = NULL;
		new_information->NUM_OF_MESSAGE = i;
		new_information->CHECK_BE_READ = 1;
		new_information->RECEIVER = circle_in_members;
		new_information->SENDER = WHO_ENTERED;
		new_information->TEXT = CHECK_TEXT;
		new_information->TIME = RECIEVE_NOW_TIME();
		new_information->GROUPNAME = GROUP_TARGETED;
		NEW_LIST_MESSAGES->next = new_information;
		head_message = first;
	}
	printf("	MESSAGE SUCESSFULLY SENT !!!\n>> ");
}
MESSAGE* HELP_SEND_MESSAGE(int i, USER* WHO_RECIVED, USER* WHO_ENTERED, char* CHECK_TEXT)
{
	MESSAGE* new_information = malloc(sizeof(MESSAGE));               //bakhshi az code ersal message ke baraye kahesh khate tabe inja ghara dade shode
	new_information->next = NULL;
	new_information->NUM_OF_MESSAGE = i;
	new_information->CHECK_BE_READ = 1;
	new_information->RECEIVER = WHO_RECIVED;
	new_information->SENDER = WHO_ENTERED;
	if (strcmp(new_information->RECEIVER->USERNAME, new_information->SENDER->USERNAME) == 0) new_information->CHECK_BE_READ = 0;
	new_information->TEXT = CHECK_TEXT;
	new_information->TIME = RECIEVE_NOW_TIME();
	new_information->GROUPNAME = NULL;
	return new_information;
}
void SEND_MESSAGES(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group) {
	int num = 0, i = 0;                            //anjam marahel ersal payam va anjam an
	char* CHECK_USERNAME = RECIVE();
	char* CHECK_TEXT = RECIVE();
	USER* WHO_RECIVED = malloc(sizeof(USER));
	MESSAGE* alternative = head_message;
	MESSAGE* first = alternative;
	GROUP* GROUP_TARGETED = FIND_GROUP(head, head_group, CHECK_USERNAME, 0);
	if (GROUP_TARGETED != NULL) {                                                            //check karadane inke payam goroohi bashad ya normal
		SEND_MESSAGE_TO_GROUP(head, WHO_ENTERED, head_message, head_group, GROUP_TARGETED, CHECK_TEXT, i);
		return;
	}
	num = FIND_WHO_RECIEVE(head, CHECK_USERNAME);
	if (num == 0) {
		free(CHECK_USERNAME);
		return;
	}
	WHO_RECIVED = FIND_WHO_ENTERED2(head, num);
	while ((alternative->next) != NULL) {
		alternative = (alternative->next);
		i++;
	}
	alternative->next = HELP_SEND_MESSAGE(i, WHO_RECIVED, WHO_ENTERED, CHECK_TEXT);
	head_message = first;
	printf("	MESSAGE SUCESSFULLY SENT !!!\n>> ");
}
void SHOW_UNREAD_MESSAGE(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group)
{
	int first_time = 1;
	MESSAGE* find = malloc(sizeof(MESSAGE));                  //namayesh payam haye read nashodeh dar soorati ke vojood dashteh bashand
	find = head_message;
	while ((find->next) != NULL)
	{
		find = (find->next);
		if ((strcmp(find->RECEIVER->USERNAME, WHO_ENTERED->USERNAME) == 0) && (find->CHECK_BE_READ == 1))
		{
			if (strcmp(find->RECEIVER->USERNAME, find->SENDER->USERNAME) == 0) continue;
			if (first_time == 1) {
				printf("	UNREAD MESSAGES :\n");
				first_time = 0;
			}
			if (find->GROUPNAME == NULL) printf("	MESSAGE FROM %s at %s\n", find->SENDER->USERNAME, find->TIME);
			else printf("	IN GROUP %s MESSAGE FROM %s at %s\n", find->GROUPNAME->G_NAME, find->SENDER->USERNAME, find->TIME);
		}
	}
}
void SHOW_SEND_MESSAGE(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group)
{
	int check = 0;
	char* CHECK_USERNAME;                      //namayesh payam haye ersali va halat an
	CHECK_USERNAME = RECIVE();
	MESSAGE* find = head_message;
	while (find->next != NULL) {
		find = find->next;
		if ((strcmp(find->SENDER->USERNAME, WHO_ENTERED->USERNAME) == 0) && (strcmp(CHECK_USERNAME, find->RECEIVER->USERNAME) == 0) && (find->GROUPNAME == NULL)) {          //payam haye normal
			check = 1;
			if (find->CHECK_BE_READ) set_Text_Color(LIGHT_GREEN);
			printf("	MESSAGE TO %s IS : %s at %s\n", find->RECEIVER->USERNAME, find->TEXT, find->TIME);
			set_Text_Color(WHITE);
		}
		if ((strcmp(find->SENDER->USERNAME, WHO_ENTERED->USERNAME) == 0) && (find->GROUPNAME != NULL)) {              //payam haye goroohi
			if (strcmp(CHECK_USERNAME, find->GROUPNAME->G_NAME) != 0) continue;
			if (find->RECEIVER->NUM_OF_USER != find->GROUPNAME->NUM_OF_ADMIN_USER) continue;
			check = 1;
			if (find->CHECK_BE_READ) set_Text_Color(LIGHT_GREEN);
			printf("	IN GROUP %s MESSAGE IS : %s at %s\n", find->GROUPNAME->G_NAME, find->TEXT, find->TIME);
			set_Text_Color(WHITE);
		}
	}
	if (check == 0)
		printf("	YOU HAS'NT SENT ANY MESSAGE TO %s !!! \n", CHECK_USERNAME);
	free(CHECK_USERNAME);
	printf(">> ");
}
void SHOW_RECIEVE_MESSAGE(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group)
{
	int check = 0;                            //namayesh payam haye daryafti
	char* CHECK_USERNAME;
	CHECK_USERNAME = RECIVE();
	MESSAGE* find = malloc(sizeof(MESSAGE));
	find = head_message;
	while (find->next != NULL)
	{
		find = find->next;
		if (((strcmp(find->RECEIVER->USERNAME, WHO_ENTERED->USERNAME) == 0) && (strcmp(CHECK_USERNAME, find->SENDER->USERNAME) == 0)) && ((find->GROUPNAME == NULL)))          //payam haye normal
		{
			check = 1;
			find->CHECK_BE_READ = 0;
			printf("	MESSAGE FORM %s IS : %s at %s\n", find->SENDER->USERNAME, find->TEXT, find->TIME);
		}
		if ((strcmp(find->RECEIVER->USERNAME, WHO_ENTERED->USERNAME) == 0) && (find->GROUPNAME != NULL))               //payam haye goroohi
		{
			if (strcmp(CHECK_USERNAME, find->GROUPNAME->G_NAME) != 0) continue;
			check = 1;
			find->CHECK_BE_READ = 0;
			printf("	IN GROUP %s MESSAGE FROM %s : %s at %s\n", find->GROUPNAME->G_NAME, find->SENDER->USERNAME, find->TEXT, find->TIME);
		}
	}
	if (check == 0)
		printf("	YOU HAS'NT RECIEVED ANY MESSAGE FROM %s !!! \n", CHECK_USERNAME);
	free(CHECK_USERNAME);
	printf(">> ");
}
void CREAT_GROUP(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group)
{
	int i = 0;                                  //ijad yek grooh va anjam tamam jozyiaat an
	char* CHECK_NAME = RECIVE();
	if (CHECK_GROUP_NAME_EXIST(head, WHO_ENTERED, head_message, head_group, CHECK_NAME))
	{
		GROUP* new_information = malloc(sizeof(GROUP));
		GROUP* NEW_LIST_OF_GROUP = head_group;
		GROUP* first = NEW_LIST_OF_GROUP;
		USER* new_member = malloc(sizeof(USER));
		EQUIVALEN_TWO_STRUCT(new_member, WHO_ENTERED);
		while (NEW_LIST_OF_GROUP->next != NULL)
		{
			NEW_LIST_OF_GROUP = NEW_LIST_OF_GROUP->next;
			i++;
		}
		new_information->G_NAME = CHECK_NAME;
		new_information->head_of_members = malloc(sizeof(GROUP));
		new_information->head_of_members->next = new_member;
		new_information->NUM_OF_ADMIN_USER = WHO_ENTERED->NUM_OF_USER;
		new_information->NUM_OF_GROUP = i;
		new_information->NUM_OF_MEMBERS = 1;
		new_information->next = NULL;
		NEW_LIST_OF_GROUP->next = new_information;
		head_group = first;
		printf("	YOU SUCUSSFULLY CREAT %s GROUP AND YOU ARE ADMIN OF THIS GROUP!!!\n>> ", CHECK_NAME);
	}
	else free(CHECK_NAME);
}
void ADD_TO(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group) {
	char* CHECK_GROUP = RECIVE();                    //ezafe karadane karbarane mored nazar
	char* CHECK_USER = RECIVE();
	GROUP* GROUP_TARGETED = malloc(sizeof(GROUP));
	USER* WHO_TARGETED = malloc(sizeof(USER));
	if ((GROUP_TARGETED = FIND_GROUP(head, head_group, CHECK_GROUP, 1)) == NULL) return;          //chek vojood grooh
	if (GROUP_TARGETED->NUM_OF_ADMIN_USER != WHO_ENTERED->NUM_OF_USER) {                     //chek admin boodan
		printf("	YOU ARE NOT ADMIN OF THIS GROUP!!!\n>> ");
		return;
	}
	if ((WHO_TARGETED = FIND_WHO_ENTERED_NORMAL(head, CHECK_USER)) == NULL) return;            //chek vojood fard
	USER* new_member = malloc(sizeof(USER));
	EQUIVALEN_TWO_STRUCT(new_member, WHO_TARGETED);
	USER* NEW_LIST_MEMBERS = GROUP_TARGETED->head_of_members;
	USER* first = NEW_LIST_MEMBERS;
	while (NEW_LIST_MEMBERS->next != NULL) {                               //chek ozviat nadashtan
		NEW_LIST_MEMBERS = NEW_LIST_MEMBERS->next;
		if (NEW_LIST_MEMBERS->NUM_OF_USER == WHO_TARGETED->NUM_OF_USER) {
			printf("	THIS USER IS MEMBERED FROM BEFORE !!!\n>> ");
			return;
		}
	}
	NEW_LIST_MEMBERS->next = new_member;
	GROUP_TARGETED->head_of_members = first;
	(GROUP_TARGETED->NUM_OF_MEMBERS)++;
	printf("	YOU SUCUSSFULLY ADD %s TO %s !!!\n>> ", WHO_TARGETED->USERNAME, GROUP_TARGETED->G_NAME);
}
int GET_NUM_IN_LOAD(FILE *information)
{
	char c;                              //daryaft yek khat dar load be soorat adadi
	int num = 0, helper = 1;
	while ((c = fgetc(information)) != '\n')
	{
		num = (num*helper) + c - '0';
		helper = helper * 10;
	}
	return num;
}
void LOADING_INFORMATION_OF_USERS(USER* head)
{
	char* CHECK;                                       //khandane file va ettelaate user ha
	USER* new_information = malloc(sizeof(USER));
	USER* find1 = head;
	USER* first = find1;
	FILE* USERLOAD = fopen(USERDATA, "r");
	rewind(USERLOAD);
	while (1)
	{
		while (find1->next != NULL)
			find1 = find1->next;
		new_information = malloc(sizeof(USER));
		CHECK = GET_IN_LOAD(USERLOAD);
		if (strcmp(CHECK, "+") == 0) break;
		new_information->USERNAME = CHECK;
		new_information->PASSWORD = GET_IN_LOAD(USERLOAD);
		new_information->PHONE_NUMBER = GET_IN_LOAD(USERLOAD);
		new_information->date_of_signup = GET_IN_LOAD(USERLOAD);
		new_information->NUM_OF_USER = GET_NUM_IN_LOAD(USERLOAD);
		new_information->next = NULL;
		find1->next = new_information;
	}
	head = first;
	fclose(USERLOAD);
}
void LOADING_INFORMATION_OF_GROUPS(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	FILE *GROUPLOAD = fopen(GROUPDATA, "r");              //khandane file va ettelaate gorooh ha
	rewind(GROUPLOAD);
	GROUP* new_list = head_group;
	GROUP* first1 = new_list;
	char* CHECK1;
	while (1) {
		CHECK1 = GET_IN_LOAD(GROUPLOAD);
		if (strcmp(CHECK1, "+") == 0) break;
		GROUP* new_information1 = malloc(sizeof(GROUP));
		USER* list_members = malloc(sizeof(USER));
		list_members->next = NULL;
		USER* first2 = list_members;
		new_information1->G_NAME = CHECK1;
		new_information1->NUM_OF_ADMIN_USER = GET_NUM_IN_LOAD(GROUPLOAD);
		new_information1->NUM_OF_GROUP = GET_NUM_IN_LOAD(GROUPLOAD);
		new_information1->NUM_OF_MEMBERS = GET_NUM_IN_LOAD(GROUPLOAD);
		for (int i = 0; i < (new_information1->NUM_OF_MEMBERS); i++) {
			char* CHECK2 = GET_IN_LOAD(GROUPLOAD);
			while (list_members->next != NULL) list_members = list_members->next;
			USER* find = FIND_WHO_ENTERED_NORMAL(head, CHECK2);
			USER* new_information2 = malloc(sizeof(USER));
			EQUIVALEN_TWO_STRUCT(new_information2, find);
			list_members->next = new_information2;
		}
		new_information1->head_of_members = first2;
		new_information1->next = NULL;
		new_list->next = new_information1;
		new_list = new_list->next;
	}
	head_group = first1;
	fclose(GROUPLOAD);
}
void LOADING_INFORMATION_OF_MESSAGES(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	int CHECK1;                                   //khandane file va ettelaate message ha
	char* CHECK2;
	MESSAGE* find1 = head_message;
	MESSAGE* first = find1;
	FILE *MESSAGELOAD = fopen(MESSAGEDATA, "r");
	rewind(MESSAGELOAD);
	while (1)
	{
		while (find1->next != NULL) find1 = find1->next;
		MESSAGE* new_information = malloc(sizeof(MESSAGE));
		CHECK2 = GET_IN_LOAD(MESSAGELOAD);
		if (strcmp(CHECK2, "+") == 0) break;
		new_information->TEXT = CHECK2;
		new_information->TIME = GET_IN_LOAD(MESSAGELOAD);
		CHECK1 = GET_NUM_IN_LOAD(MESSAGELOAD);
		if (CHECK1 == 0) new_information->GROUPNAME = NULL;
		else new_information->GROUPNAME = FIND_GROUP_WHIT_NUMBER(head, head_group, CHECK1 - 1);
		new_information->CHECK_BE_READ = GET_NUM_IN_LOAD(MESSAGELOAD);
		new_information->NUM_OF_MESSAGE = GET_NUM_IN_LOAD(MESSAGELOAD);
		new_information->SENDER = FIND_WHO_ENTERED2(head, GET_NUM_IN_LOAD(MESSAGELOAD) + 1);
		new_information->RECEIVER = FIND_WHO_ENTERED2(head, GET_NUM_IN_LOAD(MESSAGELOAD) + 1);
		new_information->next = NULL;
		find1->next = new_information;
	}
	head_message = first;
	fclose(MESSAGELOAD);
}
void WRITING_FILE1(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	FILE* USERSAVE = fopen(USERDATA, "w");                 //neveshtane file va ettelaate user ha
	USER* find_user = head;
	while ((find_user->next) != NULL)
	{
		find_user = find_user->next;
		fprintf(USERSAVE, "%s\n%s\n%s\n%s\n%d\n", find_user->USERNAME, find_user->PASSWORD, find_user->PHONE_NUMBER, find_user->date_of_signup, find_user->NUM_OF_USER);
	}
	fprintf(USERSAVE, "+\n");
	fclose(USERSAVE);
}
void WRITING_FILE2(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	FILE* MESSAGESAVE = fopen(MESSAGEDATA, "w");            //neveshtane file va ettelaate message ha
	MESSAGE* find_message = head_message;
	while ((find_message->next) != NULL)
	{
		find_message = find_message->next;
		int alternative = 0;
		if (find_message->GROUPNAME != NULL) alternative = find_message->GROUPNAME->NUM_OF_GROUP + 1;
		fprintf(MESSAGESAVE, "%s\n%s\n%d\n%d\n%d\n%d\n%d\n", find_message->TEXT, find_message->TIME, alternative, find_message->CHECK_BE_READ, find_message->NUM_OF_MESSAGE, find_message->SENDER->NUM_OF_USER, find_message->RECEIVER->NUM_OF_USER);
	}
	fprintf(MESSAGESAVE, "+\n");
	fclose(MESSAGESAVE);
}
void WRITING_FILE3(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	FILE* GROUPSAVE = fopen(GROUPDATA, "w");            //neveshtane file va ettelaate gorooh ha
	GROUP* find_group = head_group;
	while ((find_group->next) != NULL)
	{
		find_group = find_group->next;
		USER* list_member = find_group->head_of_members;
		fprintf(GROUPSAVE, "%s\n%d\n%d\n%d\n", find_group->G_NAME, find_group->NUM_OF_ADMIN_USER, find_group->NUM_OF_GROUP, find_group->NUM_OF_MEMBERS);
		for (int i = 0; i < find_group->NUM_OF_MEMBERS; i++) {
			list_member = list_member->next;
			fprintf(GROUPSAVE, "%s\n", list_member->USERNAME);
		}
	}
	fprintf(GROUPSAVE, "+\n");
	fclose(GROUPSAVE);
}
void EXIT(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	WRITING_FILE1(head, head_message, head_group);          //khorooj az barname
	WRITING_FILE2(head, head_message, head_group);
	WRITING_FILE3(head, head_message, head_group);
	printf("	GOOD LUCK !!! \n");
	exit(0);
}
void LOGIN_LIST(USER* head, int SPECIAL, MESSAGE* head_message, GROUP* head_group, USER* WHO_ENTERED)
{
	int checking_login = 0;             //otagh faremane bakhshe dakheli barname va daryaft dastoor va hedayat be samt tabea anjam an
	char* order;
	while (1)
	{
		order = RECIVE_IN_MAIN(&checking_login);
		if (strcmp(order, "logout") == 0) {
			printf("	YOU LOGOUT !!!\n>> ");
			break;
		}
		else if (strcmp(order, "close") == 0) EXIT(head, head_message, head_group);
		else if (strcmp(order, "edit_username") == 0) EDIT_USERNAME(WHO_ENTERED, head, head_group);
		else if (strcmp(order, "edit_password") == 0) EDIT_PASSWORD(WHO_ENTERED);
		else if (strcmp(order, "info") == 0) INFO(head, head_group);
		else if (strcmp(order, "about") == 0) ABOUT(head);
		else if (strcmp(order, "send") == 0) SEND_MESSAGES(head, WHO_ENTERED, head_message, head_group);
		else if (strcmp(order, "show_sent") == 0) SHOW_SEND_MESSAGE(head, WHO_ENTERED, head_message, head_group);
		else if (strcmp(order, "show_received") == 0) SHOW_RECIEVE_MESSAGE(head, WHO_ENTERED, head_message, head_group);
		else if (strcmp(order, "create_group") == 0) CREAT_GROUP(head, WHO_ENTERED, head_message, head_group);
		else if (strcmp(order, "add_to") == 0) ADD_TO(head, WHO_ENTERED, head_message, head_group);
		else if (strcmp(order, "help") == 0) printf("	***IN SECOND LIST YOU CAN ENTER\n	1-edit_username <new username>\n	2-edit_password <new password>\n	3-send <username> <content>\n	4-show_sent <username>\n	5-show_ received <username>\n	6-about <username>\n	7-create_group <group_name>\n	8-add_to <group name> <username>\n	9-logout\n	10-close\n>> ");
		else if (checking_login == 1) {
			printf("	USE CORRECT COMMAND !!!\n>> ");
			checking_login = 0;
		}
		free(order);
	}
	free(order);
}
void LOGIN(USER* head, int SPECIAL, MESSAGE* head_message, GROUP* head_group)
{
	USER* WHO_ENTERED = malloc(sizeof(USER));
	WHO_ENTERED = head;
	int num = 0;
	char* GARBAGE;
	if (head->next == NULL) {                                     //chek vojood user
		GARBAGE = RECIVE();                                  //gereftan ettelate ezafe va bedoone ehtiaj
		GARBAGE = RECIVE();
		free(GARBAGE);
		printf("	THERE ISN'T ANY USERNAME !!!\n>> ");
		return;
	}
	if (SPECIAL == 1)
		while ((WHO_ENTERED->next) != NULL)
			WHO_ENTERED = (WHO_ENTERED->next);
	else
	{
		if ((num = FIND_WHO_ENTERED1(head, WHO_ENTERED)) == 0) return;
		else
		{
			printf("	YOU LOGIN SUCCESSFULLY !!! \n");
			WHO_ENTERED = FIND_WHO_ENTERED2(head, num);
			SHOW_UNREAD_MESSAGE(head, WHO_ENTERED, head_message, head_group);
			printf(">> ");
		}
	}
	LOGIN_LIST(head, SPECIAL, head_message, head_group, WHO_ENTERED);
}
void MAIN_MENU(USER* head, MESSAGE* head_message, GROUP* head_group)
{
	int SPECIAL = 0, checking = 0, check_exist_command = 1;                    //otagh faremane bakhshe khareji va ma ghabl vorood be bakhsh dakheli barname va daryaft dastoor va hedayat be samt tabea anjam an
	char* command;
	while (1)
	{
		if (SPECIAL == 1) command = "login";
		else command = RECIVE_IN_MAIN(&checking);
		if (strcmp(command, "close") == 0) EXIT(head, head_message, head_group);
		else if (strcmp(command, "signup") == 0) SPECIAL = SIGNUP(head, head_group);
		else if (strcmp(command, "login") == 0) {
			LOGIN(head, SPECIAL, head_message, head_group);
			check_exist_command = 0;
			SPECIAL = 0;
		}
		else if (strcmp(command, "info") == 0) INFO(head, head_group);
		else if (strcmp(command, "help") == 0) printf("	***IN FIRST LIST YOU CAN ENTER\n	1-signup <username> <password> <number>\n	2-login <username> <pass>\n	3-info\n	4-close\n>> ");
		else if (strcmp(command, "logout") == 0) printf("	YOU CAN NOT LOGOUT BEFORE LOGIN \n>> ");
		else if (checking == 1) {
			printf("	USE CORRECT COMMAND !!!\n>> ");
			checking = 0;
		}
		else printf("");
		if (check_exist_command == 1) free(command);
		check_exist_command = 1;
	}
}