#include<stdlib.h>
#include<assert.h>
#include "screen.h"

int main()
{
    Result result;

    Type *silver;
    Type *gold;
    Type *vip;

    silver = init_type(80,150,&result);
    gold = init_type(40,200,&result);
    vip = init_type(30,300,&result);

    assert(silver != MEM_ALLOC_FAIL);
    assert(gold != MEM_ALLOC_FAIL);
    assert(vip != MEM_ALLOC_FAIL);

    Screen *screen_1;

    screen_1 = init_screen(*gold,*silver,*vip,&result);
    
    assert(screen_1->silver != MEM_ALLOC_FAIL);
    assert(screen_1->gold != MEM_ALLOC_FAIL);
    assert(screen_1->vip != MEM_ALLOC_FAIL);

    cases(screen_1, result);
    return 0;
}
