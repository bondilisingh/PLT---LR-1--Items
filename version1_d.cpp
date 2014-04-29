#include<iostream>
#include<string>
#include<list>
using namespace std;
string prod[10];
list<char> listArr[30][10];		//CLOSURE SETS
int n[30];						//NO OF PRODUCTIOJ RULES PER CLOSURE SET
int anand = 1;					//NO OF CLOSURE SETS
char nonTerm[10];

//FUNCTIONS
void nonTermList();
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
    nonTermList(); //CREATING A LIST OF AL LEFT HAND NON TERMINALS
    gotoo();       //CREATING A GOTO WITH THE DOTS
    print();       // PRINTS ALL CLOSURE SETS
    system("pause");
}
//CREATING A SET OF TERMINALS
void nonTermList()
{
     for(int i=0;i<n[0];i++)
     {
             list<char>::iterator it = listArr[0][i].begin();
             nonTerm[i] = *it;
     }
     cout<<"\nNon-Terminals List:"<<nonTerm<<endl;
        
        
}
int checkmoredots(p_anand,p_z,p_i,p_j)
{
	list<char>::iterator it = listArr[p_anand][p_z].begin();
	while(*it!='.') it++;
	//CHECK IF THERE IS A NON TERMINAL
	for(int t=0;t<nonTerm.length();t++)  //TRAVERSING THE NON TERMINAl LIST
     {
        if(*it == nonTerm[t])		//IF A NON TERMINAL IS FOUND
        {
           listArr[p_anand][p_z].assign(listArr[1][t].begin(),listArr[1][t].end())  //COPY ELEMENTS FROM GOTO TO THE NEXT ANAND POSITION
    		p_z=checkmoredots(pp_anand,pp_z,pp_i,pp_j);	
        }                            
     }
}
//CREATES A CLOSURE OF FURTHER SETS
void closure()
{
	int m=0;					//ELEMENT AFTER THE DOT
     for(int i=1;i<=anand;i++)    //ANAND KEEPS A COUNT OF THE NUMBER OF SETS
     {
     	int z = 0;     			  //NO OF INDEX POSITIONS IN THE NEW ANAND; 
     	int done[10]; int d=0;
     	int pos_dotAfter[10];
     	
             for(j=0;j<n[i];j++)  //THIS WILL RUN FOR N[i] TIMES SINCE THAT IS THE NUMBER OF PRODUCTION RULES
             {
             	int check_done=1;
             	for(int y=0;y<d;y++)
             	{
             		if(done[y]==j)
             			check_done = 0;
             	}
             	if(check_done == 1)
             	{
             		list<char>::iterator it= listArr[i][j].begin();
	                while(*it!='.') it++;		//KEEP MOVING TILL YOU FIND A DOT(.)
	                it++;                 
					char temp = *it; 
					done[d++] = j;
	                int repeat = 1;
	                if(repeat==1)  //ONLY IF REPEAT IS 1, CHECK IF THERE ARE ANY MORE REPETITIONS
	                {
	                	for(k=0;k<n[i];k++)			//CHECK IF THERE ARE MORE PROD RULE WITH SAME ELEMENT AFTER THE DOT
		                {
		                	list<char>::iterator it= listArr[i][k].begin();
		                	while(*it!='.') it++;
		                	it++;
		                	if(*it == temp)			//IF MATCH OF CHARACTERS
		                	{
		                		done[d++] = k;
		                		repeat++;
		                	}         			
		                }
	                }
					
	                anand = anand+1; //create a new goto
	                for(k=0;k<repeat;k++) //RUN ACCORDING TO NUMBER OF REPITITIONS
	            	{
	            		listArr[anand][z].assign(listArr[i][j].begin(),listArr[i][j].end()); n[z]++ //increment the number of prod rules by 1
	            		list<char>::iterator it = listArr[anand][z].begin();
	            		while(*it!='.') it++;
	            		it++; char temp = *it;   it--;   *it=temp; it++ ; *it='.'; it++; //MOVING THE DOT AHEAD BY ONE POSITION
	            		z++;
						//CHECK IF THERE IS A NON TERMINAL
						for(int t=0;t<nonTerm.length();t++)  //TRAVERSING THE NON TERMINAl LIST
			             {
		                    if(*it == nonTerm[t])		//IF A NON TERMINAL IS FOUND
		                    {
		                       listArr[anand][z].assign(listArr[1][t].begin(),listArr[1][t].end())  //COPY ELEMENTS FROM GOTO TO THE NEXT ANAND POSITION
		                		z=checkmoredots(anand,z,i,j);	
		                    }                            
			             }	
                	}	
	            }
            }
                
            }
        }
    }

//PRODUCING I0 GOTO FUNCTION.THIS IS THE STARTING POINT
void gotoo()
{
     list<char>:: iterator itS = listArr[0][0].begin();
     char S = (char)*itS;
     listArr[1][0].push_back('Z');  
     listArr[1][0].push_back('-');
     listArr[1][0].push_back('>');
     listArr[1][0].push_back('.');
     listArr[1][0].push_back(S);     
     for(int i=1;i<n[1];i++) //HERE N[1] IS THE NUMBER OF CLOSURE SETS
     {
         listArr[1][i].assign(listArr[0][i-1].begin(),listArr[0][i-1].end());    //COPYING PROD RULES FROM SET 0 TO SET 1
         list<char>::iterator it = listArr[1][i].begin();
         advance(it,3);
         listArr[1][i].insert(it,'.');
     }
}

//PRINTS ALL CLOSURE SETS ALONG WITH GOTO
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
 //CRAP
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
