#include <stdio.h>
#include <math.h>
#include <cs50.h>


int main() {
	float change = -1.0;
	int quarters = 0, dimes = 0, nickles = 0, pennies = 0, coins = 0, newchange;
	
	printf("how much change?\n");
	change = GetFloat();

while (change < 0) {
	printf("how much change?\n");
	change = GetFloat();
}
	
	newchange = roundf(change * 100);
	
//	printf("%d", newchange);

// Checks to see if any quarter values are available
	while (newchange >= 25){
		quarters++;
		newchange = newchange - 25;
	}
//	Checks to see if any dime values are available
	while (newchange >= 10) {
		dimes++;
		newchange = newchange - 10;
	}
//	Checks to see if any nickel values are available
	while (newchange >= 5) {
		nickles++;
		newchange = newchange - 5;
	}
//	Checks to see if any penny values are available
	while (newchange >= 1) {
		pennies++;
		newchange = newchange - 1;
	}
// Adds the coins together
	coins = quarters + dimes + nickles + pennies;
	printf("%d\n", coins);
}
