#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;


class Trie
{
    public:
        Trie* Children[10];
        int count;
        // count indicates the total possible node emergining from it
        Trie()
        {
            count=0;
            for(int i=0;i<10;i++)
            {
                Children[i]=NULL;
            }
        }
        bool insert(Trie*,string ph_no);
};



int iscorrectchar(string s)
{
    if(s=="M"||s=="F")
    {
        return 1;
    }
    return 0;
}
int check(string s)
{
    for(int i=0;i<s.length();i++)
    {
        if(s.at(i)<'0'||s.at(i)>'9')
        {
            return 0;
        }
    }
    return 1;
}
int validno(string n,char ch)
{
    if(ch=='u'&&n.length()==12&&check(n))
    {
        return 1;
    }
    else if(ch=='p'&&n.length()==10&&((n.at(0)=='9')||(n.at(0)=='8')||(n.at(0)=='7')||(n.at(0)=='6'))&&check(n))
    {
        return 1;
    }
    return 0;
}

bool Trie::insert(Trie* root,string s)
{
    Trie* temp=root;
    if(temp->count==0)
    {
        return false;
    }
    bool fl=true;
    for(int i=0;i<10;i++)
    {
        if(temp->Children[s[i]-'0']!=NULL)
        {
            temp=temp->Children[s[i]-'0'];
        }
        else 
        {
            Trie *temp1=new Trie();
            temp1->count=0;
            temp->Children[s[i]-'0']=temp1;
            temp=temp->Children[s[i]-'0'];
            fl=false;
        }
    }
    if(!fl)
    {
        Trie* temp1=root;
        for(int i=0;i<10;i++)
        {
            temp1=temp1->Children[s[i]-'0'];
            temp1->count++;
        }
        temp1->count=-1;
        return true;
    }
    return false;
}



void addrecord(Trie* root)
{
    string Ph_no;
    string info[5];
    string z;
    
    getline(cin,z);
    cout<<"ENTER YOUR NAME \n";
    getline(cin,info[0]);                        //info[0]=name
    cout<<"Enter Your Father's Name  \n";
    getline(cin,info[1]);                        //info[1]=father name
    cout<<"Enter Your Mother's Name   \n";
    getline(cin,info[2]);                        //info[2]=mother name
    cout<<"Enter Your Gender:(M/F)              \n";
    getline(cin,info[3]);   



    //CHECKING IF GENDER IS CORRECT OR NOT

    while((!iscorrectchar(info[3]))){
        cout<<"Enter valid Gender as instructed(M/F)    \n";
        getline(cin,info[3]);
    }
    cout<<"Enter UID NO(12-digit No:)   \n";
    getline(cin,info[4]);                        //info[4]=UID
    
    //CHECKING IF UID IS CORRECT OR NOT

    while(!validno(info[4],'u')){
        cout<<"Enter valid UID NO:      \n";
        getline(cin,info[4]);
    }

    cout<<"Enter phone number            \n";
    getline(cin,Ph_no);                             //all item[5]=PHN NO;

    //CHECKING IF VALID PHONE NUMBER OR NOT;

    while(!validno(Ph_no,'p'))
    {
        cout<<"Enter valid phone number     \n";
        getline(cin,Ph_no);
    }
    // passing allitems and object to insert function


    // if we are able to insert phno in trie then create a file of name phno.txt and 
    // store info in it.
   if(root->insert(root,Ph_no))
   {
        ofstream myfile;
        string dummy=Ph_no;
        dummy+=".txt";
        myfile.open (dummy);
        for(string i:info)
        {
            string z=i;
            i+="\n";
            myfile<<i;
        }
        myfile.close();
      //  cout<<"CAME\n";
        return;
   }
   else 
   {
        cout<<"** Number Already Exists ** \n";
   }
}
vector<string>getdetails(string& num)
{
    // fetch value from file
    string line;
    string dummy=num;
    dummy+=".txt";
    ifstream myfile(dummy);
    vector<string>details;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            details.push_back(line);
        }
        myfile.close();
    }
    else 
    {
        cout<<"CANNOT OPEN FILE";
    }
    return details;
}



void updatedetails(vector<string>&details,string& num)
{
    cout<<details[0]<<" ARE \n";
    ofstream myfile;
    string dummy=num;
    dummy+=".txt";
    myfile.open(dummy);
    for(string i:details)
    {
        string z=i;
        z+="\n";
        myfile<<z;
    }
    myfile.close();
}


void iterateTrie(Trie* root,string& num)
{
    if(root==NULL)
    {
        return;
    }
    if(root->count==0)
    {
        return;
    }
    if(num.length()==10)
    {
        vector<string>s=getdetails(num);
        cout<<"NAME: "<<s[0]<<"\n";
        cout<<"FATHER's NAME: "<<s[1]<<"\n";
        cout<<"MOTHER's NAME: "<<s[2]<<"\n";
        cout<<"GENDER: "<<s[3]<<"\n";
        cout<<"UID: "<<s[4]<<"\n";

        cout<<"\n\n --Record--  \n\n";
        return;
    }
    for(int i=0;i<10;i++)
    {
        num.push_back(i+'0');
        iterateTrie(root->Children[i],num);
        num.pop_back();
    }
}

