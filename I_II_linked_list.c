#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define LEN 20
#define N 5

typedef int data_t; //定义元素数据类型
typedef struct Node {
    data_t data;
    struct Node *next;
} Node, *LinkList;

//*LinkList写法等价于==
//typedef  struct Node *Linklist;
LinkList CreateEmptyLinklist(void);

//init——创建空链表
LinkList CreateListHead(LinkList, int);

//init1——头插法创建链表
LinkList CreateListTail(LinkList, int);

//init2——尾插法创建链表
int PrintList(LinkList);

//insert——插入节点
int ListDelete(LinkList, int, data_t *);

//删除节点
LinkList Adjmax(LinkList);

//——————————————————————————————————————————
//未需求

//打印链表
int ListInsert(LinkList, int, data_t);

//寻找最大元素对
int ListReverse(LinkList);

//链表反序
int ClearList(LinkList);

//----------------------------------------------

//1init
LinkList CreateEmptyLinklist(void) {
    LinkList p;
    p = (LinkList) malloc(sizeof(Node));
    if (NULL == p) {
        perror("CreateEmptyLinklist error");
        exit(0);
    }
    p->next = NULL;
    return p;
}

//2insert
int ListInsert(LinkList L, int i, data_t dt) {
    int j = 1;
    LinkList p, s;
    p = L;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p) {
        printf("%d position error!\n", i);
        return ERROR;
    }

    s = (LinkList) malloc(sizeof(Node));
    s->data = dt;
    s->next = p->next;
    p->next = s;

    return OK;
}

//3delete
int ListDelete(LinkList L, int i, data_t *dt) {
    int j;
    LinkList p, q;
    if (NULL == L->next) {
        printf("LinkList is Empty!\n");
        return ERROR;
    }
    p = L;
    j = 1;
    while (p->next && j < i) {
        p = p->next;
        j++;
    }
    if (!(p->next)) {
        printf("%d position error!\n", i);
        return ERROR;
    }

    q = p->next;
    p->next = q->next;
    *dt = q->data;
    free(q);

    return OK;
}

//---------------------------------------------------
//未需求

//头插
LinkList CreateListHead(LinkList L, int len) {
    LinkList p;
    int i;
    srand(time(NULL));
    for (i = 0; i < len; i++) {
        p = (LinkList) malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        p->next = L->next;
        L->next = p;
    }
    return L;
}

//尾插
LinkList CreateListTail(LinkList L, int len) {
    LinkList p, r;
    int i;
    srand(time(NULL));
    r = L;
    for (i = 0; i < len; i++) {
        p = (LinkList) malloc(sizeof(Node));
        p->data = rand() % 100 + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;

    return L;
}

LinkList Adjmax(LinkList L) {
    LinkList p, p1, q;
    int m0, m1;
    p = L->next;
    p1 = p;
    if (NULL == p1)
        return p1;
    q = p->next;
    if (NULL == q)
        return p1;
    m0 = p->data + q->data;
    while (q->next != NULL) {
        p = q;
        q = q->next;
        m1 = p->data + q->data;
        if (m1 > m0) {
            p1 = p;
            m0 = m1;
        }
    }

    return p1;
}

int ListReverse(LinkList L) {
    LinkList p, q;
    p = L->next;
    L->next = NULL;
    while (p != NULL) {
        q = p;
        p = p->next;
        q->next = L->next;
        L->next = q;
    }

    return OK;
}

int ClearList(LinkList L) {
    LinkList p, q;
    p = L->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;

    return OK;
}

int PrintList(LinkList L) {
    LinkList p = L->next;
    int count = 0;
    while (p) {
        printf("%d\t", p->data);
        p = p->next;
        if (0 == ++count % N)
            printf("\n");
    }
    printf("\n");
    return OK;
}

//------------------------------------------------
//main
int main(int argc, const char *argv[]) {
    LinkList head1, head2;
    int i;
    data_t data = 122;
    head1 = CreateEmptyLinklist();
    head2 = CreateEmptyLinklist();
    printf("head1 and head2 create successfully!\n");

    head1 = CreateListHead(head1, LEN);
    PrintList(head1);
    head2 = CreateListTail(head2, LEN);
    PrintList(head2);

    scanf("%d", &i);
    printf("Insert head1 %d position, data is %d\n", i, data);
    ListInsert(head1, i, data);
    PrintList(head1);

    scanf("%d", &i);
    ListDelete(head1, i, &data);
    printf("Delete head1 %d position, data is %d\n", i, data);
    PrintList(head1);

    LinkList adjmax = Adjmax(head1);
    printf("Adjmax data is %d, Adjmax data next data is %d\n",
           adjmax->data, adjmax->next->data);

    ListReverse(head1);
    printf("Reserve head1:\n");
    PrintList(head1);

    if (OK == ClearList(head1))
        printf("head1 Clear success!\n");
    if (OK == ClearList(head2))
        printf("head2 clear success!\n");

    return 0;
}
