#include <stdio.h>
#include <string.h>

/*Define the Operation struct to hold opcode details*/
#define MAX_OPERATIONS 30   
#define MAX_LINE_LENGTH 256
#define REGISTER_SIZE 8
#define MEMORY_SIZE 256

typedef struct {
    char opcode[9];
    char type;
    char format[10];
    char explanation[MAX_LINE_LENGTH];
} Operation;
/*Define the Instruction struct to hold instruction details*/
typedef struct {
    char opcode[9];
    char operand[9];
    char operand2[9];
} Instruction;

/*Global variables*/
Operation operations[MAX_OPERATIONS];
int num_operations = 0;

/*Converts a decimal number to a binary string*/
int to_binary(int decimal_number, char *binary_str, int size) {
    int i;
    for (i = size - 1; i >= 0; i--) {
        binary_str[i] = (decimal_number % 2) + '0';
        decimal_number /= 2;
    }
    binary_str[size] = '\0';
    return 0;
}
/*Converts a binary string to a decimal number*/
int to_decimal(const char *binary_number) {
    int decimal = 0;
    int i;
    for (i = 0; i < strlen(binary_number); i++) {
        decimal = (decimal << 1) + (binary_number[i] - '0');
    }
    return decimal;
}
/*Returns the value of the opcode based on its binary representation*/
int getOpcodeValue(const char *opcode) {
    if (strcmp(opcode, "00000001") == 0) return 1;
    if (strcmp(opcode, "00000010") == 0) return 2;
    if (strcmp(opcode, "00000011") == 0) return 3;
    if (strcmp(opcode, "00000100") == 0) return 4;
    if (strcmp(opcode, "00000101") == 0) return 5;
    if (strcmp(opcode, "00000110") == 0) return 6;
    if (strcmp(opcode, "00000111") == 0) return 7;
    if (strcmp(opcode, "00001000") == 0) return 8;
    if (strcmp(opcode, "00001001") == 0) return 9;
    if (strcmp(opcode, "00001010") == 0) return 10;
    if (strcmp(opcode, "00001011") == 0) return 11;
    if (strcmp(opcode, "00001100") == 0) return 12;
    if (strcmp(opcode, "00001101") == 0) return 13;
    if (strcmp(opcode, "00001110") == 0) return 14;
    if (strcmp(opcode, "00001111") == 0) return 15;
    if (strcmp(opcode, "00010000") == 0) return 16;
    if (strcmp(opcode, "00010001") == 0) return 17;
    if (strcmp(opcode, "00010010") == 0) return 18;
    if (strcmp(opcode, "00010011") == 0) return 19;
    if (strcmp(opcode, "00010100") == 0) return 20;
    if (strcmp(opcode, "00010101") == 0) return 21;
    if (strcmp(opcode, "00010110") == 0) return 22;
    if (strcmp(opcode, "00010111") == 0) return 23;
    if (strcmp(opcode, "00011000") == 0) return 24;
    if (strcmp(opcode, "00011001") == 0) return 25;
    if (strcmp(opcode, "00011010") == 0) return 26;
    if (strcmp(opcode, "00011011") == 0) return 27;
    if (strcmp(opcode, "00011100") == 0) return 28;
    if (strcmp(opcode, "00011101") == 0) return 29;
    if (strcmp(opcode, "00011110") == 0) return 30;
    return -1;
}
/*Converts a binary string to a decimal number*/
void add_operation(Instruction *instr, char *register_A, char *register_B) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    int result = reg_A_value + reg_B_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the ADDI operation (register_A + immediate operand)*/
void addi_operation(Instruction *instr, char *register_A) {
    int operand = to_decimal(instr->operand);
    int reg_A_value = to_decimal(register_A);
    int result = reg_A_value + operand;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the AND operation (register_A & register_B)*/
void and_operation(Instruction *instr, char *register_A, char *register_B) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    int result = reg_A_value & reg_B_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the ADDM operation (register_A + memory value at address)*/
void addm_operation(Instruction *instr, char *register_A, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    char *memory_value = memory[address];
    int reg_A_value = to_decimal(register_A);
    int mem_value = to_decimal(memory_value);
    int result = reg_A_value + mem_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the ANDI operation (register_A & immediate operand)*/
void andi_operation(Instruction *instr, char *register_A) {
    int operand = to_decimal(instr->operand);
    int reg_A_value = to_decimal(register_A);
    int result = reg_A_value & operand;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*It ands register A and a number that stored in memory address B then stores the result in A.*/
void andm_operation(Instruction *instr, char *register_A, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    char *memory_value = memory[address];
    int reg_A_value = to_decimal(register_A);
    int mem_value = to_decimal(memory_value);
    int result = reg_A_value & mem_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*It does or operation between register A and B, then stores the result in A.*/
void or_operation(Instruction *instr, char *register_A, char *register_B) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    int result = reg_A_value | reg_B_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*It does or operation between register A and given number, then stores the result in A.*/
void ori_operation(Instruction *instr, char *register_A) {
    int operand = to_decimal(instr->operand);
    int reg_A_value = to_decimal(register_A);
    int result = reg_A_value | operand;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the ORM operation (register_A | memory value at address)*/
void orm_operation(Instruction *instr, char *register_A, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    char *memory_value = memory[address];
    int reg_A_value = to_decimal(register_A);
    int mem_value = to_decimal(memory_value);
    int result = reg_A_value | mem_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the SUB operation (register_A - register_B)*/
void sub_operation(Instruction *instr, char *register_A, char *register_B) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    int result = reg_A_value - reg_B_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the SUBI operation (register_A - immediate operand)*/
void subi_operation(Instruction *instr, char *register_A) {
    int operand = to_decimal(instr->operand);
    int reg_A_value = to_decimal(register_A);
    int result = reg_A_value - operand;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the SUBM operation (register_A - memory value at address)*/
void subm_operation(Instruction *instr, char *register_A, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    char *memory_value = memory[address];
    int reg_A_value = to_decimal(register_A);
    int mem_value = to_decimal(memory_value);
    int result = reg_A_value - mem_value;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the INC operation (increment register_A by 1)*/
void inc_operation(char *register_A) {
    int reg_A_value = to_decimal(register_A);
    int result = reg_A_value + 1;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the DEC operation (decrement register_A by 1)*/
void dec_operation(char *register_A) {
    int reg_A_value = to_decimal(register_A);
    int result = reg_A_value - 1;
    to_binary(result, register_A, REGISTER_SIZE);
}
/*Performs the SHL operation (left shift register_A by operand)*/
void shl_operation(int num,char re1,Instruction *instr, char *register_A, char *register_B) {
    int i;
   if(re1=='A'){
    int reg_A_value = to_decimal(register_A);
    for ( i = 0; i < num; i++) {
                reg_A_value *= 2;
            }
    to_binary(reg_A_value, register_A, REGISTER_SIZE);
   }
   else{
    int reg_A_value = to_decimal(register_B);
    for ( i = 0; i < num; i++) {
                reg_A_value *= 2;
            }
           
    to_binary(reg_A_value, register_B, REGISTER_SIZE);
   }
}
/*Performs the SHR operation (right shift register_A by operand)*/
void shr_operation(int num,char re1,Instruction *instr, char *register_A,char *register_B) {
    int i;
    
   if(re1=='A'){
    int reg_A_value = to_decimal(register_A);
    for ( i = 0; i < num; i++) {
                reg_A_value /= 2;
            }
           
    to_binary(reg_A_value, register_A, REGISTER_SIZE);
   }
   else{
    int reg_A_value = to_decimal(register_B);
    for ( i = 0; i < num; i++) {
                reg_A_value /= 2;
            }
            
    to_binary(reg_A_value, register_B, REGISTER_SIZE);
   }
}
/*Branch on line A if A and B equal.*/
void bre_operation(Instruction *instr, char *register_A, char *register_B, int *pc) {
    if (strcmp(register_A, register_B) == 0) {
        int address = to_decimal(instr->operand);
        *pc = address - 1;
    }
}
/*Branch on line A if A and B not equal.*/
void brn_operation(Instruction *instr, char *register_A, char *register_B, int *pc) {
    if (strcmp(register_A, register_B) != 0) {
        int address = to_decimal(instr->operand);
        *pc = address - 1;
    }
}
/*Jump to specific line number which is A + B.*/
void j_operation(Instruction *instr, char *register_A, char *register_B, int *pc) {
    int address = to_decimal(instr->operand) + to_decimal(register_B);
    *pc = address - 1;
}
/*It does nor operation between register A and B, then stores the result in A*/
void nor_operation(Instruction *instr, char *register_A, char *register_B) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    int result = ~(reg_A_value | reg_B_value);
    to_binary(result, register_A, REGISTER_SIZE);
}
/*It loads the value from memory address A into register A.*/
void lda_operation(char re1,Instruction *instr, char *register_A,char *register_B, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address;
    if(re1=='A'){
     address = to_decimal(register_A);
    strcpy(register_A, memory[address]);
    }
    else{
     address = to_decimal(register_B);
    strcpy(register_B, memory[address]);
    }
}
/*It loads the value from memory address B into register A.*/
void ldam_operation(Instruction *instr, char *register_A, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    int mem_address = to_decimal(memory[address]);
    strncpy(register_A, memory[mem_address], REGISTER_SIZE);
}

void ldb_operation(Instruction *instr, char *register_B, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    strncpy(register_B, memory[address], REGISTER_SIZE);
}
/*It loads the value from memory address B into register A.*/
void ldbm_operation(Instruction *instr, char *register_B, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    int mem_address = to_decimal(memory[address]);
    strncpy(register_B, memory[mem_address], REGISTER_SIZE);
}
/*It stores the value to memory address B from register A.*/
void str_operation(Instruction *instr, char *register_A, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    strncpy(memory[address], register_A, REGISTER_SIZE);
}
/*It swaps register A and B.*/
void swp_operation(char *register_A, char *register_B) {
    char temp[REGISTER_SIZE + 1];
    strncpy(temp, register_A, REGISTER_SIZE);
    strncpy(register_A, register_B, REGISTER_SIZE);
    strncpy(register_B, temp, REGISTER_SIZE);
}
/*It checks whether A is less than B.*/
void less_operation(char *register_A, char *register_B, char *result) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    if (reg_A_value < reg_B_value) {
        strncpy(result, "00000001", REGISTER_SIZE);
    } else {
        strncpy(result, "00000000", REGISTER_SIZE);
    }
}
/*It check whether A is greater than B.*/
void grt_operation(char *register_A, char *register_B, char *result) {
    int reg_A_value = to_decimal(register_A);
    int reg_B_value = to_decimal(register_B);
    if (reg_A_value > reg_B_value) {
        strncpy(result, "00000001", REGISTER_SIZE);
    } else {
        strncpy(result, "00000000", REGISTER_SIZE);
    }
}
/*It prints the value of register A. The value need to be converted to decimal number.*/
void pri_operation(char re1,char *register_A,char *register_B) {
    if(re1=='A'){
    int reg_A_value = to_decimal(register_A);
    printf("Result of the execution: %d\n", reg_A_value);
    }
    else
    {
    int reg_A_value = to_decimal(register_B);
    printf("Result of the execution: %d\n", reg_A_value);
    }
}
/*It prints the value of I. The value need to be converted to decimal number.*/
void prii_operation(Instruction *instr) {
    int value = to_decimal(instr->operand);
    printf("Result of the execution: %d\n", value);
}

/*It prints the value from memory address A. The value need to be converted to decimal number.*/
void prim_operation(Instruction *instr, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    int address = to_decimal(instr->operand);
    int value = to_decimal(memory[address]);
    printf("Result of the execution: %d\n", value);
}
/*Load I value to A register*/
void ldai_operation(char re1,Instruction *instr,char *register_A,char *register_B) {
    int value = to_decimal(instr->operand2);

    if(re1=='A')
    to_binary(value, register_A, REGISTER_SIZE);
    else
    to_binary(value, register_B, REGISTER_SIZE);
}

void fetch_instruction(int *pc, Instruction *IR, char memory[MEMORY_SIZE][REGISTER_SIZE + 1],char *register_A, char *register_B) {

    strcpy(IR->opcode, memory[*pc]);
    (*pc)++;
    strcpy(IR->operand, memory[*pc]);
    (*pc)++;
    strcpy(IR->operand2, memory[*pc]);
    (*pc)++;
   
    
}

void decode(Instruction IR,char *re1,char *re2,int *num1,int *num2){
    if(strcmp(IR.operand,"00011111")==0){
        *re1='A';
    }
    else if(strcmp(IR.operand,"00100000")==0){
        *re1='B';
    }
    else
        *num1=to_decimal(IR.operand);
    if(strcmp(IR.operand2,"00011111")==0){
        *re2='A';
    }
    else if(strcmp(IR.operand2,"00100000")==0){
        *re2='B';
    }
    else
        *num2=to_decimal(IR.operand2);
}

/*Load instructions from the file and execute them*/
int execute_instruction(Instruction *IR, char re1,char re2,int num1,int num2,char *register_A,char *register_B, char memory[MEMORY_SIZE][REGISTER_SIZE + 1], int *pc) {
    int opcode_value = getOpcodeValue(IR->opcode);

    switch (opcode_value) {
        case 1: add_operation(IR, register_A, register_B); break;
        case 2: addi_operation(IR, register_A); break;
        case 3: addm_operation(IR, register_A, memory); break;
        case 4: and_operation(IR, register_A, register_B); break;
        case 5: andi_operation(IR, register_A); break;
        case 6: andm_operation(IR, register_A, memory); break;
        case 7: or_operation(IR, register_A, register_B); break;
        case 8: ori_operation(IR, register_A); break;
        case 9: orm_operation(IR, register_A, memory); break;
        case 10: sub_operation(IR, register_A, register_B); break;
        case 11: subi_operation(IR, register_A); break;
        case 12: subm_operation(IR, register_A, memory); break;
        case 13: inc_operation(register_A); break;
        case 14: dec_operation(register_A); break;
        case 15: shl_operation(num2,re1,IR, register_A,register_B); break;
        case 16: shr_operation(num2,re1,IR, register_A,register_B); break;
        case 17: bre_operation(IR, register_A, register_B, pc); break;
        case 18: brn_operation(IR, register_A, register_B, pc); break;
        case 19: j_operation(IR, register_A, register_B, pc); break;
        case 20: nor_operation(IR, register_A, register_B); break;
        case 21: lda_operation(re1,IR, register_A,register_B, memory); break;
        case 22: str_operation(IR, register_A, memory); break;
        case 23: swp_operation(register_A, register_B); break;
        case 24: less_operation(register_A, register_B, register_A); break;
        case 25: grt_operation(register_A, register_B, register_A); break;
        case 26: pri_operation(re1,register_A,register_B); break;
        case 27: prii_operation(IR); break;
        case 28: prim_operation(IR, memory); break;
        case 29: ldai_operation(re1,IR, register_A,register_B); break;
        case 30: return 0;
        default: printf("Unknown operation type.\n"); break;
    }
    return 1;
}
/*Function to load memory with instructions from a file*/
void load_memory(const char *filename, char memory[MEMORY_SIZE][REGISTER_SIZE + 1]) {
    char array[30][2][9] = {{"ADD","00000001"},{"ADDI","00000010"},{"ADDM","00000011"},{"AND","00000100"},{"ANDI","00000101"},{"ANDM","00000110"},{"OR","00000111"},{"ORI","00001000"},{"ORM","00001001"},{"SUB","00001010"},{"SUBI","00001011"},{"SUBM","00001100"},{"INC","00001101"},{"DEC","00001110"},{"SHL","00001111"},{"SHR","00010000"},{"BRE","00010001"},{"BRN","00010010"},{"J","00010011"},{"NOR","00010100"},{"LDA","00010101"},{"STR","00010110"},{"SWP","00010111"},{"LESS","00011000"},{"GRT","00011001"},{"PRI","00011010"},{"PRII","00011011"},{"PRIM","00011100"},{"LDAI","00011101"},{"EXIT","00011110"}};
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    int i,num;
    char line[MAX_LINE_LENGTH],binary[9];
    int address = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char instruction[REGISTER_SIZE * 2 + 1] = {0};
        char a[REGISTER_SIZE + 1] = {0};
        char b[REGISTER_SIZE + 1] = {0};
        if(sscanf(line, "%s %s %s", instruction,a,b) == 3) {
            for(i = 0; i < 30; i++){
                if(strcmp(array[i][0], instruction) == 0){
                    strcpy(memory[address], array[i][1]);
                    address++;
                    break;
                }
            }
            if(strcmp(a, "A") == 0){
                strcpy(memory[address], "00011111");
                address++;
            }
            else if(strcmp(a, "B") == 0){
                strcpy(memory[address], "00100000");
                address++;
            }
            else if(strcmp(a,"M[B]") == 0){
                strncpy(memory[address], "00100010", REGISTER_SIZE * 2);
                address++;
            }
            else if(strcmp(a,"M[A]")== 0){
                strncpy(memory[address], "00100011", REGISTER_SIZE * 2);
                address++;
            }
            else{
                num=0;
                 for(i=0;i<strlen(a);i++){
                num*=10;
                num+=a[i]-'0';
            }
            num=to_binary(num,binary,8);
            strcpy(memory[address],binary);
            address++;
            }
            if(strcmp(b,"A")==0){
                strncpy(memory[address], "00011111", REGISTER_SIZE * 2);
                address++;
            }
            else if(strcmp(b,"B")==0){
                strncpy(memory[address], "00100000", REGISTER_SIZE * 2);
                address++;
            }
            else if(strcmp(b,"M[B]")==0){
                strncpy(memory[address], "00100010", REGISTER_SIZE * 2);
                address++;
            }
            else if(strcmp(b,"M[A]")==0){
                strncpy(memory[address], "00100011", REGISTER_SIZE * 2);
                address++;
            }
            else{
                
                num=0;
                 for(i=0;i<strlen(b);i++){
                num*=10;
                num+=b[i]-'0';
            }
            num=to_binary(num,binary,8);
            strcpy(memory[address],binary);
            address++;
            }
        
        }
        else if(sscanf(line, "%s %s", instruction,a) == 2) {
            for(i = 0; i < 30; i++){
                if(strcmp(array[i][0], instruction) == 0){
                    strcpy(memory[address], array[i][1]);
                    address++;
                    break;
                }
            }

            if(strcmp(a, "A") == 0){
                strcpy(memory[address], "00011111");
                address++;
            }
            else if(strcmp(a, "B") == 0){
                strcpy(memory[address], "00100000");
                address++;
            }
            else if(strcmp(a,"M[B]") == 0){
                strcpy(memory[address], "00100010");
                address++;
            }
            else if(strcmp(a,"M[A]")== 0){
                strcpy(memory[address], "00100011");
                address++;
            }
            else{
                num=0;
                 for(i=0;i<strlen(a);i++){
                num*=10;
                num+=a[i]-'0';
            }
            num=to_binary(num,binary,8);
            strcpy(memory[address],binary);
            address++;
            }
            strcpy(memory[address],"00000000");
            address++;


            

        }
        else {
            /*Convert instruction to binary*/
            for(i = 0; i < 30; i++){
                if(strcmp(array[i][0], instruction) == 0){
                    strncpy(memory[address], array[i][1], REGISTER_SIZE * 2);
                    address++;
                    break;
                }
            }
             strcpy(memory[address],"00000000");
            address++;
             strcpy(memory[address],"00000000");
            address++;
            
        }

    }
    
    fclose(file);
}
int main() {
    char filename[MAX_LINE_LENGTH];
    int continue_execution = 1,num1,num2,num;

    char re1,re2;

    while (continue_execution) {
        printf("Enter the filename: ");
        scanf("%s", filename);

        char register_A[REGISTER_SIZE + 1] = "00000000";
        char register_B[REGISTER_SIZE + 1] = "00000000";

        char memory[MEMORY_SIZE][REGISTER_SIZE + 1] = {{0}};
        strcpy(memory[100],"00000101");
        strcpy(memory[101],"00000110");

        int pc = 0;
        Instruction IR;

        /*Load instructions into memory*/
        load_memory(filename, memory);

        /*Fetch, decode, and execute instructions until end of memory or exit instruction*/
        while (pc < MEMORY_SIZE) {
            fetch_instruction(&pc, &IR, memory, register_A, register_B);
            decode(IR,&re1,&re2,&num1,&num2);
            num=execute_instruction(&IR, re1, re2,num1,num2,register_A,register_B, memory, &pc);
            if(num==0){
                break;
            }
        }

        /*Prompt user to execute another code*/
        printf("Do you want to execute another assembly code? Press (1) for yes, Press (0) for exit: ");
        scanf("%d", &continue_execution);
        if (continue_execution == 1) {
            pc = 0;
            continue;
        }
    }

    return 0;
}
