#include "Functions.h"
int main(void)
{
	system("chcp 1251");
	
	Node* head=NULL;
	Node* tail = NULL;
	read_from_file_list("DataList.txt", &head, &tail);
	print_list(head, tail);
	sort_list(&head, &tail);
	printf("\n");
	print_list(head, tail);
	printf("\n");
	remove_bad(&head, &tail);
	print_list(head, tail);
	return 0;
}