//
//  main.cpp
//  OSXfuzz
//
//  Created by 송상준 on 2017. 9. 21..
//  Copyright © 2017년 송상준. All rights reserved.
//


#include "parsing.h"
#include "fuzz.h"

int main(int argc, const char * argv[]) {
    kern_return_t err;
    
    char *pData;
    char *ptr;
    char *pService[8192];
    int i = 0;
    pData = parsing_main();
    
    // parsing kextstat result
    ptr = strtok(pData,"\n");
    while (ptr != NULL)
    {
        pService[i] = ptr;
        ptr = strtok(NULL, "\n");
        i++;
    }

    
    userclient_fuzz(pService[21]);


    return 0;
    
}
