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

        // this is the cryptographic key
        int key = atoi(argv[1]);

        // this is the message
        string message = GetString();
      
        // begin loop 
        for(int x = 0, n = strlen(message);x < n; x++)
        {
            // checks to see if it is an alphabetical char. if not it prints
            if ( !isalpha(message[x])) 
            { 
                printf("%c", message[x]); 
            }
            // checks to see if char is lowercase.
            // if lowercase will print with the following
            
            if (islower(message[x]))
            {
                printf("%c", ((message[x] + key - 97) % 26) + 97);
            }
            // checks to see if char is uppercase
            // if uppercase will print with the following
            if (isupper(message[x]))
            {
                printf("%c", ((message[x] + key - 65) % 26) + 65);
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
