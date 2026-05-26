/*
* Project Name: NOKIA_5110_RPI
* File: NOKIA_5110_graphics.hpp
* Description: header file for the custom graphics functions
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/NOKIA_5110_RPI
*/

#ifndef _getipv4_h
#define _getipv4_h

// #define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>

void uinttochar(char* a, unsigned int n);
static char *get_addr(int sock, char * ifname, struct sockaddr * ifaddr);
void mtdGerarVetorEstruturaInformacoesInterfaceRede();
int getNumeroInterface();
char *mtdObterNomeInterface(int NumeroInterface);
char *mtdObterEnderecoIPInterface(int NumeroInterface);
char *mtdObterEnderecoHWInterface(int NumeroInterface);
char *mtdObterNetmaskInterface(int NumeroInterface);
char *mtdObterBroadcastInterface(int NumeroInterface);
char *mtdObterMTUInterface(int NumeroInterface);
char *mtdObterMetricInterface(int NumeroInterface);

#endif // file header guard

// ********************** EOF *********************
