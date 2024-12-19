#include <stdio.h>

/*Function numPathsHome calculates the number of paths to take back home*/
int numPathsHome(int street, int avenue) {
    if (street == 1 || avenue == 1) {
        return 1;
    } else {
        return numPathsHome(street - 1, avenue) + numPathsHome(street, avenue - 1);
    }
}
/*Function main begins program execution*/
int main() {
    int street, avenue;
    printf("Enter the street number: ");
    scanf("%d", &street);
    printf("street: %d\n", street);
    printf("Enter the avenue number: ");
    scanf("%d", &avenue);
    printf("avenue: %d\n", avenue);
    printf("Number of paths to take back home: %d\n", numPathsHome(street, avenue));
    return 0;
}
