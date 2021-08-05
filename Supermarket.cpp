#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>

#define size 10
using namespace std;

struct node_i
{
    long long int itemid;
    int name;
    float rate;
    int quantity;
    node_i* next;
};
struct node_c
{
    long long int custid;
    int name;
    float rate;
    int points;
    node_c* next;
};

//The following struct are for entering data into inventory items and customer transactions.
struct itemdata
{
    long long int id;
    int name;
    float rate;
    int quantity;
};
struct custdata
{
    long long int c_id;
    int cname;
    int cpoints;
};

class inventoryitem
{
    protected:
    node_i *chain[size];
     public:
   virtual void insertitem(long long int ID, int name, float price, int quantity) 
    {
        cout << "Only Manager can access the inventory database." <<endl;
    }
  virtual  node_i* Search(long long int ID)
   {
        cout << "Only Manager can access the inventory database." <<endl;
       return chain[0];
    }         
 virtual void delete_Item(long long int ID) 
    {
        cout << "Only Manager can access the inventory database." <<endl;
    }
  virtual  void updateitem(long long int ID, int name, float price) 
    {
        cout << "Only Manager can access the inventory database." <<endl;
    }
  
   virtual void updateqty(long long int ID, int qty) 
    {
       cout << "Only Manager can access the inventory database." <<endl;
    }
  virtual node_i* iteminfo(long long int ID) 
    {
       cout << "Only Manager can access the inventory database." <<endl;
      return chain[0];
    }
};
class Manager:public inventoryitem
{
    private:
    long long int ID;
    std::string name;
    public:
     void init()
    {
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
    }
    void managerinfo() 
    {
        name = "Aditya";
        ID = 2000010100201;
    }
    void insertitem(long long int ID, int name, float price, int quantity)
    {
    node_i* newNode = new node_i;
        newNode->itemid = ID;
        newNode->name = name;
        newNode->rate = price;
        newNode->quantity = quantity;
    //calculate hash key
    
    int key = ID%size;
    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
    else
    {
        //add the node at the end of chain[key].
        struct node_i *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }    
    }
    node_i* Search(long long int ID)
{
        int key = ID % 10;
        int flag = 0;
        node_i* temp = chain[key];
        while (temp != NULL)
        {
            if (temp->itemid == ID)
            {
                flag = 1;
                return temp;
            }
            temp = temp->next;
        }
            if (flag == 0)
            {
            cout << "Not Found.Please enter some valid item ID and re-run!" << endl;
            exit(0);
            }
            return chain[0];
}         
    void delete_Item(long long int ID)
    {
        node_i* newNode = new node_i;
        newNode = Search(ID);
        int key = (newNode->itemid)%size;   
    node_i *entry = chain[key];
    node_i *prev = NULL;
    while (entry->itemid!= newNode->itemid) // 3 4 5 6
    {
        prev = entry;
        entry = entry->next;
    }
    if (prev != NULL)
    {
        prev->next = entry->next;
    }
    delete entry;
    }
    void updateitem(long long int ID, int name, float price) 
    {
        node_i* temp = new node_i;
        temp = Search(ID);
        temp->name = name;
        temp->rate = price;
    }
     void updateqty(long long int ID, int qty) 
    {
        node_i* temp = new node_i;
        temp = Search(ID);
        temp->quantity = (temp->quantity) - qty; //For updating product's quantity in the inventory databse.
    }
   node_i* iteminfo(long long int ID) 
    {
        node_i* temp = new node_i;
       int key = ID % 10;
        int flag = 0;
         temp = chain[key];
        while (temp != NULL)
        {
            if (temp->itemid == ID)
            {
                flag = 1;
                return temp;
            }
            temp = temp->next;
        }
            if (flag == 0)
            {
            cout << "Not Found" << endl;         
             exit(0);
            }
            return chain[0];
    }
};
class customer
{
    protected:
     node_c *chain[size];
    public:
    void init()
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}
    void insertcust(long long int ID, int name,int points) 
    {
        node_c* newNode = new node_c;
        newNode->custid = ID;
        newNode->name = name;
        newNode->rate = points;
    //calculate hash key
    int key = ID%size;
    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
    else
      {
        //add the node at the end of chain[key].
        struct node_c *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
      }   
    }    
    node_c* Search(long long int ID)
{
        int key = ID % 10;
        int flag = 0;
        node_c* temp = chain[key];
        while (temp != NULL)
        {
            if (temp->custid == ID)
            {
                flag = 1;
                return temp;
            }
            temp = temp->next;
        }
            if (flag == 0)
            {
            cout << "Not Found.Please enter some valid customer ID and re-run!" << endl;
            exit(0);
            }
        return chain[0];
}         

    void delete_Item(long long int ID) 
    {
        node_c* newNode = new node_c;
        newNode = Search(ID);
         int key = (ID)%size;   
    node_c *entry = chain[key];
    node_c *prev = NULL;
    while (entry->custid!= newNode->custid) // 3 4 5 6
    {
        prev = entry;
        entry = entry->next;
    }
    if (prev != NULL)
    {
        prev->next = entry->next;
    }
    delete entry;
    }
    
    void updatepoints(long long int ID,int points) 
    {
        node_c* temp = new node_c;
        temp = Search(ID);
        temp->points = points;
    }  
    node_c* custinfo(long long int ID) 
    {
        node_c* temp = new node_c;
        temp = Search(ID);
        return temp;
    }
};

