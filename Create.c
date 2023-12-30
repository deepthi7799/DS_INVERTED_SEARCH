#include "Inverted.h"

char *f_name;

//Create_Database Function Definition
void Create_Database(Flist *f_head,Wlist *w_head[])
{
	int ret;
	//Travesing the list untill Last node
	while ( f_head != NULL )
	{
		//Calling Read_File_Contents Function to Read the File Contents
		ret = Read_File_Contents(f_head,w_head,f_head -> file_name);

		//Printing an Error if Creating Data Base Oepration is Failed
		if ( ret == FAILURE )
		{
			Colors(RED);
			printf("ERROR : Creating Data Base for %s File is Failure!\n",f_head -> file_name);
			Colors(NORMAL);
		}
		
		else if ( ret == SUCCESS )
		{
			Colors(GREEN);
			printf("INFO : Data Base is Created Sucessfully for %s File\n",f_head -> file_name);
			Colors(NORMAL);
		}

		//Moving f_head
		f_head = f_head -> link;
	}
}

//Read_File_Contents Function Definition
int Read_File_Contents(Flist *f_head,Wlist *w_head[],char *file_name)
{
	//Storing the File Name
	f_name = file_name;

	//Opening the File in read Mode
	FILE *Fptr = fopen(file_name,"r");

	fseek(Fptr,0,SEEK_SET);

	char words[100];
	int index, flag = 1, ret;
	Wlist *travel = NULL;

	//Reading Words from File Untill EOF
	while ( fscanf(Fptr,"%s",words) != EOF )
	{
		//Getting Index to Store the Word
		index = tolower(words[0]) % 97;

		//Storing 26 as Index if the Word is Not An Alphabet
		if ( index > 25 )
		index = 26;

		//Validating Whether w_head[index] is NULL or not
		if ( w_head[index] != NULL )
		{
			travel = w_head[index];			//Storing The Word Address in Travel

			//Traversing the List to Validate for Repeated Words
			while ( travel != NULL )
			{
				//Validating if Words are Repeated or Not
				if ( strcmp(travel -> words,words) == 0 )
				{
					//Calling Update_Word_Count Function to Increment Word Count
					ret = Update_Word_Count(&travel,file_name);

					if ( ret == FAILURE )
					{
						Colors(RED);
						printf("ERROR : Failed to Update Word Count of %s Word!\n",words);
						Colors(NORMAL);
					}

					flag = 0;		//Updating Flag
					break;
				}

				travel = travel -> link;	//Moving travel
			}
		}

		//Calling Insert_Word_Node Function if Words are Different
		if ( flag == 1 )
		{
			ret = Insert_Word_Node(&w_head[index],words);

			//Printing An Error if Inserting the Word into Data Base Operation is Failed
			if ( ret == FAILURE )
			{
				Colors(RED);
				printf("ERROR : Failed to Insert %s Word of %s File into the Data Base!\n",words,file_name);
				Colors(NORMAL);
				
				return FAILURE;
			}
		}
	}

	//Closing the File
	fclose(Fptr);

	return SUCCESS;
}

//Update_Word_Count Function Definition
int Update_Word_Count(Wlist **w_head,char *file_name)
{	
	Ltable *travel_table = (*w_head) -> Tlink;	//Storing Tlink address in travel_table
	Ltable *previous = NULL;

	//Traversing Table untill travel_table reaches NULL
	while ( travel_table != NULL )
	{
		//Incrementing the Word Count if word is repeated in the Same File 
		if ( strcmp(travel_table -> file_name,file_name) == 0 )
		{
			travel_table -> word_count++;
			return SUCCESS;
		}

		//Updating Previous and Moving travel_table
		previous = travel_table;
		travel_table = travel_table -> table_link;
	}

	//Incrementing the File count if word is repeated in Different file
	(*w_head) -> file_count++;

	//Creating a New Table
	Ltable *Table = malloc(sizeof(Ltable));

	//Returning FAILURE if Table is Not Created
	if ( Table == NULL )
	return FAILURE;

	//Updating the Fields of Table
	Table -> word_count = 1;
	strcpy(Table -> file_name,file_name);
	Table -> table_link = NULL;

	//Linking Previous Table & New Table
	previous -> table_link = Table;

	return SUCCESS;
}

//Insert_Word_Node Function Definition
int Insert_Word_Node(Wlist **w_head,char *data)
{
	int ret;

	//Creating a New Node
	Wlist *node = malloc(sizeof(Wlist));

	//Returning FAILURE if Node is Not Created
	if ( node == NULL )
	return FAILURE;

	//Updating the Fields of Node
	node -> file_count = 1;
	strcpy(node -> words,data);
	node -> Tlink = NULL;
	node -> link = NULL;

	//Calling Make_Link_Table Function to Create a Link table for Node
	ret = Make_Link_Table(&node);

	//Printing an Error if Linking Table and Node Operation is Failed
	if ( ret == FAILURE )
	{
		Colors(RED);
		printf("ERROR : Linking Node With Table is Failed for %s Word!\n",data);
		Colors(NORMAL);

		return FAILURE;
	}	

	//Inserting the New Node at First if List is Empty
	if ( *w_head == NULL )
	{
		*w_head = node;
		return SUCCESS;
	}

	//Stroing w_head address in travel
	Wlist *travel = *w_head;

	//Traversing the List Untill Travel reaches last Node
	while ( travel -> link != NULL )
	travel = travel -> link;

	//Linking New node at Last
	travel -> link = node;

	return SUCCESS;
}

//Make_Link_Table Function Definition
int Make_Link_Table(Wlist **w_head)
{
	//Creating a New Table
	Ltable *Table = malloc(sizeof(Ltable));

	//Returning FAILURE if Table is Not Created
	if ( Table == NULL )
	return FAILURE;

	//Updating the Fields of Table
	Table -> word_count = 1;
	strcpy(Table -> file_name,f_name);
	Table -> table_link = NULL;

	//Linking the Table with Node
	(*w_head) -> Tlink = Table;

	return SUCCESS;
}

