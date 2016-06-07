#include "UserBST.h"

extern int count;
//Ʈ���� ���� ������ 5���� ���� ���
void printTopFiveTweetUser(UserBST users) {
	if (!users.root) {
		printf("0 User\n");
		return;
	}
	User* five[5] = { NULL };
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
		if (five[i]) {
			printf("Top %d : %s %dȸ\n", i, five[i - 1]->ID, five[i - 1]->tweetc);
		}
	}
	free(userQueue);
}

//��� User�� Ʈ����, ģ������ ���� ����(����) User ���
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
	printf("Minimum number of friends : %d %s\n", minF->friends, minF->ID);
	printf("Maximum number of friends : %d %s\n", maxF->friends, maxF->ID);
	printf("\n");
	printf("Average tweets per user : %.3lf\n", (double)totalTweet / users.totalUesr);
	printf("Minimum tweets per user : %d %s\n", minTC->tweetc, minTC->ID);
	printf("Maximum tweets per user : %d %s\n", maxTC->tweetc, maxTC->ID);
	free(userQueue);
	return;
}

//User�� ģ�� ���
void printFriends(User* user) {
	if (user == NULL) {
		printf("�ش� ������ �������� �ʽ��ϴ�.\n");
		return;
	}
	UserList* tmp = user->first;
	for (int i = 1; i <= user->friends; i++) {
		printf("%d. %s\n", i, tmp->ID);
	}
	if (user->friends == 0) {
		printf("�ش� ������ ģ���� 0���Դϴ�.");
	}
}

//UserID�� Userã��
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

//User�� Ʈ���� ���� �� �� ������ ���
void userTweet(User* root, char* id) {
	int compare;
	while (1) {
		if (root == NULL) {
			return;
		}
		if ((compare = strcmp(root->ID, id)) == 0) {
			root->tweetc++;
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

//Tree���� ID�� ã�� �װ��� friendId �߰�
void insertFriend(UserBST* userBST, char* ID, char* friendId) {
	User* root = userBST->root;
	while (1) {
		if (strcmp(root->ID, ID) > 0) {
			if (root->left == NULL) return;
			root = root->left;
		}
		else if (strcmp(root->ID, ID) < 0) {
			if (root->right == NULL) return;
			root = root->right;
		}
		else {
			UserList* friendList = root->first;
			UserList* tmp = (UserList*)malloc(sizeof(UserList));
			tmp->next = NULL; memcpy(tmp->ID, friendId, 30);
			if (friendList == NULL) {
				root->first = tmp;
				userBST->totalFriend++;
				root->friends++;
				return;
			}
			while (friendList->next) {
				friendList = friendList->next;
			}
			friendList->next = tmp;
			userBST->totalFriend++;
			root->friends++;
			return;
		}
	}
}

//User���� �׽�Ʈ��
void print(User* root) {
	if (root->left != NULL) {
		print(root->left);
	}
	printf("%s\n", root->ID);
	if (root->right != NULL) {
		print(root->right);
	}
}

//UserBST �ʱ�ȭ
void UserBSTInit(UserBST* users) {
	users->height = 0;
	users->root = NULL;
	users->totalFriend = 0;
	users->totalUesr = 0;
}

//UserTree�� ���� ���
int userTreeHeight(User* root) {
	if (root == NULL) return 0;
	return Max(userTreeHeight(root->left) + 1, userTreeHeight(root->right));
}

//Tree ����

//minUser�� ���� ���� ��带 ã����
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

//maxUser�� ���� ������ ��带 ã����
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

//target��� �ڸ��� newUser�� �ٿ���;
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

//��� ����;
void insertUser(UserBST* bst, char* ID) {
	User* tmp = (User*)malloc(sizeof(User));
	tmp->left = NULL; tmp->right = NULL; tmp->parent = NULL; memcpy(tmp->ID, ID, 30);
	tmp->first = NULL; tmp->friends = 0; tmp->tweetc = 0;  tmp->color = 1;
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

//��� ����
void deleteUser(UserBST* bst, User* deleteUser) {
	User* parent = deleteUser->parent;
	//�ڽ��� ���� ���
	if (deleteUser->left == NULL) {
		transPlant(bst, deleteUser, deleteUser->right);
	}
	//������ �ڽ��� ���� ���
	else if (deleteUser->right == NULL) {
		transPlant(bst, deleteUser, deleteUser->left);
	}
	//�ڽ��� �� �� �ִ� ���
	else {
		User* successor = findMinUser(deleteUser->right);
		if (successor != deleteUser->right) {
			transPlant(bst, successor, successor->right);
			successor->right = deleteUser->right;
			successor->right->parent = successor;
		}
		transPlant(bst, deleteUser, successor);
		successor->left = deleteUser->left;
		successor->left->parent = successor;
	}
	freeUser(deleteUser);
}

//RBƮ�� insertFix
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

//RBƮ�� Tree Left Rotate
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

//RBƮ�� Tree Right Rotate
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
	UserList* tmp = user->first;
	while (tmp) {
		UserList* next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(user);
}