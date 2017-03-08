   #ifdef WIN32
   #include <Windows.h>
   #else
   #include <sys/time.h>
    #include <stdio.h>
    #include <math.h>
    #endif

    struct time_counter{
    	void set_start();
    	void get_time(const char* strs);
#ifdef WIN32
    _LARGE_INTEGER time_start;  //start time counting
    _LARGE_INTEGER time_over;   // end time counting
    double dqFreq;   //counter frequency
    LARGE_INTEGER f; //counter frequnecy
#else
    timeval time_start;
    timeval time_pend;
#endif
    double times;
    };


void time_counter::set_start()
{
#ifdef WIN32
	QueryPerformanceFrequncy(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);
#else
	gettimeofday(&time_start,NULL);
#endif
	return;
}

void time_counter::get_time(const char* strs)
{
#ifdef WIN32
	QueryPerformanceCounter(&time_over);
	times = ((time_over.QuadPart-time_start.QuadPart)/dqFreq);
	printf("%s time is %f seconds\n", strs,times);
#else
	gettimeofday(&time_pend,NULL);
	times = 1000000*(time_pend.tv_sec-time_start.tv_sec)+time_pend.tv_usec-time_start.tv_usec;
	times/=1000000;
	printf("%s time is %f seconds\n",strs,times);
#endif
    return;
}
