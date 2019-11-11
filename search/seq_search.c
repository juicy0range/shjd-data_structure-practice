//
// Created by pan on 2019-11-10.
//

#include <stdio.h>
#include <stdlib.h>

/**
 *
 *


查找表：
在日常生活中，几乎每天都要进行一些查找的工作，在电话簿中查阅某个人的电话号码；在电脑的文件夹中查找某个具体的文件等等。本节主要介绍用于查找操作的数据结构——查找表。

查找表是由   **同一类型的数据元素构成的集合。例如电话号码簿和字典都可以看作是一张查找表。

操作：
在查找表中查找某个具体的数据元素；
在查找表中插入数据元素；
从查找表中删除数据元素；

 关键字：
 在查找表查找某个特定元素时，前提是需要知道这个元素的一些属性。
 例如，每个人上学的时候都会有自己唯一的学号，因为你的姓名、年龄都有可能和其他人是重复的，唯独学号不会重复。
 而学生具有的这些属性（学号、姓名、年龄等）都可以称为关键字。
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * **/

#define keyType int

typedef struct {
    keyType key;//查找表中每个数据元素的值
    //如果需要，还可以添加其他属性
} ElemType;

typedef struct {
    ElemType *elem;//存放查找表中数据元素的数组
    int length;//记录查找表中数据的总数量
} SSTable;

//init——创建查找表
void Create(SSTable **st, int length) {
    (*st) = (SSTable *) malloc(sizeof(SSTable));
    (*st)->length = length;
    (*st)->elem = (ElemType *) malloc((length + 1) * sizeof(ElemType));
    printf("输入表中的数据元素：\n");
    //根据查找表中数据元素的总长度，在存储时，从数组下标为 1 的空间开始存储数据
    for (int i = 1; i <= length; i++) {
        scanf("%d", &((*st)->elem[i].key));
    }
}

//search——查找表查找的功能函数，其中key为关键字
int Search_seq(SSTable *st, keyType key) {
    st->elem[0].key = key;//将关键字作为一个数据元素存放到查找表的第一个位置，起监视哨的作用
    int i = st->length;
    //从查找表的最后一个数据元素依次遍历，一直遍历到数组下标为0
    while (st->elem[i].key != key) {
        i--;
    }
    //如果 i=0，说明查找失败；反之，返回的是含有关键字key的数据元素在查找表中的位置
    return i;
}

int main(int argc, const char *argv[]) {
    SSTable *st;
    Create(&st, 6);

    getchar();
    printf("请输入查找数据的关键字：\n");
    int key;
    scanf("%d", &key);
    int location = Search_seq(st, key);
    if (location == 0) {
        printf("查找失败");
    } else {
        printf("数据在查找表中的位置为：%d", location);
    }
    return 0;
}