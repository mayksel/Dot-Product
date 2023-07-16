// Template C to x86 call
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include <stdint.h>



extern  int dotproductasm(int n,  long * a,  long * b);
extern  int dotproductsimd(int n, long* a, long* b);

//C Dot Product Function
void dot_product(int n,  int* h_out, long int* h_in1, long int* h_in2) {
    for (int i = 0; i < n; i++)
        *h_out += h_in1[i] * h_in2[i];
}

int main(int argc, char* argv[]) {

    const unsigned int ARRAY_SIZE =1 << 24;
    const unsigned ARRAY_BYTES = ARRAY_SIZE * sizeof(long);
    const unsigned int run = 30;
    clock_t start, end;


    long int* in1, * in2;
    int out = 0;
    in1 = (long int*)malloc(ARRAY_BYTES);
    in2 = (long int*)malloc(ARRAY_BYTES);
    

    //init data
    for (int i = 0; i < ARRAY_SIZE;i++) {
        in1[i] = (i);
        in2[i] = (i + 1);
    }

    dot_product(ARRAY_SIZE, &out, in1, in2);
    double time_taken = 0;

    start = clock();
    for (int i = 0; i < run; i++)
        out = 0;
    dot_product(ARRAY_SIZE, &out, in1, in2);
    end = clock();
    time_taken += (double)end - start;
    time_taken = ((time_taken) * 1e6 / CLOCKS_PER_SEC) / run;
   
    //Check for errors
    long int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += in1[i] * in2[i];
    }

    printf("C function took an average of %lf microseconds for array size %d.\n", time_taken, ARRAY_SIZE);
    printf("Output: %lu \n", out);
    printf("Expected: %lu \n", sum);
   
    double p_error = abs((out - sum) / sum) * 100.0;

    printf("error percent for C: %f \n\n", p_error);

    int asm;
    start = clock();
    for (int i = 0; i < run; i++)
    asm = dotproductasm(ARRAY_SIZE, in1, in2);
    end = clock();
    time_taken += (double)end - start;
    time_taken = ((time_taken) * 1e6 / CLOCKS_PER_SEC) / run;

    printf("ASM function took an average of %lf microseconds for array size %d.\n", time_taken, ARRAY_SIZE);
    printf("ASM output: %lu \n", asm);
    printf("Expected: %lu \n", sum);

    double p_errorasm = abs((asm - sum) / sum) * 100.0;

    printf("error percent for asm: %f \n\n", p_errorasm);
    
    int simd;
    start = clock();
    for (int i = 0; i < run; i++)
        simd = dotproductasm(ARRAY_SIZE, in1, in2);
    end = clock();
    time_taken += (double)end - start;
    time_taken = ((time_taken) * 1e6 / CLOCKS_PER_SEC) / run;

    printf("SIMD function took an average of %lf microseconds for array size %d.\n", time_taken, ARRAY_SIZE);
    printf("simd output: %lu \n", simd);
    printf("Expected: %lu \n", sum);

    double p_errorsimd = abs((simd - sum) / sum) * 100.0;

    printf("error percent for asm: %f \n", p_errorsimd);



    //free memory
    free(in1);
    free(in2);


    return 0;

}
