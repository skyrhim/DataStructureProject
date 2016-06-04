#include "WordBST.h"

void printWord(Word* root) {
	if (root->left != NULL) {
		printWord(root->left);
	}
	printf("%s\n", root->tweet);
	if (root->right != NULL) {
		printWord(root->right);
	}
}
void WordBSTInit(WordBST* words) {
	words->height = 0;
	words->root = NULL;
	words->totalTweet = 0;
}
int wordTreeHeight(Word* root) {
	if (root == NULL) return 0;
	return max(wordTreeHeight(root->left) + 1, wordTreeHeight(root->right) + 1);
}
//minWord의 가장 왼쪽노드를 찾아줌
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
//maxWord의 가장 왼쪽노드를 찾아줌
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

//target노드 자리에 newWord를 붙여줌;
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
//노드 삽입;
void insertWord(WordBST* bst, char* tweet, char* tweetID) {
	Word* tmp = (Word*)malloc(sizeof(Word));
	tmp->userCount = 1; tmp->first = NULL;
	tmp->left = NULL; tmp->right = NULL; tmp->parent = NULL; memcpy(tmp->tweet, tweet, 200);
	bst->totalTweet++;
	if (bst->root == NULL) {
		bst->root = tmp;
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
				return;
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
				return;
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
}
//노드 삭제
void deleteWord(WordBST* bst, Word* deleteWord) {
	Word* parent = deleteWord->parent;
	//자식이 없을 경우
	if (deleteWord->left == NULL) {
		transPlant(bst, deleteWord, deleteWord->right);
	}
	//오른쪽 자식이 없을 경우
	else if (deleteWord->right == NULL) {
		transPlant(bst, deleteWord, deleteWord->left);
	}
	//자식이 둘 다 있는 경우
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
	UserList *del = deleteWord->first;
	for (int i = 0; i < deleteWord->userCount; i++) {
		UserList *delNext = del->next;
		free(del);
		del = delNext;
	}
	free(deleteWord);
}

void insertWordF(WordBST *bst, Word *word) {
	Word *tmp = (Word*)malloc(sizeof(Word));
	tmp->left = NULL; tmp->right = NULL; tmp->userCount = word->userCount;
	if (!bst->root) {
		bst->root = tmp;
		return;
	}
	Word *parent = bst->root;
	while (1) {
		if (parent->userCount > tmp->userCount) {
			if (!parent->left) {
				parent->left = tmp;
				return;
			}
			else {
				parent = parent->left;
			}
		}
		else {
			if (!parent->right) {
				parent->right = tmp;
				return;
			}
			else {
				parent = parent->right;
			}
		}
	}
}

WordBST constructWordFTree(WordBST target) {
	WordBST bst;
	WordBSTInit(&bst);
	Word** WordQueue = (Word**)malloc(sizeof(Word*) * (target.totalTweet));
	int front = 0, back = 0;
	WordQueue[back++] = target.root;
	insertWordF(&bst, WordQueue[front]);
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