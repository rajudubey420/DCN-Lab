#include <stdio.h>
#include <math.h>
#include <time.h>
#include <dos.h>
#define FRAME_TIME 250
main()
{
    float S1, S2, G, J, val[100] ;
    int I, n, K, delay ;
    void wait() ;
    clrscr() ;
    printf("Please Give the Total Load : ");
    scanf("%d", &n);
    printf("Please Enter the value of load \n");
    for (I=0; I<n; I++)
    {
        scanf("%f", &val[I]);
    }
    clrscr();
    printf("\nOUTPUT 1: (THROUGHPUT Vs LOADCURVE)\n\n");
    printf("s=g*exp(-G) FOR SLOTTED ALOHA * \n");
    printf("s=g*exp(-2G) FOR PURE ALPHA #\n");
    printf("\n------ (THROUGHPUT PER FRAME TIME)----\n");
    for(K=0; K<n; K++)
    {
        G=val[K];
        S1 = G * exp (-G);
        S2 = G * exp(-2 * G);
        printf("%1.3f", G );
        for (I=0; I <=S1*20; I++)
        {
            printf(" ");
        }
        printf("*");
        for(I=S2*20; I<=S2*75; I++ )
        {
            printf(" ");
        }
        printf("#\n");
    }
    printf("G (ATTEMPTS PER PACKET TIME) \n\n");
    wait() ;
    getch() ;
    clrscr() ;
    printf("\nOUTPUT 2 (DELAY Vs THROUGHPUT) \n\n");
    printf("\n-----(THOUGHPUT PER FRAME TIME)----\n");
    for(K=0; K<n; K++)
    {
        G=val[K];
        S1 = G * exp (-G);
        printf("3");
        for (I=0; I <=S1*2.7; I++)
        {
            printf(" ");
        }
        printf("*\n");
    }
    printf("\n");
    printf("---- DELAY -----");
    wait();
    getch();
    clrscr();
}
void wait()
{
    sound(440);
    delay(300);
    nosound();
}
