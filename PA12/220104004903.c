#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customDict.h"     /*Include the header file*/

int main() {
    struct CustomDict* dict = create_dict();

    /*Add items to the dictionary*/
    read_csv(dict, "data.csv");
    int i;

    int choice;
    do {

        /*Print the menu*/
        printf("1- Print\n");
        printf("2- Search\n");
        printf("3- Sort\n");
        printf("4- Update\n");
        printf("5- Remove\n");
        printf("6- Add\n");
        printf("7- Free\n");
        printf("0- Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                print_dict(dict);
                break;
            case 2: {

                /*Search for an item by key in the dictionary*/
                char key[100];
                printf("Enter the key: ");
                scanf("%s", key);
                union Value* value = search_item(dict, key);
                if (value != NULL) {
                    printf("Key: %s\n", key);
                    Item* item = NULL;

                    /*Find the item in the dictionary*/
                    for (i = 0; i < dict->size; i++) {
                        if (strcmp(dict->items[i].key, key) == 0) {
                            item = &dict->items[i];
                            break;
                        }
                    }
                    /*Print the values based on the datatype*/
                    if (item) {
                        if (strcmp(item->datatype, "int") == 0) {
                            for (i = 0; i < item->count; i++) {
                                printf("Value: %d\n", value[i].i);
                            }
                        } else if (strcmp(item->datatype, "float") == 0) {
                            for (i = 0; i < item->count; i++) {
                                printf("Value: %f\n", value[i].f);
                            }
                        } else if (strcmp(item->datatype, "char") == 0) {
                            for (i = 0; i < item->count; i++) {
                                printf("Value: %c\n", value[i].s);
                            }
                        } else if (strcmp(item->datatype, "double") == 0) {
                            for ( i = 0; i < item->count; i++) {
                                printf("Value: %lf\n", value[i].d);
                            }
                        }
                    }
                } else {
                    printf("Key not found\n");
                }
                break;
            }
            case 3:
                /*Sort the dictionary by keys*/
                sort_dict(dict);
                print_dict(dict);
                break;

            case 4: {
                /*Update an item in the dictionary*/
                char key[100], datatype[100];
                int new_count, i;
                union Value* new_values;
                
                printf("Enter the key: ");
                scanf("%s", key);
                printf("Enter the datatype: ");
                scanf("%s", datatype);
                printf("Enter the number of values: ");
                scanf("%d", &new_count);
                
                /*Allocate memory for the new values*/
                new_values = malloc(new_count * sizeof(union Value));
                for (i = 0; i < new_count; i++) {
                    if (strcmp(datatype, "int") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%d", &new_values[i].i);
                    } else if (strcmp(datatype, "float") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%f", &new_values[i].f);
                    } else if (strcmp(datatype, "char") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf(" %c", &new_values[i].s);
                    } else if (strcmp(datatype, "double") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%lf", &new_values[i].d);
                    }
                }
                /*Find the item in the dictionary and update it*/
                for (i = 0; i < dict->size; i++) {

                    if (strcmp(dict->items[i].key, key) == 0) {
                        /*Free the old values and update the item*/
                        free(dict->items[i].value);
                        dict->items[i].value = new_values;
                        dict->items[i].count = new_count;
                        strcpy(dict->items[i].datatype, datatype);
                        break;
                    }
                }
                break;
            }
           
            case 5: {
                /*Remove an item from the dictionary*/
                char key[100];
                printf("Enter the key of the item to remove: ");
                scanf("%s", key);
                delete_item(dict, key);
                break;
            }
            case 6: {
                /*Add a new item to the dictionary*/
                char key[100], datatype[100];
                int new_count, i;
                union Value* new_values;

                printf("Enter the key: ");
                scanf("%s", key);
                printf("Enter the datatype: ");
                scanf("%s", datatype);
                printf("Enter the number of values to add: ");
                scanf("%d", &new_count);

                /*Allocate memory for the new values*/  
                new_values = malloc(new_count * sizeof(union Value));
                for (i = 0; i < new_count; i++) {
                    if (strcmp(datatype, "int") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%d", &new_values[i].i);
                    } else if (strcmp(datatype, "float") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%f", &new_values[i].f);
                    } else if (strcmp(datatype, "char") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf(" %c", &new_values[i].s);
                    } else if (strcmp(datatype, "double") == 0) {
                        printf("Enter value %d: ", i + 1);
                        scanf("%lf", &new_values[i].d);
                    }
                }
                /*Add the new item to the dictionary*/
                add_item(dict, key, datatype, new_values, new_count);
                free(new_values);
                break;
}
            case 7:
                /*Free the dictionary*/
                free_dict(dict);
                dict = create_dict();   
                break;
            case 0:
                /*Exit the program*/
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);
    return 0;
}
