#include<iostream>
int64_t m,n,r,i,b,c,a;
uint z(uint n){r=0,i=1;
while(1){b=n/i;c=n%i;a=b/10;b%=10;
if(!a)return r;
if(!b)r+=(a-1)*i+c+1;
else r+=a*i;i*=10;}}
int main(){while(1){std::cin>>m>>n;if(m==-1)break;std::cout<<(n?z(n):1)-(m?z(m-1):-1)<<"\n";}}
