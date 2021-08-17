#include "editor.h"
#include <string.h>

//TASK FOUR:
int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos)
{
	//a boolean integer, on whether insertion occured or not.
	int inserted = 0;
	
	//STEP ONE: create a copy
	char unmodified[editing_buflen];
	strncpy(unmodified, editing_buffer, editing_buflen);
	
	//STEP TWO: insert the character...
	for(int i = 0; i < editing_buflen; i++)
	{
		if(i == pos)
		{
			editing_buffer[i] = to_insert;
			inserted = 1;
		}
		else if(inserted == 1)
		{
			editing_buffer[i] = unmodified[i-1];
		}
		else //if it reaches this else statement, character has not been inserted yet.
		{
			editing_buffer[i] = unmodified[i];
		}
	}
	
	return inserted;
}


//TASK FIVE:
int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset)
{
	//a boolean integer, on whether deletion occured or not.
	int deleted = 0;
	
	//STEP ONE: create a copy
	char unmodified[editing_buflen];
	strncpy(unmodified, editing_buffer, editing_buflen);
	
	//STEP TWO: delete the character...
	for(int i = 0; i < editing_buflen; i++)
	{
		if(deleted == 1)
		{
			editing_buffer[i-1] = unmodified[i];
		}
		else if(i >= offset)
		{
			if(editing_buffer[i] == to_delete)
			{
				deleted = 1;
			}
		}
	}
	
	return deleted;
}

//TASK SIX:
int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset)
{
	//integers determining the position. and size of the word within the editing buffer.
	int start = -1;
	int targetSize = strlen(str);
	int replacementSize = strlen(replacement);
	int endString = -1; //index of the last letter of str. comes in handy for "STEP THREE" as the "secondHalf"'s iterator.
	int end = -1;	//index of the last letter of replacement. This is what the program returns...
	
	//the first half of string, and the second half. These two combined, makes the editing_buffer without the str targetted for replacement.
	char firstHalf[editing_buflen];
	char secondHalf[editing_buflen];
	
	//STEP ONE: scan, detect and copy
	int strIterator = 0;
	int matchCount = 0;
	for(int i = 0; i < editing_buflen; i++)
	{
		if(i >= offset)
		{
			if(editing_buffer[i] == str[strIterator]) //see if the letter by letter case matches... (str[] should start at index 0)
			{
				if(start == -1)
				{
					start = i;
				}
				strIterator++;
				matchCount++; //this ENSURES that the ENTIRE str array has been detected...
			}
		}
		
		//below we create a version of editing_buffer without the removed string.
		if(start == -1) //start of the string not detected yet
		{
			firstHalf[i] = editing_buffer[i];
		}
		else if(matchCount == targetSize) //start string has been detected and passed
		{
			secondHalf[i] = editing_buffer[i];
		}
	}
	endString = start+strIterator;
	
	//STEP TWO: placement
	if(matchCount >= targetSize)
	{
		int replacementIterator = 0;
		for(int i = 0; i < editing_buflen; i++)
		{
			if(i < start)
			{
				editing_buffer[i] = firstHalf[i];
			}
			else if(i >= start && i < (replacementSize + start)) //if iterator inbetween the start index AND the (supposed) final replacement letter index
			{
				editing_buffer[i] = replacement[replacementIterator];
				replacementIterator++;
				end = i;
			}
			else
			{
				editing_buffer[i] = secondHalf[endString - 1];
				endString++;
			}
		}
	}
	
	return end;
}
