#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
// Main function does not take any argumentes
int main(void) {
   
    // Setting name into var 
    string name = GetString();

    // Getting length of string
    int str_length = strlen(name);

    // Printing first initial
    printf("%c", toupper(name[0]));

    // Looping through to find the space before the last name
    for(int  x = 0; x < str_length; x++){
        if(name[x] == ' ')
        {
            // Printing the initial of the last name
            printf("%c", toupper(name[x+1]));
        }
    }
    // Line break
   printf("\n"); 
}
