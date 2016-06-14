#include "WordBST.h"

extern WordBST words;
//delete Word tweeted by delUser
void delTweetWord(User* delUser) {
	wordList* delWord = delUser->wordFirst;
	while (delWord) {
		delWord->word->userCount = delWord->word->userCount - delWord->count;
		UserList* list = delWord->word->first;
		if (list->user == delUser) {
			delWord->word->first = list->next;
			free(list);
		}
		else {
			UserList* pre = list;
			list = list->next;
			while (list) {
				if (list->user == delUser) {
					pre->next = list->next;
					free(list);
					break;
				}
				pre = pre->next;
				list = list->next;
			}
		}
		if (delWord->word->userCount == 0) {
			deleteWord(&words, delWord->word);
		}
		delWord = delWord->next;
	}
}

//Most 5 tweeted Word
void printTopFiveTweetWord(WordBST words) {
	if (!words.root) {
		printf("Zero Word in WordTree\n");
		return;
	}
	Word* five[5] = { NULL };
	Word** wordQueue = (Word**)malloc(sizeof(Word*) * words.totalTweet);
	int front = 0, back = 0;
	five[0] = wordQueue[back++] = words.root;
	while (front < back) {
		int tmpback = back;
		for (; front < tmpback; front++) {
			if (wordQueue[front]->left) {
				wordQueue[back++] = wordQueue[front]->left;
				if (!five[4] || wordQueue[front]->left->userCount > five[4]->userCount) {
					int i;
					for (i = 4; i >= 1; i--) {
						if (!five[i - 1] || five[i - 1]->userCount < wordQueue[front]->left->userCount) {
							five[i] = five[i - 1];
						}
						else {
							break;
						}
					}
					five[i] = wordQueue[front]->left;
				}
			}
			if (wordQueue[front]->right) {
				wordQueue[back++] = wordQueue[front]->right;
				if (!five[4] || wordQueue[front]->right->userCount > five[4]->userCount) {
					int i;
					for (i = 4; i >= 1; i--) {
						if (!five[i - 1] || five[i - 1]->userCount < wordQueue[front]->right->userCount) {
							five[i] = five[i - 1];
						}
						else {
							break;
						}
					}
					five[i] = wordQueue[front]->right;
				}
			}
		}
	}
	for (int i = 1; i <= 5; i++) {
		if (five[i - 1]) {
			printf("Top %d : %s %dtime(s).\n", i, five[i - 1]->tweet, five[i - 1]->userCount);
		}
	}
	free(wordQueue);
	return;
}

//Print user ID who tweet Word
void printTweetUser(Word* word) {
	if (word == NULL) {
		printf("User can't find.\n");
		return;
	}
	UserList* tmp = word->first;
	for (int i = 1; tmp; tmp = tmp->next, i++) {
		printf("%d. %s\n", i, tmp->user->screenName);
	}
}

//Find Word in WordTree
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

//Print all Word in Word tree
void printWord(Word* root) {
	if (root->left != NULL) {
		printWord(root->left);
	}
	printf("%s\n", root->tweet);
	if (root->right != NULL) {
		printWord(root->right);
	}
}

//Init WordTree
void WordBSTInit(WordBST* words) {
	words->height = 0;
	words->root = NULL;
	words->totalTweet = 0;
}

//Height of WordTree
int wordTreeHeight(Word* root) {
	if (root == NULL) return 0;
	return Max(wordTreeHeight(root->left) + 1, wordTreeHeight(root->right) + 1);
}

//Find MinWord
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

//Find MaxWord
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

//Transplant target to newWord
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

//Insert Node
Word* insertWord(WordBST* bst, char* tweet, User* tweetUser) {
	Word* tmp = (Word*)malloc(sizeof(Word));
	tmp->userCount = 1; tmp->first = NULL; tmp->color = 1;
	tmp->left = NULL; tmp->right = NULL; tmp->parent = NULL; memcpy(tmp->tweet, tweet, 300);
	bst->totalTweet++;
	if (bst->root == NULL) {
		UserList *temp = (UserList*)malloc(sizeof(UserList));
		temp->user = tweetUser;
		temp->count = 1;
		temp->next = NULL;
		bst->root = tmp;
		tmp->first = temp;
		bst->root->color = 0;
		return tmp;
	}
	Word* parent = bst->root;
	while (1) {
		if (strcmp(tweet, parent->tweet) < 0) {
			if (parent->left == NULL) {
				UserList *temp = (UserList*)malloc(sizeof(UserList));
				temp->user = tweetUser;
				temp->next = NULL;
				temp->count = 1;
				tmp->first = temp;
				tmp->parent = parent;
				parent->left = tmp;
				break;
			}
			parent = parent->left;
		}
		else if (strcmp(tweet, parent->tweet) > 0) {
			if (parent->right == NULL) {
				UserList *temp = (UserList*)malloc(sizeof(UserList));
				temp->user = tweetUser;
				temp->next = NULL;
				temp->count = 1;
				tmp->first = temp;
				tmp->parent = parent;
				parent->right = tmp;
				break;
			}
			parent = parent->right;
		}
		else {
			free(tmp);
			parent->userCount++;
			int inList = 0;
			UserList* list = parent->first;
			while (list) {
				if (list->user == tweetUser) {
					inList = 1;
					list->count++;
					break;
				}
				list = list->next;
			}
			if (inList) {
				return parent;
			}
			UserList *temp = (UserList*)malloc(sizeof(UserList));
			temp->user = tweetUser;
			temp->next = parent->first;
			temp->count = 1;
			parent->first = temp;
			return parent;
		}
	}
	WordinsertFixUp(bst, tmp);
	return tmp;
}

//Delete Node
void deleteWord(WordBST* bst, Word* z) {
	Word* y = z;
	Word *x, *xParent;
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
		y = findMinWord(z->right);
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
		WorddeleteFixUp(bst, x, xParent);
	}
	freeWord(z);
}

//WordTree delete
void destroyWordTree(WordBST target) {
	Word** WordQueue = (Word**)malloc(sizeof(Word*) * (target.totalTweet + 1));
	int front = 0, back = 0;
	WordQueue[back++] = target.root;
	if (!target.root) {
		return;
	}
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

//RB Tree Insert Fix
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

//RB Tree Delete Fix
void WorddeleteFixUp(WordBST* bst, Word* x, Word* xParent) {
	Word* w;
	while (x != bst->root && (x == NULL || x->color == 0)) {
		if (x == xParent->left) {
			w = xParent->right;
			if (w->color == 1) {
				w->color = 0;
				xParent->color = 1;
				WordleftRotate(bst, xParent);
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
					WordrightRotate(bst, w);
					w = xParent->right;
				}
				w->color = xParent->color;
				xParent->color = 0;
				if (w->right) {
					w->right->color = 0;
				}
				WordleftRotate(bst, xParent);
				x = bst->root;
			}
		}
		else {
			w = xParent->left;
			if (w->color == 1) {
				w->color = 0;
				xParent->color = 1;
				WordrightRotate(bst, xParent);
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
					WordleftRotate(bst, w);
					w = xParent->left;
				}
				w->color = xParent->color;
				xParent->color = 0;
				if (w->left) {
					w->left->color = 0;
				}
				WordrightRotate(bst, xParent);
				x = bst->root;
			}
		}
	}
	if (x) {
		x->color = 0;
	}
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

//Word free
void freeWord(Word* word) {
	UserList* tmp = word->first;
	while (tmp) {
		UserList* next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(word);
}