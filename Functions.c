#include "Functions.h"

int compare_dates(const char* d1, const char* d2)
{
    struct tm tm1 = { 0 }, tm2 = { 0 };
    sscanf(d1, "%d.%d.%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
    sscanf(d2, "%d.%d.%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);

    tm1.tm_mon--;  tm1.tm_year -= 1900;
    tm2.tm_mon--;  tm2.tm_year -= 1900;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    if (t1 < t2) return -1;
    if (t1 > t2) return 1;
    return 0;
}

void list_push_back(Node** head, Node** tail, const Student* s)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = *s;
    node->next = NULL;

    if (*head == NULL) {
        *head = *tail = node;
    }
    else {
        (*tail)->next = node;
        *tail = node;
    }
}

int list_read_from_file(const char* fileName, Node** head, Node** tail)
{
    FILE* f = fopen(fileName, "r");
    if (!f) return 0;

    Student s;
    while (fscanf(f, "%19s %19s %10s",
        s.surname, s.name, s.date) == 3)
    {
        for (int i = 0; i < MAX_GRADES; i++)
            fscanf(f, "%d", &s.grades[i]);

        list_push_back(head, tail, &s);
    }
    fclose(f);
    return 1;
}

void list_print(const Node* head)
{
    const Node* p = head;
    while (p) {
        printf("%s %s %s | ", p->data.surname, p->data.name, p->data.date);
        for (int i = 0; i < MAX_GRADES; i++)
            printf("%d ", p->data.grades[i]);
        printf("\n");
        p = p->next;
    }
}

int student_has_grade2(const Student* s)
{
    for (int i = 0; i < MAX_GRADES; i++)
        if (s->grades[i] == 2)
            return 1;
    return 0;
}

void list_remove_without_grade2(Node** head, Node** tail)
{
    while (*head && !student_has_grade2(&(*head)->data)) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }

    if (!*head) {
        *tail = NULL;
        return;
    }

    Node* cur = *head;
    while (cur->next) {
        if (!student_has_grade2(&cur->next->data)) {
            Node* tmp = cur->next;
            cur->next = tmp->next;
            if (tmp == *tail) *tail = cur;
            free(tmp);
        }
        else {
            cur = cur->next;
        }
    }
}

void list_sort_by_age_desc(Node** head, Node** tail)
{
    if (!*head || !(*head)->next) return;

    int swapped;
    do {
        swapped = 0;
        Node** pp = head;
        Node* a = *pp;

        while (a && a->next) {
            Node* b = a->next;
            if (compare_dates(a->data.date, b->data.date) > 0) {
                a->next = b->next;
                b->next = a;
                *pp = b;
                swapped = 1;
            }
            pp = &((*pp)->next);
            a = *pp;
        }
    } while (swapped);

    Node* t = *head;
    while (t->next) t = t->next;
    *tail = t;
}