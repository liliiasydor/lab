#include <windows.h>
#include "Functions.h"

int main(void)
{
    SetConsoleCP(1251);       
    SetConsoleOutputCP(1251);
    Node* head = NULL;
    Node* tail = NULL;

    if (!list_read_from_file("DataList.txt", &head, &tail)) {
        printf("Помилка відкриття файлу\n");
        return 1;
    }

    list_print(head);
    printf("\n--- Sorted by age (desc) ---\n");
    list_sort_by_age_desc(&head, &tail);
    list_print(head);

    printf("\n--- Only students with grade 2 ---\n");
    list_remove_without_grade2(&head, &tail);
    list_print(head);

    return 0;
}