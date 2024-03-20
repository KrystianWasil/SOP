#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>



int a, b, sum, difference, product;
int test_sum = false;
int test_difference = false;

void *add_thread(void*arg) {
    // sleep(5);
    sum = a + b;
    test_sum = true;
    // sleep(5);
    return NULL;
}
void *subtract_thread(void*arg) {
    difference = a - b;
    test_difference= true;
    return NULL;
}
void *mulipy_thread(void*arg) {
    if (test_sum == true && test_difference == true) {
        product = a * b;
        printf("Sum: %d\n", sum);
        printf("Difference: %d\n", difference);
        printf("Product: %d\n", product);
    } else {
        perror("Other threads are still working");
    }
    return NULL;
}





int main() {
    printf("Ente numbers: ");
    scanf("%d %d",&a,&b);
    pthread_t thread_add, thread_subtract, thread_muliply;

    pthread_create(&thread_add, NULL, add_thread, NULL);
    pthread_create(&thread_subtract, NULL, subtract_thread, NULL);
    pthread_create(&thread_muliply, NULL, mulipy_thread, NULL);

    pthread_join(thread_add, NULL);
    pthread_join(thread_subtract, NULL);
    pthread_join(thread_muliply, NULL);


    return 0;
}
