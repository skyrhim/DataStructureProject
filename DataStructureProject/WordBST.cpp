#include "WordBST.h"

extern int count;
//word�� Ʈ���� User�� ����ID ���
void printTweetUser(Word* word) {
	if (word == NULL) {
		printf("�ش�ܾ Ʈ���� User�� �����ϴ�.\n");
		return;
	}
	UserList* tmp = word->first;
	for (int i = 1; i <= word->userCount; i++) {
		printf("%d. %s\n", i, tmp->ID);
		tmp = tmp->next;
	}
}

//WordTree���� Wordã��
Word* findWord(Word* root, char* word) {
	int compare;
	while (root) {
		if ((compare = strcmp(root->tweet, word)) > 0) {
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

//���� ���� Tweet�� �ܾ� 5��
void printTopFiveWord(Word* root) {
	if (root == NULL) {
		printf("�ܾ��� ������ 0�� �Դϴ�.\n");
		return;
	}
	if (root->right != NULL) {
		printTopFiveWord(root->right);
	}
	if (count == 6) {
		return;
	}
	printf("Top %d : %s %dȸ\n", count, root->tweet, root->userCount);
	count++;
	if (root->left != NULL) {
		printTopFiveWord(root->left);
	}
}

//Tree�� �ܾ�� ���
void printWord(Word* root) {
	if (root->left != NULL) {
		printWord(root->left);
	}
	printf("%s\n", root->tweet);
	if (root->right != NULL) {
		printWord(root->right);
	}
}

//WordTree �ʱ�ȭ
void WordBSTInit(WordBST* words) {
	words->height = 0;
	words->root = NULL;
	words->totalTweet = 0;
}

//WordTree�� ����
int wordTreeHeight(Word* root) {
	if (root == NULL) return 0;
	return max(wordTreeHeight(root->left) + 1, wordTreeHeight(root->right) + 1);
}

//minWord�� ���� ���ʳ�带 ã����
Word* findMinWord(Word* minWord) {
	while (1) {
		if (minWord->left) {
			minWord = minWord->left;
		}
		else {
			return minWord;
		}
	}
}

//maxWord�� ���� ���ʳ�带 ã����
Word* findMaxWord(Word* maxWord) {
	while (1) {
		if (maxWord->right) {
			maxWord = maxWord->right;
		}
		else {
			return maxWord;
		}
	}
}

//target��� �ڸ��� newWord�� �ٿ���;
void transPlant(WordBST* bst, Word* target, Word* newWord) {
	if (target->parent == NULL) {
		bst->root = newWord;
	}
	else if (target == target->parent->left) {
		target->parent->left = newWord;
	}
	else {
		target->parent->right = newWord;
	}
	if (newWord != NULL) {
		newWord->parent = target->parent;
	}
}

//��� ����
void insertWord(WordBST* bst, char* tweet, char* tweetID) {
	Word* tmp = (Word*)malloc(sizeof(Word));
	tmp->userCount = 1; tmp->first = NULL; tmp->color = 1;
	tmp->left = NULL; tmp->right = NULL; tmp->parent = NULL; memcpy(tmp->tweet, tweet, 300);
	bst->totalTweet++;
	if (bst->root == NULL) {
		UserList *temp = (UserList*)malloc(sizeof(UserList));
		memcpy(temp->ID, tweetID, 30);
		temp->next = NULL;
		bst->root = tmp;
		tmp->first = temp;
		bst->root->color = 0;
		return;
	}
	Word* parent = bst->root;
	while (1) {
		if (strcmp(tweet, parent->tweet) < 0) {
			if (parent->left == NULL) {
				UserList *temp = (UserList*)malloc(sizeof(UserList));
				memcpy(temp->ID, tweetID, 30);
				temp->next = NULL;
				tmp->first = temp;
				tmp->parent = parent;
				parent->left = tmp;
				break;
			}
			parent = parent->left;
		}
		else if(strcmp(tweet, parent->tweet) > 0){
			if (parent->right == NULL) {
				UserList *temp = (UserList*)malloc(sizeof(UserList));
				memcpy(temp->ID, tweetID, 30);
				temp->next = NULL;
				tmp->first = temp;
				tmp->parent = parent;
				parent->right = tmp;
				break;
			}
			parent = parent->right;
		}
		else {
			parent->userCount++;
			UserList *temp = (UserList*)malloc(sizeof(UserList));
			memcpy(temp->ID, tweetID, 30);
			temp->next = NULL;
			UserList* t = parent->first;
			while (t->next) {
				t = t->next;
			}
			t->next = temp;
			free(tmp);
			return;
		}
	}
	WordinsertFixUp(bst, tmp);
}

//��� ����
void deleteWord(WordBST* bst, Word* deleteWord) {
	Word* parent = deleteWord->parent;
	//�ڽ��� ���� ���
	if (deleteWord->left == NULL) {
		transPlant(bst, deleteWord, deleteWord->right);
	}
	//������ �ڽ��� ���� ���
	else if (deleteWord->right == NULL) {
		transPlant(bst, deleteWord, deleteWord->left);
	}
	//�ڽ��� �� �� �ִ� ���
	else {
		Word* successor = findMinWord(deleteWord->right);
		if (successor != deleteWord->right) {
			transPlant(bst, successor, successor->right);
			successor->right = deleteWord->right;
			successor->right->parent = successor;
		}
		transPlant(bst, deleteWord, successor);
		successor->left = deleteWord->left;
		successor->left->parent = successor;
	}
	freeWord(deleteWord);
}

//�ܾ� �󵵼� ������ Tree�� ����
void insertWordF(WordBST *bst, Word *word) {
	Word *tmp = (Word*)malloc(sizeof(Word));
	tmp->left = NULL; tmp->right = NULL; tmp->userCount = word->userCount; tmp->parent = NULL;
	memcpy(tmp->tweet, word->tweet, 300); tmp->color = 1; tmp->first = NULL;
	if (!bst->root) {
		bst->root = tmp;
		bst->root->color = 0;
		return;
	}
	Word *parent = bst->root;
	while (1) {
		if (parent->userCount > tmp->userCount) {
			if (!parent->left) {
				parent->left = tmp;
				tmp->parent = parent;
				break;
			}
			else {
				parent = parent->left;
			}
		}
		else {
			if (!parent->right) {
				parent->right = tmp;
				tmp->parent = parent;
				break;
			}
			else {
				parent = parent->right;
			}
		}
	}
	WordinsertFixUp(bst, tmp);
}

//�ܾ� �󵵼� ���� ���������� Tree����
WordBST constructWordFTree(WordBST target) {
	WordBST bst;
	WordBSTInit(&bst);
	bst.totalTweet = target.totalTweet;
	Word** WordQueue = (Word**)malloc(sizeof(Word*) * (target.totalTweet));
	int front = 0, back = 0;
	WordQueue[back++] = target.root;
	if (WordQueue[front]) {
		insertWordF(&bst, WordQueue[front]);
	}
	else {
		return bst;
	}
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (WordQueue[front]->left) {
				WordQueue[back++] = WordQueue[front]->left;
				insertWordF(&bst, WordQueue[front]->left);
			}
			if (WordQueue[front]->right) {
				WordQueue[back++] = WordQueue[front]->right;
				insertWordF(&bst, WordQueue[front]->right);
			}
		}
	}
	free(WordQueue);
	return bst;
}

//WordTree delete
void destroyWordTree(WordBST target) {
	WordBST bst;
	WordBSTInit(&bst);
	Word** WordQueue = (Word**)malloc(sizeof(Word*) * (target.totalTweet + 1));
	int front = 0, back = 0;
	WordQueue[back++] = target.root;
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (WordQueue[front] && WordQueue[front]->left) {
				WordQueue[back++] = WordQueue[front]->left;
			}
			if (WordQueue[front] && WordQueue[front]->right) {
				WordQueue[back++] = WordQueue[front]->right;
			}
			freeWord(WordQueue[front]);
		}
	}
	free(WordQueue);
	return;
}

