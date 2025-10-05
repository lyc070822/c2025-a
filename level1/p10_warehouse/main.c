#include <stdio.h>
#include <conio.h>
#include <windows.h>
typedef struct item{
    char name[20];
    int quantity;
} Item;
Item items[100];
int num=0;
void printList();
void input();
void output();

int main() {
    FILE *fp=fopen("warehouse.txt","r");
    while (fscanf(fp,"%s %d",items[num].name,&items[num].quantity) == 2) {//不是数组名别忘了&
        num++;
    }
    fclose(fp);
    while (1) {
        system("cls");
        printf("list:1\ninput:2\noutput:3\nescape:0\n");
        char n=getch();
        switch (n) {
            case '0':
                return 0;
                break;
            case '1':
                printList();
                break;
            case '2':
                input();
                break;
            case '3':
                output();
                break;
            default:
                printf("error");
                break;
        }
        FILE* fp1=fopen("warehouse.txt","w");
        for(int i=0;i<num;i++) {
            fprintf(fp1,"%s %d\n",items[i].name,items[i].quantity);
        }
        fclose(fp1);
    }
}
void printList() {
    system("cls");
    for (int i = 0; i < num; i++) {
        printf("name:%s  quantity:%d\n", items[i].name,items[i].quantity);
    }
    system("pause");
}
void input() {
    system("cls");
    printf("if new item press 1 \nif not new press 2");
    char m = getch();
    switch (m) {
        case '1':
            system("cls");
            printf("name:");
            scanf("%s",items[num].name);
            printf("quantity:");
            scanf("%d",&items[num].quantity);
            num++;
            break;
        case '2':
            system("cls");
            int temp,add;
            for (int i = 0; i < num; i++) {
                printf("if %s press %d\n",items[i].name,i+1);
            }
            scanf("%d",&temp);
            printf("add quantity:");
            scanf("%d",&add);
            for (int i = 0; i < num; i++) {
                if (i==temp-1) {
                    items[i].quantity += add;
                    break;
                }
            }

    }
}
void output() {
    system("cls");
    int temp,quantity;
    for (int i = 0; i < num; i++) {
        printf("if %s press %d\n",items[i].name,i+1);
    }
    scanf("%d",&temp);
    printf("output quantity:");
    scanf("%d",&quantity);
    for (int i = 0; i < num; i++) {
        if (i==temp-1) {
            if (quantity<=items[i].quantity) {
                items[i].quantity -= quantity;
                break;
            }
            else {
                printf("%s only %d",items[i].name,items[i].quantity);
                system("pause");
                break;
            }
        }
    }

}