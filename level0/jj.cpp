#include <bits/stdc++.h>
using namespace std;

int w(int a);

int main(){
    int a,b,c,f,n,t;
    cin>>a>>b;
    for(int i=a;i<=b;i++){
        f=0;//注意清零位置
        c = i;
        n=w(c);
        while(c > 0){
            t=c%10;
            f=f+round(pow(t,n));
            c=int(c/10);
        }
        if(f==i){
            cout<<i<<" ";
        }
    }
    return 0;
}

// 求位数
int w(int a){
    int s = 0;
    while(a > 0){
        a=a/10;
        s++;
    }
    return s;
}