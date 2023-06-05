#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<stdio.h> 
using namespace std;
class Account
{
	protected:
		float balance;
		float Annual_intrest_rate;
		float service_charge;
		float start_balance;
		float wit_charge;
		bool stat;
		char name[50],pass[30];
		int no_of_wit,no_of_dep;
	public:
		Account()
		{
			wit_charge=0;
			service_charge=0.0;
			stat=1;
			balance=0;
			Annual_intrest_rate=6.5;
			start_balance=0;
			no_of_wit=no_of_withdrawl;
			no_of_dep=no_of_deposite;
		}

		
		static int no_of_deposite;
		static int no_of_withdrawl;
		
		
		void createAccount()
		{
			fstream file;
			file.open("Account.txt",ios::in | ios::binary);
			if(!file)
			{
				cout<<"Can't find file"<<endl;
				exit(0);
			}
			else
			{
				char *n;
				char nam[50];
				n=new char[50];
				Account a;
				username:
				fflush(stdin);
				cout<<"Enter your Username: ";
				cin.getline(name,50,'\n');
				file.seekp(ios::beg);	
				file.read((char*)&a,sizeof(a));
				while(!file.eof())
				{
					n=a.get_name();
					if(strcmpi(name,n)!=0)
					{
						goto process;
					}
					else
					{
						cout<<"Username Exists please try another user name"<<endl;
						cout<<"Try Again!!"<<endl;
						goto username;
					}
					process:
					fflush(stdin);
					cout<<"Enter new password: ";
					cin.getline(pass,50,'\n');
					cout<<"Note: For an active account you need to have initial balance more than $25"<<endl;
					cout<<"Enter your initial balance: $";
					cin>>balance;
					start_balance=balance;
					cout<<"Account Created"<<endl; 
					system("pause");
					system("cls");
					cout<<"Account Details: \nName: "<<name<<"\nPassword: "<<pass<<"\nBalance: $"<<balance<<endl;
				file.read((char*)&a,sizeof(a));
				}
				file.close();
			}
		}
		
		
		float get_balance()
		{
			return(balance);
		}

		char * get_name()
		{
			char *n;
			n=new char[50];
			strcpy(n,name);
			return(n);
		}
		
		char * get_pass()
		{
			char *p;
			p=new char[30];
			strcpy(p,pass);
			return(p);
		}
		
		
		void set_stat(bool st)
		{
			stat=st;
		}
		
		bool get_stat()
		{
			return(stat);
		}
		
		void set_bal(float bal)
		{
			balance=bal;
		}
		
		float get_bal()
		{
			return(balance);
		}
		
