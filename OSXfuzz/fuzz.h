//
//  fuzz.h
//  OSXfuzz
//
//  Created by 송상준 on 2017. 9. 22..
//  Copyright © 2017년 송상준. All rights reserved.
//

#ifndef fuzz_h
#define fuzz_h


#endif /* fuzz_h */

#include "define.h"

io_connect_t global_conn = MACH_PORT_NULL;





uint64_t inputScalar[16] = {0};
uint64_t inputScalarCnt = 0;

char inputStruct[4096] = {0};
size_t inputStructCnt = 0;

uint64_t outputScalar[16] = {0};
uint32_t outputScalarCnt = 0;

char outputStruct[4096] = {0};
size_t outputStructCnt = 0;

int fuzz_scalar(char *name) {
    io_iterator_t iterator;
    kern_return_t err;
    io_connect_t con = MACH_PORT_NULL;
    CFMutableDictionaryRef matchingClass;
    io_service_t service;
    int i;
    
    matchingClass = IOServiceMatching(name);
    if(matchingClass == NULL){
        printf("[-] Error call to IOServiceMatching()\n");
        exit(1);
    }
    printf("[+] IOServiceMatching() Success\n");
    
    err = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingClass, &iterator);
    if (err != KERN_SUCCESS){
        printf("[-] Error call to IOServiceGetMatchingServices()\n");
        exit(1);
    }
    printf("[+] IOServiceGetMatchingServices() Success\n");
    
    service = IOIteratorNext(iterator);
    if (service == IO_OBJECT_NULL){
        printf("[-] Error call to IOIteratorNext()\n");
        exit(1);
    }
    printf("[+] IOIteratorNext() Success\n");
    
    err = IOServiceOpen(service, mach_task_self(), 0, &con);
    if(err == KERN_SUCCESS){
        printf("[+] IOServiceOpen() Success\n");
    }
    
    else if(err == KERN_FAILURE) {
        printf("[-] IOServiceOPen() Failed\n");
        return 0;
    }
    for(i=0;i<0x7000;i++) {
        IOConnectCallMethod(con,
                            i,
                            inputScalar,
                            inputScalarCnt,
                            inputStruct,
                            inputStructCnt,
                            outputScalar,
                            outputScalarCnt,
                            outputStruct,
                            outputStructCnt);
        //TODO
    }
    return err;
}


int get_client(char *name) {
    io_iterator_t iterator;
    kern_return_t err;
    io_connect_t con = MACH_PORT_NULL;
    CFMutableDictionaryRef matchingClass;
    io_service_t service;
    
    matchingClass = IOServiceMatching(name);
    if(matchingClass == NULL){
        printf("[-] Error call to IOServiceMatching()\n");
        exit(1);
    }
    printf("[+] IOServiceMatching() Success\n");
    
    
    err = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingClass, &iterator);
    if (err != KERN_SUCCESS){
        printf("[-] Error call to IOServiceGetMatchingServices()\n");
        exit(1);
    }
    printf("[+] IOServiceGetMatchingServices() Success\n");
    
    service = IOIteratorNext(iterator);
    if (service == IO_OBJECT_NULL){
        printf("[-] Error call to IOIteratorNext()\n");
        exit(1);
    }
    printf("[+] IOIteratorNext() Success\n");
    
    err = IOServiceOpen(service, mach_task_self(), 0, &con);
    if(err == KERN_SUCCESS){
        printf("[+] IOServiceOpen() Success\n");
    }
    return err;
}


int userclient_fuzz(char *name,unsigned int fuzz_arg) {
    io_iterator_t iterator;
    kern_return_t err;
    io_connect_t con = MACH_PORT_NULL;
    CFMutableDictionaryRef matchingClass;
    io_service_t service;
    int i;
    if(name == NULL) {
        printf("Services's not found\n");
        exit(1);
    }
    for(i=0;i<fuzz_arg;i++) {
        matchingClass = IOServiceMatching(name);
        printf("%s\n",name);
        if(matchingClass == NULL){
            printf("[-] Error call to IOServiceMatching()\n");
            return 0;
        }
        printf("[+] IOServiceMatching() Success\n");
        
        
        err = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingClass, &iterator);
        if (err != KERN_SUCCESS){
            printf("[-] Error call to IOServiceGetMatchingServices()\n");
            return 0;
        }
        printf("[+] IOServiceGetMatchingServices() Success\n");
        
        service = IOIteratorNext(iterator);
        if (service == IO_OBJECT_NULL){
            printf("[-] Error call to IOIteratorNext()\n");
            return 0;
        }
        printf("[+] IOIteratorNext() Success\n");
        
        err = IOServiceOpen(service, mach_task_self(), i, &con);
            
        if(err == KERN_SUCCESS){
            printf("[+] IOServiceOpen() Success\n");
        }
    }
    return 0;
}





