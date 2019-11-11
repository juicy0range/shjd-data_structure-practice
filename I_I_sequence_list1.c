/* 线性表的顺序存储实现 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 定义符号常量
#define LIST_INIT_SIZE 50 /* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 10    /* 线性表存储空间的分配增量 */
#define OK 1
#define ERROR 0
#define OVERFLOW -2

// 定义元素类型   ///假设为int
typedef int ElemType;

// 定义顺序表类型
typedef struct {
    ElemType *elem; // 元素    /* 存储空间基址 */
    int length;     /* 当前长度 */
    int listsize;   /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
} SqList;   /* 顺序表类型 */

// 初始化——构造空顺序表  //malloc
int InitList(SqList *L) {
    // 获取顺序表基址
    L->elem = (ElemType *) malloc(sizeof(ElemType));
    if (!L->elem) return ERROR;
    // 空表、容量
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

// 查找——获取顺序表第i个元素
ElemType GetListElem(SqList *L, int i) {
    // 检查i的合法性
    if (i < 1 || i > L->length)
        return ERROR;
    else
        return L->elem[i - 1];
}


// 插入——在顺序表第i个位置插入元素    //recalloc
int InsertListElem(SqList *L, int i, ElemType e) {
    int k;
    // 位置合法性判断
    if (i < 1 || i > L->length + 1) return ERROR;
    // 顺序表空间满，按增量重新分配
    if (L->length >= L->listsize) {
        // 增加LISTINCREMENT个元素元素，获取顺序表新基址
        L->elem = (ElemType *) realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!L->elem) return ERROR;
        // 按增量修改存储空间大小
        L->listsize += LISTINCREMENT;
    }

    // 元素后移1位
    for (k = L->length - 1; k >= i - 1; k--)
        L->elem[k + 1] = L->elem[k];
    // 插入元素
    L->elem[i - 1] = e;

    L->length++;
    return OK;
}

// 删除——删除顺序表第i个元素
int DeleteListElem(SqList *L, int i) {
    int k;
    // 判断位置合法性
    if (i < 1 || i > L->length) return ERROR;
    // 元素前移1位
    for (k = i; k <= L->length; k++)
        L->elem[k - 1] = L->elem[k];

    L->length--;
    return OK;
}

//——————————————————————————————————————————————————————
//未考察项目

// 定位——定位目标元素在顺序表中位置
int LocateListElem(SqList *L, ElemType e) {
    int i = 1;
    // 定义指针p，指向第一个元素
    ElemType *p = L->elem;
    // 目标元素依次与顺序表元素比较
    while (*p != e && i <= L->length) {
        i++;
        p++;
    }
    if (i > L->length)
        return 0;
    else
        return i;
}

// 修改——修改顺序表第i个元素
int UpdateListElem(SqList *L, int i, ElemType e) {
    // 判断位置合法性
    if (i < 1 || i > L->length) return ERROR;
    // 修改第i个元素值
    L->elem[i - 1] = e;
    // 修改成功
    return OK;
}

// 输出顺序表全部元素
void PrintList(SqList *L) {
    int i;
    if (L->length == 0)
        printf("\n顺序表为空！\n\n");
    else
        for (i = 1; i <= L->length; i++)
            printf("%d ", L->elem[i - 1]);
    printf("\n");
}

int main() {
    int i, choice, position;
    ElemType data, elem;
    int isRunning = 1;

    //init
    SqList *pl = (SqList *) malloc(sizeof(SqList));

    while (isRunning) {
        printf("======顺序表操作演示=======\n");
        printf("1. 创建一个空的顺序表\n");
        printf("2. 输出顺序表的全部数据\n");
        printf("3. 查询顺序表某个位置的数据\n");
        printf("4. 查询数据在顺序表中的位置\n");
        printf("5. 向顺序表指定位置插入数据\n");
        printf("6. 删除顺序表指定位置的数据\n");
        printf("7. 更新顺序表指定位置的数据\n");
        printf("8. 退出顺序表操作演示程序\n");
        printf("===========================\n");
        printf("\n输入1-8，选择所需功能号：");
        scanf("%d", &choice);
        printf("\n您选择的功能号为：%d\n", choice);

        switch (choice) {
            //初始化
            case 1:
                if (InitList(pl))
                    printf("\n顺序表创建成功！\n\n");
                else
                    printf("\n顺序表创建失败！\n\n");
                system("pause");
                break;
                //查找
            case 3:
                printf("i=");
                scanf("%d", &i);
                elem = GetListElem(pl, i);
                if (elem)
                    printf("L[%d]=%d\n\n", i, elem);
                else
                    printf("输入的位置不合法！");
                system("pause");
                break;
            case 4:
                printf("data=");
                scanf("%d", &data);
                position = LocateListElem(pl, data);
                if (position)
                    printf("%d is at [%d] of the list.\n\n", data, position);
                else
                    printf("%d is not in the list.\n\n", data);
                system("pause");
                break;
                //插入
            case 5:
                printf("i,data=");
                scanf("%d,%d", &i, &data);
                if (InsertListElem(pl, i, data))
                    printf("\n数据插入成功！\n\n");
                else
                    printf("\n数据插入失败！\n\n");
                system("pause");
                break;
                //删除
            case 6:
                printf("i=");
                scanf("%d", &i);
                if (DeleteListElem(pl, i))
                    printf("\n数据删除成功！\n\n");
                else
                    printf("\n数据删除失败！\n\n");
                system("pause");
                break;



                //---------------------------------------------------------
                //未要求功能

                //输出全部
            case 2:
                PrintList(pl);
                system("pause");
                break;


            case 7:
                printf("i,data=");
                scanf("%d,%d", &i, &data);
                if (UpdateListElem(pl, i, data))
                    printf("\n数据更新成功！\n\n");
                else
                    printf("\n数据更新失败！\n\n");
                system("pause");
                break;
            case 8:
                isRunning = 0;
                break;
        }
    }

    printf("\n谢谢使用本程序~");

    return 0;
}