		virtual float makeDeposite(float dep,float bal)
		{
			Account a;
			bal=bal+dep;
			++no_of_dep;
			a.set_bal(bal);
			if(bal>=25)
			{
				stat=1;
			}
			else
			{
				stat=0;
			}
			system("cls");
			cout<<"Amount Deposited: $"<<dep<<"\nBalance: $"<<bal<<endl;
			return(bal);
		}
		
		
		virtual float makeWithdrawl(float wit, float bal)
		{
			Account a;
			bal=bal-wit;
			a.set_bal(bal);
			if(bal>=25)
			{
				stat=1;
				a.increment_wit();
			}
			else
			{
				stat=0;
				cout<<"Sorry your account is inactive to make it active your balance should be $25 or more"<<endl;
			}
			system("cls");
			cout<<"Amount Withdrawled: $"<<wit<<"\nBalance: $"<<bal<<endl;
			return(bal);
		}
		
		
		virtual float calcInt(float bal)
		{
			cout<<endl<<Annual_intrest_rate;
			
			float Monthly_intrest_rate , Monthly_intrest;
			Monthly_intrest_rate=(Annual_intrest_rate/12);
			Monthly_intrest=bal*(Monthly_intrest_rate/100);
			bal=bal+Monthly_intrest;
			return(bal);
		}
		
		
		virtual float monthlyProc(float ch,float bal)
		{
			Account a;
			bal=bal-ch;
			cout<<endl<<bal;
			bal=a.calcInt(bal);
			a.no_of_wit = 0;
			a.no_of_dep = 0;
			service_charge = 0.0;
			return(bal);
		}
		
		
		void increment_wit()
		{
			++no_of_wit;
		}
		
		
		void displayData()
		{
			char password[10];
			fflush(stdin);
			cout<<"Enter admin password to access all acoount details: ";
			cin.getline(password,10,'\n');
			if (strcmpi(password, "admin")==0)
				{
				fstream file;
				file.open("Account.txt",ios::in | ios::binary);
				if(!file)
				{
					cout<<"Can't find file'"<<endl;
					exit(0);
				}
				else
				{
					Account a;
					file.seekp(ios::beg);	
					file.read((char*)&a,sizeof(a));
					while(!file.eof())
					{
						cout<<"------*******-------******-------"<<endl;
						cout<<"Your name is: "<<a.name<<endl;
						cout<<"Your starting balance was: "<<a.start_balance<<endl;
						cout<<"Your current balance is: "<<a.get_bal()<<endl;
						if(a.get_bal()>=25)
						{
							cout<<"You have an active account"<<endl;
							cout<<endl;
						}
						else
						{
							cout<<"You have an inactive account"<<endl;
							cout<<endl;
						}
						file.read((char*)&a,sizeof(a));	
					}
					file.close();
				}
				}
				else
				{
					cout<<"Invalid Password!!"<<endl;
				}
		}
		
		
		void delRecord()
		{
			Account a;
			char *n,*p;
			char nam[50],pas[30];
			n=new char[50];
			p=new char[30];
			fstream file;
			fstream temp;
			file.open("Account.txt",ios::in | ios::binary );
			if(!file)
			{
				cout<<"File not be opened"<<endl;
			}
			else
			{
				fflush(stdin);
				cout<<"Enter your name: ";
				cin.getline(nam,50,'\n');
				fflush(stdin);
				fflush(stdin);
				cout<<"Enter your account password: ";
				cin.getline(pas,30,'\n');
				fflush(stdin);
				file.seekp(ios::beg);
				temp.open("Tempfile.txt",ios::out | ios::binary);
				file.read((char*)&a,sizeof(a));
				while(!file.eof())
				{
					n=a.get_name();
					if(strcmpi(nam,n)!=0)
					{
						temp.write((char*)&a,sizeof(a));
					}
					file.read((char*)&a,sizeof(a));	
					cout<<"Account Deleted!!"<<endl;
				}
				file.close();
				temp.close();
				remove("Account.txt");
				rename("Tempfile.txt","Account.txt");
			}
		}
		
		
		void display()
		{
			fstream file;
			file.open("Account.txt",ios::in |ios::out | ios::binary);
			if(!file)
			{
				cout<<"Can't find file"<<endl;
				exit(0);
			}
			else
			{
				char *n;
				char nam[50];
				n=new char[50];
				Account a;
				fflush(stdin);
				cout<<"Enter your name: ";
				cin.getline(nam,50,'\n');
				fflush(stdin);
				file.seekp(ios::beg);	
				file.read((char*)&a,sizeof(a));
				while(!file.eof())
				{
					n=a.get_name();
					if(strcmpi(nam,n)==0)
					{
						cout<<endl<<"------*******-------******-------"<<endl;
						cout<<"Your name is: "<<a.name<<endl;
						cout<<"Your starting balance was: "<<a.start_balance<<endl;
						cout<<"Your current balance is: "<<a.get_bal()<<endl;
						cout<<"Your number of withdrawal are: "<<a.no_of_wit<<endl;
						if(a.get_bal()>=25)
						{
							cout<<"You have an active account"<<endl;
							cout<<endl;
						}
						else
						{
							cout<<"You have an inactive account"<<endl;
							cout<<endl;
						}
						file.close();
					}
					file.read((char*)&a,sizeof(a));
				}
				file.close();
			}
		}
		
};

int Account::no_of_deposite = 0;
int Account::no_of_withdrawl = 0;

class Saving_Account : public Account
{
	public:
		bool status(float bal)
		{
			Account a;
			if(bal<25)
			{
				a.set_stat(0);
			}
			else if(bal>=25)
			{
				a.set_stat(1);
			}
			return(a.get_stat());
		}
		
		
		float make_Withdrawl(float wit,float bal)
		{
			Account a;
			float b;
			Saving_Account Sa;
			a.increment_wit();
			b=a.makeWithdrawl(wit,bal);
			return(b);
		}
		
		
		float makedeposite(float dep, float bal)
		{
			Account a;
			float b;
			b=a.makeDeposite(dep,bal);
			a.set_stat(1);
			return(b);	
		}
		
		
		float MonthlyProc(float ch,float bal)
		{
			Account a;
			float b;
			if(no_of_withdrawl>4)
			{
				ch=ch+(no_of_withdrawl-4)*1;
				ch=a.monthlyProc(ch,bal);
				return(ch);
			}
			else
			{
				ch=ch;
				b=a.monthlyProc(ch,bal);
				return(b);
			}
		}
			
};


class Checking_Account : public Account
{
	public:
		float makewithdrawl(float wit, float bal)
		{
			float b,ch;
			Checking_Account Ca;
			Account a;
			if(wit>bal)
			{
				wit_charge=wit_charge+15;
				if(wit_charge>=bal)
				{
					cout<<"Sorry! insufficient balance"<<endl;
				}
				else if(bal>=wit_charge)
				{
					bal=bal-wit_charge;
					wit_charge=0;
					if(balance<25)
					{
						a.set_stat(0);
					}
					else
					{
						a.set_stat(1);
					}
				}
			}
			else if(wit<=bal)
			{
				Saving_Account Sa;
				Sa.status(bal);
				if(a.get_stat()==1)
				{
					bal=Ca.monthlyproc(bal);
					b=Sa.make_Withdrawl(wit,bal);
					return(b);
				}
				else
				{
					cout<<"Sorry your account is inactive transaction can not be proceeded"<<endl;
				}
			}
		}
		
		
		float monthlyproc(float bal)
		{
			float ch=0;
			Saving_Account Sa;
			ch=ch+5.0+0.10;
			bal=Sa.MonthlyProc(ch,bal);
			return(bal);
		}
		
