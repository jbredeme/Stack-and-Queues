#include <llist/llist.h>
#include <llist/dbg.h>
#include <stdlib.h>


/*
  Just initializes the list structure (the node pointers are NULL and
  the count = 0.
*/
List* list_create() {
	List* list = malloc(sizeof(List));
	list->count = 0;
	list->first = NULL;
	list->last = NULL;
	return list;

}


/*
  Just initializes a ListNode structure (the node pointers are NULL and
  the pointer to the data is set to payload.
*/
ListNode* list_create_node(void* payload) {
	ListNode* node = malloc(sizeof(ListNode));
	node->value = payload;
	node->next = NULL;
	node->prev = NULL;
	return node;

}


/*
  Frees any nodes in the list and then frees the list structure.
*/
List* list_destroy(List* list) {
	if((list->count) == 0) {
		free(list);
		
	} else {
		list_clear(list);
		free(list);
		
	}
	
	return NULL;

}


/*
  Frees any nodes in the list but leaves the list structure.
*/
void list_clear(List* list) {
	if(list != NULL) {
		ListNode* current = list->first;
		
		while(current != NULL) {
			ListNode* temp = current;
			current = current->next;
			free(temp);
			list->count -= 1;
			
		}

		list->first = NULL;
		list->last = NULL;	
	}

}


/*
  Returns the count in the list structure.
*/
int list_count(List* list) {
	return list->count;

}


/*
  Returns the first node in the list.
*/
ListNode* list_first(List* list) {
	return list->first;
	
}


/*
  Returns the last node in the list.
*/
ListNode* list_last(List* list) {
	return list->last;
	
}


/*
  Finds a node in the list by value and returns the pointer to the node.
  If no matching node is found, returns NULL.
*/
ListNode* list_find(List* list, void* value) {
	ListNode* tnode = NULL;
	
	if(list != NULL) {
		ListNode* current = list->first;
		
		while(current != NULL) {
			if((current->value) == value) {
				tnode = current;
				break;
				
			} else {
				current = current->next;
				
			}
			
		}	
		
	}
	
	return tnode;
	
}


/*
  Inserts a node in the list after the node containing value.  If no node
  has the passed value or if value == NULL, insert at the end of the list.
*/
void list_insert_after(List* list, ListNode* node, void* value) {
	ListNode* current = list_find(list, value);
	
	if((list != NULL) && (node != NULL)) {
		if(list->count == 0) {
			list->first = node;
			list->last = node;
			list->count += 1;
			
		} else if((current == NULL) || (value == NULL) || ((list->last) == current)) {
			(list->last)->next = node;
			node->prev = (list->last);
			list->last = node;
			list->count += 1;
	
		} else {
			node->next = current->next;
			(current->next)->prev = node;
			current->next = node;
			node->prev = current;
			list->count += 1;
			
		} 
		
	}

}


/*
  Inserts a node in the list before the node containing value.  If no node has
  the passed value or if value == NULL, insert at the beginning of the list.
*/
void list_insert_before(List* list, ListNode* node, void* value) {
	ListNode* current = list_find(list, value);
	
	if((list != NULL) && (node != NULL)) {
		if(list->count == 0) {
			list->first = node;
			list->last = node;
			list->count += 1;
			
		} else if((current == NULL) || (value == NULL) || ((list->first) == current)) {
			(list->first)->prev = node;
			node->next = (list->first);
			list->first = node;
			list->count += 1;
	
		} else {
			node->prev = current->prev;
			(current->prev)->next = node;
			current->prev = node;
			node->next = current;
			list->count += 1;
			
		} 
		
	}
}


/*
  Removes the specified node from the list and frees it.  The node's value
  is saved and returned.
*/
void* list_remove_node(List* list, ListNode* node) {
	void* node_val = NULL;
	
	if((list != NULL) && (node != NULL)) {
		node_val = node->value;
		
		if(list->count == 1) {
			list->first = NULL;
			list->last = NULL;
			
		} else if(node == (list->first)) {
			list->first = node->next;
			(list->first)->prev = NULL;
			
		} else if(node == (list->last)) {
			list->last = node->prev;
			(list->last)->next = NULL;
			
		} else {
			(node->next)->prev = (node->prev);
			(node->prev)->next = (node->next);
		}
		
		free(node);
		list->count -= 1;
		return node_val;
			
		
	} else {
		return node_val;
		
	}
	
}


/*
  Removes the node with the specified value from the list.  The node's value
  is saved and returned.  If a node with the value is not found in the list,
  return NULL
*/
void* list_remove_value(List* list, void* value) {
	ListNode* current = list_find(list, value);
	void* node_val = NULL;

		if(current != NULL) {
			node_val = list_remove_node(list, current);
			
		}
		
		return node_val;

}


/*
  Adds a node at the head of the ADT doubly linked-list
*/
void list_push(List* list, void* value) {
	ListNode* node = list_create_node(value);	//<= Create new node
	
	if((list->first) != NULL) {					//<= Condition 1: the list is not empty
		(list->first)->prev = node;
		node->next = list->first;
		list->first = node;
		
	} else {									//<= Condition 2: the list has one or more nodes
		list->first = list->last = node;
		
	}
	
	list->count += 1;
}


/*
  Adds a node at the tail of the ADT doubly linked-list
*/
void list_enqueue(List* list, void* value) {
	ListNode* node = list_create_node(value);	//<= Create new node
	
	if((list->first) != NULL) {					//<= Condition 1: the list is not empty
		(list->last)->next = node;
		node->prev = list->last;
		list->last = node;
		
	} else {									//<= Condition 2: the list has one or more nodes
		list->first = list->last = node;
		
	}
	
	list->count += 1;
	
}


/*
  Removes a node at the head of the ADT doubly linked-list. The value of the removed node is returned.
*/
void* list_pop(List* list) {
	if((list->count) == 0) {	//<= Condition 1: the linked list is empty
		return NULL;
		
	} else {					//<= Condition 2: the linked list is not empty
		return list_remove_node(list, (list->first));
		
	}
	
}


/*
  Removes a node at the head of the ADT doubly linked-list. The value of the removed node is returned.
*/
void* list_dequeue(List* list) {
	if((list->count) == 0) {	//<= Condition 1: the linked list is empty
		return NULL;
		
	} else {					//<= Condition 2: the linked list is not empty
		return list_remove_node(list, (list->first));
		
	}
	
}