void listrecord(Trie *root){
    Trie* temp=root;
    string num="";
  //  cout<<"CAME\n";
    iterateTrie(temp,num);
}

void modifyrecord(Trie *root){
    //modifying the value in this we need to also check if the user inout is valid or not
    // in this we need to try to optimise the way we take input for which thing to be modified
    // we also need an option of changing phn no
    // we can also check if previous and present are same
    // modify record done
    // in modify check if list is empty TRIE IS empty
    cout<<" AS A PART OF SECURITY CONCERNS WE NEED TO VEREIFY WHETHER ITS YOU OR SOMEBODY ELSE\n";
    cout<<" SO PLEASE ENTER YOU MOBILE NUMBER\n";
    string z;
    getline(cin,z);
    string number;
    getline(cin,number);
    cout<<"ENTER NAME\n";
    string name;
     getline(cin,name);
    string uid;
    cout<<"ENTER UID\n";
     getline(cin,uid);
    int i;
    if(number.length()!=10)
    {
        cout<<"  Invlaid \n";
        return;
    }
    Trie* temp=root;
    for( i=0;i<10;i++)
    {
       if(root->Children[number.at(i)-'0']==NULL)
       {
           cout<<" Invalid Number\n";
           return;
       }
       root=root->Children[number.at(i)-'0'];
    }
    root=temp;
    vector<string>s;
    s=getdetails(number);
    root=temp;
    if(uid.length()!=s[4].length())
    {
        cout<<" Invalid \n";
        return;
    }
    for(i=0;i<uid.length();i++)
    {
        if(s[4][i]!=uid[i])
        {
            cout<<" Invalid UID\n";
            return;
        }
    }
    if(s[0].length()!=name.length())
    {
        cout<<" Invalid \n";
        return;
    }
    for(int i=0;i<name.length();i++)
    {
        if(s[0][i]!=name[i])
        {
            cout<<" Invalid \n";
            return;
        }
    }
    cout<<"**## PLEASE WAIT VALIDATING  ##**\n";
    //usleep(10);
    cout<<"ENTER DETAILS ARE CORRECT\n";
    cout<<"You are eligible to edit only your UID Father's Mother's and you name\n";
    while(1){
        int changer;
        cout<<"Enter 1. for changing name\n2. for changing father's name\n3. for changing mother's name\n4. for editng UID\nany other key to if modification is done\n";
        cin>>changer;
        switch(changer){
            case 1:
            {
            cout<<"Enter Correct name\n";
            string z;
             getline(cin,z);
            string cname;
             getline(cin,cname);
          //   cout<<"cname is "<<cname;
          //  cin>>z;
            if(s[0]==cname)
            {
                cout<<"INVALID THIS IS THE PREVIOUS NAME\n";
            }
            s[0]=cname;
        //    cout<<s[0]<<" IS \n";
            updatedetails(s,number);
            break;
            }
            case 2:
            {
            cout<<"Enter correct fathers name\n";
            string z;
         //   getline(cin,z);
            cin>>z;
            string fname;
             getline(cin,fname);
            if(fname==s[1])
            {
                cout<<"INVALID THIS IS THE PREVIOUS NAME\n";
            }
            s[1]=fname;
            updatedetails(s,number);
            break;
            }
            case 3:
            {
            cout<<"Enter correct Mothers name\n";
            string z;
        //    getline(cin,z);
            cin>>z;
            string mname;
             getline(cin,mname);
            if(mname==s[2])
            {
                cout<<"INVALIID THIS IS THE PREVIOUS NAME\n";
            }
            s[2]=mname;
            updatedetails(s,number);
            break;
            }
            case 4:
            {
                cout<<"Enter correct UID\n";
                string z;
        //    getline(cin,z);
                cin>>z;
                string uid;
                 getline(cin,uid);
                if(uid==s[4])
                {
                    cout<<"INVALID THIS IS THE PREVIOUS UID\n";
                }
                s[4]=uid;
                updatedetails(s,number);
                break;
            }
            default:
            {
            //1goto end;
            cout<<"\n\n **UPDATED SUCCESS FULLY **\n\n";
            return;
            break;
            
            }

            cout<<"\n\n **UPDATED SUCCESS FULLY **\n\n";
        }
    }
    return;
}


void menu(){
    cout<<"------------------------------------*-MENU-*-------------------------------------\n";
    cout<<"|                                1. ADDRECORD                                   |\n";
    cout<<"|                                2. listrecord                                  |\n";
    cout<<"|                                3. modifyrecord                                |\n";
    cout<<"|                                4. Stop the Application                        |\n";
    cout<<"---------------------------------------------------------------------------------\n";
}

int32_t main(){ 
    Trie *root=new Trie();
    //intitially setting dummy node value as -1 while operating cheking if root->count is -1 
    while(1)
    {
        menu();
        int key;
        cin>>key;
        switch(key){
            case 1:{
                // taking details and adding them into a trie
                //each time if we try to insert we need increase count on dummny node
                root->count++;
                addrecord(root);
                break;
                //DONE
            }  
            case 2:
            {
                listrecord(root);
                break;
            }
            case 3:
            {
                modifyrecord(root);
                break;
            }
            case 4:
            {
                exit(0);
            }
            default:{
                cout<<"___Enter Valid Key___\n";
                break;
            }
        }
    }
}