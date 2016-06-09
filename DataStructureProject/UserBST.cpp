#include "UserBST.h"

extern UserBST users;
User* five[5];

//delete following list of delUser's follower
void delFollower(User* delUser) {
	UserList* follower = delUser->follower;
	while (follower) {
		UserList* following = follower->user->following;
		if (following->user == delUser) {
			follower->user->following = following->next;
			follower->user->friends--;
			users.totalFriend--;
			free(following);
		}
		else {
			UserList* pre = following;
			following = following->next;
			while (following) {
				if (following->user == delUser) {
					pre->next = following->next;
					follower->user->friends--;
					users.totalFriend--;
					free(following);
					break;
				}
				pre = pre->next;
				following = following->next;
			}
		}
		follower = follower->next;
	}
}

//delete follower list of User who delUser follow
void delFollowing(User* delUser) {
	UserList* following = delUser->following;
	while (following) {
		UserList* follower = following->user->follower;
		if (follower->user == delUser) {
			following->user->follower = follower->next;
			free(follower);
		}
		else {
			UserList* pre = follower;
			follower = follower->next;
			while (follower) {
				if (follower->user == delUser) {
					pre->next = follower->next;
					free(follower);
					break;
				}
				pre = pre->next;
				follower = follower->next;
			}
		}
		following = following->next;
	}
}

//array five init
void cleanFiveUser() {
	for (int i = 0; i < 5; i++) {
		five[i] = 0;
	}
}

//delete user's word list
void delTweet(User* user, Word* tweet, int count) {
	if (user == NULL) {
		return;
	}
	user->tweetc = user->tweetc - count;
	wordList* word = user->wordFirst;
	wordList *pre;
	if (word->word == tweet) {
		user->wordFirst = word->next;
		free(word);
		return;
	}
	pre = user->wordFirst;
	word = word->next;
	while (word) {
		if (word->word == tweet) {
			pre->next = word->next;
			free(word);
			return;
		}
		pre = pre->next;
		word = pre->next;
	}
}

//Most 5 tweeted User
void printTopFiveTweetUser(UserBST users) {
	if (!users.root) {
		printf("Zero User in UserTree\n");
		return;
	}
	cleanFiveUser();
	User** userQueue = (User**)malloc(sizeof(User*) * users.totalUesr);
	int front = 0, back = 0;
	five[0] = userQueue[back++] = users.root;
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (userQueue[front]->left) {
				userQueue[back++] = userQueue[front]->left;
				if (!five[4] || userQueue[front]->left->tweetc > five[4]->tweetc) {
					int i;
					for (i = 4; i >= 1; i--) {
						if (!five[i - 1] || five[i - 1]->tweetc < userQueue[front]->left->tweetc) {
							five[i] = five[i - 1];
						}
						else {
							break;
						}
					}
					five[i] = userQueue[front]->left;
				}
			}
			if (userQueue[front]->right) {
				userQueue[back++] = userQueue[front]->right;
				if (!five[4] || userQueue[front]->right->tweetc > five[4]->tweetc) {
					int i;
					for (i = 4; i >= 1; i--) {
						if (!five[i - 1] || five[i - 1]->tweetc < userQueue[front]->right->tweetc) {
							five[i] = five[i - 1];
						}
						else {
							break;
						}
					}
					five[i] = userQueue[front]->right;
				}
			}
		}
	}
	for (int i = 1; i <= 5; i++) {
		if (five[i - 1]) {
			printf("Top %d : %s %d time(s)\n", i, five[i - 1]->screenName, five[i - 1]->tweetc);
		}
	}
	free(userQueue);
}

