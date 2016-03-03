#pragma once


//////////////////////////////////////////////////////////////////////////
// Thanks to tdifw1.4.4
// Thanks to ReactOS 0.3.13
//////////////////////////////////////////////////////////////////////////


#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						


#include "VisualDDKHelpers.h"
#include <ntddk.h>
#include <ntddstor.h>
#include <mountdev.h>
#include <ntddvol.h>
#include <tdi.h>
#include <tdiinfo.h>
#include <TdiKrnl.h>
#include <tdistat.h>
#include <ntstrsafe.h>

#include <stdlib.h>


// �ṹ�嶨���ͷ�ļ�
#include "structs.h"

// ���紫�����Ͷ���
#include "Sock.h"

// IPv4�豸��
#include "fw_ioctl.h"
#include "IPv4ProtocolSet.h"
#include "ObjListManager.h"


// ����δ�����ĺ���(����EPROCESS ��ȡ������)
//UCHAR* PsGetProcessImageFileName( PEPROCESS Process );


// �ڴ�����궨��
#define kmalloc(size)           ExAllocatePoolWithTag( NonPagedPool, size, 'root' )
#define kfree(ptr)              ExFreePoolWithTag( ptr, 'root' )


#define PASS_NET_WORK 0x01
#define FORBID_NET_WORK 0x02

#define STORAGE_DATA_BUFFER 0x04 //ʹ���˴�����buffer�������ͷ�
#define RECEIVE_STORAGE_PACKET 0x08//����ʱ�洢�İ��ύ�ϲ�
#define SEND_STORAGE_PACKET 0x10 //����ʱ�洢�İ�����
#define CHANGE_PACKET_DATA 0x20 //�޸����ݰ�
#define RECEIVE_DISCARD_PACKET 0x40 //ֱ�Ӷ����յ������ݰ�
#define DATA_IS_LESS 0x80 //ָʾ���ڵİ�̫С����Ҫ�ݴ�������������ݲ���512,���ܽ����ļ�ͷ��
#define RETURN_PACKET 0x100 //ָʾ�����ڵİ�����
#define SPLIT_PACKET 0x200 //��ֱ��εİ�Ϊ��������ǰһ���ַ��ͣ���һ���ֱ����²㵽�´η���
//��http���ļ����ӣ��ļ����Ȳ���������򵥷���return_packet�������ڽ��������״̬�Ͳ����ˣ�
#define DEBUG_TEST	0x4000

#define FLAG_ON_UINT(x, flag) ((UINT)x & (UINT)flag)
#define FLAG_SET_UINT(x, flag) (x = x | flag)

// ��ӡIP��ַ��Ϣ
void PrintIpAddressInfo( PCHAR pszMsg, PTA_ADDRESS pTaAddress );

void DbgMsg(char *lpszFile, int Line, char *lpszMsg, ...);
