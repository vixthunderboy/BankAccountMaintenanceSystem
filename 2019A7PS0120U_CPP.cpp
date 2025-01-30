//Vikrant Prashant Gurav
//2019A7PS0120U

#include <iostream> // cin and cout
#include <stdlib.h> // system("CLS"); - (clear screen)
#include <conio.h> // getch to hold output screen
#include <vector> // vectors instead of arrays so accounts can keep being added without limit
#include <string.h> // getline to take in strings 
#include <math.h> // power function for compound interest formula

using namespace std;

class account
{   private:
    string CustName;
    int AccNo;
    int AccType; // account type is integer, 0 = current, 1 = savings
    
    
    public:
    
    account() // non parameterized constructor
    {
        CustName="NONE";
        AccNo=0;
        AccType=-1;
    }
    
    void change(string name, int no, int typeofacc) // to change the values of private parent members via publicly inherited child class
    {
        CustName=name;
        AccNo=no;
        AccType=typeofacc;
    }
    
    int ret_an() // return account number, since it is private parent member
    {
        return AccNo;
    }

    string ret_CustName() // return customer name, since it is private parent member
    {
        return CustName;
    }
    
};

class cur_acct : public account
{
    private:
    float balance;
    
    
    public:
    
    void checksvc() // deducts AED 20 service charge from balance if balance found to be < AED 100
    {
        if (balance<100)
        {cout<<endl<<"Since your balance is lower than AED 100, a service charge of AED 20 has been deducted from your balance"<<endl;
        balance-=20;}
    }
    
    cur_acct(string name, int no, int typeofacc, float bal) // parameterized constructor
    {
        change(name, no, typeofacc); // passes arguments to parent class to change private parent members
        balance = bal;
        checksvc(); // check if service charge should be deducted
    }
    
    
    void deposit()
    
    {   cout<<endl<<"Your balance is AED "<<balance<<endl<<"Enter amount to be deposited"<<endl;
        int dep;
        cin>>dep;
        balance+=dep;

        checksvc(); // check if service charge should be deducted

        cout<<endl<<"Successfully deposited, your new balance is AED "<<balance<<endl<<"Press any key to continue"<<endl;
        getch(); // holds output screen till key is pressed
    }
    
    void withdraw()
    {   
        cout<<endl<<"Your balance is AED "<<balance<<endl<<"Enter amount to be withdrawn"<<endl;
        int wd;
        cin>>wd;
        
        if (wd>balance||balance-wd<20) // checks if amount to be withdrawn is greater than balance, and if difference between balance and withdrawn amount will be less than AED 20, which will be insufficient funds due to service charge which is AED 20
        {   
            system("CLS");
            cout<<endl<<"Insufficient funds in account, your balance is AED "<<balance<<endl<<"Press any key to continue"<<endl;
            getch();        
            
        }
        else {balance-=wd;
        
        checksvc();

        cout<<endl<<"Successfully withdrawn, your new balance is AED "<<balance<<endl<<"Press any key to continue"<<endl;
        getch();}
    }
    
    void disp_balance()
    {   system("CLS"); // clear screen
        cout<<endl<<"Your balance is AED "<<balance<<endl<<"Press any key to continue";
        getch();
    }
    
};

class sav_acct : public account
{
    private:
    float balance;
    
    public:
    sav_acct(string name, int no, int typeofacc, float bal)
    {
        change(name, no, typeofacc);
        balance = bal;
        
    }
    
    void deposit()
    {   
        cout<<endl<<"Your balance is AED "<<balance<<endl<<"Enter amount to be deposited"<<endl;
        int dep;
        cin>>dep;
        balance += dep;

        cout<<endl<<"Successfully deposited, your new balance is AED "<<balance<<endl<<"Press any key to continue"<<endl;
        getch();
    }
    
    void withdraw()
    {   
        cout<<endl<<"Your balance is AED "<<balance<<endl<<"Enter amount to be withdrawn"<<endl;
        int wd;
        cin>>wd;
        
        if (wd>balance)
        {   
            system("CLS");
            cout<<endl<<"Insufficient funds in account"<<endl<<"Press any key to continue";
            getch();        
            
        }
        else balance-=wd;

        cout<<endl<<"Successfully withdrawn, your new balance is AED "<<balance<<endl<<"Press any key to continue"<<endl;
        getch();
    }
    
    void disp_balance()
    {   system("CLS");
        cout<<endl<<"Your balance is AED "<<balance<<endl<<"Press any key to continue";
        getch();
        
    }
    
