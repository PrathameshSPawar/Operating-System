#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

int findlru(vector<int>& times,int n)
{
	int min=times[0],pos=0;
	for(int i=0;i<n;i++)
	{
		if(times[i]<min)
		{
			min=times[i];
			pos=i;
		}
	}
	return pos;
} 

void lru(int n, vector<int>& pages, int frames)
{
	vector<int> frame(frames,-1);
	vector<int> times(frames,0);
	int count=0,pageF=0;
	
	for(int i=0;i<n;i++)
	{
		bool found=false;
		for(int j=0;j<frames;j++)
		{
			if(frame[j]==pages[i])
			{
				found=true;
				times[j]=++count;
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
					times[j]=++count;
					possible=true;
					pageF++;
					break;
				}
			}
			if(!possible)
			{
				int pos=findlru(times,frames);
				frame[pos]=pages[i];
				times[pos]=++count;
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
