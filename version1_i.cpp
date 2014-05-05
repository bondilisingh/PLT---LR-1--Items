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
vector<char> Term;
vector<int> done;
vector<int> repeat;  
int repeatState[30];
//FUNCTIONS
void nonTermList();
void print();
void gotoo();
void closure();
void termList();
void init();
void multiplicity(int);
int validate();
void print_latest(int,int);
int main(){
    init();
    
    //INPUTTING THE PROD RULES
    /*
    cout<<"Enter number of production rules:"; cin>>n[0]; 
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
    */
    n[1] = n[0] + 1;
    print();
    if(validate())
    {
        nonTermList(); termList();//CREATING A LIST OF AL LEFT HAND NON TERMINALS
        gotoo();       //CREATING A GOTO WITH THE DOTS
    	closure();
    }
    print();      
    system("pause");
}
int validate()
{
     int count = n[0];
     for(int i=0;i<count;i++)
     {
         list<char>::iterator it = listArr[0][i].begin();
         if((int)*it>=65  && (int)*it<=92)
         {
             it++;
             if(*it!='-')
             {
                cout<<"There can be only one non-Terminal in LHS";
                return 0;
             }
         }
         else
         {
             cout<<"The LHS characters should be in capital";
             return 0;
         }    
     }
     return 1;
     
}
//CREATING A SET OF NON  TERMINALS
void nonTermList()
{
	cout<<endl<<"Non Terminal List:";
     for(int i=0;i<n[0];i++)
     {
             list<char>::iterator it = listArr[0][i].begin();
             nonTerm.push_back(*it);
     }
     for(int i=0;i<nonTerm.size();i++)
     	cout<<nonTerm[i]<<" ";    
    cout<<endl;
}
void termList()
{
	cout<<endl<<"Terminal List:";
	char temp;
	int count,count2;
	for(int i=0;i<n[0];i++)
     {
             list<char>::iterator it = listArr[0][i].begin();
             it++; it++; it++;
             
             for(; it!=listArr[0][i].end();it++)
             {
             	count = 0;    
	            for(int j=0;j<nonTerm.size();j++)
	             {
	             	if((*it == nonTerm[j]))
	             	{
	             		count = 1;			 //IF NON TERMINAL FOUND SET AS COUNT=1
	             	}
	             }
	             count2=0;
	             if(count == 0)				//IF NOT NON TERMINAL THEN COUNT WILL STILL BE 0
	             {
	             	for(int k=0;k<Term.size();k++)		//TO CHECK FOR MULTIPLICITY
	             	{
	             		if(*it == Term[k])
	             			count2 = 1;
	             	}
	             	if(count2 == 0)
	             		Term.push_back(*it);
	             }	
             }
     }
     for(int i=0;i<Term.size();i++)
     	cout<<Term[i]<<" ";
    cout<<endl;
}
void print_check(vector<int>& done)
{
	cout<<"Done Array:";
	for(int i=0;i<done.size();i++)
		cout<<done[i]<<" ";
}
void print_latest(int p_anand,int p_z)
{
     cout<<endl<<"-->States=anand:"<<p_anand;
	list<char>::iterator it;
	for(int i=0;i<p_z;i++)
	{
	  	for(it = listArr[p_anand][i].begin();it!=listArr[p_anand][i].end();it++)
	  	{
           cout<<*it;  
	  	}
	  	cout<<endl;
	}
}
int checkForEnd(int p_i,int p_j,int x)
{
	list<char>::iterator it = listArr[p_i][p_j].begin();
	while(*it!='.') it++;
	it++;
	if(x==1)
	cout<<endl<<"->"<<x<<":Value of *it:"<<*it;
	if(x==2)
	cout<<endl<<"----->"<<x<<":Value of *it:"<<*it;
	int check = 0;
	for(int m=0;m<nonTerm.size();m++)
	{
		if(*it == nonTerm[m])
			check = -1;
	}
	for(int m=0;m<Term.size();m++)
	{
		if(*it == Term[m])
			check = -1;
	}
	if(check == -1)
		return 0;
	else 
		return 1;
}