    void calc_interest() 
    {   system("CLS");
        cout<<"Your current balance is AED "<<balance<<endl<<"Your interest will be compounded at a rate of 5%, per year"<<endl<<endl;
        cout<<"Enter starting year"<<endl;
        int y; cin>>y;
        cout<<endl<<"Enter starting month (1-12)"<<endl;
        int m; cin>>m;
        while (m<1||m>12) // ensures month is between 1 and 12
        {cout<<endl<<"Invalid month, please enter again"<<endl;
        cin>>m;}
        cout<<endl<<"Enter starting day"<<endl;
        int d; cin>>d;
        while((d<1)||(d>31)||((y%4!=0)&&(m==2)&&(d>28))||((m==2)&&(d>29))||(((m==4)||(m==6)||(m==9)||(m==11))&&d>30)) // checks if day is valid (between 1 and 31, not > 29 if Feb and not > 28 in Feb if not a leap year, ensures day not > 30 in Apr, Jun, Sep, Nov)
        {cout<<endl<<"Invalid day, please enter again"<<endl;
        cin>>d;}

        cout<<endl<<"Enter ending year"<<endl;
        int yy; cin>>yy;
        while (yy<y) // ensures end year isn't less than start year
        {cout<<endl<<"Invalid year, please enter again"<<endl;
        cin>>yy;}
        cout<<endl<<"Enter ending month"<<endl;
        int mm; cin>>mm;
        while ((mm<1||mm>12)||((y==yy)&&(mm<m))) // ensures month is between 1 and 12 and not less than start month if year is same
        {cout<<endl<<"Invalid month, please enter again"<<endl;
        cin>>mm;}
        cout<<endl<<"Enter ending day"<<endl;
        int dd; cin>>dd;
        while((dd<1)||(dd>31)||((yy%4!=0)&&(mm==2)&&(dd>28))||((mm==2)&&(dd>29))||(((mm==4)||(mm==6)||(mm==9)||(mm==11))&&dd>30)||((y==yy&&m==mm)&&dd<d)) // checks if day is valid, as well as ensures end day is not less than start day if year and month are same
        {cout<<endl<<"Invalid day, please enter again"<<endl;
        cin>>dd;}

        int t;

        t = yy-y; // number of years

        if (y!=yy&&mm<m) // if new month less than old month, and year isn't the same, then decrements 1 since that full year will not be completed and therefore not compounded
        {t-=1;}

        if (y!=yy&&mm==m&&dd<d) // if year isn't the same, and month is same, and new day less than old day, then decrements 1 since full year will not be completed and therefore not compounded
        {t-=1;}

        float amount;

        amount = balance*(pow(1.05,t)); // ASSUMPTION: Compound Interest rate is 5%, n = 1, therefore r = 0.05 therefore (1 + r/n) = 1 + 0.05 = 1.05 (Compound Interest Formula: Amount = Principal (1 + rate/n)^time period)

        balance = amount;

        system("CLS");

        cout<<"Interest has been compounded at a rate of 5%, your new balance is AED "<<balance<<endl<<"Press any key to continue"<<endl;

        getch();
    }
    
    
};

struct acnos // used a structure to map account number to account type
{
    int acnum;
    int actype;
};

