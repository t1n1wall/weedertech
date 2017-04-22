
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sys/time.h>


using namespace std;
struct timeval stop, start;
 string filen = "stdout";

int main(int argc, char* argv[])
{
	char  buffer[2];
	unsigned char a;
	int high=0,low=0;
	double duration;
	FILE * pFile;
	int debug=0,decodecount=0,decodedcount=0;
    for (int i = 1; i < argc; i++)
    {
        string sw = argv[i];
        if (sw == "-f") {
            i++;
            filen = argv[i];
        } else if (sw == "-c") {
            i++;
            decodecount = atoi(argv[i]);
        } else if (sw == "-d") {
            debug=1;
        } else {
        	i++;
        }
    }

	while (( (decodedcount < decodecount) | (decodecount==0 ) ) && (fgets(buffer, 2, stdin) != NULL) )
	{
		
		
		a = buffer[0];
		if ( a ==  0x48) {
			if ( debug == 1 ) std::cout << "High\n";
			high=1;
			low=0;
		}
		if ( a ==  0x4C) {
		if ( debug == 1 ) std::cout << "Low\n";
			low = 1;
			high = 0;
		}
		
		if (low == 1) {
			low = 0;
			gettimeofday(&start, NULL);
		}
		if (high == 1) {
			high = 0;
			gettimeofday(&stop, NULL);
			if (start.tv_usec ) {
				
				if (filen == "stdout")
                    {
                    printf("kwh %f\n", ( (60*60*1000) / ( (stop.tv_sec - start.tv_sec) * 1000.0f + (stop.tv_usec - start.tv_usec) / 1000.0f ) ) /1000 );
                } else {
                	pFile = fopen (filen.c_str(),"w");
			fprintf (pFile, "%f",( (60*60*1000) / ( (stop.tv_sec - start.tv_sec) * 1000.0f + (stop.tv_usec - start.tv_usec) / 1000.0f ) ) /1000 );
               		fprintf (pFile, " %ld\n", time(NULL));
		fclose (pFile);
                }
		decodedcount++;
	 if ( debug == 1 ) std::cout << "Decoded: ";
                        if ( debug == 1 ) std::cout <<  decodedcount ;
                        if ( debug == 1 ) std::cout <<  "\n";
	}
		}
		
	}
}

