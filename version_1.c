#include<iostream>
#include<string>
#include<list>
using namespace std;
string prod[10];
list<char> listArr[30][10];
int n[30];
int n0;
int anand = 1;
void print();
void gotoo();
void termList();
void init();
int main(){
    init();
    //INPUTTING THE PROD RULES
    cout<<"Enter number of production rules:"; cin>>n[0]; n[1] = n[0] + 1;
    cout<<"Enter the production rules:\n"; 
    for(int i=0;i<n[0];i++)
    cin>>prod[i];
    
    //INSERTION INTO LIST
    for(int i=0;i<n[0];i++)
    {
            int m = prod[i].length();
            char prodChar[10];
            strcpy(prodChar, prod[i].c_str());
            listArr[0][i].assign(prodChar,prodChar+m); 
    }
    termList();
    gotoo();
    print();
    system("pause");
}
//CREATING A SET OF TERMINALS
void termList()
{
     
}
void closure()
{
     
 }
 
//PRODUCING I0 GOTO FUNCTION
void gotoo()
{
     list<char>:: iterator itS = listArr[0][0].begin();
     char S = (char)*itS;
     listArr[1][0].push_back('Z');  
     listArr[1][0].push_back('-');
     listArr[1][0].push_back('>');
     listArr[1][0].push_back('.');
     listArr[1][0].push_back(S);     
     for(int i=1;i<n[1];i++)
     {
         listArr[1][i].assign(listArr[0][i-1].begin(),listArr[0][i-1].end());
         list<char>::iterator it = listArr[1][i].begin();
         advance(it,3);
         listArr[1][i].insert(it,'.');
     }
}
void print()
{
     cout<<endl;
     for(int i=0;i<30;i++)
    {
             if(n[i]>0)
             {
                 for(int j=0;j<n[i];j++)
                 {
                       list<char>::iterator k;
                       for(k = listArr[i][j].begin(); k!=listArr[i][j].end();k++)
                             cout<<*k;
                       cout<<endl;  
                 } 
                 cout<<"---------------"<<endl;      
             }
         
    }
 }
 void init()
 {
      for(int i=0;i<30;i++)
              n[i] == -1;
  }
 
 //list<char>::iterator it = listArr[i].begin();
            /*for(int j=0;j<m;j++)
            {
                    listArr[i].insert(it,prod[i][j]);
                    cout<<prod[i][j]<<"\t"<<*it;
                    cout<<endl;
                    it++;
            } */
            
            //cout<<endl; 


