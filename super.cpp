#include<conio.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
using namespace std;
class product
{
    int pno,qua;
    char name[50];
    float price,qty,tax,dis;
public:
    void create_product()
    {
        system("cls");
        cout<<"\n\t\tPlease Enter The Product No. of The Product ";
        cin>>pno;
        cout<<"\n\n\t\tPlease Enter The Name of The Product ";
        cin>>name;
        cout<<"\n\t\tPlease Enter The Price of The Product ";
        cin>>price;
        cout<<"\n\t\tPlease Enter The Discount (%) ";
        cin>>dis;
        cout<<"\n\n\t\tPlease Enter Quantity ";
        cin>>qua;
    }

    void show_product()
    {
        cout<<"\n\t\tThe Product No. of The Product : "<<pno;
        cout<<"\n\t\tThe Name of The Product : "<<name;
        cout<<"\n\t\tThe Price of The Product : "<<price;
        cout<<"\n\t\tDiscount (%) : "<<dis;
        cout<<"\n\t\tQuantity : "<<qua;
        _getch();
    }

    int retpno()
    {return pno;}

    float retprice()
    {return price;}

    char* retname()
    {return name;}

    int retdis()
    {return dis;}

    int quantity()
    {return qua;}

};
fstream fp;
product pr;
void write_product()
{
    system("cls");
    fp.open("Shop.dat",ios::out|ios::app);
    pr.create_product();
    fp.write((char*)&pr,sizeof(product));
    fp.close();
    cout<<"\n\nThe Product Created Successfully... ";
    _getch();

}
void display_all()
{
    system("cls");
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        pr.show_product();
        cout<<"\n\n\t\t====================================\n";
    }
    fp.close();
    _getch();
}
void display_sp(int n)
{
    system("cls");
    int flag=0;
    fp.open("Shop.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        if(pr.retpno()==n)
        {
            pr.show_product();
            flag=1;
        }
    }
    fp.close();
    _getch();
    if(flag==0)
    cout<<"\n\nrecord not exist";

}
void modify_product()
{
    system("cls");
    int no,found=0;
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The Product No. of The Product ";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(product)) && found==0)
    {
        if(pr.retpno()==no)
        {
            pr.show_product();
            cout<<"\n\n\nPlease Enter The New Details of Product "<<endl;
            _getch();
            pr.create_product();
            int pos=-1*sizeof(pr);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&pr,sizeof(product));
            cout<<"\n\n\t Record Updated Successfully...";
            _getch();
            found=1;
        }
    }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
}
void delete_product()
{
    system("cls");
    int no;
    cout<<"\n\n\n\t\t\tDelete Record";
    cout<<"\n\n\t\tPlease Enter The product no. of The Product You Want To Delete ";
    cin>>no;
    fp.open("Shop.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(product)))
    {
        if(pr.retpno()!=no)
        {
            fp2.write((char*)&pr,sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    cout<<"\n\n\tRecord Deleted ..";
    _getch();

}
int menu()
{
    system("cls");
    fp.open("Shop.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
        cout<<"\n\n\n Program is closing ....";
    }
    cout<<"\n\n\t\t\t\t\tProduct MENU\n\n";
    cout<<"\t\t=======================================================================\n";
    cout<<"\t\tP.NO.\t\tNAME\t\t\t\tPRICE\t\tDiscount\n";
    cout<<"\t\t=======================================================================\n";
    while(fp.read((char*)&pr,sizeof(product)))
    {
        cout<<"\t\t"<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t\t"<<pr.retprice()<<"\t\t"<<pr.retdis()<<" %"<<endl;
    }
    fp.close();
    _getch();
}
void place_order()
{
    system("cls");
    int order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='Y';
    char r;
    menu();
    cout<<"\n\n\t\tDo you want to place your Order ? (y/n)";
    cin>>r;
    if(r=='y'){
    cout<<"\n\t\t\t============================";
    cout<<"\n \t\t\t\tPLACE YOUR ORDER";
    cout<<"\n\t\t\t============================\n";
    do{
        cout<<"\n\n\t\tEnter The Product No. Of The Product : ";
        cin>>order_arr[c];
        cout<<"\n\t\tQuantity in number : ";
        cin>>quan[c];
        c++;
        cout<<"\n\t\tDo You Want To Order Another Product ? (y/n)";
        cin>>ch;
    }while(ch=='y' ||ch=='Y');
    }
    else{
        exit(0);
    }
    system("cls");
    cout<<"\n\n\t\tThank You For Placing The Order";
    cout<<"\n\n\t\t***********************************INVOICE***********************************\n";
    cout<<"\n\t\tPr No.\tPr Name\t\tQuantity \tPrice \tAmount \t   Amount after discount\n";
    for(int x=0;x<=c;x++)
    {
        fp.open("Shop.dat",ios::in);
        fp.read((char*)&pr,sizeof(product));
        while(!fp.eof())
        {
        if(pr.retpno()==order_arr[x])
        {
        amt=pr.retprice()*quan[x];
        damt=amt-(amt*pr.retdis()/100);
        cout<<"\n\t\t"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
        total+=damt;
        }
        fp.read((char*)&pr,sizeof(product));
        }

        fp.close();
    }
    cout<<"\n\n\t\t\t\t\t\t\tTOTAL = "<<total;
    cout<<"\n\n\t\t*****************************************************************************\n";
    _getch();
}

void admin_menu()
{
    system("cls");
    char ch2;
    cout<<"\n\n\n\tADMIN MENU";
    cout<<"\n\n\t1.CREATE PRODUCT";
    cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
    cout<<"\n\n\t3.QUERY ";
    cout<<"\n\n\t4.MODIFY PRODUCT";
    cout<<"\n\n\t5.DELETE PRODUCT";
    cout<<"\n\n\t6.VIEW PRODUCT MENU";
    cout<<"\n\n\t7.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
    cin>>ch2;
    switch(ch2)
    {
        case '1':
            write_product();
            break;
        case '2':
            display_all();
            break;
        case '3':
            int num;
            cout<<"\n\n\tPlease Enter The Product No. ";
            cin>>num;
            display_sp(num);
            break;
        case '4':
            modify_product();
            break;
        case '5':
            delete_product();
            break;
        case '6':
            menu();

        case '7':
            system("cls");
            break;
        default:cout<<"\a";
            admin_menu();
    }
}
int main()
{
    system("color f0");
    char ch;
    char user[50];
    char pass[50];
    char name[50]="Rohan";
    char word[50]="rohan";
    int i;
    char a;
    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. CUSTOMER";
        cout<<"\n\n\t02. ADMINISTRATOR";
        cout<<"\n\n\t03. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>ch;
        switch(ch)
        {
            case '1':
                system("cls");
                place_order();
                break;
            case '2':
                system("cls");
                cout<<"\n\n\n\t\t\tPlease enter username :- ";
                cin>>user;
                cout<<"\n\t\t\tplease enter password :- ";
                for( int i=0; ; ){
                     a=_getch();
                     if((a>='a' && a<='z')||(a>='A' && a<='Z')||(a>='0' && a<='9'))
                    {
                        pass[i]=a;
                        i++;
                        cout<<"*";
                    }
                    if(a=='\b'&&i>=1)
                    {
                        cout<<"\b \b";
                        i--;
                    }
                    if(a=='\r')
                    {
                        pass[i]='\0';
                        break;
                    }
                }
                int resultpass{strcmp(word,pass)};
                int resultuser{strcmp(user,name)};
               if(resultuser==0 && resultpass==0)
               {
                   admin_menu();
               }
               else{
                        cout<<"\n\nuser name and password does not match ";

                break;
                }

             //default :cout<<"\a";
        }
    }while(ch!='3');
return 0;
}

