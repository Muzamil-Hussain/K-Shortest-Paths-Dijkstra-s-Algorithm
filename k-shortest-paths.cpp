// assignment4.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "assignment4.h"

int main()
{
	//list <int> l1;
	//l1.insert(3);
	//l1.insert(4);
	//l1.insert(5);
	//l1.insert(6);
	//l1.insert(7);
	//l1.displayList();
	//l1.remove();
	//l1.displayList();
	//l1.remove();
	//l1.remove();
	//l1.remove();
	//l1.displayList();
	//l1.insertAt(2,1);
	//l1.displayList();
	//l1.removeAt(1);
	//l1.displayList();
	//l1.insert(3);
	//l1.insert(4);
	//l1.insert(5);
	//l1.insert(6);
	//l1.insert(7);
	//l1.displayList();
	//l1.removeAt(4);
	//l1.displayList();
	//l1.removeAt(1);
	//l1.displayList();
	//	l1.removeAt(2);
	//l1.displayList();
	//l1.removeAt(1);
	//l1.displayList();
	//l1.removeAt(2);
	//l1.displayList();
	//l1.remove();
	//l1.displayList();

		//ifstream readFile ("GraphData.csv");
		//string line;
		//if (readFile.is_open())
		//{
		//	while (!readFile.eof())
		//	{
		//		getline(readFile, line,'\0');
		//		
		//	}
		//	cout<<line;
		//}
		//line+='\0';

	//    int count=0;
	//	for (int i=0;line[i]!='\0';i++)
	//	{
	//		if (line[i]==',')
	//		{
	//			count++;
	//			cout<<count;
	//		}
	//	}
	//	string *cities=new string [count];
	//	int j=0;
	//	for (int i=1;i<line.length();i++)
	//	{
	//		while (line[i]!=',' && line[i]!='\0')
	//		{
	//			cities[j]+=line[i];
	//			i++;
	//		}
	//			j++;	
	//	}
	////for (int j=0;j<count;j++)
	////	cout<<cities[j]<<endl;


	//graph <string,int> g("GraphData.csv");
	general<string,double>("GraphData.csv");
	return 0;
}
