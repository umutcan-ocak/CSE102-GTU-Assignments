#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Structure Hospital definition*/
struct Hospital {
    char *name;
    char citiesServed[3];
};

/*Function numHospitals calculates the number of hospitals to construct*/
int numHospitals(char cities[], char locations[][3], int Hospital_num, int maxHospitals, int currentHospital, char coveredCities[], int numCoveredCities, int *usedHospitals) {
    int i;
    /*Base case*/
    if (maxHospitals == 0) {
        /*Check if all cities are covered*/
        if (numCoveredCities == strlen(cities)) {
            return 1;
        } else {
            /*Some cities are not covered*/
            return 0;
        }
    }
    if (currentHospital == Hospital_num) {
        return 0;
    }
    /*Check if the hospital can be constructed*/
    char newCoveredCities[strlen(cities) + 1];
    strcpy(newCoveredCities, coveredCities);
    for (i = 0; i < 3; i++) {

        /*Check if the city is covered by the hospital*/
        if (strchr(cities, locations[currentHospital][i]) != NULL && strchr(newCoveredCities, locations[currentHospital][i]) == NULL) {
            strncat(newCoveredCities, &locations[currentHospital][i], 1);
        }
    }

    /*Construct the hospital*/
    usedHospitals[currentHospital] = 1;
    if (numHospitals(cities, locations, Hospital_num, maxHospitals - 1, currentHospital + 1, newCoveredCities, strlen(newCoveredCities), usedHospitals)) {
        return 1;
    }
    usedHospitals[currentHospital] = 0;

    /*Do not construct the hospital*/
    if (numHospitals(cities, locations, Hospital_num, maxHospitals, currentHospital + 1, coveredCities, numCoveredCities, usedHospitals)) {
        return 1;
    }

    return 0;
}

int main() {
    /*Initialize the array of hospitals*/
    struct Hospital *hospitals;
    char *cities[] = { "A", "B", "C", "D", "E", "F" };
    char locations[][3] = { {'A', 'B', 'C'}, {'A', 'C', 'D'}, {'B', 'F'}, {'C', 'E', 'F'} };
    int maxHospitals;

    printf("Enter the maximum number of hospitals that can be constructed: ");
    scanf("%d", &maxHospitals);
    
    /*Allocate memory for the hospitals*/
    int Hospital_num = sizeof(locations) / sizeof(locations[0]);
    hospitals = (struct Hospital *)malloc(Hospital_num * sizeof(struct Hospital));

    if (hospitals == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    int i, j;

    int usedHospitals[Hospital_num];
    for (i = 0; i < Hospital_num; i++) {
        usedHospitals[i] = 0;
    }
    char coveredCities[7] = "";

    /*Initialize the hospitals*/
    for (i = 0; i < Hospital_num; i++) {
        hospitals[i].name = (char *)malloc(100 * sizeof(char));

        if (hospitals[i].name == NULL) {

            printf("Memory allocation for hospital name failed\n");
            for (j = 0; j < i; j++) {
                free(hospitals[j].name);
            }

            free(hospitals);
            return 1;
        }
        sprintf(hospitals[i].name, "Hospital - %d", i + 1);
        strncpy(hospitals[i].citiesServed, locations[i], 3);
        hospitals[i].citiesServed[3] = '\0';
    }
    
    /*Calculate the number of hospitals to construct*/
    int result = numHospitals("ABCDEF", locations, Hospital_num, maxHospitals, 0, coveredCities, 0, usedHospitals);
    if (maxHospitals > Hospital_num) {
    
    printf("\nYes, can offer health care to all!\n");
    printf("\nThere are more hospitals than necessary.\n\n");
    } 

    else if (result) {
        printf("\nYes, can offer health care to all!\n");
        for (i = 0; i < Hospital_num; i++) {
            if (usedHospitals[i]) {
                printf("%s\nHospital locations: %s\n", hospitals[i].name, hospitals[i].citiesServed);
            }
        }
    }
    else {
        printf("\nNo, some cities are not covered.\n");
    }

    for (i = 0; i < Hospital_num; i++) {
        free(hospitals[i].name);
    }

    free(hospitals);

    return 0;
}
