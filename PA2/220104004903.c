#include <stdio.h>

int main(){
	int menu;
	/*Main loop for menu*/
	while(1){
		/*Display menu options*/	
		printf("1. Explore Data: \n");
		printf("2. Train Model: \n");
		printf("3. Test Model: \n");
		printf("4. Exit: \n");
		printf("Enter your choice: ");
		scanf("%d",&menu);
	
	switch(menu){
	
	case 1: /*Explore Data*/
	
	FILE* fptr;
	fptr = fopen("data.txt","r"); /*Open data file for reading*/
	
	int x,y,c,x1min,x1max,x2min,x2max,y1min,y1max,y2max,y2min;
 	
 	/*Initialize min and max values for each class*/	
	x1min = y1min = x2min = y2min = 9999;
        x1max = y1max = x2max = y2max = -9999;

	/*Read data from file and find min/max for each class*/
	while (fscanf(fptr, "%d %d %d", &x, &y, &c) == 3) {
		if(c == 0){
					
			if(x > x1max){
				x1max = x;
				}
			if(x < x1min){
				x1min = x;
				}
			if(y > y1max){
				y1max = y;
				}
			if(y < y1min){
				y1min = y;
				}
			}	
		else if(c == 1){
			
			if(x > x2max){
				x2max = x;
				}
			if(x < x2min){
				x2min = x;
				}
			if(y > y2max){
				y2max = y;
				}
			if(y < y2min){
				y2min = y;
				}
			}
	
    }			
    	fclose(fptr); /*Close data file*/
    		
    		printf("Minimum and Maximum X and Y values:\n");
   		printf("Class 0: X in [%d,%d], Y in [%d,%d]\n",x1min,x1max,y1min,y1max);
   		printf("Class 1: X in [%d,%d], Y in [%d,%d]\n",x2min,x2max,y2min,y2max);
  	break;  	
  	
  	case 2: /*Training Model*/
  	 
  	/*Declaring variables for model training*/ 	
	int x1,y1,c1,x_total_max,y_total_max,x_control,y_control,x_min,y_min,x_seperator,y_seperator;	
	int c_r1_1,c_r1_0,c_r2_1,c_r2_0,c_r3_1,c_r3_0,c_r4_1,c_r4_0;	
	int error1=0,error2=0,error3=0,error4=0,error5=0,error6=0,error7=0,error8=0,error_total=0;
	int error_min = 9999;
	int R1,R2,R3,R4;
	x_total_max = x2max;
	y_total_max = y2max;
	x_min = x1min;
	y_min = y1min;
	int i,j	;
	
	    /*Adjusting minimum and maximum values for x and y to include data from both classes*/
	if(x2min < x1min){
		x_min = x2min;
		}
		else{
		x_min=x1min;
		}
	if(y2min < y1min){
		y_min = y2min; 
		}
		else{
		y_min=y1min;
		}
		
	if(x1max >= x2max){
		x_total_max = x1max;
		}
		else{
		x_total_max=x2max;
		}
	if(y1max >= y2max){
		y_total_max = y1max; 
		}	
		else{
		y_total_max=y2max;
		}
	
	fptr = fopen("data.txt","r");
			     			 	  
	for(i=x_min; i < x_total_max; i++){	    
      			 	  
	for(j=y_min; j < y_total_max; j++){					
		rewind(fptr);	
		/*Resetting error variables for each separation point*/	
		error1=0,error2=0,error3=0,error4=0,error5=0,error6=0,error7=0,error8=0,error_total=0;
   		c_r1_1 = c_r1_0 = c_r2_1 = c_r2_0 = c_r3_1 = c_r3_0 = c_r4_1 = c_r4_0 = 0; 	
		  while (fscanf(fptr, "%d %d %d", &x1, &y1, &c1) == 3) {
			
			if(c1 == 1){
				if(x1 <= i && y1 > j){							
				c_r1_1++;					
					}
    				if(x1 > i && y1 >j){								
				c_r2_1++;			
				}
    				if(x1 <= i && y1 <= j){											 	
				c_r3_1++;		
				}							
				if(x1 > i && y1 <= j){															
				c_r4_1++;
				}	
				}
			else if(c1 == 0){
				if(x1 <= i && y1 > j){							
				c_r1_0++;					
					}
    				if(x1 > i && y1 > j){								
				c_r2_0++;			
				}
    				if(x1 <= i && y1 <= j){											 	
				c_r3_0++;		
				}							
				if(x1 > i && y1 <= j){															
				c_r4_0++;
				}	
			}
			}
			/*Determining errors for each region based on counts*/
			if(c_r1_1 >= c_r1_0){	
				error1 = c_r1_0;
				R1 = 1;				
				}
			if(c_r1_0 > c_r1_1){
				error2 = c_r1_1;
				R1 = 0;
				 
				}
			if(c_r2_1 >= c_r2_0){
				error3 = c_r2_0;
				R2 = 1;
				
				}	
			if(c_r2_0 > c_r2_1){
				error4 = c_r2_1;
				R2 = 0;
				
				}
			if(c_r3_1 >= c_r3_0){
				error5 = c_r3_0;
				R3 = 1;				
				}
			if(c_r3_0 > c_r3_1){
				error6 = c_r3_1;
				R3 = 0;				
				}
			if(c_r4_1 >= c_r4_0){
				error7 = c_r4_0;
				R4 = 1;				
				}
			if(c_r4_0 > c_r4_1){
				error8 = c_r4_1;
				R4 = 0;
				}
		
		/*Total error calculation*/	
		error_total = error1 + error2 + error3 + error4 + error5 + error6 + error7 + error8;
		
			/*Update minimum error and corresponding separation point if applicable*/
			if(error_total < error_min){
					x_seperator = i;
                            		y_seperator = j;			
					error_min = error_total;
					
					}		
				
											
		}
	 }				 
	
	/*Printing minimum error, separator coordinates, and region labels*/ 
	printf("Minimum Error: %d\n", error_min);
        printf("Separator Coordinates: (%d, %d)\n", x_seperator, y_seperator);
        printf("Labels of the regions: R1 = %d, R2 = %d, R3 = %d, R4 = %d\n",R1,R2,R3,R4);
	
	fclose(fptr); 
	
	break;
	
	
	case 3:	
	FILE* fp;
	fp = fopen("test 1.txt","r");
	
	int x2,y2,c2,error_count = 0,c_count = 0;
	float success;
	
	
	/*Iterating through each data point in the test file*/
	while (fscanf(fp, "%d %d %d", &x2, &y2, &c2) == 3) {
		if(x_seperator <= x2 && y_seperator > y2 && R1 != c2){
			error_count++;
			}
		else if(x_seperator > x2 && y_seperator > y2 && R2 != c2){
			error_count++;
			} 	
		else if(x_seperator <= x2 && y_seperator <= y2 && R3 != c2){
			error_count++;
			}
		else if(x_seperator > x2 && y_seperator <= y2 && R4 != c2){
			error_count++;
			}	
		c_count++;	/*Counting the total number of data points*/
		}
	fclose(fp);
	
	success = (float)error_count / c_count * 100; 	
	/*Calculating success rate as the percentage of correctly classified data points*/
    	
    	printf("Success rate: %f\n", success);
    	
	
	FILE* fp1; 	/* Opening final test data file for reading */
	fp1 = fopen("test-final.txt","r");
	int x3,y3;
	while (fscanf(fp1, "%d %d", &x3, &y3) == 2) {
		
		if(x_seperator <= x3 && y_seperator > y3){
			printf("[%d,%d] Class is %d\n",x3,y3,R1);			
			}
		else if(x_seperator > x3 && y_seperator > y3){
			printf("[%d,%d] Class is %d\n",x3,y3,R2);
			} 	
		else if(x_seperator <= x3 && y_seperator <= y3){
			printf("[%d,%d] Class is %d\n",x3,y3,R3);
			}
		else if(x_seperator > x3 && y_seperator <= y3){
			printf("[%d,%d] Class is %d\n",x3,y3,R4);
			}	
		}
	fclose(fp1); /*Closing the final test file*/	
	break;
	
	case 4:
		/*Exit the program*/
                printf("Exiting...\n");
                return 0;
           
            default:
                /*Handling invalid menu options*/
                printf("Invalid option!\n");
                break;
	}	
  	}
  	return 0;
	
}
