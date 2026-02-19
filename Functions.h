#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME 20
#define MAX_GRADES 7
#define WITH 60
typedef struct Student {
    char surname[MAX_NAME];
    char name[MAX_NAME];
    char date[11];
    int grades[MAX_GRADES];
}Student;
typedef struct Node
{
	struct Student data;
	struct Node* next;
}Node;
void read_from_file_list(char* fileName, Node** head, Node** tail);
void print_list(Node* head, Node* tail);
void sort_list(Node** head, Node** tail);
int is_bad(Student s);
void remove_bad(Node** head, Node** tail);
