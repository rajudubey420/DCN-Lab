
#include<stdio.h>
#include<string.h>

// Function to find out the Class
char findClass(char str[])
{
    // storing first octet in arr[] variable
    char arr[4];
    int i = 0;
    while (str[i] != '.')
    {
        arr[i] = str[i];
        i++;
    }
    i--;

    // converting str[] variable into number for
    // comparison
    int ip = 0, j = 1;
    while (i >= 0)
    {
        ip = ip + (str[i] - '0') * j;
        j = j * 10;
        i--;
    }

    // Class A
    if (ip >=1 && ip <= 126)
        return 'A';

    // Class B
    else if (ip >= 128 && ip <= 191)
        return 'B';

    // Class C
    else if (ip >= 192 && ip <= 223)
        return 'C';

    // Class D
    else if (ip >= 224 && ip <= 239)
        return 'D';

    // Class E
    else
        return 'E';
}



// Driver function is to test above function
int main()
{
    char str[] = "192.226.12.11";
    char ipClass = findClass(str);
    printf("Given IP address belongs to Class %c\n",
                                           ipClass);
    return 0;
}
