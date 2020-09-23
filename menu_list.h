/*
 * menu_list.h
 *
 * Created: 23.09.2020 16:57:57
 *  Author: magneah
 */ 


#ifndef MENU_LIST_H_
#define MENU_LIST_H_



typedef struct{
	struct menuItem* prev;
	struct menuItem* next;
	char label[];
} menuItem;

struct menuItem* head;

menuItem* ptr;
ptr = (menuItem*)malloc(sizeof(menuItem));

ptr->label = "start";
ptr->prev = NULL;
ptr->next = NULL;
head = ptr;

ptr = (menuItem*)malloc(sizeof(menuItem));

ptr->label = "second";
ptr->prev = head;
ptr->prev->next = ptr;
ptr->next = NULL;



ptr = (menuItem*)malloc(sizeof(menuItem));

menuItem* temp = head;

ptr->label = "third";
while(temp->next != NULL){
	temp = temp->next;
}
temp->next = ptr;
ptr->prev = temp;
ptr->next = NULL;

ptr = head;

while(ptr != NULL){
	printf("%s \n", ptr->label);
	ptr = ptr->next;
}





#endif /* MENU_LIST_H_ */