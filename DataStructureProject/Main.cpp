#include "UserBST.h"
#include "WordBST.h"

int count;
UserBST users;
WordBST words;
//delete word
void delWord(char* tweet) {
	Word* word = findWord(words.root, tweet);
	if (!word) {
		printf("%s is not in WordTree", tweet);
		return;
	}
	cleanFiveUser();
	words.totalTweet -= word->userCount;
	UserList* user = word->first;
	while (user) {
		delTweet(user->user, word, user->count);
		user = user->next;
	}
	printf("Delete Word %s", word->tweet);
	deleteWord(&words, word);
	//printWord(words.root);
}

//delete User who tweet word
void delUser(char* tweet) {
	Word* word = findWord(words.root, tweet);
	if (word == NULL) {
		printf("%s is not in WordTree\n", tweet);
		return;
	}
	cleanFiveUser();
	UserList* tmp = word->first;
	while (tmp) {
		words.totalTweet -= tmp->user->tweetc;
		users.totalFriend -= tmp->user->friends;
		User* delUser = tmp->user;
		UserList* next = tmp->next;
		//users.totalFriend -= delUser->friends;
		delTweetWord(delUser);
		delFollower(delUser);
		delFollowing(delUser);
		deleteUser(&users, delUser);
		users.totalUesr--;
		tmp = next;
	}
	printf("Delete all User who tweet %s", tweet);
}

bool isNum(char * chr) {
	for (; *chr; chr++) {
		if (*chr < '0' || *chr > '9') {
			return false;
		}
	}
	return true;
}

int main() {
	int command, inputReady = 0;
	char tmp1[1000], tmp2[1000], userId[30], mention[300], screenName[100];
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
			printf("It is not number. Try again.\n");
			continue;
		}
		else {
			command = atoi(tmp2);
		}
		if (inputReady == 0 && command != 0 && command != 99) {
			system("cls");
			printf("Enter data before other command.\n\n\n\n\n\n");
			continue;
		}
		if (inputReady == 1 && command == 0) {
			system("cls");
			printf("Input already. Please run other command\n\n\n\n\n\n");
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
			char word[300];
			char friendId[30];
			while (fscanf(userIn, "%s", userId) != -1) {
				fgets(tmp1, 1000, userIn);
				fgets(tmp1, 1000, userIn);
				fscanf(userIn, "%s", screenName);
				fgets(tmp1, 1000, userIn);
				fgets(tmp1, 1000, userIn);
				insertUser(&users, userId, screenName);
			}
			while (fscanf(wordIn, "%s", userId) != -1) {
				Word* tmp;
				fgets(tmp1, 1000, wordIn);
				fgets(tmp1, 1000, wordIn);
				fscanf(wordIn, "%s", word);
				fgets(tmp1, 1000, wordIn);
				tmp = insertWord(&words, word, findUser(users.root, userId));
				userTweet(users.root, userId, tmp);
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
			fclose(userIn);
			fclose(wordIn);
			fclose(friendIn);
			break;
		}
		case 1:
			system("cls");
			printf("total user : %d\n", users.totalUesr);
			printf("total tweets : %d\n", words.totalTweet);
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
			printf("Enter a word : ");
			scanf("%s", mention);
			printf("%s is tweeted by\n", mention);
			printTweetUser(findWord(words.root, mention));
			printf("\n\n\n\n\n");
			break;
		case 5:
			system("cls");
			printFriends();
			printf("\n\n\n\n\n");
			break;
		case 6:
			system("cls");
			printf("Enter a word : ");
			scanf("%s", mention);
			delWord(mention);
			printf("\n\n\n\n\n\n");
			break;
		case 7:
			system("cls");
			printf("Enter a word : ");
			scanf("%s", mention);
			delUser(mention);
			printf("\n\n\n\n\n\n");
			break;
		case 99:
			destroyUserTree(users);
			destroyWordTree(words);
			users.root = NULL;
			words.root = NULL;
			return 0;
		default:
			system("cls");
			printf("Command not exist. Try again.\n");
			printf("\n\n\n\n\n\n\n");
			break;
		}
	}
	return 0;
}