#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    // checks to see if there is a number argument

    if (argc == 2)
    {
    // checks to see if argument contains numbers
        for(int z = 0, m = strlen(argv[1]); z < m; z++)
        {
            if (isdigit(argv[1][z]))
            {
                printf("no bueno.\n");
                return 1;
            } 
        }
        // this is the message
        string message = GetString();

        int key_length = strlen(argv[1]);
        int key_num = 0;
       

        // begin loop 
        for(int x = 0, n = strlen(message);x < n; x++)
        {
            char d = tolower(argv[1][key_num % key_length]);
            // checks to see if it is an alphabetical char. if not it prints
            if ( !isalpha(message[x])) 
            { 
                printf("%c", message[x]);
            }
            // checks to see if char is lowercase.
            // if lowercase will print with the following
            
            if (islower(message[x]))
            {
                printf("%c", (((message[x] - 97) + (d - 97))) % 26 + 97);
                key_num++;
            }
            // checks to see if char is uppercase
            // if uppercase will print with the following
            if (isupper(message[x]))
            {

                printf("%c", (((message[x] - 65) + (d - 97))) % 26 + 65);
                key_num++;
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("no bueno\n");
        return 1;
    }
}
