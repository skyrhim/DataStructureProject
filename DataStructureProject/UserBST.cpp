#include "UserBST.h"

void insertFriend(UserBST* userBST, char* ID, char* friendId) {
	User* root = userBST->root;
	while (1) {
		if (strcmp(root->ID, ID) > 0){
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
int userTreeHeight(User* root) {
	if (root == NULL) return 0;
	return max(userTreeHeight(root->left) + 1, userTreeHeight(root->right));
}
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
	tmp->first = NULL; tmp->friends = 0; tmp->tweetc = 0;
	bst->totalUesr++;
	if (bst->root == NULL) {
		bst->root = tmp;
		return;
	}
	User* parent = bst->root;
	while (1) {
		if (strcmp(ID, parent->ID) < 0) {
			if (parent->left == NULL) {
				tmp->parent = parent;
				parent->left = tmp;
				return;
			}
			parent = parent->left;
		}
		else {
			if (parent->right == NULL) {
				tmp->parent = parent;
				parent->right = tmp;
				return;
			}
			parent = parent->right;
		}
	}
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
	UserList *del = deleteUser->first;
	for (int i = 0; i < deleteUser->friends; i++) {
		UserList *delNext = del->next;
		free(del);
		del = delNext;
	}
	free(deleteUser);
}
void insertUserF(UserBST* bst, User* user) {
	User* tmp = (User*)malloc(sizeof(User));
	tmp->left = NULL; tmp->right = NULL; tmp->friends = user->friends;
	memcpy(tmp->ID, user->ID, 30);
	if (bst->root == NULL) {
		bst->root = tmp;
		return;
	}
	User* parent = bst->root;
	while (1) {
		if (parent->friends > tmp->friends) {
			if (parent->left == NULL) {
				tmp->parent = parent;
				parent->left = tmp;
				return;
			}
			parent = parent->left;
		}
		else {
			if (parent->right == NULL) {
				tmp->parent = parent;
				parent->right = tmp;
				return;
			}
			parent = parent->right;
		}
	}
}

UserBST constructUserFTree(UserBST target) {
	UserBST bst;
	UserBSTInit(&bst);
	User** UserQueue = (User**)malloc(sizeof(User*) * (target.totalUesr));
	int front = 0, back = 0;
	UserQueue[back++] = target.root;
	insertUserF(&bst, UserQueue[front]);
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (UserQueue[front]->left) {
				UserQueue[back++] = UserQueue[front]->left;
				insertUserF(&bst, UserQueue[front]->left);
			}
			if (UserQueue[front]->right) {
				UserQueue[back++] = UserQueue[front]->right;
				insertUserF(&bst, UserQueue[front]->right);
			}
		}
	}
	free(UserQueue);
	return bst;
}

void userTweet(User* root, char* id) {
	int compare;
	while (1) {
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

void insertUserTC(UserBST* bst, User* user) {
	User* tmp = (User*)malloc(sizeof(User));
	tmp->left = NULL; tmp->right = NULL; tmp->tweetc = user->tweetc;
	memcpy(tmp->ID, user->ID, 30);
	if (bst->root == NULL) {
		bst->root = tmp;
		return;
	}
	User* parent = bst->root;
	while (1) {
		if (parent->tweetc > tmp->tweetc) {
			if (parent->left == NULL) {
				tmp->parent = parent;
				parent->left = tmp;
				return;
			}
			parent = parent->left;
		}
		else {
			if (parent->right == NULL) {
				tmp->parent = parent;
				parent->right = tmp;
				return;
			}
			parent = parent->right;
		}
	}
}

UserBST constructUserTCTree(UserBST target) {
	UserBST bst;
	UserBSTInit(&bst);
	User** UserQueue = (User**)malloc(sizeof(User*) * (target.totalUesr));
	int front = 0, back = 0;
	UserQueue[back++] = target.root;
	insertUserTC(&bst, UserQueue[front]);
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (UserQueue[front]->left) {
				UserQueue[back++] = UserQueue[front]->left;
				insertUserTC(&bst, UserQueue[front]->left);
			}
			if (UserQueue[front]->right) {
				UserQueue[back++] = UserQueue[front]->right;
				insertUserTC(&bst, UserQueue[front]->right);
			}
		}
	}
	free(UserQueue);
	return bst;
}