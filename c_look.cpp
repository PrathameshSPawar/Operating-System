#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

int clook(int req[],int n,int head)
{
	int seek_time=0;
	int curr_head=head;
	
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(req[i]>req[j])
			{
				int temp=req[i];
				req[i]=req[j];
				req[j]=temp;
			}
		}
	}
	
	int i;
	for(i=0;i<n;i++)
	{
		if(req[i]>=curr_head)
		{
			seek_time+=abs(req[i]-curr_head);
			curr_head=req[i];
			cout<<"\nHead Moves to: "<<curr_head;
		}
	}
	
	if(i>0 && req[i-1]!=curr_head)
	{
		seek_time+=abs(curr_head-req[0]);
		curr_head=req[0];
		cout<<"Head Moves to: "<<curr_head;
	}
	
	for(int i=0;i<n && req[i]<head;i++)
	{
		seek_time+=abs(req[i]-curr_head);
		curr_head=req[i];
		cout<<"Head moves to: "<<curr_head;
	}
	return seek_time;
}


int main()
{
	int n,head;
	cout<<"\nEnter the total requests & initial head :: ";
	cin>>n>>head;

	int req[n];
	for(int i=0;i<n;i++)
	{
		cin>>req[i];	
	}
	
	int seek=clook(req,n,head);
	float average=seek/n;

	cout<<"\nSeek time: "<<seek;
	cout<<"Average time: "<<average;
	
	return 0;
}
