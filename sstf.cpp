#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int sstf(vector<int>& req,int n,int head)
{
	int seek=0;
	int complete[n]={0};
	int dist=0;
	
	for(int i=0;i<n;i++)
	{
		int index=-1;
		int min=999;
		for(int j=0;j<n;j++)
		{
			if(complete[j]!=1)
			{
				dist=abs(req[j]-head);
				if(dist<min)
				{
					index=j;
					min=dist;
				}
			}	
		}
		seek+=min;
		complete[index]=1;
		head=req[index];
		cout<<"\nHead moves to "<<head;
	}
	return seek;
}

int main()
{
	int n,head;
	cout<<"\nEnter the Total Requests: ";
	cin>>n;
	vector<int> req(n);
	cout<<"\nEnter the requests one by one:";
	for(int i=0;i<n;i++)
	{
		cin>>req[i];
	}
	cout<<"\nEnter the Head position: ";
	cin>>head;
	int ans=sstf(req,n,head);
	cout<<"\nSeek time is: "<<ans;
	double avg=ans/n;
	cout<<"\nAverage seek Time is: "<<avg;
	return 0;
}