int main()
{   
    // used vectors so that new accounts can keep being added without a limit
    vector<cur_acct> ca; 
    vector<sav_acct> sa;
    vector<acnos> an;
    int n; // n is taken in when loop is entered, 1 for new acc, 2 for existing
    
    do // loop runs as long as user inputs 1 or 2 in the beginning
    {   
    system("CLS");
    cout<<"1) Create New Account"<<endl<<"2) Access Existing Account"<<endl<<"Any other key to exit"<<endl;
    
    cin>>n; // user choice
    
    switch(n)
    {   
        case 1: // creating new account
        
        {   system("CLS");
            cout<<"Enter 0 for current account and 1 for savings account, enter anything else to return to the main menu"<<endl;
            int c; // account type, 0 = curr, 1 = savings
            int flag = 0;
            cin>>c;
            if(c!=1&&c!=0)
            {
                flag++; // if user doesn't enter 0 or 1, then flag becomes 1
            }
            if (flag==1)
            {
                break; // flag is 1 since user didn't enter 0 or 1, therefore breaks out of loop and goes to main menu
            }
            string a; //name
            int b; //account number
            float d; //initial balance
            
            cout<<endl<<"Enter name"<<endl;
            cin.ignore();
            getline(cin, a); // user inputs name
            cout<<endl<<"Enter account number"<<endl;
            cin>>b;
            for (int i=0;i<an.size();i++) // structure vector is being traversed to ensure account number doesn't already exist when creating new account
            {
                if (b==an[i].acnum) // if user input account number matches account number in structure vector, user is asked to input account number again
                {
                    cout<<endl<<"This account already exists, please enter account number again"<<endl;
                    cin>>b; // user inputs account number again
                    i=-1; // i is made -1 so that when it is incremented (i++), i becomes 0 and traverses structure vector from the beginning for new input
                }
            }
            acnos newan; // new structure instance is created
            newan.acnum=b; // account number
            newan.actype=c; // account type mapped to account number
            an.push_back(newan); // structure pushed back into vector
            cout<<endl<<"Enter initial deposit"<<endl;
            cin>>d; // user inputs initial deposit
            while(c==0&&d<20) // if account type is current, and initial deposit is less than 20, user prompted to input init. deposit again
            {
            cout<<endl<<"Minimum initial deposit should be 20. If balance is less than 100, service charge of 20 will be incurred. Please enter initial deposit again"<<endl;
            cin>>d;
            }
            if (c==0) // checks account type
            {
                cur_acct curacc(a,b,c,d); // if account type is current, an object of cur_acct created with parameters received earlier from user input
                ca.push_back(curacc); // object pushed back into current account vector
            }
            
            if (c==1)
            {
                sav_acct savacc(a,b,c,d); // same as above but for savings account instead
                sa.push_back(savacc); // object pushed back into savings account vector
            }
        
            break;
        }
        
        case 2: // accessing existing account
        {
            system("CLS");
            cout<<"Please enter account number"<<endl;
            int acno;
            cin>>acno; // user inputs acc no.
            int fl = 0, i=0; // flag is initialised as 0, i is iterator
            for (;i<an.size();i++) // structure vector is traversed to check whether input account number exists
            {
                if (an[i].acnum == acno) // checks if user input acc no. matches acc no. in structure
                {fl++; // if user input acc no. exists, flag becomes 1
                break;}
            }
            
            
            if (fl==0)
            {
                cout<<endl<<"Account doesn't exist, press any key to go back to main menu"<<endl; // if flag doesn't change, user input acc no. doesn't exist
                getch();
                break;
            }
            
            int actypeflag=-1; // initialise account type flag
            int j=0; // iterator
            if (an[i].actype==0) // i broken out of previous loop as index of input acc no. in structure, checks if account type is cur acc (0)
            
            {for (;j<ca.size();j++) // traverses current account vector 
            {
                if (an[i].acnum==ca[j].ret_an()) 
                {   actypeflag=0; // account type is current
                    break; // breaks out of loop with j as index of current account number
                }
            }
            }
            
            if (an[i].actype==1) // checks if account type is savings acc (1)
            {for (;j<sa.size();j++)
            {
                if (an[i].acnum==sa[j].ret_an())
                {   actypeflag = 1; // account type is savings
                    break; // breaks out of loop with j as index of savings account number
                }
            }
            }
            
            system("CLS");

            string nam; // customer name

            if (actypeflag==1)
                    {
                        nam = sa[j].ret_CustName(); // returns customer name (savings acc)
                        
                    }

            if (actypeflag==0)
                    {
                        nam = ca[j].ret_CustName(); // returns customer name (current acc)
                        
                        
                    }

            int x; // user choice for next menu
            do // loops as long as x isn't between 1 and 4
            {
            system("CLS");
            cout<<"Hi "<<nam<<"!"<<endl; // greets customer, name returned from object
            
            cout<<"1) Deposit"<<endl<<"2) Withdraw"<<endl<<"3) Display Balance"<<endl<<"4) Compound Interest (only for Savings Accounts)"<<endl<<"Press any other key to go back"<<endl;
            
            cin>>x;
            switch(x)
            {
                case 1:
                {
                    if (actypeflag==0)
                    {
                        ca[j].deposit(); // deposit function call (cur)
                        break;
                        
                    }
                    
                    if (actypeflag==1)
                    {
                        sa[j].deposit(); // dep. fn call (sav)
                        break;
                    }
                    
                    break;
                }
                
                case 2:
                {
                    if (actypeflag==0)
                    {
                        ca[j].withdraw(); // withdraw fn call (cur)
                        break;
                        
                    }
                    
                    if (actypeflag==1)
                    {
                        sa[j].withdraw(); // withdraw fn call (sav)
                        break;
                        
                    }
                    
                    break;
                }
                
                case 3:
                {
                   if (actypeflag==0)
                    {
                        ca[j].disp_balance(); // display balance fn call (cur)
                        break;
                    }
                    
                    if (actypeflag==1)
                    {
                        sa[j].disp_balance(); // display balance fn call (sav)
                        break;
                    }
                    break;
                }
                    
                case 4:
                {
                    if (actypeflag==0)
                    {
                        cout<<endl<<"This option is not available for your account"<<endl; // if current account, compound interest not available
                        getch();
                        break;
                    }
                    
                    if (actypeflag==1)
                    {
                        sa[j].calc_interest(); // compound interest fn call
                        break;
                        
                    }
                    break;
                    
                }
                
                default: {break;}
                
             break;   
            }}while(x>=1&&x<=4); // access existing loop (see line 368)
            
            break;
        }
        
        default: {exit(0);break;}
        break;
    }
    }while(n==1||n==2); // create / access account loop (main menu), see line 235
   
    return 0;
    
}



