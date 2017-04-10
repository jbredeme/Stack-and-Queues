#include "./llist/llist.h"
#include <stdio.h>

int main(){
	ListNode *current = NULL;		//<= current node, temp pointer
	char *endptr = NULL;			//<= reference to an value set by strtol to the next character in str after the numerical value.
	char payload[1024];				//<= input buffer
	int i = 0;						//<= loop counter
	char in;						//<= input buffer	
	void *vout;						//<= output pointer for guards

	List *list = list_create();		//<= instantiate a ADT doubly linked list

	// Welcome message
	printf("\n*** Queue data structure implimented using doubly linked list ***\n\n");
	printf("When prompted, enter a one-letter command.\n");
	printf("'q' to push to the queue\n");
	printf("'d' to pop node item from the queue\n");
	printf("'p' to print the current queue\n");
	printf("'h' to halt the program.\n\n");

	
	while(1) {	//<= input loop
		printf("Ok, enter your command: ");
		while (((in = getc(stdin)) != '\n') && (in != EOF)) {	//<= filter 'enter' character
			switch(in) {
			case 'h':
				printf("Program halted, goodbye.\n\n");
				exit(0);
				
			case 'q':
				fscanf(stdin, "%s", payload);				
				list_enqueue(list, (void*)strtol(payload, &endptr, 10));
				break;
				
			case 'd':
				vout = list_dequeue(list);

				if(vout == NULL) {
					printf("Removal unsuccessful, linked list is empty.\n\n");
					
				} else {
					printf("Head node removed successfully. Payload value = %ld\n\n", (long)vout);
					
				}
				break;
				
			case 'p':
				if((list->count) <= 0) {
					printf("Linked list is empty.\n\n");
					
				} else {
					current = list->first;
					
					if((list->count) == 1) {
						printf("%ld\n", (long*)current->value);
						
					} else {
						for(i = 0; i < (list->count); i++) {
							if(current->next != NULL) {
								printf("%ld -> ", (long*)current->value);
								
							} else {
								printf("%ld\n\n", (long*)current->value);
								
							}
							
							current = current->next;
						  
						}
						
					}
					
				}
				break;
				
			default:
				printf("You entered an invalid command.\n\n");
				break;
			}
		}
	}
	return 0;
}