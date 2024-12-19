/*Define a union to hold different data types*/
typedef union Value {
    int i;
    float f;
    char s;
    double d;
} Value;

/*Define a structure to represent an item in the dictionary*/
typedef struct Item {
    char* datatype;
    int count;
    char* key;
    Value* value;
} Item;

/*Define a structure to represent the custom dictionary*/
typedef struct CustomDict {
    Item* items;
    int size;
    int capacity;
} CustomDict;

/*Function to create and initialize a new dictionary*/
struct CustomDict* create_dict() {
    struct CustomDict* dict = malloc(sizeof(struct CustomDict));
    dict->items = NULL;
    dict->size = 0;
    dict->capacity = 0;
    return dict;
}
/*Function to search for an item by key in the dictionary*/
union Value* search_item(struct CustomDict* dict, char* key) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return dict->items[i].value;
        }
    }
    return NULL;
}

/*Function to delete an item by key in the dictionary*/
void delete_item(struct CustomDict* dict, char* key){
    int i,j;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            /*Shift the elements to the left*/
            int index;
            printf("Enter the index of the item to remove: ");
            scanf("%d", &index);

            if (index >= 0 && index < dict->items[i].count) {       
                if (dict->items[i].count == 1) {    
                    delete_item(dict, key);
                } 
                else {
                    /*Shift the elements to the left*/
                    for (j = index; j < dict->items[i].count - 1; j++) {
                        dict->items[i].value[j] = dict->items[i].value[j + 1];
                    }
                    dict->items[i].count--;
                }

                printf("Item at index %d for key '%s' removed successfully.\n", index, key);
                return;
            } else {
                printf("Invalid item index. Please enter a valid index.\n");
                return;
            }
        }
    }
    printf("Key '%s' not found.\n", key);
}

/*Function to sort the dictionary by keys*/
void sort_dict(struct CustomDict *dict)
{
    int i, j;
    for (i = 0; i < dict->size - 1; i++)
    {
        for (j = 0; j < dict->size - i - 1; j++)
        {
            if (strcmp(dict->items[j].key, dict->items[j + 1].key) > 0)
            {
                struct Item temp = dict->items[j];
                dict->items[j] = dict->items[j + 1];
                dict->items[j + 1] = temp;
            }
        }
    }
}
/*Function to print the dictionary*/
void print_dict(struct CustomDict* dict) {
    int i,k;
    for (i = 0; i < dict->size; i++) {
        printf("Key: %s, Datatype: %s, ", dict->items[i].key, dict->items[i].datatype);
        for(k=0;k<dict->items[i].count;k++){
            if (strcmp(dict->items[i].datatype, "int") == 0) {
                printf(" %d ", dict->items[i].value[k].i);

            } else if (strcmp(dict->items[i].datatype, "float") == 0) {
                printf(" %f ", dict->items[i].value[k].f);
                
            } else if (strcmp(dict->items[i].datatype, "char") == 0) {
                printf(" %c ", dict->items[i].value[k].s);

            } else if (strcmp(dict->items[i].datatype, "double") == 0) {
                printf(" %lf ", dict->items[i].value[k].d);
            }

    }
    printf("\n");
}
}
/*Function to add an item to the dictionary*/
void add_item(struct CustomDict* dict, char* key, char* datatype, union Value* new_values, int new_count) {
    int i, j;
    /*Check if the key already exists*/
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            /*Add the new values to the existing item*/
            dict->items[i].value = realloc(dict->items[i].value, (dict->items[i].count + new_count) * sizeof(Value));
            for (j = 0; j < new_count; j++) {
                dict->items[i].value[dict->items[i].count + j] = new_values[j];
            }
            dict->items[i].count += new_count;
            return;
        }
    }

    /*Add a new item to the dictionary*/
    dict->items = realloc(dict->items, (dict->size + 1) * sizeof(Item));
    dict->items[dict->size].key = malloc((strlen(key) + 1) * sizeof(char));
    strcpy(dict->items[dict->size].key, key);
    dict->items[dict->size].datatype = malloc((strlen(datatype) + 1) * sizeof(char));
    strcpy(dict->items[dict->size].datatype, datatype);
    dict->items[dict->size].value = malloc(new_count * sizeof(Value));
    for (j = 0; j < new_count; j++) {
        dict->items[dict->size].value[j] = new_values[j];
    }
    dict->items[dict->size].count = new_count;
    dict->size++;
}
/*Function to set the value of an item in the dictionary*/
void set_value(struct CustomDict* dict, char* key, union Value* new_value) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            int j;
            for (j = 0; j < dict->items[i].count; j++) {
                dict->items[i].value[j] = *new_value;
            }
            return;
        }
    }
    printf("Key not found\n");
}
/*Function to free the dictionary*/
void free_dict(struct CustomDict* dict) {
    int i;
    for (i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].datatype);
    }
    free(dict->items);
    free(dict);

}
/*Function to read a CSV file and populate the dictionary*/
int read_csv(struct CustomDict* dict, const char* filename) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        return 0;
    }
    union Value *val;
    int i,j,y;
    int counter = 0;
    char line[1024];
    char* value[7];
    while (fgets(line, 1024, file)) { 

        /*Count the number of values in the line*/   
        counter = 0;
        for(i=0;line[i]!='\0';i++){
            if(line[i]=='\n'){
                line[i]='\0';
            }
        if(line[i]==','){
                counter++;
            }
        }
        char* datatype = strtok(line, ",");
        char* key = strtok(NULL, ",");   

        /*Remove the first character of the key*/   
        for(j=0;j<strlen(key)-1;j++){
            key[j]=key[j+1];    
        }
        key[strlen(key)-1]='\0';

        /*Allocate memory for the values*/
        val = (union Value*)malloc((counter-1)*sizeof(union Value));

        for (i = 0; i <counter-1; i++) {
            value[i] = strtok(NULL, ",");         
                }
            for(y=0;y<counter-1;y++){
                
                    if (strcmp(datatype, "int") == 0) {
                        val[y].i = atoi(value[y]);
    
                    } else if (strcmp(datatype, "float") == 0) {
                        val[y].f = atof(value[y]);
                        
                    } else if (strcmp(datatype, "char") == 0) {
                    
                        val[y].s = value[y][1];
                        

                    } else if (strcmp(datatype, "double") == 0) {
                        val[y].d = atof(value[y]);
                       
                    }
            }      
            /*Add the item to the dictionary*/     
            add_item(dict, key, datatype, val, counter-1);
        }
    
    fclose(file);
    return 1;
}