void multiplicity(int p_anand)
{
     for(int i=0;i<p_anand;i++)
     {
          //FIRST DO A COUNT CHECK
          for(int j=0;j<p_anand;j++)
          {
             if(i!=j)
             {
                if(n[i]==n[j])
                {
                     int count=0;
                     int tempcount = n[i];
                     for(int f=0;f<tempcount;f++)
                     {
                             for(int g=0;g<tempcount;g++)
                             {
                                 if(listArr[i][f] == listArr[j][g])
                                    count++;          
                             }
                     }
                     if(count==tempcount)
                     {
                        //SET P_J AS NULL
                        for(int h=0;h<tempcount;h++)
                                listArr[j][h].clear();
                     }          
                }    
                //removeMultiple(i,j);
             }
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
     	  	done.clear();
     	  	cout<<endl<<"Value of n["<<i<<"]:"<<n[i]<<endl;
             for(int j=0;j<n[i];j++)  //THIS WILL RUN FOR N[i] TIMES SINCE THAT IS THE NUMBER OF PRODUCTION RULES
             {
                repeat.clear();
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
	                if(checkForEnd(i,j,1))   //TO CHECK IF DOT HAS REACHED THE END
	                	{ cout<<endl<<"->Going To Last Dot"; goto lastdot;}   
                     it++;                  
					char temp = *it;
					cout<<endl<<"-->Value of before dot char:"<<temp; 
					done.push_back(j); repeat.push_back(j);
	                if(repeat.size()==1)  //ONLY IF REPEAT IS 1, CHECK IF THERE ARE ANY MORE REPETITIONS
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
			                		repeat.push_back(k);
			                	}         		
		                	}
		                }
	                }//END OF REPEAT FOR
	                anand = anand+1; //create a new goto
	                z=0; //EVERY TIME A NEW FLOOR IS CREATED SET APARTMENT = 0
	                for(int k=0;k<repeat.size();k++) //RUN ACCORDING TO NUMBER OF REPITITIONS
	            	{
                        int pos = repeat[k];
	            		cout<<endl<<"--->Enter the anand:"<<anand;
	            		listArr[anand][z].assign(listArr[i][pos].begin(),listArr[i][pos].end());  n[anand]++;
	            		print_latest(anand,z);
	            		list<char>::iterator it = listArr[anand][z].begin();
	            		while(*it!='.') it++;
	            		it++; char temp = *it;   it--;   *it=temp; it++ ; *it='.';  //MOVING THE DOT AHEAD BY ONE POSITION
	            		if(checkForEnd(anand,z,2))   //TO CHECK IF DOT HAS REACHED THE END
	                	{ cout<<endl<<"---->Going To Last Dott"; goto lastdott;}
					    it++;
	            		z++;
						//CHECK IF THERE IS A NON TERMINAL
						for(int t=0;t<nonTerm.size();t++)  //TRAVERSING THE NON TERMINAl LIST
			             {
		                    if(*it == nonTerm[t])		//IF A NON TERMINAL IS FOUND
		                    {
		                    	cout<<endl<<"Found NonTerminal:"<<*it;
		                    	cout<<"    Value of anand:"<<anand;
		                    	cout<<"    Value of z:"<<z;
		                    	cout<<"    VAlue of t:"<<t+1;
		                       listArr[anand][z].assign(listArr[1][t+1].begin(),listArr[1][t+1].end());  //COPY ELEMENTS FROM GOTO TO THE NEXT ANAND POSITION
		                		n[anand]++; 
		                		z++;	
		                    }                            
			             }
			             //multiple_done:;
						 //z++;
						 lastdott:;	
						 multiplicity(anand);
                	}	
	            }
            }//J LOOP
            //LAST DOT DETECTED
            lastdot:;
            if(i==9)
               goto imdone;
            print();
        }//I LOOP
        imdone:;
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
      /*listArr[0][0].push_back('A'); listArr[0][0].push_back('-'); listArr[0][0].push_back('>');listArr[0][0].push_back('B'); listArr[0][0].push_back('C');
      listArr[0][1].push_back('A'); listArr[0][1].push_back('-'); listArr[0][1].push_back('>');listArr[0][1].push_back('D');
      listArr[0][2].push_back('C'); listArr[0][2].push_back('-'); listArr[0][2].push_back('>');listArr[0][2].push_back('b'); listArr[0][2].push_back('C');
      listArr[0][3].push_back('C'); listArr[0][3].push_back('-'); listArr[0][3].push_back('>');listArr[0][3].push_back('c');
      listArr[0][4].push_back('B'); listArr[0][4].push_back('-'); listArr[0][4].push_back('>');listArr[0][4].push_back('b');
      listArr[0][5].push_back('D'); listArr[0][5].push_back('-'); listArr[0][5].push_back('>');listArr[0][5].push_back('d'); 
      n[0] = 6;*/
        
      listArr[0][0].push_back('E'); listArr[0][0].push_back('-'); listArr[0][0].push_back('>');listArr[0][0].push_back('T'); 
      listArr[0][1].push_back('E'); listArr[0][1].push_back('-'); listArr[0][1].push_back('>');listArr[0][1].push_back('E');listArr[0][1].push_back('+');listArr[0][1].push_back('T');
      listArr[0][2].push_back('T'); listArr[0][2].push_back('-'); listArr[0][2].push_back('>');listArr[0][2].push_back('F'); 
      listArr[0][3].push_back('T'); listArr[0][3].push_back('-'); listArr[0][3].push_back('>');listArr[0][3].push_back('T');listArr[0][3].push_back('*');listArr[0][3].push_back('F');
      listArr[0][4].push_back('F'); listArr[0][4].push_back('-'); listArr[0][4].push_back('>');listArr[0][4].push_back('i');
      listArr[0][5].push_back('F'); listArr[0][5].push_back('-'); listArr[0][5].push_back('>');listArr[0][5].push_back('*');listArr[0][5].push_back('E');listArr[0][5].push_back('*'); 
      n[0] = 6;
 }
