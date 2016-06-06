#pragma once
#include <Windows.h>
struct UserList {
	char ID[30];
	UserList* next;
};