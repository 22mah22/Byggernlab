/*
 * menu_list.c
 *
 * Created: 23.09.2020 16:57:30
 *  Author: magneah
 */ 
#include "menu_list.h"
#include <stdlib.h>

uint8_t totalMenuItems = 0;
uint8_t current_line = 0;
uint8_t current_line_max = 0;
uint8_t current_col = 0;
uint8_t current_col_max = 0;
DIRECTION direction = WAITING;

menuItem *head; // Må vi ha med i main før man begynner å lage listen?
menuItem *currentHead;


/*
 * Ha med i hoved-while-løkke:
 * 
 * direction = joystick_check(direction, joystick);
 * update_position(direction);
 * 
 * if(button_check()){
 *		button_action();
 * }
 * 
 * */

char* mainList[] = {
	"first",
	"second",
	"third",
	"fourth",
	"fifth",
	"sixth"
};

char* firstChildList[] = {
	"first", //name of parent
	"first1",
	"first2",
	"first3",
	"return"
};

char* fourthChildList[] = {
	"fourth", //name of parent
	"fourth1",
	"fourth2",
	"fourth3",
	"return"
};

void init_main(char* list[]){
	for(int i = 0; i < (sizeof(list)/sizeof(list[0])); i++){
		insertion_last(list[i], i);
	}
}

void init_child(char* list[]){
	for(int i = 1; i < (sizeof(list)/sizeof(list[0])); i++){
		child_insertion_last(list[0], list[i], i-1);
	}
}

void list_init(){
	init_main(mainList);
	init_child(firstChildList);
	init_child(fourthChildList);
} 

//button_action not finished
void button_action(){
	menuItem *ptr, *temp;
	ptr = menuItem_at_line(currentHead,current_line);
	if(ptr->child != NULL){
		currentHead = ptr->child;
		totalMenuItems = write_menu(currentHead);
	}else if(ptr->label == "return"){
		temp = ptr->parent;
		while(temp->prev != NULL){
			temp = temp->prev;
		}
		currentHead = temp;
		totalMenuItems = write_menu(currentHead);
	}
}
/*
DIRECTION joystick_check(DIRECTION dir, joyval stick){
    if(stick.x < 50 && stick.x > -50 && stick.y < 50 && stick.y > -50 ){
        dir = NEUTRAL;
    }
    if(dir == NEUTRAL){
        if(stick.x > 50){
            return RIGHT;
        }
        if(stick.x < -50){
            return LEFT;
        }
        if(stick.y < -50){
            return DOWN;
        }
        if(stick.y > 50){
            return UP;
        }
        return NEUTRAL;
    }
    return WAITING;
}*/

void update_position(DIRECTION dir){
	if(dir != WAITING && dir != NEUTRAL){
		if(direction == UP){
			if(current_line < current_line_max){
				current_line ++;
			}else{
				current_line = 0;
		}
		}else if(direction == DOWN){
			if(current_line > 0){
				current_line --;
			}else{
				current_line = current_line_max;
			}
		}else if(direction == RIGHT){
			if(current_col < current_col_max){
				current_col ++;
			}else{
				current_col = 0;
			}
		}else if(direction == LEFT){
			if(current_col > 0){
				current_col --;
			}else{
				current_col = current_col_max;
			}
		}
	}
}

uint8_t write_menu(menuItem *listHead){
	
    menuItem *ptr; 
    ptr = listHead;
    while(ptr->next != NULL){
        if(ptr->line == current_line){
            oled_write_string_inverted(ptr->line, ptr->label, 8);
        }else{
            oled_write_string(ptr->line, ptr->label, 8);
        }
        ptr = ptr->next;
   }
    totalMenuItems = ptr->line+1;
    return totalMenuItems;
}

menuItem* menuItem_at_line(menuItem *listHead, uint8_t lineToFind){

    menuItem *ptr;
    ptr = listHead;
    if(lineToFind > totalMenuItems){
		printf("%s", "line number to high!");
		return ptr;
	}
    while(ptr->line != lineToFind){
        ptr = ptr->next;
    }
    return ptr;
}

void insertion_beginning(char *label, uint8_t line){ 
	menuItem *ptr; 
	ptr = (menuItem *)malloc(sizeof(menuItem)); 
	if(ptr == NULL){ 
		printf("\nOVERFLOW"); 
	}
	if(head==NULL){ 
		ptr->next = NULL; 
		ptr->prev=NULL;
		ptr->child = NULL; 
		ptr->parent = NULL; 
		ptr->label=label;
		ptr->line=line; 
		head=ptr; 
	}else{ 
		ptr->label=label;
		ptr->line=line; 
		ptr->prev=NULL;
		ptr->next = head; 
		ptr->child = NULL; 
		ptr->parent = NULL; 
		head->prev=ptr; 
		head=ptr; 
		
		while(ptr->next != NULL){ 
			ptr = ptr->next; 
			ptr->line += 1;
		}
	} 
	printf("\n menuItem inserted\n"); 
}

