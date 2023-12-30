#include "Inverted.h"

void Search_Database(Wlist *w_head[])
{
	char word[WORD_SIZE];

	Colors(DARK_BLUE);
	printf("Enter the Word You Want to Search : ");
	Colors(NORMAL);
	
	scanf(" %s",word);		//Reading Word
	
	//Getting Index
	int index = tolower(word[0]) % 97;

	Wlist *search = w_head[index];
	Ltable *travel = NULL;

	//Traversing Word List untill search reaches NULL
	while ( search != NULL )
	{
		//Validating Whether Word is Repeated or Not & Printing the File Count
		if ( strcmp(search -> words,word) == 0 )
		{
			Colors(CYAN);
			printf("INFO : Word %s is Present in %d File(s) : \n",word,search -> file_count);

			//Storing Tlink address in travel
			travel = search -> Tlink;

			//Traversing Table untill travel reaches NULL & Printing the File name & word count
			while ( travel != NULL )
			{
				printf("In File %s for %d Time(s)\n",travel -> file_name,travel -> word_count);
			    travel =  travel -> table_link;			// Moving travel
			}
			
			return;

			Colors(NORMAL);
		}

		search = search -> link;		//Moving w_head
	}

	//Printing An Error if Word is Not Present
	Colors(RED);	
	printf("ERROR : %s Word is Not Present in Any of The Data Base!\n",word);
	Colors(NORMAL);
}


