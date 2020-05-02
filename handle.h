
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "btree.h"
#include"soundex.h"
#define Longest_Word 30
#define Longest_Mean 10000

void SoundexCode_of_Dic(BTA *Dic, BTA **SoundexCode_Tree)
{
	char word[Longest_Word];
	char mean[Longest_Mean];
	int real_size;
	char soundex_code[5];
	*SoundexCode_Tree = btcrt("soundexTree", 0, 0);
	btsel(Dic, "", mean, Longest_Mean*sizeof(char), &real_size);
	while( btseln(Dic, word, mean, Longest_Mean*sizeof(char), &real_size) == 0)
	{
		SoundEx(soundex_code, word, 4, 1);
		btins(*SoundexCode_Tree, word, soundex_code, 5*sizeof(char));
	}
}

int SuggestWord(BTA *SoundexCode_Tree, char *word, char result[][100]){
	int real_size, count=0;
	char en[40], soundex[5], code[5];
	SoundEx(code, word, 4, 1);
	btsel(SoundexCode_Tree,"", soundex, 5*sizeof(char), &real_size);
	while(btseln(SoundexCode_Tree, en, soundex, 5*sizeof(char), &real_size)==0 && count<49){
		if(strcmp(code,soundex)==0)
			strcpy(result[count++], en);
	}
	return count;
}

int check(char *str1, char *str2)
{
	int l1 = strlen(str1);
	int l2 = strlen(str2);
	if (l1 > l2) return 0;
	else if ( strncmp(str1, str2, l1) == 0) 
	{
		return 1;
	}
	return 0;
}

int CompleteWord(BTA *SoundexCode_Tree, char *word, char *fullWord)
{
	int real_size;
	char temp[Longest_Word];
	char code[5];
	btsel(SoundexCode_Tree, "", code, 5*sizeof(char), &real_size);
	while( btseln(SoundexCode_Tree, temp, code, 5*sizeof(char), &real_size) == 0)
	{
		if (check(word, temp) == 1)
		{
			strcpy(fullWord, temp);
			return 1;
		}
	}
	return 0;
}

void Show_SoundexTree(BTA *SoundexCode_Tree)
{
	char word[Longest_Word];
	char code[5];
	int real_size;
	btsel( SoundexCode_Tree, "", code, 5*sizeof(char), &real_size);
	while (btseln( SoundexCode_Tree, word, code, 5*sizeof(char), &real_size) == 0)
	{
		printf("%s\n%s\n", word, code);
	}
}

void Show_DicTree(BTA *Dic)
{
	char word[Longest_Word];
	char mean[Longest_Mean];
	int real_size;
	btsel( Dic, "", mean, Longest_Mean*sizeof(char), &real_size);
	while ( btseln( Dic, word, mean, Longest_Mean*sizeof(char), &real_size) == 0)
	{
		printf("%s\n%s\n", word, mean);
	}
}


