#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "Project.h"
#ifndef Max
#define Max(a, b) (a) > (b) ? (a) : (b)
#endif 

struct wordList {
	char* word;
	wordList* next;
};

struct User {
	char ID[30];
	wordList* wordFirst;
	UserList* first;
	int friends;
	int tweetc;
	User* parent;
	User* left;
	User* right;
	int color;
};
struct UserBST {
	int height;
	int totalUesr;
	int totalFriend;
	User* root;
};
void deleteUser(UserBST*, User*);
User* findMinUser(User*);
User* findMaxUser(User*);
void insertUser(UserBST*, char*);
void transPlant(UserBST*, User*, User*);
int userTreeHeight(User*);
void UserBSTInit(UserBST*);
void print(User*);
void insertFriend(UserBST*, char*, char*);
void userTweet(User*, char*, char*);
void destroyUserTree(UserBST);
void printTopFiveUser(User*);
void UserinsertFixUp(UserBST*, User*);
void UserleftRotate(UserBST*, User*);
void UserrightRotate(UserBST*, User*);
void freeUser(User*);
User* findUser(User*, char*);
void printFriends();
void printMinMaxUser(UserBST, int);
void printTopFiveTweetUser(UserBST);
void UserdeleteFixUp(UserBST*, User*, User*);
void delTweet(User*, char*);
