#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 20
#define MAX_GRADES 7

typedef struct Student {
    char surname[MAX_NAME];
    char name[MAX_NAME];
    char date[11]; // dd.mm.yyyy
    int grades[MAX_GRADES];
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

int list_read_from_file(const char* fileName, Node** head, Node** tail);
void list_print(const Node* head);
void list_sort_by_age_desc(Node** head, Node** tail);
int student_has_grade2(const Student* s);
void list_remove_without_grade2(Node** head, Node** tail);
void list_push_back(Node** head, Node** tail, const Student* s);
int compare_dates(const char* d1, const char* d2);