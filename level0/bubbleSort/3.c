#include <bits/stdc++.h>
using namespace std;

int w(int a);

int main(){
    int a,b,c,f,n,t;
    cin>>a>>b;
    for(int i=a;i<=b;i++){
        f=0;//注意清零位置
        c=i;
        n=w(i);
        while(1){
            if(i==0){
                break;
            }
            t=i%10;
            f=f+pow(t,n);
            i=i/10;
        }
        if(f==c){
            cout<<c<<" ";
        }
    }

}

// 求位数
int w(int a){
    int s;
    while(1){
        if(a==0){
            break;
        }
        a=a/10;
        s++;
    }
    return s;
}