//RB Tree Fix
void WordinsertFixUp(WordBST* bst, Word* fix) {
	while (fix->parent && fix->parent->color) {
		if (fix->parent == fix->parent->parent->left) {
			Word* uncle = fix->parent->parent->right;
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
					WordleftRotate(bst, fix);
				}
				fix->parent->color = 0;
				if (fix->parent->parent) {
					fix->parent->parent->color = 1;
				}
				WordrightRotate(bst, fix->parent->parent);
			}
		}
		else {
			Word* uncle = fix->parent->parent->left;
			if (uncle && uncle->color) {
				fix->parent->color = 0;
				uncle->color = 0;
				fix->parent->parent->color = 1;
				fix = fix->parent->parent;
			}
			else {
				if (fix == fix->parent->left) {
					fix = fix->parent;
					WordrightRotate(bst, fix);
				}
				fix->parent->color = 0;
				if (fix->parent->parent) {
					fix->parent->parent->color = 1;
				}
				WordleftRotate(bst, fix->parent->parent);
			}
		}
	}
	bst->root->color = 0;
}

//RB Tree Left Rotate
void WordleftRotate(WordBST* bst, Word* fix) {
	Word* tmp = fix->right;
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

//RB Tree Right Rotate
void WordrightRotate(WordBST* bst, Word* fix) {
	Word* tmp = fix->left;
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

void freeWord(Word* word) {
	UserList* tmp = word->first;
	while (tmp) {
		UserList* next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(word);
}