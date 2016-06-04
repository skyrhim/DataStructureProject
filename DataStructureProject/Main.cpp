#include <cstring>
#include "UserBST.h"
#include "WordBST.h"

int count;
int main() {
	int command, inputReady = 0;
	UserBST users, usersF, userTC;
	WordBST words, wordsF;
	char tmp1[1000], tmp2[1000];
	UserBSTInit(&users);
	WordBSTInit(&words);
	while (1) {
		printf("0. Read data files\n");
		printf("1. display statistics\n");
		printf("2. Top 5 most tweeted words\n");
		printf("3. Top 5 most tweeted users\n");
		printf("4. Find users who tweeted a word\n");
		printf("5. Find all people who are firends of the above users\n");
		printf("6. Delete all mentions of a word\n");
		printf("7. Delete all users who mentioned a word\n");
		printf("8. Find strongly connected components\n");
		printf("9. Find shortest path from a given uesr\n");
		printf("99. Quit\n");
		printf("Select Menu : ");
		scanf("%d", &command);
		if (inputReady == 0 && command != 0) {
			printf("입력을 먼저 받아주세요.\n");
			continue;
		}
		if (inputReady == 1 && command == 0) {
			printf("이미 입력을 받았습니다. 다른 명령어를 선택해주세요.\n");
			continue;
		}
		switch (command) {
		case 0: {
			inputReady = 1;
			FILE* userIn = fopen("user.txt", "r");
			FILE* friendIn = fopen("friend.txt", "r");
			FILE* wordIn = fopen("word.txt", "r");
			char userId[30];
			char word[200];
			char friendId[30];
			while (fscanf(userIn, "%s", userId) != -1) {
				fgets(tmp1, 1000, userIn);
				fgets(tmp1, 1000, userIn);
				fgets(tmp1, 1000, userIn);
				fgets(tmp1, 1000, userIn);
				insertUser(&users, userId);
			}
			while (fscanf(wordIn, "%s", userId) != -1) {
				fgets(tmp1, 1000, wordIn);
				fgets(tmp1, 1000, wordIn);
				fscanf(wordIn, "%s", word);
				fgets(tmp1, 1000, wordIn);
				insertWord(&words, word, userId);
				userTweet(users.root, userId);
			}
			while (fscanf(friendIn, "%s", userId) != -1) {
				fgets(tmp1, 1000, friendIn);
				fscanf(friendIn, "%s", friendId);
				fgets(tmp1, 1000, friendIn);
				insertFriend(&users, userId, friendId);
			}
			printf("total user : %d\n", users.totalUesr);
			printf("total friendship record : %d\n", users.totalFriend);
			printf("total tweets : %d\n", words.totalTweet);
			//
			//printf("user tree height : %d\n", userTreeHeight(users.root));
			//printf("word tree height : %d\n", wordTreeHeight(words.root));
			//print(users.root);
			//printWord(words.root);
			break;
		}
		case 1:
			usersF = constructUserFTree(users);
			userTC = constructUserTCTree(users);
			printf("Average number of friends : %d\n", users.totalFriend / users.totalUesr);
			printf("Minimum number of friends : %d %s\n", findMinUser(usersF.root)->friends, findMinUser(usersF.root)->ID);
			printf("Maximum number of friends : %d %s\n\n", findMaxUser(usersF.root)->friends, findMaxUser(usersF.root)->ID);
			printf("Average tweets per user : %d\n", words.totalTweet / users.totalUesr);
			printf("Minimum tweets per uesr : %d %s\n", findMinUser(userTC.root)->tweetc, findMinUser(userTC.root)->ID);
			printf("Maximum tweets per user : %d %s\n", findMaxUser(userTC.root)->tweetc, findMaxUser(userTC.root)->ID);
			break;
		case 2:
			wordsF = constructWordFTree(words);
			count = 1;
			printTopFiveWord(wordsF.root);
			break;
		case 3:
			userTC = constructUserTCTree(users);
			count = 1;
			printTopFiveUser(userTC.root);
			break;
		case 99:
			return 0;
		default:
			printf("없는 명령어입니다. 다른 명령을 입력해주세요\n");
			break;
		}
	}
	return 0;
}
