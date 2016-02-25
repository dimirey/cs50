#include <stdio.h>
#include <cs50.h>

int main() {
	
	int rows, rownum, counter ;
	int is_incorrect = 1;

// is_incorrect is a boolean value which controls the while loop

	while (is_incorrect) {
		printf("Height:\n");
		rows = GetInt();
        if (rows >= 0 && rows <= 23) {
			is_incorrect = 0;
		} else {
			printf("Retry:");
		rows = GetInt();
                if (rows >= 0 && rows <= 23) {
					is_incorrect = 0;
				}
		}
	}
	
// loop to control the height of the pyramid	
	for (rownum = 1; rownum <= rows; rownum++) {
		for (counter = 0; counter < rows - rownum ; counter++) {
			printf(" ");
		}
		for (counter = 0; counter < rownum; counter++) {
			if (counter == 0) {
				printf("##");
			} else {
				printf("#");
			}
			
		}
		printf("\n");
	}
	
}
