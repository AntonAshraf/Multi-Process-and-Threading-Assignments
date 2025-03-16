#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep()

#define MAX_CUSTOMERS 10
#define MAX_ORDERS 5

sem_t order_semaphore, serve_semaphore, customer_semaphore;

void *customer(void *arg) {
    while(1) {
        sem_wait(&customer_semaphore); // Wait for available spot to place order
        printf("Customer placing order...\n");
        sem_wait(&order_semaphore); // Wait for available spot in the kitchen
        printf("Order placed by customer\n");
        sem_post(&order_semaphore); // Signal order placed
        sem_post(&serve_semaphore); // Signal order ready to be served
    }
    return NULL;
}

void *chef(void *arg) {
    while(1) {
        sem_wait(&order_semaphore); // Wait for order to be placed
        printf("Chef preparing order...\n");
        sleep(2); // Simulate food preparation time
        printf("Order prepared by chef\n");
        sem_post(&serve_semaphore); // Signal order ready to be served
    }
    return NULL;
}

void *waiter(void *arg) {
    while(1) {
        sem_wait(&serve_semaphore); // Wait for order to be prepared
        printf("Waiter serving order...\n");
        sleep(1); // Simulate serving time
        printf("Order served by waiter\n");
    }
    return NULL;
}

int main() {
    pthread_t customers[MAX_CUSTOMERS], chef_thread, waiter_thread;

    // Initialize semaphores
    sem_init(&order_semaphore, 0, MAX_ORDERS);
    sem_init(&serve_semaphore, 0, 0);
    sem_init(&customer_semaphore, 0, MAX_CUSTOMERS);

    // Create threads
    pthread_create(&chef_thread, NULL, chef, NULL);
    pthread_create(&waiter_thread, NULL, waiter, NULL);
    for(int i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_create(&customers[i], NULL, customer, NULL);
    }

    // Join threads (not reached in this example)
    pthread_join(chef_thread, NULL);
    pthread_join(waiter_thread, NULL);
    for(int i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&order_semaphore);
    sem_destroy(&serve_semaphore);
    sem_destroy(&customer_semaphore);

    return 0;
}
