#pragma once
#include "Project.h"
#ifndef Max
#define Max(a, b) (a) > (b) ? (a) : (b)
#endif 


void deleteUser(UserBST*, User*);
User* findMinUser(User*);
User* findMaxUser(User*);
void insertUser(UserBST*, char*, char*);
void transPlant(UserBST*, User*, User*);
int userTreeHeight(User*);
void UserBSTInit(UserBST*);
void print(User*);
void insertFriend(UserBST*, char*, char*);
void userTweet(User*, char*, Word*);
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
void delTweet(User*, Word*, int);
void cleanFiveUser();
void delFollower(User*);
void delFollowing(User*);
