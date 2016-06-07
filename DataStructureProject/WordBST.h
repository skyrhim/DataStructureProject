#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "Project.h"
#ifndef Max
#define Max(a, b) (a) > (b) ? (a) : (b)
#endif 


struct Word {
	char tweet[300];
	UserList* first;
	int userCount;
	Word* parent;
	Word* left;
	Word* right;
	int color;
};
struct WordBST {
	int height;
	int totalTweet;
	Word* root;
};
void deleteWord(WordBST*, Word*);
Word* findMinWord(Word*);
Word* findMaxWord(Word*);
void insertWord(WordBST*, char*, char*);
void transPlant(WordBST*, Word*, Word*);
int wordTreeHeight(Word*);
void WordBSTInit(WordBST*);
void printWord(Word*);
void printTopFiveWord(Word*);
void WordinsertFixUp(WordBST*, Word*);
void WordleftRotate(WordBST*, Word*);
void WordrightRotate(WordBST*, Word*);
void destroyWordTree(WordBST);
Word* findWord(Word*, char*);
void printTweetUser(Word*);
void freeWord(Word*);
void printTopFiveTweetWord(WordBST);