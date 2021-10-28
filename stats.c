#include "stats.h"
#include <math.h>

int emailAlertCallCount = 0;
int ledAlertCallCount = 0;

struct Stats compute_statistics(const float* numberset, int setlength) {
    struct Stats s;
    int i;

    /*Check if the array has alements otherwise set min,max and average to NAN*/
    if(setlength == 0)
    {
        s.average = NAN;
        s.min = NAN;
        s.max = NAN;
    }
    else
    {
        /* If the array has even number of elements then
            initialize the first two elements as minimum and
            maximum */
		if (setlength%2 == 0)
		{
			if (numberset[0] > numberset[1])
			{
			  s.max = numberset[0];
			  s.min = numberset[1];
			}
			else
			{
			  s.min = numberset[0];
			  s.max = numberset[1];
			}
			s.average = numberset[0] + numberset[1];
			i = 2;  /* set the starting index for loop */
		}

		/* If the array has odd number of elements then
		initialize the first element as minimum and
		maximum */
		else
		{
			s.min = numberset[0];
			s.max = numberset[0];
			s.average = numberset[0];
			i = 1;  /* set the starting index for loop */
		}

		/* In the while loop, pick elements in pair and
		 compare the pair with max and min so far */
		while (i < setlength-1)
		{
			if (numberset[i] > numberset[i+1])
			{
			  if(numberset[i] > s.max)
				s.max = numberset[i];
			  if(numberset[i+1] < s.min)
				s.min = numberset[i+1];
			}
			else
			{
			  if (numberset[i+1] > s.max)
				s.max = numberset[i+1];
			  if (numberset[i] < s.min)
				s.min = numberset[i];
			}
			/*Unpate the average sumatory and index*/
			s.average += numberset[i];
			s.average += numberset[i+1];
			i += 2; /* Increment the index by 2 as two
					   elements are processed in loop */
		}
		/*Calculate the average*/
		s.average /= setlength;
    }
	return s;
}

void check_and_alert(float maxThreshold, alerter_funcptr alerters[], struct Stats computedStats, int alerters_size)
{
    /*Check the max value is under the maxThreshold*/
    if(maxThreshold < computedStats.max )
    {
    	/*Call all alerts callback*/
    	for(int index = 0U; index < alerters_size; index++)
		{
    		alerters[index]();
		}
    }
    else
    {
        /*Do nothig*/
    }
}


