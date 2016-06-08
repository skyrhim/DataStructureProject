#pragma once
#include "Project.h"
#ifndef Max
#define Max(a, b) (a) > (b) ? (a) : (b)
#endif 



void deleteWord(WordBST*, Word*);
Word* findMinWord(Word*);
Word* findMaxWord(Word*);
Word* insertWord(WordBST*, char*, User*);
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
void deleteWord(WordBST*, Word*);
void WorddeleteFixUp(WordBST*, Word*, Word*);
void delTweetWord(User*);