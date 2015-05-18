/**
 * @file pfhook.h
 * Copyright 2012, 2013 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/* Created by Casper S. Hornstrup <chorns@users.sourceforge.net> */
#ifndef __PFHOOK_H
#define __PFHOOK_H
#pragma GCC system_header
#include <_mingw.h>

/*
 * Packet filter API
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ntddk.h"

#define DD_IPFLTRDRVR_DEVICE_NAME         L"\\Device\\IPFILTERDRIVER"

#define INVALID_PF_IF_INDEX               0xffffffff
#define ZERO_PF_IP_ADDR                   0

typedef ULONG IPAddr;

typedef enum _PF_FORWARD_ACTION {
	PF_FORWARD = 0,
	PF_DROP = 1,
	PF_PASS = 2,
	PF_ICMP_ON_DROP = 3
} PF_FORWARD_ACTION;

typedef PF_FORWARD_ACTION STDCALL
(*PacketFilterExtensionPtr)(
  /*IN*/ unsigned char  *PacketHeader,
  /*IN*/ unsigned char  *Packet, 
  /*IN*/ unsigned int  PacketLength, 
  /*IN*/ unsigned int  RecvInterfaceIndex, 
  /*IN*/ unsigned int  SendInterfaceIndex, 
  /*IN*/ IPAddr  RecvLinkNextHop, 
  /*IN*/ IPAddr  SendLinkNextHop); 

typedef struct _PF_SET_EXTENSION_HOOK_INFO {
  PacketFilterExtensionPtr  ExtensionPointer; 
} PF_SET_EXTENSION_HOOK_INFO, *PPF_SET_EXTENSION_HOOK_INFO;

#define FSCTL_IPFLTRDRVR_BASE             FILE_DEVICE_NETWORK

#define _IPFLTRDRVR_CTL_CODE(function, method, access) \
  CTL_CODE(FSCTL_IPFLTRDRVR_BASE, function, method, access)

#define IOCTL_PF_SET_EXTENSION_POINTER \
  _IPFLTRDRVR_CTL_CODE(22, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#ifdef __cplusplus
}
#endif

#endif /* __PFHOOK_H */