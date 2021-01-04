#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;

int a=7,b=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm,dd,yy;
};

ofstream fout;
ifstream fin;

class item
{
    int Itemno;
    char Name[20];
    date d;
public:
    void add_itemdetails()
    {
        cout<<"\n\n\t Enter the Item No: ";
        cin>>Itemno;
        cout<<"\n\n\tEnter the Item Name: ";
        cin>>Name;

        cout<<"\n\n\tEnter the Manufacturing Date(dd-mm-yy): ";
        cin>>d.mm>>d.dd>>d.yy;
    }
    void display_itemdetails()
    {
        cout<<"\n\tItem No: ";
        cout<<Itemno;
        cout<<"\n\n\tItem Name: ";
        cout<<Name;
        cout<<"\n\n\tItem Manufacturing Date : ";
        cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    }
    void report()
    {
        gotoxy(3,a);
        cout<<Itemno;
        gotoxy(13,a);
        puts(Name);
    }
    int retno()
    {
        return(Itemno);

    }

};

class amount: public item
{
    float price,qty,tax,gross,dis,netamt;
public:
	void display();
    void add_itemdetails();
    void details();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

void amount::add_itemdetails()
{
    item::add_itemdetails();
    cout<<"\n\n\tItem Price: ";
    cin>>price;
    cout<<"\n\n\tItem Quantity: ";
    cin>>qty;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross=price+(price*(tax/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::display()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::display_itemdetails();
    cout<<"\n\n\tNet amount: ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,a);
    cout<<price;
    gotoxy(33,a);
    cout<<qty;
    gotoxy(44,a);
    cout<<tax;
    gotoxy(52,a);
    cout<<dis;
    gotoxy(64,a);
    cout<<netamt;
    a=a+1;
    if(a==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        a=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS: ";
        gotoxy(3,5);
        cout<<"ITEM NUMBER:";
        gotoxy(13,5);
        cout<<"ITEM NAME:";
        gotoxy(23,5);
        cout<<"ITEM PRICE:";
        gotoxy(33,5);
        cout<<"ITEM QUANTITY:";
        gotoxy(44,5);
        cout<<"TAX:";
        gotoxy(52,5);
        cout<<"DEDUCTION:";
        gotoxy(64,5);
        cout<<"NET AMOUNT:";
    }
}

void amount::pay()
{
    display();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tPRICE                     :"<<price;
    cout<<"\n\n\t\tQUANTITY                  :"<<qty;
    cout<<"\n\t\tTAX PERCENTAGE            :"<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE       :"<<dis;
    cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<netamt;
    cout<<"\n\t\t*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
cout<<"############################# Shriya's SuperMarket Management System ############################# ";
    gotoxy(25,3);
    
    cout<<"\n\t\t1.Generate Bill \n\n";
    cout<<"\t\t2.Add/Remove/Edit Item\n\n";
    cout<<"\t\t3.Show Item Details\n\n";
    cout<<"\t\t4.Exit\n\n"<<endl;
    
    cout<<"\t\tPlease Enter Your Choice: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"$$$$$$$$$$ Bill Details $$$$$$$$$$";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.All Items\n\n";
        cout<<"\t\t2.Back to Main menu\n\n";
        cout<<"\t\tPlease Enter Required Option: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" BILL DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"ITEM NAME";
            gotoxy(23,5);
            cout<<"ITEM PRICE";
            gotoxy(33,5);
            cout<<"ITEM QUANTITY";
            gotoxy(44,5);
            cout<<"TAX %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,a);
            cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
        
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"$$$$$$$$$$ Bill Editor $$$$$$$$$$";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout<<"\t\t4.Back to Main Menu\n\n";
        cout<<"Please enter your choice:"<<endl;
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add_itemdetails();
            cout<<"\n\t\tItem Added Successfully!";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\tEnter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            b=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(b*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\tCurrent Details are:\n";
                        amt.display();
                        cout<<"\n\n\t\tEnter New Details\n";
                        amt.add_itemdetails();
                        cout<<"\n\t\tItem Details editted!";
                    }
                }
                b++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tItem No. does not exist...Please Retry!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<"\n\n\tEnter Item Number to be deleted :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }

            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File!!!!";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"\n\t\tItem Succesfully Deleted!";
            else if (flag==0)
                cout<<"\n\t\tItem does not Exist! Please Retry";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\tWrong Choice!!! Retry";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\tEnter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tItem does not exist....Please Retry!";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"************************** THANKS **************************************";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tWrong Choice....Please Retry!";
        getch();
        goto menu;
    }
    return 0;
}
