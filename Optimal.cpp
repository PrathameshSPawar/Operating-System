#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

int findopti(int frames,vector<int>& frame,vector<int>& pages,int index,int n)
{
	int farest=index,pos=-1;
	for(int i=0;i<frames;i++)
	{
		int j;
		for(j=index;j<n;j++)
		{
			if(frame[i]==pages[j])
			{
				if(farest<j)
				{
					farest=j;
					pos=i;
					break;
				}
			}
		}
		if(j==n)
		{
			return i;
		}
	}
	
	return (pos == -1) ? 0 : pos;
} 

void lru(int n, vector<int>& pages, int frames)
{
	vector<int> frame(frames,-1);
	int pageF=0;
	
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
			bool possible=false;
			for(int j=0;j<frames;j++)
			{
				if(frame[j]==-1)
				{
					frame[j]=pages[i];
					possible=true;
					pageF++;
					break;
				}
			}
			if(!possible)
			{
				int pos=findopti(frames,frame,pages,i+1,n);
				frame[pos]=pages[i];
				pageF++;
			}
		}
		
		cout<<"\nFrames "<<i+1<<" : ";
		for(int j=0;j<frames;j++)
		{
			if(frame[j]==-1)
			{
				cout<<"-";
			}else{
				cout<<frame[j];
			}
		}
	}
	cout<<"\nPages faults: "<<pageF;

}

int main()
{
	int n;
	cout<<"\nEnter the count of pages: ";
	cin>>n;
	
	vector<int> pages(n);
	cout<<"\nEnter the Pages:: ";
	for(int i=0;i<n;i++)
	{
		cout<<"\nPage "<<i+1<<" : ";
		cin>>pages[i]; 
	}
	
	int frames;
	cout<<"\nEnter the frame size : ";
	cin>>frames;
	
	lru(n,pages,frames);	
}
