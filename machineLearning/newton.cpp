/* 
 Author: Song Yuhao/lampson
 Date  : 2015-4-30
 Input : A dataset that contains training data, income && profit
	________________________________
  price per share		|   income   |  profit
	________________________________
	 0.09			|  5811.89   |  723.73		(2010-06-30)
	________________________________
   	 0.33			|  14421.93  |  2766.96		(2010-12-31)
	________________________________
	 0.047			|  6565.74   |  591.51		(2011-06-30)
	_________________________________
	 0.22	    		| 15808.84   |  2748.51		(2011-12-31)
	_________________________________
	 0.034			|  6816.92   |  427.39		(2012-06-30)
	_________________________________
	 0.096	    		|  15446.51  |  1605.50		(2012-12-31)
	_________________________________
	 0.04			|  6002.91   |  496.79		(2013-06-30)
	_________________________________
	 0.53			|  46342.22  |  16708.62	(2013-12-31)
	_________________________________
 Output : Predict profit in 2014
		The ground-truth value is
			_________________________
	-0.032		| 6002.91  |  -458.09
			_________________________
	0.59		| 47952.72 |  20162.84
			_________________________
*/

/*
 * Newton method: it is used to optimize  data.
*/

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	float trainData[8][3] = {		  
							  {0.09,  5811.89,  723.73},
							  {0.33,  14421.93, 2766.96},
							  {0.047, 6565.74,  591.51},
							  {0.22,  15808.84, 2748.51},
							  {0.034, 6816.92,  427.39},
							  {0.096, 15446.51, 1605.5},
							  {0.04,  6002.91,  496.79},
							  {0.53,  46342.22, 16708.62}
							 };
	
	//hypothesis result     profit = h(x) = theta_0 + theta_1*x_1 + theta_2*x_2
	//inititial state theta_0 = theta_1 = theta_2 = 0
	float theta[3] = {0.000004,0.000002,0.18};
	float E = 0;
	float alpha = 0.000000001;

	float theta_new[3] = {0,0,0};

	//record the step length
	float delta[3] = {0,0,0};
	float eps = 50;
	int count = 1;
	int flag = 0;
	//loss function
	float jx = 0;
	/*
	   train theta
	*/
	do
	{
			//update parameters theta[0,1,2]
			for(int j = 0; j < 3; j++)
			{
				for(int i = 0; i < 8; i++)
				{	
					//sum of differences, jx could be placed out of the j loop to reduce computation
					jx = theta[0] + theta[1] * trainData[i][0] + theta[2] * trainData[i][1] - trainData[i][2];
			
					if(j == 0)
						E += jx;
					else
					{
						E += jx / trainData[i][j-1];
					}
				}
				theta_new[j] = theta[j] - E / 8;

				//test the step length
				delta[j] = fabs(theta_new[j] - theta[j]);
				
				E = 0;
			}
			

			//determine whether stop the program
			flag = 0;
			for(int m = 0; m < 3; m++)
			{
				if(delta[m] < eps)
				{
					flag ++;
				}
			}
			if(flag < 3)
			{
				theta[0] = theta_new[0];
				theta[1] = theta_new[1];
				theta[2] = theta_new[2];
			}
			cout<<"The "<<count<<" time"<<endl;
			cout<<theta[0]<<endl;
			cout<<theta[1]<<endl;
			cout<<theta[2]<<endl;
			cout<<" "<<endl;
			
			count++;
//	}while(flag < 3);
	}while(count < 5);
	return 0;
}
