/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node //노드 구조체
{
    int key;
    struct node *left;  //왼쪽 자식노드 주소 저장
    struct node *right; //오른쪽 자식노드 주소 저장
} Node;

int initializeBST(Node **h); //이중포인터를 매개변수로 받는다.

/* functions that you have to implement */
//노드 삽입. 기존에 있는 노드와 크기비교도 필요함
int insert(Node *head, int key);            /* insert a node to the tree */


void inorderTraversal(Node *ptr);           /* recursive inorder traversal */


void postorderTraversal(Node *ptr);         /* recursive postorder traversal */


void preorderTraversal(Node *ptr);          /* recursive preorder traversal */


int deleteLeafNode(Node *head, int key);    /* delete the leaf node for the key */

/*입력한 key 값이 tree에 저장되어있는지 확인
재귀를 사용한다.
반환값은 찾았을 경우 주소를, 못 찾은 경우 NULL을 반환한다.*/
Node *searchRecursive(Node *ptr, int key);  /* search the node for the key */

/*입력한 key 값이 tree에 저장되어있는지 확인
non-recursive 방식으로 반복문을 사용한다.
반환값은 찾았을 경우 주소를, 못 찾은 경우 NULL을 반환한다.*/
Node *searchIterative(Node *head, int key); /* search the node for the key */

//모든 노드 동적할당 해제
int freeBST(Node *head);                    /* free all memories allocated to the tree */

//노드 삽입 주소 찾는 함수 추가.
Node *searchInsertAddress(Node *head, int key, int* isNodeExist);

/* you may add your own defined functions if necessary */

int main()
{
    char command;      //사용자 메뉴 입력
    int key;           //노드의 값 저장
    Node *head = NULL; //헤드 노드의 주소 저장
    Node *ptr = NULL;  /* temp */

    do
    {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Binary Search Tree #1                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize BST       = z                                       \n");
        printf(" Insert Node          = n      Delete Leaf Node             = d \n");
        printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
        printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
        printf(" Postorder Traversal  = t      Quit                         = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            initializeBST(&head); //노드형의 주소를 저장하는 포인터 변수의 주소를 넣어줌.
            break;
        case 'q':
        case 'Q':
            freeBST(head);
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            printf("%p\n",head);
            insert(head, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteLeafNode(head, key);
            break;
        case 'f':
        case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            ptr = searchIterative(head, key);
            if (ptr != NULL)
                printf("\n node [%d] found at %p\n", ptr->key, ptr);
            else
                printf("\n Cannot find the node [%d]\n", key);
            break;
        case 's':
        case 'S':
            printf("Your Key = ");
            scanf("%d", &key);
            ptr = searchRecursive(head->left, key);
            if (ptr != NULL)
                printf("\n node [%d] found at %p\n", ptr->key, ptr);
            else
                printf("\n Cannot find the node [%d]\n", key);
            break;

        case 'i':
        case 'I':
            inorderTraversal(head->left);
            break;
        case 'p':
        case 'P':
            preorderTraversal(head->left);
            break;
        case 't':
        case 'T':
            postorderTraversal(head->left);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initializeBST(Node **h) //main에 있는 head에 직접 값을 보내준다.
{

    /* if the tree is not empty, then remove all allocated nodes from the tree*/
    if (*h != NULL)
        freeBST(*h);

    /* create a head node */
    *h = (Node *)malloc(sizeof(Node));
    (*h)->left = NULL; /* root */
    (*h)->right = *h;
    (*h)->key = -9999;
    return 1;
}

void inorderTraversal(Node *ptr)
{
    while(ptr != NULL){
        inorderTraversal(ptr->left);
        printf("%d", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node *ptr)//처음 ptr은 루트노드의 주소이다.
{
    while(ptr != NULL){
        printf("[%d]", ptr->key);
        preorderTraversal(ptr->left);
        preorderTraversal(ptr->right);
        return ;
    }
}

void postorderTraversal(Node *ptr)
{
    while(ptr != NULL){
        postorderTraversal(ptr->left);
        postorderTraversal(ptr->right);
        printf("%d", ptr->key);
    }
}

/*1. 입력받은 key가 기존에 있는 노드인가 -> serch의 반환값이 null이 아닐경우 : 이미 있는 key입니다. [주소:]로 전처리
2. 노드를 삽입할 주소 찾기
3. 노드 생성 및 값 대입*/
int insert(Node *head, int key)
{
    Node* node;//동적할당 할 노드
    Node* temp;//위치를 임시 저장
    int isNodeExist =0;
    
    node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    if(head->left == NULL){//루트노드 삽입시
        head->left = node;
        return 0;
    }
    else{
        temp = searchInsertAddress(head, key, &isNodeExist);//전처리 - 이미 key값이 저장되어 있는가?
    }
    
    if(isNodeExist == 1){
        printf("트리에 이미 존재하는 key값입니다. [주소 : %p]\n\n", temp);
        free(node);
        return 0;
    }
    else{
        if(temp->key > key){//삽입한 key가 기존 노드(부모노드)의 key보다 작으면
            temp->left = node;//왼쪽 자신노드로
        }
        else{
            temp->right = node;//아니면 오른쪽 자식노드로
        }
    }

    return 0;
}

int deleteLeafNode(Node *head, int key)
{
  return 0;
}

Node *searchRecursive(Node *ptr, int key)
{
  return 0;
}

Node *searchIterative(Node *head, int key)
{
    Node* node = head->left;//node에 루트노드 주소 저장
    while(node == NULL){
        if(node->key == key){//노드의 key값이 입력한 key값과 같다면
            return node;//노드의 주소 반환
        }
        if(node->key > key){//현재 읽고있는 노드의 key값이 찾는 key값보다 크면
            node = node->left;//왼쪽 자식노드 탐색
        }
        else{//그렇지 않으면
            node = node->right;//오른쪽 자식노드 탑색
        }
    }

    return NULL;//끝까지 못 찾은 경우
}

int freeBST(Node *head)//모든 노드를 해제해주어야 함. 후위순회 방식에서 방문시 동적할당을 해제하는 방식을 사용한다.
{
    if(head == head->right){//헤드노드일 때
        free(head);
        return 0;//바로 해제해주고 탈출
    }
    if(head){//맨 처음에는 헤드노드에서 루트노드로 내려감.
        freeBST(head->left);//재귀적
        freeBST(head->right);//헤드노드에서 무한루프에 빠지나?
        free(head);
    }
    return 0;
}

Node *searchInsertAddress(Node *head, int key, int* isNodeExist){
    Node* node = head->left;//반환할 주소
    Node* tail = node;//반환할 주소
    while(node != NULL){
        if(node->key == key){//노드의 key값이 입력한 key값과 같다면
            *isNodeExist = 1;
            return node;//노드의 주소 반환
        }

        if(node->key > key){//현재 읽고있는 노드의 key값이 찾는 key값보다 크면
            tail = node;
            node = node->left;//왼쪽 자식노드로 이동
        }
        else{//그렇지 않으면
            tail = node;
            node = node->right;//오른쪽 자식노드 탑색
        }
    }

    return tail;
}