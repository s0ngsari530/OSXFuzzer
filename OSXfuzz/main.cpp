//
//  main.cpp
//  OSXfuzz
//
//  Created by 송상준 on 2017. 9. 21..
//  Copyright © 2017년 송상준. All rights reserved.
//

#include "define.h"
#include "parsing.h"
#include "fuzz.h"

void help();

int main(int argc,char *argv[]) {
    kern_return_t err;
    
    char *pData;
    char *ptr;
    char *pService[8192];
    int i = 0;
    int select;
    pData = parsing_main();
    
    
    if(argc < 2) {
        help();
        exit(0);
    }
    // parsing kextstat result
    ptr = strtok(pData,"\n");
    while (ptr != NULL)
    {
        pService[i] = ptr;
        ptr = strtok(NULL, "\n");
        i++;
    }
    
    select = atoi(argv[1]);
    
    switch(select) {
            
        case 0: //newUserClient argument fuzz
            for(i=0;i<200;i++) {
                userclient_fuzz(pService[i]);
            }
            break;
            
        case 1:
            //TODO
            break;
            
        default:
            printf("[-] Invalid argument\n");
            break;
            
    }
    return 0;
    
}


void help() {
    printf("usage: OSXfuzz [Type]\n");
    printf("Type:           0 : newUserClient Fuzz\n");
    printf("                1 : IOConnectCall Fuzz\n");

    
}
