#include "Inverted.h"

//Save_Database Function Definition
void Save_Database(Wlist *w_head[])
{
	char file_name[FNAME_SIZE];

	Colors(DARK_BLUE);
	printf("Enter the File Name to Save The Database : ");
	Colors(NORMAL);

	scanf("%s",file_name);		//Reading File Name

	//Opening the File in Write Mode
	FILE *Back_up = fopen(file_name,"w");

	//Using For Loop to Check w_head[i] is NULL or Not
	for ( int i = 0; i < 27; i++ )
	{
		//Calling Write_to_File Function to Write the Data base to the File
		if ( w_head[i] != NULL )
		Write_to_File(w_head[i],Back_up);
	}

	Colors(GREEN);
	printf("INFO : Database is Saved Successfully in %s File\n",file_name);
	Colors(NORMAL);

	//Closing the File
	fclose(Back_up);
}

//Write_to_File Function Definition
void Write_to_File(Wlist *w_head,FILE *Backup)
{
	Ltable *t_head = NULL;
	int index;

	//Traversing Word List untill w_head reaches NULL
	while ( w_head != NULL )
	{
		//Getting Index
		index = tolower(w_head -> words[0]) % 97;

		//Writting Index,Word & File Count to the File
		fprintf(Backup,"Index: #%d\nWord: %s     File Count: %d     ",index,w_head -> words,w_head -> file_count);

		t_head = w_head -> Tlink;		//Storing w_head -> Tlink in t_head

		//Traversing Table untill t_head reaches NULL
		while ( t_head != NULL )
		{
			//Writting File Name & Word Count to File
			fprintf(Backup,"File Name: %s     Word Count: %d\n",t_head -> file_name,t_head -> word_count);

			t_head = t_head -> table_link;		//Moving t_head
		}

		w_head = w_head -> link;		//Moving w_head
	}
}


		
