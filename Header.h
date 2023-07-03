#include <windows.h>
#include <stdio.h>
typedef struct INFORMATION_OF_USERS USER;
typedef struct INFORMATION_OF_MESSAGES MESSAGE;
typedef struct INFORMATION_OF_GROUPS GROUP;
typedef enum
{
	BLACK = 0, BLUE = 1, GREEN = 2,
	AQUA = 3, RED = 4, PURPLE = 5,
	YELLOW = 6, WHITE = 7, GRAY = 8,
	LIGHT_BLUE = 9, LIGHT_GREEN = 10,
	LIGHT_AQUA = 11, LIGHT_RED = 12,
	LIGHT_PURPLE = 13, LIGHT_YELLOW = 14,
	LIGHT_WHITE = 15
} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
struct INFORMATION_OF_USERS
{
	char* USERNAME;
	char* PHONE_NUMBER;
	char* PASSWORD;
	char* date_of_signup;
	int NUM_OF_USER;
	USER* next;
};
struct INFORMATION_OF_MESSAGES
{
	int NUM_OF_MESSAGE;
	int CHECK_BE_READ;
	char* TIME;
	char* TEXT;
	USER* SENDER;
	USER* RECEIVER;
	GROUP* GROUPNAME;
	MESSAGE* next;
};
struct INFORMATION_OF_GROUPS
{
	int NUM_OF_GROUP;
	int NUM_OF_ADMIN_USER;
	int NUM_OF_MEMBERS;
	char* G_NAME;
	USER* head_of_members;
	GROUP* next;
};
short set_Text_Color(const ConsoleColors foreground);
char* GET_IN_LOAD(FILE *information);
int CHECK_LENGHT(char* entry);
int CHECK_USERNAME_EXIST(char* USERNAME, USER* head, GROUP* head_group);
int CHECK_PASSWORD_IN_SIGNUP(char* PASSWORD);
int CHECK_PHONE_NUMBER_IN_SIGNUP(char* PHONE_NUMBER, USER* head);
int CHECK_PHONE_NUMBER_EXIST(char* PHONE_NUMBER, USER* head);
int CHECK_GROUP_NAME_EXIST(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group, char* CHECK_NAME);
char* RECIVE();
char* RECIVE_IN_MAIN(int* p_checking);
void EQUIVALEN_TWO_STRUCT(USER* a, USER* b);
int FIND_WHO_ENTERED1(USER* head, USER* WHO_ENTERED);
USER* FIND_WHO_ENTERED2(USER* head, int num);
USER* FIND_WHO_ENTERED_NORMAL(USER* head, char* CHECK_USER);
GROUP* FIND_GROUP(USER* head, GROUP* head_group, char* CHECK_GROUP, int special);
GROUP* FIND_GROUP_WHIT_NUMBER(USER* head, GROUP* head_group, int num);
int FIND_WHO_RECIEVE(USER* head, char* CHECK_USERNAME);
void EDIT_USERNAME(USER* WHO_ENTERED, USER* head, GROUP* head_group);
void EDIT_PASSWORD(USER* WHO_ENTERED);
char* RECIEVE_NOW_TIME();
void FREE_USER(USER* user);
int SIGNUP(USER* head, GROUP* head_group);
void INFO(USER* head, GROUP* head_group);
void ABOUT(USER* head);
void SEND_MESSAGE_TO_GROUP(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group, GROUP* GROUP_TARGETED, char* CHECK_TEXT, int i);
MESSAGE* HELP_SEND_MESSAGE(int i, USER* WHO_RECIVED, USER* WHO_ENTERED, char* CHECK_TEXT);
void SEND_MESSAGES(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group);
void SHOW_UNREAD_MESSAGE(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group);
void SHOW_SEND_MESSAGE(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group);
void SHOW_RECIEVE_MESSAGE(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group);
void CREAT_GROUP(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group);
void ADD_TO(USER* head, USER* WHO_ENTERED, MESSAGE* head_message, GROUP* head_group);
int GET_NUM_IN_LOAD(FILE *information);
void LOADING_INFORMATION_OF_USERS(USER* head);
void LOADING_INFORMATION_OF_GROUPS(USER* head, MESSAGE* head_message, GROUP* head_group);
void LOADING_INFORMATION_OF_MESSAGES(USER* head, MESSAGE* head_message, GROUP* head_group);
void WRITING_FILE1(USER* head, MESSAGE* head_message, GROUP* head_group);
void WRITING_FILE2(USER* head, MESSAGE* head_message, GROUP* head_group);
void WRITING_FILE3(USER* head, MESSAGE* head_message, GROUP* head_group);
void EXIT(USER* head, MESSAGE* head_message, GROUP* head_group);
void LOGIN_LIST(USER* head, int SPECIAL, MESSAGE* head_message, GROUP* head_group, USER* WHO_ENTERED);
void LOGIN(USER* head, int SPECIAL, MESSAGE* head_message, GROUP* head_group);
void MAIN_MENU(USER* head, MESSAGE* head_message, GROUP* head_group);