		void account_check()
		{
			fstream file;
			file.open("Account.txt",ios::binary | ios::in | ios::out);
			if(!file)
			{
				cout<<"Can't find file'"<<endl;
				exit(0);
			}
			else
			{
				int count=0;
				float bal;
				char *n,*p,nam[50],pas[30];
				n=new char[50];
				p=new char[30];
				Account a ;
				fflush(stdin);
				cout<<"Enter your Username: ";
				cin.getline(nam,50,'\n');
				fflush(stdin);
				cout<<"Enter your account password: ";
				cin.getline(pas,30,'\n');
				fflush(stdin);
				file.seekp(ios::beg);
				file.read((char*)&a,sizeof(a));
				while(!file.eof())
				{
					n=a.get_name();
					p=a.get_pass();
					if((strcmpi(nam,n)==0) && (strcmp(pas,p)==0))
					{
						count++;
						bal=a.get_balance();
						int g;
						cout<<"Hello "<<nam<<"!!"<<endl;
						cout<<"Withdraw money (Press 1)"<<endl;
						cout<<"Deposite money (Press 2)"<<endl;
						cout<<"Enter your choice: ";
						cin>>g;
						if(g==1)
						{
							float blnc;
							Checking_Account Ca;
							float wit;
							system("cls");
							cout<<"Current Balance: $"<<bal<<"\nNote: There are withdraw charges as well please visit your nearest bank for detials. "<<endl;
							cout<<"Enter amount that you want to withdraw: ";
							cin>>wit;
							float cmp;
							cmp=wit+5;	
							if(cmp<bal)
							{
								blnc=Ca.makewithdrawl(wit,bal);
								a.set_bal(blnc);
								file.seekg(file.tellg()-sizeof(a));
								file.write((char*)&a,sizeof(a));
								file.close();
								break;
							}
							else
							{
								cout<<"Insuifficient Balance!!\n";
							}
						}
						else if(g==2)
						{
							float dep,blnc;
							Saving_Account Sa;
							cout<<"Enter amount that you want to deposite: ";
							cin>>dep;
							blnc=Sa.makedeposite(dep,bal);
							a.set_bal(blnc);
							file.seekg(file.tellg()-sizeof(a));
							file.write((char*)&a,sizeof(a));
							file.close();
							break;
						}
						else
						{
							cout<<"Wrong choice!!"<<endl;
						}
					}
					file.read((char*)&a,sizeof(a));
				}
				if(count==0)
				{
					cout<<endl<<"Sorry entered bank detail is incorrect"<<endl;
					file.close();	
				}
			}
		}
		
};


void menu()
{
	system("pause");
	system("cls");
	cout<<"\t\t\t Welcome to the Digital Bank"<<endl;
	cout<<"___________________________________________________________________________"<<endl;
	cout<<"\nCreate new bank account 	(Press 1)"<<endl;
	cout<<"Transaction		 	(Press 2)"<<endl;
	cout<<"View your banking information   (Press 3)"<<endl;
	cout<<"View all account data 		(Press 4)"<<endl;
	cout<<"Close your account 		(Press 5)"<<endl;
	cout<<"Exit 				(Press 6)"<<endl;
}

void createAcc()
{
	Account a;
	fstream file;
	char ch;
	file.open("Account.txt",ios::app | ios::binary);
	if(!file)
	{
		cout<<"can't create a file"<<endl;
		exit(0);
	}
	a.createAccount();
	file.write((char*)&a,sizeof(a));
	cout<<endl;
	file.close();
}


void makingDeposite_Withdraw()
{
	Checking_Account Ca;
	Ca.account_check();
}


void viewRecord()
{
	Account a;
	a.display();
}

void viewData()
{
	Account a;
	a.displayData();
}

void delRec()
{
	Account a;
	a.delRecord();
}


int main()
{
	Account a;
	int choice;
		menu();
		cout<<endl<<"Choose any of the following options : ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
			case 1 :
				createAcc();
				break;
			case 2:
				makingDeposite_Withdraw();
				break;
			case 3:
				viewRecord();
				break;
			case 4:
				viewData();
				break;
			case 5:
				delRec();
				break;
			case 6:
				exit(0);
			default:
				cout<<"wrong choice!!!"<<endl;
				break;
		}
	main();
}
