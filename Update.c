#include "Inverted.h"

//Update_Database Function Definition
void Update_Database(Flist **f_head,Wlist *w_head[])
{
	int ret;
	char file_name[FNAME_SIZE];

	Colors(DARK_BLUE);
	printf("Enter the Filename : ");
	Colors(NORMAL);

	scanf("%s",file_name);				//Reading the file_name

	//Calling Check_File_Contents Function to check the File Contents 
	ret = Check_File_Contents(file_name);

	//Printing An Error if File is Not Present
    if ( ret == FILE_NOT_AVAILABLE )
    {
		Colors(RED);
       	printf("ERROR : Unable to Open %s File\n",file_name);
       	printf("ERROR : %s File is Not Available\n",file_name);
       	printf("ERROR : So Not Adding %s File into the List!\n",file_name);
		Colors(NORMAL);
    }

    //Printing An Error if File is Empty
    else if ( ret == FILE_EMPTY )
    {
		Colors(RED);
      	printf("ERROR : %s File is Empty! It has No Contents in it!\n",file_name);
      	printf("ERROR : So Not Adding %s File into the List!\n",file_name);
		Colors(NORMAL);
    }
	
	//Printing An Error if Duplicate File is Given
    else if ( ret == DUPLICATE_FILE )
    {
		Colors(RED);
        printf("ERROR : %s File is Already Added to the List!\n",file_name);
        printf("ERROR : So Not Adding %s File Again into the List!\n",file_name);
		Colors(NORMAL);
    }

    //Printing An Error if Adding File to List Operation is Failed
    else if ( ret == FAILURE )
	{
		Colors(RED);
    	printf("ERROR : Adding %s File into the List is Failure!\n",file_name);
		Colors(NORMAL);
	}

    //Validating Whether Validation of files is Success or not
    else if ( ret == SUCCESS )
    {
       //Calling Link_Files Function to Link File into the List
       ret = Link_Files(f_head,file_name);

       if ( ret == SUCCESS )
	   {
		   	Flist *travel = *f_head;
		   
		    //Traversing file list untill travel reaches NULL;
		   	while( travel != NULL )
           	{
			    //Calling Read_File_Contents Function if file names are Matching
           	 	if( strcmp(travel -> file_name, file_name) == 0 )	
				ret = Read_File_Contents(travel,w_head,file_name);
            
            	travel = travel -> link;	//Moving Travel
			}	

			if ( ret == SUCCESS )
			{
				Colors(GREEN);
				printf("INFO : Data Base is Created Successfully for %s\n",file_name);
				Colors(NORMAL);
			}

			else
			{
				Colors(RED);
				printf("ERROR : Creating Data Base for %s File is Failure!\n",file_name);
				Colors(NORMAL);
			}
			
	   }
	}
}

