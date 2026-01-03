/*项目题目：跳表联系人管理系统
项目背景
你要实现一个简单的联系人管理系统，用跳表存储联系人信息。
每个联系人有 id（整型唯一编号）和 name（字符串）。
使用跳表保证联系人按 id 有序存储，并支持快速查找、插入和删除。
联系人按id升序排列
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define MAX_LEVEL 5

typedef struct {
    int id;
    char name[10];
} Person;

typedef struct node {
    Person data;
    struct node * next[5];
} Node;

typedef struct {
    int level;
    Node* head;
} SkipList;


SkipList initList();

void printList(Node * node);

void insert(SkipList list,int data);

int main() {
    SkipList list = initList();
    printList(list.head);
    insert(list,19);
    printList();
    printList();
    int n=find();
    assert(c==n%2);
    return 0;
}

SkipList initList() {
    SkipList list;
    list.level = 0;
    list.head = (Node*)malloc(sizeof(Node));
    assert(list.head != NULL);
    (list.head->data).id = 0;
    strcpy(list.head->data.name,  "aaa");
    list.head->next = NULL;

    return list;
}

void printList(Node * node) {
    while ( node ) {
        printf("id : %d     name : %s \n",node->data.id,node->data.name);
        node = node->next;
    }
    printf("\n");
}

void insert(SkipList list,int data) {

}