//Print min and max User(number of tweet, friend)
void printMinMaxUser(UserBST users, int totalTweet) {
	if (!users.root) {
		printf("0 User\n");
		return;
	}
	User** userQueue = (User**)malloc(sizeof(User*) * users.totalUesr);
	User* minF, *maxF, *minTC, *maxTC;
	int front = 0, back = 0;
	minF = maxF = minTC = maxTC = userQueue[back++] = users.root;
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (userQueue[front]->left) {
				userQueue[back++] = userQueue[front]->left;
				if (userQueue[front]->left->friends < minF->friends) {
					minF = userQueue[front]->left;
				}
				if (userQueue[front]->left->tweetc < minTC->tweetc) {
					minTC = userQueue[front]->left;
				}
				if (userQueue[front]->left->friends > maxF->friends) {
					maxF = userQueue[front]->left;
				}
				if (userQueue[front]->left->tweetc > maxTC->tweetc) {
					maxTC = userQueue[front]->left;
				}
			}
			if (userQueue[front]->right) {
				userQueue[back++] = userQueue[front]->right;
				if (userQueue[front]->right->friends < minF->friends) {
					minF = userQueue[front]->right;
				}
				if (userQueue[front]->right->tweetc < minTC->tweetc) {
					minTC = userQueue[front]->right;
				}
				if (userQueue[front]->right->friends > maxF->friends) {
					maxF = userQueue[front]->right;
				}
				if (userQueue[front]->right->tweetc > maxTC->tweetc) {
					maxTC = userQueue[front]->right;
				}
			}
		}
	}
	printf("Average number of friends : %.3lf\n", (double)users.totalFriend / users.totalUesr);
	printf("Minimum number of friends : %d %s\n", minF->friends, minF->screenName);
	printf("Maximum number of friends : %d %s\n", maxF->friends, maxF->screenName);
	printf("\n");
	printf("Average tweets per user : %.3lf\n", (double)totalTweet / users.totalUesr);
	printf("Minimum tweets per user : %d %s\n", minTC->tweetc, minTC->screenName);
	printf("Maximum tweets per user : %d %s\n", maxTC->tweetc, maxTC->screenName);
	free(userQueue);
	return;
}

//Print friend of User
void printFriends() {
	if (five[0] == NULL) {
		printf("0 User in UserTree or run command 3\n");
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (five[i]) {
			UserList* tmp = five[i]->following;
			printf("%d. %s's friend(s)\n", i + 1, five[i]->screenName);
			while (tmp) {
				printf("%s\n", tmp->user->screenName);
				tmp = tmp->next;
			}
		}
		else {
			return;
		}
	}
}

//Find User by ID
User* findUser(User* root, char* userId) {
	int compare;
	while (root) {
		if ((compare = strcmp(root->ID, userId)) > 0) {
			root = root->left;
		}
		else if (compare < 0) {
			root = root->right;
		}
		else {
			return root;
		}
	}
	return NULL;
}

//Tweet count
void userTweet(User* root, char* id, Word* word) {
	int compare;
	while (1) {
		if (root == NULL) {
			return;
		}
		if ((compare = strcmp(root->ID, id)) == 0) {
			root->tweetc++;
			int inList = 0;
			wordList* list = root->wordFirst;
			while (list) {
				if (list->word == word) {
					inList = 1;
					list->count++;
					return;
				}
				list = list->next;
			}
			wordList* tmp = (wordList*)malloc(sizeof(wordList));
			tmp->count = 1;
			tmp->next = root->wordFirst;
			tmp->word = word;
			root->wordFirst = tmp;
			return;
		}
		else if (compare < 0) {
			root = root->right;
		}
		else {
			root = root->left;
		}
	}
}

//Add friend
void insertFriend(UserBST* userBST, char* ID, char* friendId) {
	User* root = userBST->root;
	User* tmp1 = findUser(root, ID);
	User* tmp2 = findUser(root, friendId);
	if (tmp1 != NULL && tmp2 != NULL) {
		UserList* newlist = (UserList*)malloc(sizeof(UserList));
		newlist->user = tmp2;
		newlist->next = tmp1->following;
		tmp1->following = newlist;
		tmp1->friends++;
	}
	if (tmp1 != NULL && tmp2 != NULL) {
		UserList* newlist = (UserList*)malloc(sizeof(UserList));
		newlist->user = tmp1;
		newlist->next = tmp2->follower;
		tmp2->follower = newlist;
		userBST->totalFriend++;
	}
}

//print all User
void print(User* root) {
	if (root->left != NULL) {
		print(root->left);
	}
	printf("%s\n", root->ID);
	if (root->right != NULL) {
		print(root->right);
	}
}

//Init UserTree
void UserBSTInit(UserBST* users) {
	users->height = 0;
	users->root = NULL;
	users->totalFriend = 0;
	users->totalUesr = 0;
}

