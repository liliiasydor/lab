#include "Functions.h"
int compare_dates(const char* d1, const char* d2)
{
    struct tm tm1 = { 0 }, tm2 = { 0 };

    // Розбір dd.mm.yyyy
    sscanf(d1, "%d.%d.%d", &tm1.tm_mday, &tm1.tm_mon, &tm1.tm_year);
    sscanf(d2, "%d.%d.%d", &tm2.tm_mday, &tm2.tm_mon, &tm2.tm_year);

    tm1.tm_mon -= 1;     // місяці в tm = 0–11
    tm1.tm_year -= 1900; // роки від 1900

    tm2.tm_mon -= 1;
    tm2.tm_year -= 1900;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    if (t1 < t2) return -1;
    if (t1 > t2) return 1;
    return 0;
}
void read_from_file_list(char* fileName, Node** head, Node** tail)
{
    FILE* f = fopen(fileName, "r");
    if (!f) {
        printf("Не вдалося відкрити файл!\n");
        return 0;
    }
    Node* ptr = (Node*)malloc(sizeof(Node));
    ptr->next = NULL;
    *head = ptr;

    // Зчитуємо, поки є рядки
    while (!feof(f)) {
        /*printf("Hello\n");*/
        ptr->next= (Node*)malloc(sizeof(Node));
        /*ptr->next = NULL;*/
        ptr = ptr->next;
        ptr->next = NULL;
        /*printf("Hi\n");*/
        Student s;
        fscanf(f, "%49s %49s %10s", s.surname, s.name, s.date);
        /*printf("%s\n", s.surname);
        printf("%s\n", s.name);
        printf("%s\n", s.date);*/
        for (int i = 0; i < MAX_GRADES; i++) {
            fscanf(f, "%d", &s.grades[i]);
          /*  printf("%d ", s.grades[i]);*/
        }
        
        /*(ptr->data).surname = s.surname;*/
        (ptr->data) = s;
        /*printf("end\n");*/

    }


    fclose(f);
    *tail = ptr;
    ptr = *head;
    *head = ptr->next;
    free(ptr);
    return 1;

}

void print_list(Node* head, Node* tail)
{
    char bordure[WITH];

    for (int i = 0; i < WITH - 1; i++)
    {
        bordure[i] = '*';

    }
    bordure[WITH - 1] = '\0';
    printf("%s\n", bordure);
    printf("* %-12s | %-10s | %-10s | %-14s * \n", "Прізвище", "Ім'я", "Дата", "Оцінки");
    printf("%s\n", bordure);
    Node* ptr = head;
    while (ptr != NULL)
    {
        printf("* %-12s | %-10s | %10s | ", ptr->data.surname, ptr->data.name, ptr->data.date);
        for (int j = 0; j < MAX_GRADES; j++) {
            printf("%d ", ptr->data.grades[j]);
        }
        printf(" *\n");
        ptr = ptr->next;
    }
    printf("%s\n", bordure);
}

void sort_list(Node** head, Node** tail)
{
    if (*head == NULL)
    {
        return;
    }
    Node* head1 = (Node*)malloc(sizeof(Node));
    head1->data = (*head)->data;
    Node* tail1 = head1;
    head1->next = NULL;
    Node* ptr = *head;
    *head = (*head)->next;
    free(ptr);
    ptr = *head;
    while (ptr != NULL)
    {
        Node* ptr1 = head1;
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = ptr->data;
        if (compare_dates(ptr->data.date, ptr1->data.date)<0)
        {
            /*printf("z=%s\n", ptr->data.surname);*/
            temp->next = ptr1;
            head1 = temp;
            *head = (*head)->next;
            free(ptr);
            ptr = *head;
            
            continue;
        }
       /* printf("k=%s\n", ptr1->data.surname);
        printf("l=%s\n", tail1->data.surname);*/
        int isInserting = 0;
        while (ptr1 != tail1)
        {
            /*printf("z=%s\n", ptr->data.surname);
            printf("p=%s\n", ptr1->data.surname);
            printf("h=%s\n", ptr1->next->data.surname);*/
            if ((compare_dates(ptr->data.date, ptr1->data.date) >= 0) && (compare_dates(ptr->data.date, ptr1->next->data.date)) < 0)
            {
               /* printf("hello\n");*/
                temp->next = ptr1->next;
                ptr1->next = temp;
               /* head1 = temp;*/
                *head = (*head)->next;
                free(ptr);
                ptr = *head;
                isInserting = 1;
                break;
            }
            ptr1 = ptr1->next;
        }
        if (isInserting == 0)
        {
            tail1->next = temp;
            temp->next = NULL;
            tail1 = temp;
            /*head1 = temp;*/
            *head = (*head)->next;
            free(ptr);
            ptr = *head;
            continue;
        }
    }
    *head = head1;
    *tail = tail1;
}

int is_bad(Student s)
{
    int res = 0;
    for (int i = 0; i < MAX_GRADES; i++)
    {
        if (s.grades[i] == 2)
        {
            res = 1;
            break;
        }
    }
    return res;
}

void remove_bad(Node** head, Node** tail)
{
    Node* ptr = *head;
    while (!is_bad(ptr->data))
    {
        *head = (*head)->next;
        free(ptr);
        ptr = *head;
        
    }
    
    while (ptr != *tail)
    {
        if (!is_bad(ptr->next->data))
        {
            /*printf("f=%s\n", ptr->next->data.surname);*/
            Node* temp = ptr->next;
            ptr->next = temp->next;
            free(temp);
            if (ptr->next == NULL)
            {
                *tail = ptr;
                break;
            }
        }
        else
        {
            ptr = ptr->next;

        }
    }
    if (!is_bad((*tail)->data))
    {
        ptr->next = NULL;
        free(*tail);
        *tail = ptr;
    }
}

