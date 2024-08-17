#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "screen.h"

void display_total_price(const char *seat_type, int total_cost) {
    printf("\n");
    printf("\t\t=========================================================================================\n");
    printf("\t\t\t\t\t  Total Price for %s Seats\n", seat_type);
    printf("\t\t=========================================================================================\n");
    printf("\t\t Total cost: %d\n", total_cost);
    printf("\t\t=========================================================================================\n");
}

int main() {
    Result result;
    Type *silver, *gold, *vip;
    Type *silver1, *gold1, *vip1;

    silver = init_type(80, 150, &result);
    gold = init_type(40, 200, &result);
    vip = init_type(30, 300, &result);
    silver1 = init_type(60, 100, &result);
    gold1 = init_type(50, 200, &result);
    vip1 = init_type(40, 300, &result);

    assert(silver != MEM_ALLOC_FAIL);
    assert(gold != MEM_ALLOC_FAIL);
    assert(vip != MEM_ALLOC_FAIL);

    Screen *screen_1, *screen_2;
    screen_1 = init_screen(*gold, *silver, *vip, &result);
    screen_2 = init_screen(*gold1, *silver1, *vip1, &result);

    assert(screen_1 != MEM_ALLOC_FAIL);
    assert(screen_2 != MEM_ALLOC_FAIL);

    Seat data, data1, data2;
    int seat_number, screen_number;
    char phone_number[PHONE_SIZE];
    int cancel_status = FAILURE, cancel_status1 = FAILURE;

    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_seating(screen_1, 1);
                display_seating(screen_2, 2);
                break;

            case 2:
                // Booking a seat on Screen 1, Gold Type
                strcpy(data.phone, "8123465787");
                strcpy(data.name, "CB");
                seat_number = 5;
                int status = book_seat(screen_1, screen_1->gold, data, seat_number, &result);
                if (status == SUCCESS) {
                    print_bill(screen_1, screen_1->gold, seat_number, &result);
                } else {
                    printf("\t\t Booking failed: %s\n", result.result_message);
                }

                // Booking a seat on Screen 2, VIP Type
                strcpy(data1.phone, "2357818467");
                strcpy(data1.name, "ABCD");
                seat_number = 2;
                int status1 = book_seat(screen_2, screen_2->vip, data1, seat_number, &result);
                if (status1 == SUCCESS) {
                    print_bill(screen_2, screen_2->vip, seat_number, &result);
                } else {
                    printf("\t\t Booking failed: %s\n", result.result_message);
                }

                // Booking a seat on Screen 1, Silver Type
                strcpy(data2.phone, "8723815746");
                strcpy(data2.name, "HQWE");
                seat_number = 8;
                int status2 = book_seat(screen_1, screen_1->silver, data2, seat_number, &result);
                if (status2 == SUCCESS) {
                    print_bill(screen_1, screen_1->silver, seat_number, &result);
                } else {
                    printf("\t\t Booking failed: %s\n", result.result_message);
                }
                break;

            case 3:
                printf("\t\t Enter seat number to cancel: ");
                scanf("%d", &seat_number);
                printf("\t\t Enter your phone number: ");
                scanf("%s", phone_number);
                printf("\t\t Enter screen number: ");
                scanf("%d", &screen_number);

                if (screen_number == 1) {
                    cancel_status = cancel_seat(screen_1, seat_number, phone_number, &result);
                } else if (screen_number == 2) {
                    cancel_status1 = cancel_seat(screen_2, seat_number, phone_number, &result);
                } else {
                    printf("\t\t Invalid screen number.\n");
                    break;
                }

                if (screen_number == 1 && cancel_status == SUCCESS) {
                    printf("\t\t Seat cancelled successfully.\n");
                } else if (screen_number == 2 && cancel_status1 == SUCCESS) {
                    printf("\t\t Seat cancelled successfully.\n");
                } else {
                    printf("\t\t Cancellation failed: %s\n", result.result_message);
                }
                break;

            case 4:
                printf("Exiting the system. Thank you!\n");
                // Free allocated memory
                free(silver->seat);
                free(gold->seat);
                free(vip->seat);
                free(silver);
                free(gold);
                free(vip);
                free(silver1->seat);
                free(gold1->seat);
                free(vip1->seat);
                free(silver1);
                free(gold1);
                free(vip1);
                free(screen_1->gold);
                free(screen_1->silver);
                free(screen_1->vip);
                free(screen_1);
                free(screen_2->gold);
                free(screen_2->silver);
                free(screen_2->vip);
                free(screen_2);
                exit(0);

            default:
                printf("Invalid choice. Please select again.\n");
                break;
        }
    }

    return 0;
}
