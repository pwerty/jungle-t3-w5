//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
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


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
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
// 사전 정의 함수 사용 된 내용
void moveOddItemsToBack(LinkedList *ll)
{
	
	LinkedList* tmpll = malloc(sizeof(LinkedList));
	tmpll->head = NULL;
	tmpll->size = 0;
	// 해당 되는 수 (여기서는 홀수)를 저장 할 연결리스트 신규 선언

	ListNode *cur;
	// 모든 아이템 순회에 필요한 커서 선언
	ListNode *BackupNext;
	// 홀수 처리 발생시, 다음 목적지 누락 방지를 위한 백업
	ListNode *latestEven = NULL;
	// 가장 마지막에 있는 짝수 노드에 최종 완성된 홀수 리스트를 이어 줄 예정.
	
	if (ll == NULL)
		return;
	// 유효하지 않은 연결 리스트에 대한 작동 차단
	cur = ll->head;
	int visitedCount = 0;
	// 사전 정의 함수 사용을 위해서는 n번째 위치 파악이 필요하여 선언.
	while (cur != NULL)
	{
		BackupNext = cur->next;
		// 목적지 누락 방지
		if((cur->item % 2) == 1)
		{
			insertNode(tmpll, tmpll->size, cur->item);
			int a = removeNode(ll, visitedCount);
			// 홀수에 대한 처리로, 별도의 연결 리스트에 추가하며 기존 연결 리스트에서 제거
			visitedCount--;
			// 기존 리스트에서 한 개의 아이템이 빠졌으니 길이도 달라짐, 이 visitedCount로 해당 내용에 맞춰 조정되어야함.
			
		}
		else
		{
			latestEven = cur;
			// 짝수의 경우 붙여줘야하는 위치를 현재 위치로 조정하기
		}
		visitedCount++;

		cur = BackupNext;
		// cur 갱신 후 쭉 진행
	}
	// 전체 내용 마무리 된 경우, 마지막에 ll에 매핑시켜서 끝내기
	if(latestEven != NULL)
		latestEven->next = tmpll->head;
	else
		ll->head = tmpll->head;
	
	free(tmpll);
	// is free
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
