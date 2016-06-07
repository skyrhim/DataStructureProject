#include "UserBST.h"
#include "WordBST.h"

bool isNum(char * chr) {
	for (; *chr; chr++) {
		if (*chr < '0' || *chr > '9') {
			return false;
		}
	}
	return true;
}

int count;

int main() {
	int command, inputReady = 0;
	UserBST users;
	WordBST words;
	char tmp1[1000], tmp2[1000], userId[30], mention[300];
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
		scanf("%s", &tmp2);
		if (!isNum(tmp2)) {
			printf("숫자를 입력해주세요.\n");
			continue;
		}
		else {
			command = atoi(tmp2);
		}
		if (inputReady == 0 && command != 0 && command != 99) {
			system("cls");
			printf("입력을 먼저 받아주세요.\n\n\n\n\n\n");
			continue;
		}
		if (inputReady == 1 && command == 0) {
			system("cls");
			printf("이미 입력을 받았습니다. 다른 명령어를 선택해주세요.\n\n\n\n\n\n");
			continue;
		}
		switch (command) {
		case 0: {
			system("cls");
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
			printf("\n\n\n\n\n");
			free(userIn);
			free(wordIn);
			free(friendIn);
			break;
		}
		case 1:
			system("cls");
			printMinMaxUser(users, words.totalTweet);
			printf("\n\n\n\n\n");
			break;
		case 2:
			system("cls");
			printTopFiveTweetWord(words);
			printf("\n\n\n\n\n");
			break;
		case 3:
			system("cls");
			printTopFiveTweetUser(users);
			printf("\n\n\n\n\n");
			break;
		case 4:
			system("cls");
			printf("한 단어를 입력해주세요 : ");
			scanf("%s", mention);
			printf("%s을 tweet한 User.\n", mention);
			printTweetUser(findWord(words.root, mention));
			printf("\n\n\n\n\n");
			break;
		case 5:
			system("cls");
			printf("User의 ID를 입력해주세요 : ");
			scanf("%s", userId);
			printf("%s의 친구는 다음과 같습니다.\n", userId);
			printFriends(findUser(users.root, userId));
			printf("\n\n\n\n\n");
			break;
		case 99:
			destroyUserTree(users);
			destroyWordTree(words);
			return 0;
		default:
			system("cls");
			printf("없는 명령어입니다. 다른 명령을 입력해주세요\n");
			printf("\n\n\n\n\n\n\n");
			break;
		}
	}
	return 0;
}