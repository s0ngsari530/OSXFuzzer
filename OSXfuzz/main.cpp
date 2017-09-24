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
    unsigned int fuzz_arg;
    pData = parsing_main();
    
    
    if(argc < 2) {
        help();
        exit(0);
    }
    
    if(argv[2] != NULL) {
        fuzz_arg = atoi(argv[2]);
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
            if(fuzz_arg == NULL) {
                help();
                exit(1);
            }
            for(i=0;i<200;i++) {
                userclient_fuzz(pService[i],fuzz_arg);
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
    printf("usage: OSXfuzz [Type] [fuzz Argument]\n");
    printf("Type:           0 100 : newUserClient Fuzz argument with 100\n");
    printf("                1     : IOConnectCall Fuzz\n");

    
}
