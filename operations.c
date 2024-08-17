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

int book_seat(Screen *screen, Type *type, Seat data, int seat_number, Result *result) {
    if (seat_number < 0 || seat_number >= type->t_size) {
        result->result_status = FAILURE;
        strcpy(result->result_message, "Invalid seat number.");
        return FAILURE;
    }

    if (type->seat[seat_number].booked == 1) {
        result->result_status = FAILURE;
        strcpy(result->result_message, "Seat already booked.");
        return FAILURE;
    }

    // Book the seat
    strcpy(type->seat[seat_number].phone, data.phone);
    strcpy(type->seat[seat_number].name, data.name);
    type->seat[seat_number].booked = 1; // Set seat as booked
    type->seat[seat_number].seat_number = seat_number;
    type->c_size++;
    result->result_status = SUCCESS;
    strcpy(result->result_message, "Seat booked successfully.");
    return SUCCESS;
}

int cancel_seat(Screen *screen, int seat_number, const char *phone, Result *result) {
    // Iterate through types (gold, silver, vip)
    for (int type_index = 0; type_index < 3; ++type_index) {
        Type *type;
        if (type_index == 0) type = screen->gold;
        else if (type_index == 1) type = screen->silver;
        else type = screen->vip;

        // Iterate through seats within the type
        for (int seat_index = 0; seat_index < type->t_size; ++seat_index) {
            // Check if seat matches the given seat number and phone number
            if (type->seat[seat_index].seat_number == seat_number &&
                strcmp(type->seat[seat_index].phone, phone) == 0 &&
                type->seat[seat_index].booked == 1) {

                // Cancel the seat
                type->seat[seat_index].booked = 0;
                type->c_size--;
                result->result_status = SUCCESS;
                strcpy(result->result_message, "Seat cancelled successfully.");
                return SUCCESS;
            }
        }
    }

    // Seat not found
    result->result_status = FAILURE;
    strcpy(result->result_message, "Seat not found or not booked.");
    return FAILURE;
}
void print_bill(Screen *screen, Type *seat_type, int seat_number, Result *result) {
    if (screen == NULL || seat_type == NULL || result == NULL) {
        printf("Error: Invalid arguments provided.\n");
        return;
    }

    if (seat_number < 0 || seat_number >= seat_type->t_size) {
        printf("Error: Invalid seat number.\n");
        return;
    }

    if (seat_type->seat[seat_number].booked != 1) {
        printf("Error: Seat is not booked.\n");
        return;
    }

    printf("\n");
    printf("\t\t=========================================================================================\n");
    printf("\t\t\t\t\t         Bill for Booked Seat\n");
    printf("\t\t=========================================================================================\n");
    printf("\t\tSeat Number: %d\n", seat_number);
    printf("\t\tName: %s\n", seat_type->seat[seat_number].name);
    printf("\t\tPhone: %s\n", seat_type->seat[seat_number].phone);
    printf("\t\tPrice per seat: %d\n", seat_type->price);
    printf("\t\tTotal Cost: %d\n", seat_type->price);
    printf("\t\t=========================================================================================\n");
}
