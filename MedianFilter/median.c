#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define IMG_WIDTH (1920)
#define IMG_HEIGHT (1080)

typedef double FLOAT;
typedef unsigned int UINT32;
typedef unsigned long long int UINT64;
typedef unsigned char UINT8;

UINT8 header[22];
UINT8 R[IMG_HEIGHT*IMG_WIDTH];
UINT8 G[IMG_HEIGHT*IMG_WIDTH];
UINT8 B[IMG_HEIGHT*IMG_WIDTH];
UINT8 convR[IMG_HEIGHT*IMG_WIDTH];
UINT8 convG[IMG_HEIGHT*IMG_WIDTH];
UINT8 convB[IMG_HEIGHT*IMG_WIDTH];

int main(int argc, char *argv[])
{
    int fdin, fdout, bytesRead=0, bytesLeft, i, j;
    UINT64 microsecs=0, millisecs=0;
    FLOAT temp;
    
    if(argc < 3)
    {
       printf("Usage: sharpen input_file.ppm output_file.pgm\n");
       exit(-1);
    }
    else
    {
        if((fdin = open(argv[1], O_RDONLY, 0644)) < 0)
        {
            printf("Error opening %s\n", argv[1]);
        }
        //else
        //    printf("File opened successfully\n");

        if((fdout = open(argv[2], (O_RDWR | O_CREAT), 0666)) < 0)
        {
            printf("Error opening %s\n", argv[1]);
        }
        //else
        //    printf("Output file=%s opened successfully\n", "sharpen.ppm");
    }

    bytesLeft=21;

    //printf("Reading header\n");

    do
    {
        //printf("bytesRead=%d, bytesLeft=%d\n", bytesRead, bytesLeft);
        bytesRead=read(fdin, (void *)header, bytesLeft);
        bytesLeft -= bytesRead;
    } while(bytesLeft > 0);

    header[21]='\0';
    header[1]= '5'; // modify magic number for PGM format

    // Read RGB data
    for(i=0; i<IMG_HEIGHT*IMG_WIDTH; i++)
    {
        read(fdin, (void *)&R[i], 1); convR[i]=R[i];
        read(fdin, (void *)&G[i], 1); convG[i]=G[i];
        read(fdin, (void *)&B[i], 1); convB[i]=B[i];
    }

    UINT8 histogram[256];

    // Skip first and last row, no neighbors to convolve with
    for(i=1; i<((IMG_HEIGHT)-1); i++)
    {

        // Skip first and last column, no neighbors to convolve with
        for(j=1; j<((IMG_WIDTH)-1); j++)
        {
            int m;
            for (m=0; m<=255; m++) histogram[m]=0;

            histogram[G[((i-1)*IMG_WIDTH)+j-1]]++;
            histogram[G[((i-1)*IMG_WIDTH)+j]]++;
            histogram[G[((i-1)*IMG_WIDTH)+j+1]]++;
            histogram[G[((i)*IMG_WIDTH)+j-1]]++;
            histogram[G[((i)*IMG_WIDTH)+j]]++;
            histogram[G[((i)*IMG_WIDTH)+j+1]]++;
            histogram[G[((i+1)*IMG_WIDTH)+j-1]]++;
            histogram[G[((i+1)*IMG_WIDTH)+j]]++;
            histogram[G[((i+1)*IMG_WIDTH)+j+1]]++;

            int k=0, sum=0;

            while(sum<5){
                sum += histogram[k];
                k++;
            }
            k--;

	       convG[(i*IMG_WIDTH)+j]=(UINT8)k;

        }
    }

    write(fdout, (void *)header, 21);

    // Write RGB data
    for(i=0; i<IMG_HEIGHT*IMG_WIDTH; i++)
    {
        write(fdout, (void *)&convG[i], 1);
    }

    close(fdin);
    close(fdout);
 
}
