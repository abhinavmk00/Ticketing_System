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

/*
int add_screen(Type gold,Type silver,Type vip,Result *);//bhavana
void initializeScreens(Screen *screens, int numScreens, int *vipSeats, int *goldSeats, int *silverSeats, int *vipPrice, int *goldPrice, int *silverPrice) {
    for (int i = 0; i < numScreens; i++) {
        screens[i].screenNumber = i + 1;
        initializeSeats(&screens[i].VIP, vipSeats[i], vipPrice[i]);
        initializeSeats(&screens[i].GOLD, goldSeats[i], goldPrice[i]);
        initializeSeats(&screens[i].SILVER, silverSeats[i], silverPrice[i]);
    }
}

int display_screen(Screen *,Result *);//chinthan
int book_seat(Screen *,Type *,Seat data,Result *);//meghana
int cancle_seat(Screen *,Type *,Seat data,Result *);//sanjith
int total_price(Screen *,Type *,char data,Result *);//subeen*/
