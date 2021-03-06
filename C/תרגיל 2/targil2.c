#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WRONG_ARGUMENTS -1
#define CANNOT_OPEN_FILE -2
#define CANNOT_CLOSE_FILE -3

#define SIZE 1024
#define MAX_WORD 100

char* readLine(FILE* file);
char* getNextWord(char* str, int* index);
char* hasSynonym(char* word, FILE* vocFile);
char* replace_str(char *str, char *orig, char *rep);

int main(int argc, char* argv[])
{
	/* Local variables */
	FILE* vocFile = NULL;
	FILE* txtFile = NULL;
	FILE* outFile = NULL;
	char* txtLine = NULL;
	char* synWord = NULL;
	int rc = 0, indx = 0;

	/* Check arguments count */
	if (argc <= 2)
	{
		printf("Usage: targil2.exe file1 file2");
		return WRONG_ARGUMENTS;
	}

	/* Open files */
	vocFile = fopen(argv[1], "r");
	if (vocFile == NULL)
	{
		printf("Could not open %s.\n", argv[1]);
		return CANNOT_OPEN_FILE;
	}

	txtFile = fopen(argv[2], "r+");
	if (txtFile == NULL)
	{
		printf("Could not open %s.\n", argv[1]);
		fclose(vocFile);
		return CANNOT_OPEN_FILE;
	}

	outFile = fopen("out.txt", "w");
	if (outFile == NULL)
	{
		printf("Could not create new file.\n");
		fclose(txtFile);
		fclose(vocFile);
		return CANNOT_OPEN_FILE;
	}

	/** Recplace synonym words **/
	while ((txtLine = readLine(txtFile)) != EOF)
	{
		if (txtLine != NULL)
		{
			int len = strlen(txtLine);
			indx = 0;
			while (indx < strlen(txtLine))
			{
				char* words_split = getNextWord(txtLine, &indx);
				synWord = hasSynonym(words_split, vocFile);

				if (synWord != NULL)
				{
					txtLine = replace_str(txtLine, words_split, synWord);
					indx += strlen(synWord) - strlen(words_split);
				}

				++indx;
			}
		}

		fputs(txtLine, outFile);
	}

	/* Close files */
	if (fclose(vocFile) != 0)
	{
		printf("Could not close %s.\n", argv[1]);
		rc = CANNOT_CLOSE_FILE;
	}
	if (fclose(txtFile) != 0)
	{
		printf("Could not close %s.\n", argv[2]);
		rc = CANNOT_CLOSE_FILE;
	}
	if (fclose(outFile) != 0)
	{
		printf("Could not close new file.\n");
		rc = CANNOT_CLOSE_FILE;
	}

	remove(argv[2]);
	rename("out.txt", argv[2]);

    return rc;
}

/* readLine function - read a line from the file */
char* readLine(FILE* file)
{
	char buffer[SIZE];
	char* line = NULL;
	char c;
	int i = 0;

	c = fgetc(file);
	while (c != EOF && c != '\n')
	{
		buffer[i++] = c;
		c = fgetc(file);
	}
	buffer[i++] = '\0';

	if (c == EOF && i == 1)
		return EOF;
	else if (i > 1)
	{
		line = (char*)malloc(sizeof(char)*(i+1));
		strcpy(line, buffer);
		strcat(line, "\n");
	}
	return line;
}

/* getNextWord function - return first word from index in str*/
char* getNextWord(char* str, int* index)
{
	int i = 0;
	char* fWord = NULL;
	char temp[MAX_WORD];

	while (str[*index] != '\0' && str[*index] != ' ' && str[*index] != ',' && str[*index] != '.' && str[*index] != '-')
		temp[i++] = str[(*index)++];
	temp[i] = '\0';

	fWord = (char*)malloc(sizeof(char)*i);
	strcpy(fWord, temp);
	return fWord;
}

/* hasSynonym function - check if the vocabulary contains the word. if yes return synonym word */
char* hasSynonym(char* word, FILE* vocFile)
{
	char* line = NULL;

	fseek(vocFile, 0, SEEK_SET);
	while ((line = readLine(vocFile)) != EOF)
	{
		int len = strlen(line);
		int index = 0;
		int flag = 0;

		while (index < len)
		{
			if (strcmp(word, getNextWord(line, &index)) == 0)
			{
				if (flag != 0)
					index = -1;
				++index;
				return getNextWord(line, &index);
			}
			
			flag = 1;
			++index;
		}
	}

	return NULL;
}

/* replace_str function - replace orig to rep in str and returns new string */
char* replace_str(char *str, char *orig, char *rep)
{
	char buffer[SIZE];
	char* newStr = NULL;
	char *p = strstr(str, orig);

	strncpy(buffer, str, p - str); // Copy characters from 'str' start to 'orig' st$
	buffer[p - str] = '\0';
	sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));

	newStr = (char*)malloc(sizeof(char)*strlen(buffer));
	strcpy(newStr, buffer);
	return newStr;
}