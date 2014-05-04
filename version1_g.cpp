#include<iostream>
#include<stdlib.h> //FOR SYSTEM PAUSE
#include<string.h>
#include<list>
#include<vector>
using namespace std;
string prod[10];
list<char> listArr[30][10];		//CLOSURE SETS
list<char> temp;
int n[30];						//NO OF PRODUCTIOJ RULES PER CLOSURE SET
int anand = 1;					//NO OF CLOSURE SETS
vector<char> nonTerm;
vector<int> done; 
//FUNCTIONS
void nonTermList();
void print();
void gotoo();
void closure();
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
	closure();
    print();      
    system("pause");
}
//CREATING A SET OF TERMINALS
void nonTermList()
{
	cout<<endl<<"Non Terminal List:"<<endl;
     for(int i=0;i<n[0];i++)
     {
             list<char>::iterator it = listArr[0][i].begin();
             nonTerm.push_back(*it);
     }
     for(int i=0;i<nonTerm.size();i++)
     	cout<<nonTerm[i]<<" ";    
    cout<<endl;
}
void print_check(vector<int>& done)
{
	cout<<"Done Array:";
	for(int i=0;i<done.size();i++)
		cout<<done[i]<<" ";
}
void print_latest(int anand_old,int z_old,int anand,int z)
{
	for(int f=anand_old;f<=anand;f++)
	  {
	  	for(int g = z_old;g<z;z++)
	  	{
	  		 list<char>::iterator h;
           	for(h = listArr[f][g].begin(); h!=listArr[f][g].end();h++)
                 cout<<*h;
           cout<<endl;  
	  	}
	  }
}
int checkmoredots(int p_anand,int p_z)
{
	cout<<"   Value of anand:"<<p_anand<<"   Value of Z:"<<p_z;
	list<char>::iterator it = listArr[p_anand][p_z].begin();
	while(*it!='.') it++;
	it++;
	vector<int> occur;
	//CHECK IF THERE IS A NON TERMINAL
	for(int t=0;t<nonTerm.size();t++)  //TRAVERSING THE NON TERMINAl LIST  // HERE 10 IS THE MAX LENGTH OF NONTERM ARRAY
     {
        if(*it == nonTerm[t])		//IF A NON TERMINAL IS FOUND
        {
        	cout<<endl<<"Found match:"<<*it;
        	for(int p=0;p<nonTerm.size();p++)   //LOOKING FOR COPIES
        	{
      			if(nonTerm[p] == nonTerm[t])
				    occur.push_back(p);		
        	}
        	for(int p=0;p<occur.size();p++)
        	{
        		p_z++;
        		int pos = occur[p];
        		listArr[anand][p_z].assign(listArr[1][pos].begin(),listArr[1][pos].end());
        		//goto checkagain;
        		cout<<"   The size of occur vector:"<<occur.size();
        		cout<<"Value of z:"<<p_z;
        	}
        }                            
     }
     return p_z;
}
//CREATES A CLOSURE OF FURTHER SETS
void closure()
{
	int m=0;					//ELEMENT AFTER THE DOT
     for(int i=1;i<=anand;i++)    //ANAND KEEPS A COUNT OF THE NUMBER OF SETS
     {
     	int z = 0;     			  //NO OF INDEX POSITIONS IN THE NEW ANAND; 
     	  	done.clear();
     	  	cout<<"Value of n["<<i<<"]:"<<n[i];
             for(int j=0;j<n[i];j++)  //THIS WILL RUN FOR N[i] TIMES SINCE THAT IS THE NUMBER OF PRODUCTION RULES
             {
             	int check_done=1;
             	for(int y=0;y<done.size();y++)
             	{
             		if(done[y]==j)
             			check_done = 0;
             	}
             	if(check_done == 1)
             	{
             		list<char>::iterator it= listArr[i][j].begin();  //ITERATOR TO CHECK FOR DOT
	                while(*it!='.') it++;   //KEEP MOVING TILL YOU FIND A DOT(.)
					it++; 		
	                if(it==listArr[i][j].end())
	                	goto lastdot;                
					char temp = *it;
					cout<<endl<<"Value of before dot char:"<<temp; 
					done.push_back(j);
	                int repeat = 1;
	                if(repeat==1)  //ONLY IF REPEAT IS 1, CHECK IF THERE ARE ANY MORE REPETITIONS
	                {
	                	for(int k=0;k<n[i];k++)			//CHECK IF THERE ARE MORE PROD RULE WITH SAME ELEMENT AFTER THE DOT
		                {
		                	if(k!=j)
		                	{
		                		list<char>::iterator it= listArr[i][k].begin();
			                	while(*it!='.') it++;
			                	it++;
			                	if(*it == temp)			//IF MATCH OF CHARACTERS
			                	{
			                		done.push_back(k);
			                		repeat++;
			                	}         		
		                	}
		                }
	                }//END OF REPEAT FOR
	                anand = anand+1; //create a new goto
	                z=0; //EVERY TIME A NEW FLOOR IS CREATED SET APARTMENT = 0
	                for(int k=0;k<repeat;k++) //RUN ACCORDING TO NUMBER OF REPITITIONS
	            	{
	            		int pos = done[repeat];
	            		cout<<endl<<"Enter the dragon";
	            		listArr[anand][z].assign(listArr[i][pos].begin(),listArr[i][pos].end());  n[anand]++;
	            		list<char>::iterator it = listArr[anand][z].begin();
	            		while(*it!='.') it++;
	            		it++; char temp = *it;   it--;   *it=temp; it++ ; *it='.'; it++; //MOVING THE DOT AHEAD BY ONE POSITION
	            		if(it==listArr[i][j].end()){
	            			goto lastdott;
	            			cout<<endl<<"lastdott initiated";
	            			//DOES NOT WORK.CREATE A TERMINAL LIST AND IF END HAS REACHED THEN IT IS NOT IN TERMINAL AND NON TERMINAL LIST
						}
	                	              
						  
	            		z++;
						//CHECK IF THERE IS A NON TERMINAL
						for(int t=0;t<nonTerm.size();t++)  //TRAVERSING THE NON TERMINAl LIST
			             {
		                    if(*it == nonTerm[t])		//IF A NON TERMINAL IS FOUND
		                    {
		                    	cout<<endl<<"Found NonTerminal:"<<*it;
		                    	cout<<"    Value of anand:"<<anand;
		                    	cout<<"    Value of z:"<<z;
		                       listArr[anand][z].assign(listArr[1][t].begin(),listArr[1][t].end());  //COPY ELEMENTS FROM GOTO TO THE NEXT ANAND POSITION
		                		n[anand]++;
								//z=checkmoredots(anand,z);
		                		z++;
								//goto multiple_done;	
		                    }                            
			             }
			             //multiple_done:;
						 //z++;
						 lastdott:;	
                	}	
	            }
            }//J LOOP
            //LAST DOT DETECTED
            lastdot:;
        }//I LOOP
}//END FUNCTION

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
