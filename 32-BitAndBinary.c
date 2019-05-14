//************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read an IP address in binary form
// store it into an array of 4 strings of 8 chars each
// return 1 if read successfully or 0 if an error occurred
  int readBinary(char bin[4][8]) {
  char binString[80];
  int i, j;
  int nextChar = 0;
  int len;

// read line
  printf("Enter 32-bit IP address in binary form (xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx): ");
  fflush(stdout); //flushes the output, it is needed on some version of linux/unix before scanf
  scanf("%[^\r\n]", binString);

// store binary digits into bin array
  len = strlen(binString);
  for (i=0; i<4; i++) {
    if (nextChar >= len) {
      printf("Invalid input string (too short)\n");
      return 0;
    }
    for (j=0; j<8; j++) {
// skip spaces
      while (nextChar < len && binString[nextChar] == ' ')
        nextChar++;
// end of string? break the loop
      if (nextChar >= len) {
        printf("Invalid input string (too short)\n");
        return 0;
      }
      bin[i][j] = binString[nextChar];
      nextChar++;
// only 0 and 1 accepted
      if (bin[i][j] != '0' && bin[i][j] != '1') {
        printf("Invalid input string (not a binary number)\n");
        return 0;
      }
    }
  }

// return 1 (OK)
  return 1;
}

// read an IP address in decimal dotted form
// return 1 if ok or 0 if an error occurs
  int readIPAddress(int ipaddr[]) {
  char decstring[4][4];
  int i;

// read IP address as strings
  printf("Enter 32-bit IP address in dotted decimal notation (xxx.xxx.xxx.xxx): ");
  fflush(stdout);
  if (scanf("%[^.].%[^.].%[^.].%[^\r\n]", decstring[0], decstring[1], decstring[2], decstring[3]) < 4) {
    printf("Invalid input string (wrong IP address format)\n");
    return 0;
  }

// convert each string to integer
  for (i=0; i<4; i++) {
    ipaddr[i] = atoi(decstring[i]);  // atoi converts a string to an integer
    if (ipaddr[i] < 0 || ipaddr[i] > 255) {
      printf("Invalid input string (incorrect numbers for IP address)\n");
      return 0;
    }
  }

  return 1;
}





void convertBinToDec(char bin[4][8], int dec[]) {

  int i, j;

// convert each binary group to decimal number
  for (i=0; i<4; i++) {
    dec[i] = 0;
    for (j=0; j<8; j++) {
      dec[i] *= 2;
      if (bin[i][j] == '1')
        dec[i]++;
    }
  }

}

void convertDecToBin(int dec[], char bin[4][9]) {

  int i, j;

// convert each decimal group to binary
  for (i=0; i<4; i++) {
    for (j=7; j>=0; j--) {
      bin[i][j] = (dec[i] & 1) + '0';
      dec[i] /= 2;
    }
    bin[i][8] = 0;
  }

}



// convert to decimal
  convertBinToDec(bin, mask);
}



int main()
{
  int choice;
  char bin[4][8];
  char bin2[4][9];
  int ipaddr[4];

// temp string, used when reading - used to skip any remaining input after reading
// a menu option in the main menu.  The main menu scanf reads an integer.  If a temp
// string wasn't used, the next scanf trying to read a string would read an empty string
  char temp[80];

  do
  {
    printf("\nSelect from one of the choices:\n\n");
    printf("1) Convert from 32 bit binary ip form to dotted decimal ip form\n");
    printf("2) Convert from dotted decimal ip form to 32 bit binary ip form\n");
    printf("3) Quit the program\n");
    printf("\nEnter your choice: ");
    fflush(stdout);
    scanf("%d", &choice);
    scanf("%[^\n]", temp);
    scanf("%c", temp);

    switch (choice)
    {
      case (1) : // Convert from 32 bit binary ip form to dotted decimal ip form

                 if (!readBinary(bin))
                   break;

                 convertBinToDec(bin, ipaddr);

                 // print the resulting IP
                 printf("The address converted to decimal is: %d.%d.%d.%d\n", ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);

                 break;

      case (2) : // Convert from dotted decimal ip form to 32 bit binary ip form
                 if (!readIPAddress(ipaddr))
                   break;

                 convertDecToBin(ipaddr, bin2);

                 // print the results
                 printf("The address converted to binary is: %8s %8s %8s %8s\n", bin2[0], bin2[1], bin2[2], bin2[3]);
                 break;


      case (3) : system("clear"); //clear program
                 exit(0); // close program

      default  : printf("I don't know the option %d.\n", choice);
                 printf("Try again.\n");
                 break;
    }
  } while(1);
}
