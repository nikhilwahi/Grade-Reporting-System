#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
class data
{
	private:
		char name[255];
		float phy,chem,math,eng,cmpsci;
	public:
		void input();
		void output(int i);
		void searchname();
		void inputvar(float &var,char subname[25]);
		char* retname() {return name;}
		float retphy() {return phy;}
		float retchem() {return chem;}
		float retmath() {return math;}
		float reteng() {return eng;}
		float retcmpsci() {return cmpsci;}
};
//landing screen
void intro()
{
	int i;
	gotoxy(1,1);cout<<"Ú";
	gotoxy(80,1);cout<<"¿";
	gotoxy(1,24);cout<<"À";
	gotoxy(80,24);cout<<"Ù";
	for(i=2;i<=79;i++)
	{
		gotoxy(i,1);
		cout<<"Ä";
	}
	for(i=2;i<=23;i++)
	{
		gotoxy(80,i);
		cout<<"³"<<endl;
	}
	for(i=79;i>1;i--)
	{
		gotoxy(i,24);
		cout<<"Ä";
	}
	for(i=23;i>1;i--)
	{
		gotoxy(1,i);
		cout<<"³";
	}

	gotoxy(15,11);cout<<"É";
	gotoxy(15,12);cout<<"º";
	gotoxy(15,13);cout<<"È";
	for(i=16;i<=65;i++)
	{
		gotoxy(i,11);cout<<"Í";
	}
	for(i=16;i<=65;i++)
	{
		gotoxy(i,13);cout<<"Í";
	}
	gotoxy(66,11);cout<<"»";
	gotoxy(66,12);cout<<"º";
	gotoxy(66,13);cout<<"¼";
	gotoxy(30,16);cout<<"Loading... Please Wait!";

	delay(200);
	for(i=16;i<=65;i++)
	{
		delay(40);
		gotoxy(i,12);cout<<"Û";
	}
	gotoxy(30,16);cout<<"Press Enter To Continue!";
}

