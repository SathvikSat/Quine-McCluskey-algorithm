#include <bits/stdc++.h>
using namespace std;


class boolean
{
private:

int inputs;
string dontcares;
//things are treated in string format everywhere
public:

  //function to get the boolean term letters
  vector<string> variables()
  {
     vector<string> actualvar;
     string letters[]={"a","b","c","d", "e"};
     for(int i=0;i<inputs;i++)
      actualvar.push_back(letters[i]);
      return actualvar;
    }

   char *removeDuplicate(char str[], int n)
   {int index = 0;

   // Traverse through all characters
   for (int i=0; i<n; i++) {

     // Check if str[i] is present before it
     int j;
     for (j=0; j<i; j++)
        if (str[i] == str[j])
           break;
     // If not present, then add it to result
     if (j == i)
        str[index++] = str[i];
   }

   return str;
}
boolean(int d)
{
   inputs=d;
   dontcares.append(d,'X');
   cout<<dontcares<<" ";
}
string decToBin(const int &n) //passByReference
{
    //cout<<"&n = "<<&n<<" ";
   if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return decToBin(n / 2) + "0";
   else
       return decToBin(n / 2) + "1";
}
//function to pad zeros to the binary equivalent of digits.
//Eg: If there are 4 variables, 2, that is 10 in binary is represented as 0010
string padding(string Inbin)
{
   int max=inputs-Inbin.length();
   for(int i=0; i<max; i++)
      Inbin="0"+Inbin;
   return Inbin;
}
//function to check if two terms differ by just one bit
bool differby1(const string &s1, const string &s2)
{
    // Find lengths of given strings
    int m = s1.length(), n = s2.length();

    // If difference between lengths is more than
    // 1, then strings can't be at one distance
    if (abs(m - n) > 1)
        return false;

    int count = 0; // Count of edits

    int i = 0, j = 0;
    while (i < m && j < n)
    {
        // If current characters don't match
        if (s1[i] != s2[j])
        {
            if (count == 1)
                return false;
                // If length of one string is more, then only possible edit is to remove a char
                if (m > n)
                    i++;
                else if (m< n)
                    j++;
                else //Iflengths of both strings is same
                {
                    i++;
                    j++;
                }
        // Increment count of edits
                count++;
            }
            else // If current characters match
            {
                i++;
                j++;
            }
        }
        // If last character is extra in any string
        if (i < m || j < n)
            count++;
        return count == 1;
    }
    //function to replace complement terms with don't cares
    // Eg: 0110 and 0111 becomes 011-
    string replace_complements(string a,string b)
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
    //function to reduce minterms
    vector<string> reduce(vector<string> minterms)
    {
   for (int i=0; i<minterms.size(); i++)
          { cout << minterms[i]<<endl;
           cout <<endl;}

          vector<string> newminterms;

          int max=minterms.size();
          int* checked = new int[max];
          for( int i=0;i<max;i++)
          {
              for(int j=i;j<max;j++)
              {
                   //If a grey code pair is found, replace the differing bits with don't cares.
                   if(differby1(minterms[i],minterms[j]))
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
       string temp="";
       vector<string> vars=this->variables();

       for(int i=0;i<a.length();i++)
       {
         if(a[i]!='X')
         {
            if(a[i]=='0')
             temp=temp+vars[i]+"\'";
            else
             temp=temp+vars[i];
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
  };
  int main ()
  {
    int num;
    cout<<"Enter the number of variables:"<<endl;
    cin>>num;
    boolean q(num);
    string deci="";
    cout<<"Enter the minterms in decimal format:" <<endl;
    cin>>deci;
     int  n= sizeof(deci);
    string removeDuplicate(deci,n);
    stack<char> s;
    for(int i = deci.size(); i> 0; i--)
    {
       s.push(deci[i]);
    }
    string temp = " ";
    while(!s.empty()){
       cout<<s.top()<<endl;
      temp.push_back(s.top());
       s.pop();
    }

    //splitting the input
    vector<string> minterms;
    istringstream k(temp);
    string m;
    while (getline(k, m, ','))
    {
       int t=atoi(m.data()); //conversion to int type
       minterms.push_back(q.padding(q.decToBin(t))); //decimal to binary conversion and loaded into array of minterms
    }
    sort(minterms.begin(),minterms.end());

    do
    {
       minterms=q.reduce(minterms);
       sort(minterms.begin(),minterms.end());
    }while(!q.VectorsEqual(minterms,q.reduce(minterms)));
    int i;
    cout << "Reduced boolean Equation as SUM OF PRODUCTS is: " << endl;
    for (i=0;i<minterms.size()-1; i++)
        cout <<q.getValue(minterms[i])<<"+";
    cout<<q.getValue(minterms[i])<<endl;
}
