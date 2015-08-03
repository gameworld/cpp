
#include <utility>
#include <iostream>


bool check5(int *arr)
{
	if(arr[0]+arr[1]+22+16+15!=arr[2]+arr[3]+arr[4]+21+20)
		return false;
	return true;
}

bool  check(int *arr)
{
	static int a[][5]={
			{0,0,	22,	16,	15},
			{0,	21,20,0,0},
			{25,19,13,0,0},
			{0,12	,0,0,24},
			{0,0,0,23,17}
	};

	a[0][0]=arr[0];
	a[0][1]=arr[1];
	a[1][0]=arr[2];
	a[1][3]=arr[3];
	a[1][4]=arr[4];
	a[2][3]=arr[5];
	a[2][4]=arr[6];
	a[3][0]=arr[7];
	a[3][2]=arr[8];
	a[3][3]=arr[9];
	a[4][0]=arr[10];
	a[4][1]=arr[11];
	a[4][2]=arr[12];

	int ret[12]={};


	int reta=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			ret[i]+=a[i][j];
		}
	}


	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			ret[i+5]+=a[j][i];
		}
	}

	ret[10]=a[0][0]+a[1][1]+a[2][2]+a[3][3]+a[4][4];
	ret[11]=a[4][0]+a[3][1]+a[2][2]+a[1][3]+a[0][4];

	reta=ret[0];
	for (int i=1;i<12;i++)
	{
		if(reta!=ret[i])
			return false;
	}

	return true;
}


void perm(int *arr,int start,int end)
{
	if(start>=end)
	{
		if(check(arr))
		{
			for(int i=0;i<end;i++)
			{
				std::cout<<arr[i]<<" ";
			}
			std::cout<<std::endl;
		}
	}
	else if((start >=5 and check5(arr)) || start<5 )
	{
		for(int j=start;j<end;j++)
		{
			std::swap(arr[j],arr[start]);+
			perm(arr,start+1,end);
			std::swap(arr[j],arr[start]);
		}
	}
}

int main()
{

	int a[]={1,2,3,4,5,6,7,8,9,10,11,14,18};
	perm(a,0,sizeof(a)/sizeof(a[0]));

}
