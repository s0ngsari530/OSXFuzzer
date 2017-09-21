//
//  parsing.h
//  OSXfuzz
//
//  Created by 송상준 on 2017. 9. 22..
//  Copyright © 2017년 송상준. All rights reserved.
//

#ifndef parsing_h
#define parsing_h


#endif /* parsing_h */

#include "define.h"


char* parsing_main() {
    char command[100] = "kextstat | awk '{print $6}' | rev | cut -d'.' -f1 | rev";
    FILE *fp;
    int readSize;
    char pResult[8192] = {0,};
    
    fp = popen(command,"r");
    
    if(!fp) {
        printf("[-] Kextstat Failed\n");
        exit(1);
    }
    
    readSize = fread((void*)pResult,1,4096-1,fp);
    
    if(readSize == 0) {
        pclose(fp);
        printf("[-] fread Failed\n");
        exit(1);
    }
    pclose(fp);
    
    pResult[readSize]=0;
    
    if(pResult == NULL) {
        printf("[-] Error on parsing\n");
        exit(1);
    }
    
    return pResult;
}
