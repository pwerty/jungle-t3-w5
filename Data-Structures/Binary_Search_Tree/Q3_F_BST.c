//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void preOrderIterative(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the pre-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting pre-order traversal of the binary search tree is: ");
			preOrderIterative(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////


// Binary Search Tree, Quest 3 : 전위 순회를 스택 1개를 사용하여 구현하기
void preOrderIterative(BSTNode *root)
{
	if(root == NULL)
		return;
	// 루트 자체가 존재하지 않는 경우는 트리가 없으므로, 이 경우엔 진행 할 필요가 없습니다.

	Stack *sta = malloc(sizeof(Stack));
	sta->top = NULL;
	// 스택 한 개를 선언하고 초기화합니다. top 초기화를 하지 않으면 오류가 발생 할 수 있어 확실하게 해야합니다.

	push(sta, root);
	// 주어진 BST의 첫 값을 입력으로 받게 될텐데, 이 값을 방금 만든 스택에 넣습니다.

	while (isEmpty(&sta) == 0)
	// 스택에 내용이 남아있는 동안에는 작동하게 됩니다.
	// C언어는 True/False 개념이 없으며, isEmpty는 숫자 1이 Empty가 Yes, 숫자 0이 Not Empty를 뜻합니다.
	// 그래서 이 내용은 Python에서 isEmpty(stack) == False 와 동일합니다.
	{
		BSTNode *poped = pop(&sta);
		// 스택에서 아이템을 뽑고 이 아이템을 사용 할 준비를 합니다.
		printf("%d ", poped->item);
		// 전위 순회는 자식 노드에 대한 작업을 진행하기 전 우선 해당 노드에 대해 작업을 수행합니다.
		// 이 함수에서 해야 할 작업은 출력이니 출력을 진행합니다.

		if(poped->right != NULL)
			push(&sta, poped->right);
		// 오른쪽 자식이 존재하는 경우, 해당 노드를 스택에 넣습니다.

		if(poped->left != NULL)
			push(&sta, poped->left);
		// 왼쪽 자식이 존재하는 경우, 해당 노드를 스택에 넣습니다.

		// 통상적인 전위 순회는 [노드 자기 자신 작업] -> [자기 자신의 좌측 자식] -> [우측 자식] 순으로 이뤄집니다.
		// 여기선 [자신 작업] -> [우측 자식] -> [좌측 자식] 순서대로 흐름이 이어지고 있습니다.
		// 이렇게 구현한 것은 스택의 특성 때문입니다. 스택 특성 상 마지막으로 들어간 값이 가장 먼저 나옵니다.
		// 즉, 다음 호출에는 Left가 늦게 들어갔으니 Left에 대한 내용이 먼저 pop 될 것입니다.
		// 따라서 Left-Right가 아닌 Right-Left 순 push가 순서를 지키는 것이 됩니다.
	}

	free(sta);
	// 코드 진행이 여기까지 온 경우, 스택은 더 이상 이용 할 필요가 없으니 배정된 메모리르 반환합니다.
}
// 어떤 부분에선 스택을 사용한 순회라서 기존에 DFS와 유사한 점이 있다고 여기실 수도 있을 것 같습니다.
// 읽으시느라 고생 많으셨습니다.

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