//Height of UserTree
int userTreeHeight(User* root) {
	if (root == NULL) return 0;
	return Max(userTreeHeight(root->left) + 1, userTreeHeight(root->right));
}

//Construct Tree

//Find min User
User* findMinUser(User* minUser) {
	while (1) {
		if (minUser->left) {
			minUser = minUser->left;
		}
		else {
			return minUser;
		}
	}
}

//Find max User
User* findMaxUser(User* maxUser) {
	while (1) {
		if (maxUser->right) {
			maxUser = maxUser->right;
		}
		else {
			return maxUser;
		}
	}
}

//Transplant target to newUser
void transPlant(UserBST* bst, User* target, User* newUser) {
	if (target->parent == NULL) {
		bst->root = newUser;
	}
	else if (target == target->parent->left) {
		target->parent->left = newUser;
	}
	else {
		target->parent->right = newUser;
	}
	if (newUser != NULL) {
		newUser->parent = target->parent;
	}
}

//Insert Node
void insertUser(UserBST* bst, char* ID, char* screenName) {
	User* tmp = (User*)malloc(sizeof(User));
	tmp->left = NULL; tmp->right = NULL; tmp->parent = NULL; memcpy(tmp->ID, ID, 30);
	tmp->following = NULL; tmp->friends = 0; tmp->tweetc = 0;  tmp->color = 1; tmp->wordFirst = NULL;
	tmp->follower = NULL; memcpy(tmp->screenName, screenName, 100);
	bst->totalUesr++;
	if (bst->root == NULL) {
		bst->root = tmp;
		tmp->color = 0;
		return;
	}
	User* parent = bst->root;
	while (1) {
		if (strcmp(ID, parent->ID) < 0) {
			if (parent->left == NULL) {
				tmp->parent = parent;
				parent->left = tmp;
				break;
			}
			parent = parent->left;
		}
		else {
			if (parent->right == NULL) {
				tmp->parent = parent;
				parent->right = tmp;
				break;
			}
			parent = parent->right;
		}
	}
	UserinsertFixUp(bst, tmp);
}

