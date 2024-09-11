///////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // Include limits.h for INT_MIN

#define SIZE 1000 //The limit of expression length

/////////////////////////////////////////////////

typedef struct _listnode{
   char item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
 } LinkedList;

////////////////////////////////// stack    ///////////////////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////// function prototypes //////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void infixtoPrefix(char* infix, char* prefix);
int precedence(char op); // you may use this function

///////////////////////////////////////////////////////////////////////////////////////////////
void push(Stack *s, char item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

///////////////////////////////////////////////////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, char item);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    infixtoPrefix(infix, prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);
    return 0;
}

void infixtoPrefix(char* infix, char* prefix)
{
    Stack s;
    s.ll.head = NULL;
    s.ll.size = 0;
    int i, j;
    char c, temp;

    if(infix == NULL || strlen(infix) == 0)return;

    //reverse the infix expression w/o bracket conversion
    for(i=0, j=strlen(infix)-1; i<j; i++, j--){
        temp = infix[i];
        infix[i] = infix[j];
        infix[j] = temp;
    }
    i = 0; j = 0;
    while(i<SIZE && infix[i]!='\0'){
        c = infix[i++];
        switch(c){
        case ')':
            push(&s, c);
            break;
        case '(':
            while(!isEmptyStack(&s) && peek(&s)!=')'){
                prefix[j++] = pop(&s);}
            if(!isEmptyStack(&s) && peek(&s)==')')
                pop(&s);
            break;
        case '*':
        case '/':
        case '+':
        case '-':
            while(!isEmptyStack(&s) && peek(&s)!=')' && precedence(peek(&s)) > precedence(c)){
                prefix[j++] = pop(&s);
            } push(&s, c);
            break;
        default:
            prefix[j++] = c;
        }
    }
    while(!isEmptyStack(&s)){
        prefix[j++] = pop(&s); //pop remaining items in stack to prefix
    }
    prefix[j] = '\0';

    //reverse the expression to obtain prefix
    for(i=0, j=strlen(prefix)-1; i<j; i++, j--){
        temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
}


int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, char item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   char item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%c ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, char value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