void data::inputvar(float &var , char subname[25])
{
	while(var>100 | var<0)
	{
		cout<<"Marks should be in the range of 0-100.";
		getch();
		cout<<endl<<endl<<"Enter "<<subname<<" marks -->";
		cin>>var;
	}
}
//input menu
void data::input()
{
	clrscr();
	cout<<"Enter name -->";
	gets(name);

	cout<<endl<<"Enter physics marks -->";
	cin>>phy;
	inputvar(phy,"physics");

	cout<<endl<<"Enter chemistry marks -->";
	cin>>chem;
	inputvar(chem,"chemistry");

	cout<<endl<<"Enter maths marks -->";
	cin>>math;
	inputvar(math,"maths");

	cout<<endl<<"Enter english marks -->";
	cin>>eng;
	inputvar(eng,"english");

	cout<<endl<<"Enter computer science marks -->";
	cin>>cmpsci;
	inputvar(cmpsci,"computer science");
	clrscr();
}
//prints grades of one student
void data::output(int i)
{
	gotoxy(7,i+7);cout<<name;
	gotoxy(22,i+7);cout<<phy;
	gotoxy(32,i+7);cout<<chem;
	gotoxy(42,i+7);cout<<math;
	gotoxy(52,i+7);cout<<eng;
	gotoxy(62,i+7);cout<<cmpsci;
}
/*creating the file*/
void createfile()
{
	ofstream f;
	data a;
	int i,n;
	f.open("data.dat",ios::binary);
	cout<<"Enter no. of students -->";
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cout<<"STUDENT "<<i;
		a.input();
		f.write((char*)&a,sizeof(a));
	}
	f.close();
}
/*this is to read the grades of all students*/
void readfile()
{
	clrscr();
	ifstream f;
	data a;
	int i=0;
	f.open("data.dat",ios::binary);
	gotoxy(5,5);cout<<"__NAME__";
	gotoxy(20,5);cout<<"__PHY__";
	gotoxy(30,5);cout<<"__CHEM__";
	gotoxy(40,5);cout<<"__MATH__";
	gotoxy(50,5);cout<<"__ENG__";
	gotoxy(60,5);cout<<"__COMPSCI__";
	while(f)
	{
		f.read((char*)&a,sizeof(a));
		if(f.eof())
			break;

		a.output(i); //this method is called to print the grades of the student at current index location
		i=i+1;
	}
	f.close();
}
/*add rmenu*/
void addrecord()
{
	fstream f;
	data a;
	int i,n;
	f.open("data.dat",ios::app|ios::binary);
	cout<<"Number of records to be added -->";
	cin>>n;
	for(i=1;i<=n;i++)
	{
		a.input();
		f.write((char*)&a,sizeof(a));
	}
	f.close();
}
/*delete menu*/
void delrecord()
{
	fstream f1,f2;
	data a;
	char tempname[255];
	cout<<"Enter the name to be deleted -->";
	gets(tempname);
	f1.open("data.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	while(f1)
	{
		f1.read((char*)&a,sizeof(a));
		if(f1.eof())
			break;

		if(strcmpi(tempname,a.retname())!=0)
			f2.write((char*)&a,sizeof(a));
	}
	f1.close();
	f2.close();
	remove("data.dat");
	rename("temp.dat","data.dat");
}
/*editing menu*/
void editrecord()
{
	fstream f1,f2;
	data a;
	char tempname[255];
	cout<<"Enter the name of the person whose record is to be edited -->";
	gets(tempname);
	f1.open("data.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	while(f1)
	{
		f1.read((char*)&a,sizeof(a));
		if(f1.eof())
			break;

		if(strcmpi(tempname,a.retname())!=0)
			f2.write((char*)&a,sizeof(a));
		else
		{
			a.input();
			f2.write((char*)&a,sizeof(a));
		}
	}
	f1.close();
	f2.close();
	remove("data.dat");
	rename("temp.dat","data.dat");
}
/*printing the report card of one student*/
void indrepcard()
{
	fstream f;
	data a;
	char tname[255];
	int i;
	f.open("data.dat",ios::in|ios::binary);
	cout<<"Enter name to be searched -->";
	gets(tname);
	while(f)
	{
		if(f.eof())
			break;

		f.read((char*)&a,sizeof(a));
		if(strcmpi(tname,a.retname())==0)
		{
			clrscr();
			gotoxy(1,1);cout<<"É";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,1);cout<<"Í";
			}
			gotoxy(1,2);cout<<"º";
			gotoxy(1,3);cout<<"Ì";
			gotoxy(80,2);cout<<"º";
			gotoxy(80,3);cout<<"¹";
			for(i=3;i<=79;i++)
			{
				gotoxy(i,3);cout<<"Í";
			}
			for(i=4;i<=23;i++)
			{
				gotoxy(1,i);cout<<"º";
			}
			gotoxy(1,24);cout<<"È";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,24);cout<<"Í";
			}
			gotoxy(2,3);cout<<"Í";
			gotoxy(80,24);cout<<"¼";
			gotoxy(80,1);cout<<"»";
			for(i=4;i<=23;i++)
			{
				gotoxy(80,i);cout<<"º";
			}
			gotoxy(30,6);cout<<"ST. COLUMBA'S SCHOOL";
			gotoxy(35,2);cout<<"REPORT CARD";
			gotoxy(32,9);cout<<"1, Ashoke Place";
			gotoxy(32,12);cout<<"New Delhi-110001";
			gotoxy(34,17);cout<<"NAME --> "<<a.retname();

			getch();
			clrscr();

			gotoxy(1,1);cout<<"É";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,1);cout<<"Í";
			}
			gotoxy(1,2);cout<<"º";
			gotoxy(1,3);cout<<"Ì";
			gotoxy(80,2);cout<<"º";
			gotoxy(80,3);cout<<"¹";
			for(i=3;i<=79;i++)
			{
				gotoxy(i,3);cout<<"Í";
			}
			for(i=4;i<=23;i++)
			{
				gotoxy(1,i);cout<<"º";
			}
			gotoxy(1,24);cout<<"È";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,24);cout<<"Í";
			}
			gotoxy(2,3);cout<<"Í";
			gotoxy(80,24);cout<<"¼";
			gotoxy(80,1);cout<<"»";
			for(i=4;i<=23;i++)
			{
				gotoxy(80,i);cout<<"º";
			}
			gotoxy(35,2);cout<<"REPORT CARD";
			gotoxy(35,5);cout<<"MARKS";
			gotoxy(5,8);cout<<"PHYSICS          --> "<<a.retphy();
			gotoxy(5,10);cout<<"CHEMISTRY        --> "<<a.retchem();
			gotoxy(5,12);cout<<"MATHEMATICS      --> "<<a.retmath();
			gotoxy(5,14);cout<<"ENGLISH          --> "<<a.reteng();
			gotoxy(5,16);cout<<"COMPUTER SCIENCE --> "<<a.retcmpsci();
			gotoxy(10,20);cout<<"PERCENTAGE --> ";
			cout<<(a.retphy()+a.retchem()+a.reteng()+a.retmath()+a.retcmpsci())/5;
			getch();
			clrscr();

			gotoxy(1,1);cout<<"É";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,1);cout<<"Í";
			}
			gotoxy(1,2);cout<<"º";
			gotoxy(1,3);cout<<"Ì";
			gotoxy(80,2);cout<<"º";
			gotoxy(80,3);cout<<"¹";
			for(i=3;i<=79;i++)
			{
				gotoxy(i,3);cout<<"Í";
			}
			for(i=4;i<=23;i++)
			{
				gotoxy(1,i);cout<<"º";
			}
			gotoxy(1,24);cout<<"È";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,24);cout<<"Í";
			}
			gotoxy(2,3);cout<<"Í";
			gotoxy(80,24);cout<<"¼";
			gotoxy(80,1);cout<<"»";
			for(i=4;i<=23;i++)
			{
				gotoxy(80,i);cout<<"º";
			}
			gotoxy(35,2);cout<<"REPORT CARD";

			for(i=1;i<=(a.retphy()/2);i++)
			{
				gotoxy(15+i,4);cout<<"Ü";
			}
			gotoxy(3,4);cout<<"PHY";

			for(i=1;i<=(a.retchem()/2);i++)
			{
				gotoxy(15+i,8);cout<<"Ü";
			}
			gotoxy(3,8);cout<<"CHEM";

			for(i=1;i<=(a.retmath()/2);i++)
			{
				gotoxy(15+i,12);cout<<"Ü";
			}
			gotoxy(3,12);cout<<"MATH";

			for(i=1;i<=(a.reteng()/2);i++)
			{
				gotoxy(15+i,16);cout<<"Ü";
			}
			gotoxy(3,16);cout<<"ENG";

			for(i=1;i<=(a.retcmpsci()/2);i++)
			{
				gotoxy(15+i,20);cout<<"Ü";
			}
			gotoxy(3,20);cout<<"CMPSCI";

			for(i=14;i<=66;i++)
			{
				gotoxy(i,22);cout<<"Â";
				if(i==16)
				{
					gotoxy(i,23);cout<<"0";
				}
				else if(i==21)
				{
					gotoxy(i,23);cout<<"10";
				}
				else if(i==26)
				{
					gotoxy(i,23);cout<<"20";
				}
				else if(i==31)
				{
					gotoxy(i,23);cout<<"30";
				}
				else if(i==36)
				{
					gotoxy(i,23);cout<<"40";
				}
				else if(i==41)
				{
					gotoxy(i,23);cout<<"50";
				}
				else if(i==46)
				{
					gotoxy(i,23);cout<<"60";
				}
				else if(i==51)
				{
					gotoxy(i,23);cout<<"70";
				}
				else if(i==56)
				{
					gotoxy(i,23);cout<<"80";
				}
				else if(i==61)
				{
					gotoxy(i,23);cout<<"90";
				}
				else if(i==66)
				{
					gotoxy(i,23);cout<<"100";
				}

				else
				{
					gotoxy(i,22);cout<<"Ä";
				}
			}
			for(i=4;i<=22;i++)
			{
				gotoxy(14,i);cout<<"³";
			}

			getch();
			break;
		}
		else
		{
			clrscr();
			gotoxy(1,1);cout<<"É";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,1);cout<<"Í";
			}
			gotoxy(1,2);cout<<"º";

			gotoxy(1,3);cout<<"º";
			gotoxy(80,2);cout<<"º";
			gotoxy(80,3);cout<<"º";
			for(i=4;i<=23;i++)
			{
				gotoxy(1,i);cout<<"º";
			}
			gotoxy(1,24);cout<<"È";
			for(i=2;i<=79;i++)
			{
				gotoxy(i,24);cout<<"Í";
			}
			gotoxy(80,24);cout<<"¼";
			gotoxy(80,1);cout<<"»";
			for(i=4;i<=23;i++)
			{
				gotoxy(80,i);cout<<"º";
			}
			gotoxy(28,12);cout<<"Error 404: Name Not Found";
		}
	}
	f.close();
}
/*main method
this is the menu */
void main()
{
	data a;
	char find[25];
	int choice,n,i;
	clrscr();
	intro();
	getch();
	clrscr();
	do
	{
		gotoxy(1,1);cout<<"Ú";
		gotoxy(80,1);cout<<"¿";
		gotoxy(1,24);cout<<"À";
		gotoxy(80,24);cout<<"Ù";
		for(i=2;i<=79;i++)
		{
			gotoxy(i,1);
			cout<<"Ä";
		}
		for(i=2;i<=23;i++)
		{
			gotoxy(80,i);
			cout<<"³"<<endl;
		}
		for(i=79;i>1;i--)
		{
			gotoxy(i,24);
			cout<<"Ä";
		}
		for(i=23;i>1;i--)
		{
			gotoxy(1,i);
			cout<<"³";
		}

		gotoxy(30,5);cout<<"______MENU______" <<endl;
		gotoxy(25,10);cout<<"1. Input data";
		gotoxy(25,11);cout<<"2. Show data for all";
		gotoxy(25,12);cout<<"3. Add data";
		gotoxy(25,13);cout<<"4. Delete data";
		gotoxy(25,14);cout<<"5. Edit data";
		gotoxy(25,15);cout<<"6. Individual report card";
		gotoxy(25,16);cout<<"7. Exit";
		gotoxy(25,20);cout<<"Please input your choice :";
		cin>>choice;
		getch();
		clrscr();
		switch(choice)
		{
			case 1:createfile();
			       getch();
			       clrscr();
				break;
			case 2:readfile();
			       getch();
			       clrscr();
				break;
			case 3:addrecord();
			       getch();
			       clrscr();
				break;
			case 4:delrecord();
			       getch();
			       clrscr();
				break;
			case 5:editrecord();
			       getch();
			       clrscr();
				break;
			case 6:indrepcard();
			       getch();
			       clrscr();
				break;
			case 7: break;
			default:gotoxy(25,22);
				cout<<"Please enter a valid option";
				getch();
				clrscr();
		}
	}
	while(choice!=7);
}