#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node* next;
} Node;
void insert(Node** head, int val) {
    Node* p=(Node*)malloc(sizeof(Node));
    p->data=val;
    p->next=*head;
    *head=p;

}

void append(Node* head,int val) {
    Node* p=(Node*)malloc(sizeof(Node));
    p->data=val;
    p->next=NULL;
    while (head->next!=NULL) {
        head=head->next;
    }
    head->next=p;
}
void printList(Node* head) {
    while (head!=NULL) {
        printf("%d ",head->data);
        head=head->next;
    }
    printf("\n");
}
void reverseList(Node** head) {
    Node* pre=NULL;
    Node* cur=*head;
    while (cur!=NULL) {
        Node*next=cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    *head=pre;
}
int findFirstFive(Node* head) {
    int sNumber=1;
    while (head->data!=5) {
        sNumber++;
        head=head->next;
    }
    return sNumber;
}
int findSecondFive(Node* head) {
    int sNumber=1;
    int n=0;
    while (1) {
        if (head->data==5) {
            n++;
        }
        sNumber++;
        head=head->next;
        if (n==2 ) {
            return sNumber;
        }
        if (head==NULL) {
            return -1;
        }
    }
}
int main() {
    Node* head=NULL;
    head=(Node*)malloc(sizeof(Node));
    head->data=3;
    head->next=NULL;
    insert(&head,3);
    insert(&head,5);
    append(head,5);
    append(head,6);
    printList(head);
    reverseList(&head);
    printList(head);
    printf("%d %d",findFirstFive(head),findSecondFive(head));
}