void insertion_last(char *label, uint8_t line){ 
   menuItem *ptr,*temp;
   ptr = (menuItem *) malloc(sizeof(menuItem)); 
   if(ptr == NULL){ 
       printf("\nOVERFLOW"); 
   }else{ 
       ptr->label=label;
       ptr->line=line;
       ptr->child = NULL; 
       ptr->parent = NULL;
       if(head == NULL){ 
           ptr->next = NULL; 
           ptr->prev = NULL; 
           head = ptr; 
       }else{ 
          temp = head; 
          while(temp->next!=NULL){ 
              temp = temp->next; 
          } 
          temp->next = ptr; 
          ptr ->prev=temp; 
          ptr->next = NULL; 
          } 
       } 
     printf("\n %s menuItem inserted\n", ptr->label); 
    }
	/*
void child_insertion_last(char *parentlabel, char *label, uint8_t line){ 
	menuItem *ptr,*temp,*parentptr;
	ptr = (menuItem *) malloc(sizeof(menuItem)); 
	if(ptr == NULL){ 
		printf("\nOVERFLOW"); 
	}else{ 
		ptr->label=label;
		ptr->line=line;
		ptr->child = NULL;
		parentptr = head; 
		while(parentptr -> label != parentlabel){
			if(parentptr -> next == NULL){ 
				printf("\nCan't find parent label\n");
				return;
			} 
			parentptr = parentptr -> next;
		}
		ptr->parent = parentptr;
		if(ptr->parent->child == NULL){ 
			ptr->next = NULL; 
			ptr->prev = NULL;
			ptr->parent->child == ptr;
		}else{ 
			temp = ptr->parent->child; 
			while(temp->next!=NULL){ 
				temp = temp->next; 
			} 
			temp->next = ptr;  
			ptr->prev = temp; 
			ptr->next = NULL;
		}
	} 
	printf("\n %s menuItem inserted\n", ptr->label); 
}*/
/*
void insertion_specified(char *label, uint8_t line){ 
   menuItem *ptr,*temp;
   ptr = (menuItem *)malloc(sizeof(menuItem)); 
   if(ptr == NULL){ 
       printf("\n OVERFLOW"); 
   } 
   else{ 
       temp = head;  
       for(int i = 0 ; i < (line - 1) ; i++){ 
           temp = temp->next; 
           if(temp == NULL){ 
               printf("\n There are less than %d elements", line); 
               return; 
           } 
       } 
       ptr->child = NULL; 
       ptr->parent = NULL; 
       ptr->label = label;
       ptr->line = line;
       ptr->next = temp->next; 
       ptr->prev = temp; 
       temp->next = ptr; 
       temp->next->prev = ptr; 
	   
	   while(ptr->next != NULL){ 
			ptr = ptr->next; 
			ptr->line += 1;
		} 
       printf("\n menuItem inserted"); 
   } 
} */

void deletion_beginning(){ 
    menuItem *ptr; 
    if(head == NULL){ 
        printf("\n UNDERFLOW"); 
    } 
    else if(head->next == NULL){ 
        head = NULL;  
        free(head); 
        printf("\menuItem deleted, head now null\n"); 
    } 
    else{ 
        ptr = head; 
        head = head -> next; 
        head -> prev = NULL;
        printf("\n %s menuItem is deleting\n", ptr->label); 
		while(ptr->next != NULL){ 
			ptr = ptr->next; 
			ptr->line -= 1;
		}
        free(ptr); 
    }  
} 
/*
void deletion_last(){ 
    menuItem *ptr; 
    if(head == NULL){ 
        printf("\n UNDERFLOW"); 
    } 
    else if(head->next == NULL){ 
        head = NULL;  
        free(head);  
        printf("\menuItem deleted, head now null\n"); 
    } 
    else{ 
        ptr = head;  
        while(ptr->next != NULL){ 
            ptr = ptr -> next;  
        } 
        ptr -> prev -> next = NULL;
        printf("\n %s menuItem is deleting\n", ptr->label); 
        free(ptr); 
    } 
} */
/*
void deletion_specified(char *label){ 
    menuItem *ptr, *temp; 
    ptr = head; 
    while(ptr -> data != label){
        if(ptr -> next == NULL){ 
            printf("\nCan't delete\n");
			return;
        } 
        ptr = ptr -> next;
    }
    if(ptr -> next == NULL){ 
        ptr -> prev -> next = NULL;
        free(ptr);
        printf("\nlast menuItem deleted\n");
    } 
    else{  
        temp = ptr -> next; 
        ptr -> next = temp -> next; 
        temp -> next -> prev = ptr;
        printf("\n %s menuItem is deleting\n", temp->label); 
		while(ptr->next != NULL){ 
			ptr = ptr->next; 
			ptr->line -= 1;
		}
        free(temp);
    }    
} */
 /*
void search(){ 
    struct menuItem *ptr; 
    int item,i=0,flag; 
    ptr = head;  
    if(ptr == NULL) {
        printf("\nEmpty List\n"); 
    } 
    else{  
        printf("\nEnter item which you want to search?\n");  
        scanf("%d",&item); 
        while (ptr!=NULL){ 
            if(ptr->data == item){ 
                printf("\nitem found at location %d ",i+1); 
                flag=0; 
                break; 
            }  
            else{ 
                flag=1; 
            } 
            i++; 
            ptr = ptr -> next; 
        } 
        if(flag==1){ 
            printf("\nItem not found\n"); 
        } 
    }    
} */