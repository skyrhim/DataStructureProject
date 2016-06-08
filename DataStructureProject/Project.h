#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <Windows.h>

struct User;
struct Word;
struct UserList;
struct wordList {
	Word* word;
	int count;
	wordList* next;
};

struct User {
	char ID[30];
	char screenName[100];
	wordList* wordFirst;
	UserList* following;
	UserList* follower;
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
struct UserList {
	User* user;
	int count;
	UserList* next;
};