class Billing:public Manager,public customer
{
    protected:
  float amount=0;
   static int transactionID;
  public:
  node_i* buy_item(long long int ID,inventoryitem I)
  {
      node_i* temp=new node_i;
      temp=I.iteminfo(ID);
      return temp;
  }
  void add_bill(long long int id,int name,int points,customer C)
  {
      C.insertcust(id,name,points);
  }
  void bill_print(long long int custID,Manager M1,customer C)
  {
      int products;
      long long int ID;
      node_i* temp1=new node_i;
      
      transactionID++;
      
      node_c *temp=new node_c;
      temp=C.custinfo(custID); 
      
      cout <<"Please enter the unique(different) number of items you have bought:";
      cin >>products;
      cout <<endl<<endl;
      
      int q[products];
      
        struct itemdata out[products];
        for (int i = 0; i < products; i++)
        {
            cout << "Please enter your " <<i+1 <<" item's ID:"<<endl;
            cin >> ID;
            cout << "Please enter the quantity that you have bought of this item:"<<endl;
            cin >> q[i];
            cout << "\n";
            temp1 = M1.iteminfo(ID);
            out[i].id=temp1->itemid;
            out[i].name=temp1->name;
            out[i].rate=temp1->rate;
            
            amount = amount + (temp1->rate)*q[i];
            M1.updateqty(temp1->itemid,q[i]);
            out[i].quantity=temp1->quantity;
        }
        cout<<endl;
        cout << setw(20) << "***********WELCOME TO ADITYA GROCERY*************" <<endl;
         cout << setw(20) << "*******HOPE YOU HAVE A GREAT TIME SHOPPING*******" <<endl<<endl;
        cout <<"CUSTOMER DETAILS:"<<endl;
        cout << "Transaction ID: " << transactionID<< endl;
      cout << "Customer ID: " << custID << endl;
      cout << "Customer Name: " << temp->name << endl<<endl;
      cout <<"FINAL BILL:"<<endl;
         for (int k = 0; k < 20; k++)
            cout << "----";
        cout << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Product Name" << setw(15) << "Rate" << setw(20) << "Quantity" << setw(14) << "Amount\n";
        for (int k = 0; k < 20; k++)
            cout << "----";
        cout << endl;
        for(int i=0;i<products;i++)
        {
         cout  << out[i].id << setw(15) << out[i].name << setw(18) << out[i].rate << setw(17) << q[i] << setw(15) << (out[i].rate)*q[i] << endl;
        }
        cout <<endl;
        cout << setw(15) << " " << setw(15) << " " << setw(15) << " " << setw(14) << " " << setw(1) << "Total Amount:" << setw(5) << amount << endl;
        for (int k = 0; k < 20; k++)
            cout << "----";
        cout << endl;
        cout <<setw(20)<<"*************THANK YOU FOR SHOPPING FROM ADITYA GROCERY***************"<<endl<<endl;
        cout << "INVENTORY DATABASE AFTER UPDATING:" <<endl;
        for (int k = 0; k < 20; k++)
            cout << "----";
        cout << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Product Name" << setw(15) << "Rate" << setw(20) << "Quantity" <<endl;
         for (int k = 0; k < 20; k++)
            cout << "----";
        cout << endl;
        for(int i=0;i<products;i++)
        {
         cout  << out[i].id << setw(15) << out[i].name << setw(18) << out[i].rate << setw(17) << out[i].quantity  <<endl;
        }
        
 for (int k = 0; k < 20; k++)
            cout << "----";
        cout << endl;
  }
};
int Billing::transactionID=0;
int main()
{
    Manager M1;
    M1.managerinfo();
    M1.init();
    inventoryitem I;
    struct itemdata a[100] = {
{111100000001,1,100,20},{111100000002,2,110,20},{111100000003,3,120,20},{111100000004,4,130,20},{111100000005,5,140,20},{111100000006,6,150,20},{111100000007,7,160,20},{111100000008,8,170,20},{111100000009,9,180,20},{111100000010,10,190,20},
{111100000011,11,200,20},{111100000012,12,210,20},{111100000013,13,220,20},{111100000014,14,230,20},{111100000015,15,240,20},{111100000016,16,250,20},{111100000017,17,260,20},{111100000018,18,270,20},{111100000019,19,280,20},{111100000020,20,290,20},
{111100000021,21,300,20},{111100000022,22,310,20},{111100000023,23,320,20},{111100000024,24,330,20},{111100000025,25,340,20},{111100000026,26,350,20},{111100000027,27,360,20},{111100000028,28,370,20},{111100000029,29,380,20},{111100000030,30,390,20},
{111100000031,31,400,20},{111100000032,32,410,20},{111100000033,33,420,20},{111100000034,34,430,20},{111100000035,35,440,20},{111100000036,36,450,20},{111100000037,37,460,20},{111100000038,38,470,20},{111100000039,39,480,20},{111100000040,40,490,20},
{111100000041,41,500,20},{111100000042,42,510,20},{111100000043,43,520,20},{111100000044,44,530,20},{111100000045,45,540,20},{111100000046,46,550,20},{111100000047,47,560,20},{111100000048,48,570,20},{111100000049,49,580,20},{222200001111,50,590,20},
{222200001114,51,600,20},{222200001117,52,610,20},{222200001120,53,620,20},{222200001123,54,630,20},{222200001126,55,640,20},{222200001129,56,650,20},{222200001132,57,660,20},{222200001135,58,670,20},{222200001138,59,680,20},{222200001141,60,690,20},
{222200001144,61,700,20},{222200001147,62,710,20},{222200001150,63,720,20},{222200001153,64,730,20},{222200001156,65,740,20},{222200001159,66,750,20},{222200001162,67,760,20},{222200001165,68,770,20},{222200001168,69,780,20},{222200001171,70,790,20},
{222200001174,71,800,20},{222200001177,72,810,20},{222200001180,73,820,20},{222200001183,74,830,20},{222200001186,75,840,20},{222200001189,76,850,20},{222200001192,77,860,20},{222200001195,78,870,20},{222200001198,79,880,20},{222200001201,80,890,20},
{222200001204,81,900,20},{222200001207,82,910,20},{222200001210,83,920,20},{222200001213,84,930,20},{222200001216,85,940,20},{222200001219,86,950,20},{222200001222,87,960,20},{222200001225,88,970,20},{222200001228,89,980,20},{222200001231,90,990,20},
{222200001234,91,1000,20},{222200001237,92,1010,20},{222200001240,93,1020,20},{222200001243,94,1030,20},{222200001246,95,1040,20},{222200001249,96,1050,20},{222200001252,97,1060,20},{222200001255,98,1070,20},{222200001258,99,1080,20},{222200001261,100,1090,20},
    };
     for (int i = 0; i < 100; i++)
     {
        M1.insertitem(a[i].id, a[i].name, a[i].rate, a[i].quantity);
     }    
    Billing B;
    customer C;
    C.init();
    struct custdata a2[100] = {
{9400000001,1,0},{9400000002,2,0},{9400000003,3,0},{9400000004,4,0},{9400000005,5,0},{9400000006,6,0},{9400000007,7,0},{9400000008,8,0},{9400000009,9,0},{9400000010,10,0},
{9400000011,11,0},{9400000012,12,0},{9400000013,13,0},{9400000014,14,0},{9400000015,15,0},{9400000016,16,0},{9400000017,17,0},{9400000018,18,0},{9400000019,19,0},{9400000020,20,0},
{9400000021,21,0},{9400000022,22,0},{9400000023,23,0},{9400000024,24,0},{9400000025,25,0},{9400000026,26,0},{9400000027,27,0},{9400000028,28,0},{9400000029,29,0},{9400000030,30,0},
{9400000031,31,0},{9400000032,32,0},{9400000033,33,0},{9400000034,34,0},{9400000035,35,0},{9400000036,36,0},{9400000037,37,0},{9400000038,38,0},{9400000039,39,0},{9400000040,40,0},
{9400000041,41,0},{9400000042,42,0},{9400000043,43,0},{9400000044,44,0},{9400000045,45,0},{9400000046,46,0},{9400000047,47,0},{9400000048,48,0},{9400000049,49,0},{9400000050,50,0},
{9400000051,51,0},{9400000052,52,0},{9400000053,53,0},{9400000054,54,0},{9400000055,55,0},{9400000056,56,0},{9400000057,57,0},{9400000058,58,0},{9400000059,59,0},{9400000060,60,0},
{9400000061,61,0},{9400000062,62,0},{9400000063,63,0},{9400000064,64,0},{9400000065,65,0},{9400000066,66,0},{9400000067,67,0},{9400000068,68,0},{9400000069,69,0},{9400000070,70,0},
{9400000071,71,0},{9400000072,72,0},{9400000073,73,0},{9400000074,74,0},{9400000075,75,0},{9400000076,76,0},{9400000077,77,0},{9400000078,78,0},{9400000079,79,0},{9400000080,80,0},
{9400000081,81,0},{9400000082,82,0},{9400000083,83,0},{9400000084,84,0},{9400000085,85,0},{9400000086,86,0},{9400000087,87,0},{9400000088,88,0},{9400000089,89,0},{9400000090,90,0},
{9400000091,91,0},{9400000092,92,0},{9400000093,93,0},{9400000094,94,0},{9400000095,95,0},{9400000096,96,0},{9400000097,97,0},{9400000098,98,0},{9400000099,99,0},{9400000100,100,0},
    };
     for (int i = 0; i < 100; i++)
     {
        C.insertcust(a2[i].c_id, a2[i].cname, a2[i].cpoints);
     } 
     long long int Cust_ID;
    cout << "Please Enter Customer ID: ";
    cin >> Cust_ID;
    cout <<endl<<endl;
    B.bill_print(Cust_ID, M1, C);
    return 0;
}