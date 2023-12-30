#include "Inverted.h"

//Collecting Command Line Arguements in Main Function
int main(int argc,char *argv[])
{
	//system("clear");

	//Printing An Error & Usage if No Arguements are Passed
	if ( argc <= 1 )
	{
		Colors(RED);
		printf("ERROR : Usage!\n");
		Colors(NORMAL);
		
		Colors(GREEN);
		printf("USAGE : %s <file1> <file2> <file3> ... <filen>\n",argv[0]);
		Colors(NORMAL);
		
		return FAILURE;
	}

	Flist *f_head = NULL;		//Storing NULL in f_head
	Wlist *w_head[27] = {NULL};		//Storing NULL in w_head

	//Calling File_Validation Function to Validate File
	File_Validation(&f_head,argv);

	//Printing An Error if No Files Are Added
	if ( f_head == NULL )
	{
		Colors(RED);
		printf("ERROR : No Files are Added to the List!\n");
		Colors(NORMAL);
		
		return FAILURE;
	}

	char Choice;
	int Option;

	//Using Do - While loop untill Choice is Y or y
	do
	{
		Colors(DARK_BLUE);
		printf("#################### INVERTED SEARCH #######################\n");

		//Calling Menu Function to Display Menu
		Menu();
		scanf("%d",&Option);		//Reading Option

		//Using Switch Case for Option
		switch (Option)
		{
			//Case 1 is for Create
			case 1:

			//Calling Create_Database Function
			Create_Database(f_head,w_head);

			break;

			//Case 2 is for Display
			case 2:

			//Calling Display_Database Function
			Display_Database(w_head);

			break;

			//Case 3 is for Update
			case 3:

			//Calling Update_Database Function
			Update_Database(&f_head,w_head);

			break;

			//Case 4 is for Search
			case 4:

			//Calling Search_Database Function
			Search_Database(w_head);

			break;

			//Case 5 is for Save
			case 5:

			//Calling Save_Database Function 
			Save_Database(w_head);

			break;

			//Case 6 is for Exit
			case 6:

			Colors(GREEN);
			printf("INFO : Exited Successfully!\n");
			Colors(NORMAL);

			return SUCCESS;

			break;

			//Default Case is for Proper Choice
			default:

			Colors(RED);
			printf("Enter Proper Choice!\n");
			Colors(NORMAL);

			break;
		}
		
		Colors(YELLOW);
		printf("Do You Want to Continue? Enter (Y/y) to Continue : ");
		Colors(NORMAL);

		scanf(" %c",&Choice);
		__fpurge(stdout);
	
	} while ( Choice == 'Y' || Choice == 'y' );

	return SUCCESS;
}

//Colors Function Definition
void Colors(char *Colors)
{
	printf("%s",Colors);
}

//Menu Function Definition
void Menu(void)
{
	//Printing a Menu
	printf("1.Create Database\n");
	printf("2.Display Database\n");
	printf("3.Update Database\n");
	printf("4.Search Database\n");
	printf("5.Save Database\n");
	printf("6.Exit\n");
	printf("Enter Your Choice : ");
	Colors(NORMAL);
}

