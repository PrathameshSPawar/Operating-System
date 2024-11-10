#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

void banker(int allo[][10],int max[][10],int ava[10],int res,int pro)
{
	int need[pro][res];
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<res;j++)
		{
			need[i][j]=max[i][j]-allo[i][j];
		}
	}
	
	bool finish[10]={false};
	int safeSeq[10];	
	int count=0;
	while(count<pro)
	{
		bool found=false;
		for(int p=0;p<pro;p++)
		{
			if(!finish[p])
			{
				int j;
				for(j=0;j<res;j++)
				{
					if(need[p][j]>ava[j])
					{
						break;
					}
				}
				
				if(j==res)
				{
					for(int j=0;j<res;j++)
					{
						ava[j]+=allo[p][j];
					}
					safeSeq[count++]=p;
					finish[p]=true;
					found=true;	
				}
			}
		}
		if(!found)
		{
			cout<<"\nSystem is in An unsafe State: "<<endl;
			return;
		}
	}
	
	cout<<"\nSystem is in safe state: "<<endl;
	for(int i=0;i<pro;i++)
	{
		cout<<"P"<<safeSeq[i]<<" ";
	}
	cout<<endl;
	return;
		
		
}

int main()
{
	int res,pro;
	cout<<"\nEnter the count of resources: ";
	cin>>res;

	cout<<"\nEnter the total Processes: ";
	cin>>pro;
	
	int allo[10][10];
	cout<<"\nEnter the Process in Allocation Matrix: ";
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<res;j++)
		{
			cin>>allo[i][j];
		}
	}

	int max[10][10];
	cout<<"\nEnter the Maximum Matrix: ";
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<res;j++)
		{
			cin>>max[i][j];
		}
	}

	int ava[10];
	cout<<"\nEnter the Available Resources: ";
	for(int i=0;i<res;i++)
	{
		cin>>ava[i];
	}
	
	banker(allo,max,ava,res,pro);
	return 0;
}
