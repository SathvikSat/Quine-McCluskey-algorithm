#include <bits/stdc++.h>
using namespace std;
int inputs;
string dontcares;





//function to get the boolean term letters
 vector<string> variables()
{
   vector<string> actualvar;
   string letters[]={"a","b","c","d", "e"};
   for(int i=0;i<inputs;i++){
    actualvar.push_back(letters[i]);
   }
   
  //for( int i = 0; i<inputs; i++){
    //  cout<<actualvar[i]<<" ";
   //}
   return actualvar;
}




typedef struct stack{
   char data[100];
   int top;

int empty(stack *p){
   return(p ->top == -1);
}
int top(stack *p){
   return (p-> data) [p->top];
}stack;

void push(stack *p, char x ){
   p-> data[++(p->top)] = x;
}

void pop(stack *p){
   if (!empty(p)){
      (p -> top) = (p->top) -1;
   }
}

}



string decToBin(const  int &n) //passByReference
{
    //cout<<"n = "<<n<<" ";
  if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}

string padding( string Inbin)
{
   // string t;
    //t = *Inbin;
   int max=inputs-Inbin.length();
   for(int i=0; i<max; i++)
      Inbin="0"+Inbin;
   return Inbin;
}


bool isGreyCode( string &a,string &b)
{
   int count=0;
   for(int i=0;i<a.length();i++)
   {
       if(a[i]!=b[i])
        count++;
   }
   return (count==1); // only if count is eqqual to 1.
}

inline string replace_complements(string a,string b) //expanded in terms of binary code, if called ten times size may inrease ten times
{
   string temp="";
   for(int i=0;i<a.length();i++)
   if(a[i]!=b[i])
       temp=temp+"X";
   else
       temp=temp+a[i];

   return temp;
}

//function to check if string b exists in vector a
bool in_vector(vector<string> a,string b)
{
   for(int i=0;i<a.size();i++)
     if(a[i].compare(b)==0)
      return true;
    return false;
}


vector<string> reduce(vector<string> minterms)
{
for (int i=0; i<minterms.size(); i++)
       cout << minterms[i]<<endl;
       cout <<endl;

      vector<string> newminterms;                           

      int max=minterms.size();
      int* checked = new int[max];
      for( int i=0;i<max;i++)
      {
          for(int j=i;j<max;j++)
          {
               //If a grey code pair is found, replace the differing bits with don't cares.
               if(isGreyCode(minterms[i],minterms[j]))
               {
                  checked[i]=1;
                  checked[j]=1;
                  if(!in_vector(newminterms,replace_complements(minterms[i],minterms[j])))
                     newminterms.push_back(replace_complements(minterms[i],minterms[j]));
               }
          }
      }

      //appending all reduced terms to a new vector
      for(int i=0;i<max;i++)
      {
          //cout<<checked[i]<<endl;
          if(checked[i]!=1 && ! in_vector(newminterms,minterms[i]))
           newminterms.push_back(minterms[i]);
      }

       delete[] checked;
   
       return newminterms;
}


//Converting the boolean minterm into the variables
// Eg: 011- becomes a'bc
string getValue(string a)
{
   string use = "abcd";
   string temp="";
   //vector<string> vars=use;
   if(a==dontcares) 
     return "1";

   for(int i=0;i<a.length();i++)
   {
     if(a[i]!='X')
     {
        if(a[i]=='0')
         temp=temp+use[i]+"\'";
        else
         temp=temp+use[i];
     }
   }
   return temp;
}

//function to check if 2 vectors are equal
bool VectorsEqual(vector<string> a,vector<string> b)
{
   if(a.size()!=b.size())
      return false;
   else{
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i])
        return false;
    }
    return true;
}}



int main ()
{
  //  int d;

   
   
      uint num;
      cout<<"Enter the number of variables:"<<endl;
      cin>>num;
     
      inputs=num;
   dontcares.append(num,'X');
   cout<<dontcares<<" "; 

      string deci="";
      cout<<"Enter the minterms in decimal format:" <<endl;
      cin>>deci;
      
      stack<char> s;
      //s.top() = -1;
      //int  len = sizeof(deci);
      //cout<<len<<endl;
      for(int i = deci.size(); i> 0; i--){
        //  cout<<deci;
         s.push(deci[i]);
      }
      string temp = " ";
      while(!s.empty()){
         cout<<s.top()<<endl;
        // temp = temp + s.top();
        temp.push_back(s.top());
        //cout<<temp<<" ";
         s.pop();
      }
      //string temp = " ";
      
         //splitting the input
      vector<string> minterms;
      istringstream k(deci);
      string m;
      while (getline(k, m, ','))
      {
          //cout << s << endl;
         int t=atoi(m.data()); //conversion to int type
      //   cout<<"&t = "<< &t<<" ";
         minterms.push_back(padding(decToBin(t))); //decimal to binary conversion and loaded into array of minterms
      }


      for(int j =0; j<minterms.size(); j++){
          cout<<minterms[j]<<" ";
      }

      

      sort(minterms.begin(),minterms.end());

      do
      {
         minterms=reduce(minterms);
         sort(minterms.begin(),minterms.end());
      }while(!VectorsEqual(minterms,reduce(minterms)));


      int i;
      
      cout << "Reduced boolean Equation as SUM OF PRODUCTS is: " << endl;
      for (i=0;i<minterms.size()-1; i++)

          cout <<getValue(minterms[i])<<"+";
      cout<<getValue(minterms[i])<<endl;
       
   }
   
