#include<iostream>
#include<vector>
#include<set>
using namespace std;
int main(){
vector<int>p(10001,1);
p[0]=p[1]=0;
for(int i=2;i*i<=10000;i++)if(p[i])for(int j=i*i;j<=10000;j+=i)p[j]=0;
int n,d,u;
cin>>n;
for(int i=0;i<n;i++){
cin>>d>>u;
cout<<d<<" "<<u<<" ";
if(!p[u]){cout<<"NO\n";continue;}
int h;
set<int>v;
while(v.find(u)==v.end()){
v.insert(u);
int e=0;
while(u!=0){e+=u%10*(u%10);u/=10;}
if(e==1)h=1;u=e;}
if(h)cout<<"YES\n";
else cout<<"NO\n";}
}
