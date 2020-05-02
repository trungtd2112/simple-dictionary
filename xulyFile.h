#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"


void Tach_Nghia(char *nguon, char *dich) 
{
	int i;
	for (int i = 0; i < strlen(nguon); i++) 
	{
		if (nguon[i] == '/') 
			break; 
	}
	char *s;
	s[0] = nguon[i];
	dich = strstr(nguon, s[0]); 
	nguon[i] = '\0'; 
}

void Create_BT(BTA **root)
{
	FILE *f;
	f = fopen("anhviet.txt", "r");
	*root = btcrt("data", 0, 0); 
	char word[Longest_Word];
	char mean[Longest_Mean];
	char temp[100];
	fgets(temp, 100, f);
	while(!feof(f))
	{
		char *ch;
		ch[0] = temp[1]; 
		char *s;
		s = strstr(temp, ch);
		while( temp[0] != '@') 
		{
			strcat(word, s);
			fgets(temp, 100, f);
		}
		Tach_Nghia(word, mean);
		btins(*root, word, mean, 500*sizeof(char) );
	}
}




