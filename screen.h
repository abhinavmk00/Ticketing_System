#ifndef _EMP_HEADER_
#define _EMP_HEADER_

#define RESULT_SIZE 30
#define PHONE_SIZE 11
#define NAME_SIZE 30
#define SUCCESS 1
#define FAILURE -1
#define MEM_ALLOC_FAIL NULL

#include<stdlib.h>
#include<stdio.h>

struct _result_
{
    int result_status;
    char result_message[RESULT_SIZE];
};
typedef struct _result_ Result;

struct _seat_
{
    char phone[PHONE_SIZE];
    char name[NAME_SIZE];
    int block;
};
typedef struct _seat_ Seat;

struct _type_
{
    Seat* seat;
    int price,c_size,t_size;
};
typedef struct _type_ Type;

struct _screen_
{
    Type* silver;
    Type* gold;
    Type* vip;
};
typedef struct _screen_ Screen;

Type* init_type(int size,int price,Result *);//abhinav
Screen* init_screen(Type gold,Type silver,Type vip,Result *);//abhinav
int add_screen(Type gold,Type silver,Type vip,Result *);//bhavana
int display_screen(Screen *);//chinthan
int book_seat(Screen *,Type *,Seat data,Result *);//meghana
int cancle_seat(Screen *,Type *,Seat data,Result *);//sanjith
int total_price(Screen *,Type *,char data,Result *);//subeen


#endif