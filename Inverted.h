#ifndef INVERTED_H
#define INVERTED_H

//Including Header Files
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Defining Return Macros
#define SUCCESS					0
#define FAILURE			   	   -1
#define FILE_EMPTY   		   -2
#define FILE_NOT_AVAILABLE     -3
#define DUPLICATE_FILE		   -4

//Defining Macros
#define FNAME_SIZE			   15
#define WORD_SIZE			   10

//Defining Colour Macros
#define RED			"\x1b[031m"
#define GREEN		"\x1b[032m"
#define BLUE		"\x1b[034m"
#define DARK_BLUE 	"\x1b[034;1m"
#define YELLOW		"\x1b[033m"
#define MAGENTA 	"\x1b[035m"
#define CYAN 		"\x1b[36m"
#define NORMAL		"\x1b[0m"

//Creating a New type Flist
typedef struct file_node
{
	char file_name[FNAME_SIZE];
	struct file_node *link;
} Flist;

//Creating a New Type Ltable
typedef struct table_node
{
	int word_count;
	char file_name[FNAME_SIZE];
	struct table_node *table_link;
} Ltable;

//Creating a New Type Wlist
typedef struct word_node
{
	int file_count;
	char words[WORD_SIZE];
	Ltable *Tlink;
	struct word_node *link;
} Wlist;

/* Function Prototypes */

//Function to Display a Menu
void Menu(void);

//Function to Print Colored Texts
void Colors(char *Color);

//Function to Validate Arguements and Files
void File_Validation(Flist **f_head,char *argv[]);

//Function to Check File is Empty or Not
int Check_File_Contents(char *File_Name);

//Function to Create List and Link Files
int Link_Files(Flist **f_head,char *file_name);

//Function to Create Database
void Create_Database(Flist *f_head,Wlist *w_head[]);

//Function to Read the File Contents
int Read_File_Contents(Flist *f_head,Wlist *w_head[],char *file_name);

//Function to Update the Word Count when words are Repeated
int Update_Word_Count(Wlist **w_head,char *file_name);

//Function to Insert the Node into List
int Insert_Word_Node(Wlist **w_head,char *data);

//Function to Make a Link Table
int Make_Link_Table(Wlist **w_head);

//Function to Display the Data base
void Display_Database(Wlist *w_head[]);

//Function to Print the Contents of Data base
void Print_Contents(Wlist *w_head);

//Function to Update the Database
void Update_Database(Flist **f_head,Wlist *w_head[]);

//Function to Search a Word in Database
void Search_Database(Wlist *w_head[]);

//Function to Save the Database
void Save_Database(Wlist *w_head[]);

//Function to Write Data Base contents to File
void Write_to_File(Wlist *w_head,FILE *Backup);

#endif

