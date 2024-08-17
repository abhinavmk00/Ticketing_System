#include <stdlib.h>
#include <string.h>
#include "screen.h"

Type* init_type(int size,int price,Result *result)
{
    Type* my_type = (Type*)malloc(sizeof(Type));
    if (my_type == NULL)
    {
        result->result_status = FAILURE;
        strcpy(result->result_message, "Memory allocation failed for Type.");
        return MEM_ALLOC_FAIL;
    }
    
    my_type->seat = (Seat *)malloc(sizeof(Seat) * size);
    if(my_type->seat == NULL)
    {
        result->result_status = FAILURE;
        strcpy(result->result_message, "Memory allocation failed for Type->seat.");
        return MEM_ALLOC_FAIL;
    }
    my_type->price = price;
    my_type->c_size = 0;
    my_type->t_size = size;

    return my_type;
}
Screen* init_screen(Type gold,Type silver,Type vip,Result *result)//abhinav
{
    Screen* my_screen = (Screen*)malloc(sizeof(Screen));
    if (my_screen == NULL)
    {
        result->result_status = FAILURE;
        strcpy(result->result_message, "Memory allocation failed for Screen.");
        return MEM_ALLOC_FAIL;
    }

    my_screen->gold = (Type*)malloc(sizeof(Type));
    my_screen->silver = (Type*)malloc(sizeof(Type));
    my_screen->vip = (Type*)malloc(sizeof(Type));

    if (my_screen->gold == NULL || my_screen->silver == NULL || my_screen->vip == NULL) 
    {
        if (my_screen->gold) free(my_screen->gold);
        if (my_screen->silver) free(my_screen->silver);
        if (my_screen->vip) free(my_screen->vip);
        free(my_screen);
        
        result->result_status = FAILURE;
        strcpy(result->result_message, "Memory allocation failed for Type structures.");
        return MEM_ALLOC_FAIL;
    }

    *(my_screen->gold) = gold;
    *(my_screen->silver) = silver;
    *(my_screen->vip) = vip;

    result->result_status = SUCCESS;
    strcpy(result->result_message, "Screen initialized successfully.");

    return my_screen;    
}



#include "screen.h"
void display_menu() {
    printf("\n");
    printf("\t\t=========================================================================================\n");
    printf("\t\t\t\t\t        Ticket Booking System         \n");
    printf("\t\t=========================================================================================\n");
    printf("\t\t 1. View Seating Availability\n");
    printf("\t\t 2. Book a Seat\n");
    printf("\t\t 3. Cancel a Seat\n");
    printf("\t\t 4. Exit\n");
    printf("\t\t=========================================================================================\n");
    printf("\t\t Select an option: ");
}


void display_seating(Screen *screen, int screen_number) {
    if (screen == NULL) {
        printf("Screen %d is not available.\n", screen_number);
        return;
    }
    printf("\n");
    printf("\t\t=========================================================================================\n");
    printf("\t\t\t\t\t         Seating Availability For Screen:%d       \n", screen_number);
    printf("\t\t=========================================================================================\n");

    // Display Gold seating details
    printf("\t\tGold Seating:\n");
    printf("\t\tPrice per seat: %d\n", screen->gold->price);
    printf("\t\tTotal seats: %d\n", screen->gold->t_size);
    printf("\t\tSeats booked: %d\n", screen->gold->c_size);
    printf("\t\tSeats available: %d\n", screen->gold->t_size - screen->gold->c_size);
    printf("\n");
    printf("\t\t*************************************************************************\n");
    printf("\t\tGold Seats Reserved:\n");
    if(screen->gold->c_size == 0){
        printf("\t\tSeats Empty\n");
    } else {
        for (int i = 0; i < screen->gold->c_size; ++i) {
            printf("\t\tSeat %d: %s\n", i + 1, screen->gold->seat[i].booked ? "Booked" : "Available");
        }
    }
    printf("\t\t*************************************************************************\n");
    printf("\n\n");

    // Display Silver seating details
    printf("\t\tSilver Seating:\n");
    printf("\t\tPrice per seat: %d\n", screen->silver->price);
    printf("\t\tTotal seats: %d\n", screen->silver->t_size);
    printf("\t\tSeats booked: %d\n", screen->silver->c_size);
    printf("\t\tSeats available: %d\n", screen->silver->t_size - screen->silver->c_size);
    printf("\n");
    printf("\t\t*************************************************************************\n");
    printf("\t\tSilver Seats Reserved:\n");
    if(screen->silver->c_size == 0){
        printf("\t\tSeats Empty\n");
    } else {
        for (int i = 0; i < screen->silver->c_size; ++i) {
            printf("\t\tSeat %d: %s\n", i + 1, screen->silver->seat[i].booked ? "Booked" : "Available");
        }
    }
    printf("\t\t*************************************************************************\n");
    printf("\n\n");

    // Display VIP seating details
    printf("\t\tVIP Seating:\n");
    printf("\t\tPrice per seat: %d\n", screen->vip->price);
    printf("\t\tTotal seats: %d\n", screen->vip->t_size);
    printf("\t\tSeats booked: %d\n", screen->vip->c_size);
    printf("\t\tSeats available: %d\n", screen->vip->t_size - screen->vip->c_size);
    printf("\n");
    printf("\t\t*************************************************************************\n");
    printf("\t\tVIP Seats Reserved:\n");
    if(screen->vip->c_size == 0){
        printf("\t\tSeats Empty\n");
    } else {
        for (int i = 0; i < screen->vip->c_size; ++i) {
            printf("\t\tSeat %d: %s\n", i + 1, screen->vip->seat[i].booked ? "Booked" : "Available");
        }
    }
    printf("\t\t*************************************************************************\n");
    printf("\n\n");
}

