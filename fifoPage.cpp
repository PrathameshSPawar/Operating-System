#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

void fifo(int n,vector<int>& pages,int frames)
{
	vector<int> frame(frames,-1);
	int pageF=0,index=0;
	for(int i=0;i<n;i++)
	{
		bool found=false;
		for(int j=0;j<frames;j++)	
		{
			if(frame[j]==pages[i])
			{
				found=true;
				break;
			}
		}
		
		if(!found)
		{
			frame[index]=pages[i];
			index=(index+1)%frames;
			pageF++;
		}
		
		cout<<"\nPages Frames: ";
		for(int j=0;j<frames;j++)
		{
			if(frame[j]==-1)
			{
				cout<<"-";	
			}else{
				cout<<frame[j]<<" ";
			}
		}
		cout<<endl;
	}
	cout<<"\nPage Fault is: "<<pageF<<endl;
}

int main()
{
	int n;
	cout<<"\nEnter the count of Pages: ";
	cin>>n;
	
	cout<<"\nEnter the Pages one by one: ";
	vector<int> pages(n);
	for(int i=0;i<n;i++)
	{
		cout<<"\nPage "<<i+1<<": ";
		cin>>pages[i];
	}
	
	int frames;
	cout<<"\nEnter the total Frames: ";
	cin>>frames;
	fifo(n,pages,frames);
	
	return 0;
}
