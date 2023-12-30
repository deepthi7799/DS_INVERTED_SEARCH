#include "Inverted.h"

//File_Validation Function Definition
void File_Validation(Flist **f_head,char *argv[])
{
	int h = 1, ret;

	//Using While loop untill argv[h] reaches NULL
	while ( argv[h] != NULL )
	{
		//Calling Check_File_Contents Function to Check File is Empty or not
		ret = Check_File_Contents(argv[h]);

		//Printing An Error if File is Not Present
		if ( ret == FILE_NOT_AVAILABLE )
		{
			Colors(RED);
			printf("ERROR : Unable to Open %s File\n",argv[h]);
			printf("ERROR : %s File is Not Available\n",argv[h]);
			printf("ERROR : So Not Adding %s File into the List!\n",argv[h]);
			Colors(NORMAL);
		}

		//Printing An Error if File is Empty
		else if ( ret == FILE_EMPTY )
		{
			Colors(RED);
			printf("ERROR : %s File is Empty! It has No Contents in it!\n",argv[h]);
			printf("ERROR : So Not Adding %s File into the List!\n",argv[h]);
			Colors(NORMAL);
		}

		//Validating Whether Validation of files is Success or not
		else if ( ret == SUCCESS )
		{
			//Calling Link_Files Function to Link Files into the List
			ret = Link_Files(f_head,argv[h]);

			//Printing An Error if Duplicate File is Given
			if ( ret == DUPLICATE_FILE )
			{
				Colors(RED);
				printf("ERROR : %s File is Already Added to the List!\n",argv[h]);			
				printf("ERROR : So Not Adding %s File Again into the List!\n",argv[h]);
				Colors(NORMAL);
			}

			//Printing An Error if Adding File to List Operation is Failed
			else if ( ret == FAILURE )
			{
				Colors(RED);
				printf("ERROR : Adding %s File into the List is Failure!\n",argv[h]);
				Colors(NORMAL);
			}

		}

		//Incrementing h and continueing loop
		h++;
		continue;
	}
}

//Check_File_Contents Function Definition
int Check_File_Contents(char *File_Name)
{
	//Opening the File in read Mode
	FILE *Fptr = fopen(File_Name,"r");

	//Returning FILE_NOT_AVAILABLE if File is Not Present
	if ( Fptr == NULL )
	return FILE_NOT_AVAILABLE;

	//Moving The File Offset to Last Position
	fseek(Fptr,0,SEEK_END);

	//Returning FILE_EMPTY if File has no Contents
	if ( ftell(Fptr) == 0 )
	return FILE_EMPTY;

	return SUCCESS;
}

//Link_Files Function Definition
int Link_Files(Flist **f_head,char *Files)
{
	//Creating A New Node
	Flist *insert = malloc(sizeof(Flist));

	//Returning FAILURE if Node is Not Created
	if ( insert == NULL )
	return FAILURE;

	//Updating the Fields of Node
	strcpy(insert -> file_name,Files);
	insert -> link = NULL;

	//Inserting the Node at First if List is Empty
	if ( *f_head == NULL )
	{
		*f_head = insert;
		return SUCCESS;
	}

	//Storing Head address in travel & NULL in previous
	Flist *travel = *f_head;
	Flist *previous = NULL;

	//Traversing the List untill travel reaches NULL
	while ( travel != NULL )
	{
		//Returning DUPLICATE_FILE if Same File is Given which is Already is Present in the List
		if ( strcmp(travel -> file_name,Files) == 0 )  
		return DUPLICATE_FILE;

		//Updating prev & Moving Travel
		previous = travel;
		travel = travel -> link;
	}

	//Linking Previous File with New File
	previous -> link = insert;

	return SUCCESS;
}

