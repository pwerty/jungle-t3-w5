//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			//removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{	
	ListNode *cur;
	int numCnt = 0;
	if(ll->head == NULL)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = item;
		ll->head->next = cur;
		ll->size++;
		return 0;
		// 첫 번째 아이템 삽입 위치는 반드시 0이니 당연하게 0을 반환하도록 한다.
	}
	else 
	{
		int isInsertable = 0;
		ListNode *exists;
		exists = ll->head;
		if(exists->item == item)
			return -1;

		// cur가 제대로 준비 안된 상태에서 cur->item 사용 시도해서 SegFault
		if(exists->item > item)
		{
			cur = ll->head;
			ll->head = malloc(sizeof(ListNode));
			ll->head->item = item;
			ll->head->next = exists;
			ll->size++;
			return 0;
		}
		while (isInsertable == 0)
		{
			if(exists->next == NULL)
			{
				cur = exists->next;
				exists->next = malloc(sizeof(ListNode));
				exists->next->item = item;
				exists->next->next = NULL;
				ll->size++;
				isInsertable = 1;
				return ll->size - 1;
				// 맨 끝 도달시 이렇게 반환하도록 한다.
			}

			if(exists->next->item == item) // is this already exists?
				return -1;

			if(exists->next->item < item)
			{
				exists = exists->next;
				numCnt++;
			}
			else // 아이템을 배치 해야하는 상태
			{
				ListNode *tmp = exists->next;
				cur = exists->next;
				exists->next = malloc(sizeof(ListNode));
				exists->next->item = item;
				exists->next->next = tmp;
				ll->size++;

				isInsertable = 1;
				return numCnt + 1;
			}
			
		}
	}

	/* 
		처음 노드 부터, selected.next.item 보다 작으면 selected.next에 cur가 들어가야 한다.
		하지만 중요한 것은 맥락상 첫 노드와 끝 노드가 들어갈 위치가 된 경우에도 범용성을 가져야하는데..
		ll->head 보다 작은 상황이 날 수 있다. 그럼 새로운 ll->head를 정의하기

		selected.next가 없을 수도 있다. 즉 마지막 노드에 도달 한 상태라면

	*/


	
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

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

int insertNode(LinkedList *ll, int index, int value){

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