//Delete Node
void deleteUser(UserBST* bst, User* z) {
	User* y = z;
	User *x, *xParent;
	int yOriginalColor = y->color;
	if (z->left == NULL) {
		x = z->right;
		xParent = z->parent;
		transPlant(bst, z, z->right);
	}
	else if (z->right == NULL) {
		x = z->left;
		xParent = z->parent;
		transPlant(bst, z, z->left);
	}
	else {
		y = findMinUser(z->right);
		yOriginalColor = y->color;
		x = y->right;
		xParent = y->parent;
		if (y->parent == z) {
			xParent = y;
		}
		else {
			transPlant(bst, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transPlant(bst, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (yOriginalColor == 0) {
		UserdeleteFixUp(bst, x, xParent);
	}
	freeUser(z);
}

//RB Tree insertFix
void UserinsertFixUp(UserBST* bst, User* fix) {
	while (fix->parent && fix->parent->color) {
		if (fix->parent == fix->parent->parent->left) {
			User* uncle = fix->parent->parent->right;
			if (uncle && uncle->color) {
				fix->parent->color = 0;
				uncle->color = 0;
				if (fix->parent->parent) {
					fix->parent->parent->color = 1;
				}
				fix = fix->parent->parent;
			}
			else {
				if (fix == fix->parent->right) {
					fix = fix->parent;
					UserleftRotate(bst, fix);
				}
				fix->parent->color = 0;
				if (fix->parent->parent) {
					fix->parent->parent->color = 1;
				}
				UserrightRotate(bst, fix->parent->parent);
			}
		}
		else {
			User* uncle = fix->parent->parent->left;
			if (uncle && uncle->color) {
				fix->parent->color = 0;
				uncle->color = 0;
				fix->parent->parent->color = 1;
				fix = fix->parent->parent;
			}
			else {
				if (fix == fix->parent->left) {
					fix = fix->parent;
					UserrightRotate(bst, fix);
				}
				fix->parent->color = 0;
				if (fix->parent->parent) {
					fix->parent->parent->color = 1;
				}
				UserleftRotate(bst, fix->parent->parent);
			}
		}
	}
	bst->root->color = 0;
}

//RB Tree deleteFix
void UserdeleteFixUp(UserBST* bst, User* x, User* xParent) {
	User* w;
	while (x != bst->root && (x == NULL || x->color == 0)) {
		if (x == xParent->left) {
			w = xParent->right;
			if (w->color == 1) {
				w->color = 0;
				xParent->color = 1;
				UserleftRotate(bst, xParent);
				w = xParent->right;
			}
			if ((w->left == NULL || w->left->color == 0) && (w->right == NULL || w->right->color == 0)) {
				w->color = 1;
				x = xParent;
				xParent = x->parent;
			}
			else {
				if ((w->right == NULL || w->right->color == 0)) {
					if (w->left) {
						w->left->color = 0;
					}
					w->color = 1;
					UserrightRotate(bst, w);
					w = xParent->right;
				}
				w->color = xParent->color;
				xParent->color = 0;
				if (w->right) {
					w->right->color = 0;
				}
				UserleftRotate(bst, xParent);
				x = bst->root;
			}
		}
		else {
			w = xParent->left;
			if (w->color == 1) {
				w->color = 0;
				xParent->color = 1;
				UserrightRotate(bst, xParent);
				w = xParent->left;
			}
			if ((w->right == NULL || w->right->color == 0) && (w->left == NULL || w->left->color == 0)) {
				w->color = 1;
				x = xParent;
				xParent = x->parent;
			}
			else {
				if ((w->left == NULL || w->left->color == 0)) {
					if (w->right) {
						w->right->color = 0;
					}
					w->color = 1;
					UserleftRotate(bst, w);
					w = xParent->left;
				}
				w->color = xParent->color;
				xParent->color = 0;
				if (w->left) {
					w->left->color = 0;
				}
				UserrightRotate(bst, xParent);
				x = bst->root;
			}
		}
	}
	if (x) {
		x->color = 0;
	}
}

//RB Tree Tree Left Rotate
void UserleftRotate(UserBST* bst, User* fix) {
	User* tmp = fix->right;
	fix->right = tmp->left;
	if (tmp->left) {
		tmp->left->parent = fix;
	}
	tmp->parent = fix->parent;
	if (fix->parent == NULL) {
		bst->root = tmp;
	}
	else if (fix == fix->parent->left) {
		fix->parent->left = tmp;
	}
	else {
		fix->parent->right = tmp;
	}
	tmp->left = fix;
	fix->parent = tmp;
}

//RB Tree Tree Right Rotate
void UserrightRotate(UserBST* bst, User* fix) {
	User* tmp = fix->left;
	fix->left = tmp->right;
	if (tmp->right) {
		tmp->right->parent = fix;
	}
	tmp->parent = fix->parent;
	if (fix->parent == NULL) {
		bst->root = tmp;
	}
	else if (fix == fix->parent->left) {
		fix->parent->left = tmp;
	}
	else {
		fix->parent->right = tmp;
	}
	tmp->right = fix;
	fix->parent = tmp;
}

//UserTree delete
void destroyUserTree(UserBST target) {
	UserBST bst;
	UserBSTInit(&bst);
	User** UserQueue = (User**)malloc(sizeof(User*) * (target.totalUesr + 1));
	int front = 0, back = 0;
	UserQueue[back++] = target.root;
	if (!target.root) {
		return;
	}
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (UserQueue[front] && UserQueue[front]->left) {
				UserQueue[back++] = UserQueue[front]->left;
			}
			if (UserQueue[front] && UserQueue[front]->right) {
				UserQueue[back++] = UserQueue[front]->right;
			}
			freeUser(UserQueue[front]);
		}
	}
	free(UserQueue);
	return;
}

//free User Data
void freeUser(User* user) {
	UserList* tmp = user->following;
	while (tmp) {
		UserList* next = tmp->next;
		free(tmp);
		tmp = next;
	}
	tmp = user->follower;
	while (tmp) {
		UserList* next = tmp->next;
		free(tmp);
		tmp = next;
	}
	wordList* tmpWord = user->wordFirst;
	while (tmpWord) {
		wordList* next = tmpWord->next;
		free(tmpWord);
		tmpWord = next;
	}
	free(user);
}