void cases(Screen *screen_1, Result *result){
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
                break;

            case 2:
                // Booking a seat on Screen 1, Gold Type
                data.phone[PHONE_SIZE]= "8123465787";
                data.name[NAME_SIZE]="CB";
                seat_number = 5;
                int status = book_seat(screen_1, screen_1->gold, data, seat_number, &result);
                if (status == SUCCESS) {
                    print_bill(screen_1, screen_1->gold, seat_number, &result);
                } else {
                    printf("\t\t Booking failed: %s\n", result->result_message);
                }

                // Booking a seat on Screen 2, VIP Type
                data1.phone[PHONE_SIZE]="2357818467";
                data1.name[NAME_SIZE]= "ABCD";
                seat_number = 2;
                int status1 = book_seat(screen_1, screen_1->vip, data1, seat_number, &result);
                if (status1 == SUCCESS) {
                    print_bill(screen_1, screen_1->vip, seat_number, &result);
                } else {
                    printf("\t\t Booking failed: %s\n", result->result_message);
                }

                // Booking a seat on Screen 1, Silver Type
                data2.phone[PHONE_SIZE]= "8723815746";
                data2.name[NAME_SIZE]= "HQWE";
                seat_number = 8;
                int status2 = book_seat(screen_1, screen_1->silver, data2, seat_number, &result);
                if (status2 == SUCCESS) {
                    print_bill(screen_1, screen_1->silver, seat_number, &result);
                } else {
                    printf("\t\t Booking failed: %s\n", result->result_message);
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
                } else {
                    printf("\t\t Invalid screen number.\n");
                    break;
                }

                if (screen_number == 1 && cancel_status == SUCCESS) {
                    printf("\t\t Seat cancelled successfully.\n");
                } else if (screen_number == 2 && cancel_status1 == SUCCESS) {
                    printf("\t\t Seat cancelled successfully.\n");
                } else {
                    printf("\t\t Cancellation failed: %s\n", result->result_message);
                }
                break;

            case 4:
                printf("Exiting the system. Thank you!\n");
                // Free allocated memory
                free(screen_1->silver->seat);
                free(screen_1->gold->seat);
                free(screen_1->vip->seat);
                free(screen_1->silver);
                free(screen_1->gold);
                free(screen_1->vip);
                free(screen_1);
                exit(0);

            default:
                printf("Invalid choice. Please select again.\n");
                break;
        }
    }
}

/*
int add_screen(Type gold,Type silver,Type vip,Result *);//bhavana
int display_screen(Screen *,Result *);//chinthan
int book_seat(Screen *,Type *,Seat data,Result *);//meghana
int cancle_seat(Screen *,Type *,Seat data,Result *);//sanjith
int total_price(Screen *,Type *,char data,Result *);//subeen*/
