#pragma once

// �ṹ�嶨��ͷ�ļ�
#include <ntddk.h>


#define MAX_EVENT                   (TDI_EVENT_ERROR_EX + 1)

// ����ַ�ṹ��
#define TDI_ADDRESS_MAX_LENGTH	    TDI_ADDRESS_LENGTH_OSI_TSAP
#define TA_ADDRESS_MAX			    (sizeof(TA_ADDRESS) - 1 + TDI_ADDRESS_MAX_LENGTH)
#define TDI_ADDRESS_INFO_MAX	    (sizeof(TDI_ADDRESS_INFO) - 1 + TDI_ADDRESS_MAX_LENGTH)



// TDI�豸������豸��չ�ṹ��
typedef struct _TDI_DEVICE_EXTENSION
{
    PFILE_OBJECT  FileObject;           // �ļ�����
    PDEVICE_OBJECT  FltDeviceObject;    // �����豸����
    PDEVICE_OBJECT  NextStackDevice;    // �²��豸����
} TDI_DEVICE_EXTENSION, *PTDI_DEVICE_EXTENSION;



// TDI��������ǲ��ṹ��
typedef struct _TDI_REQUEST_TABLE
{
    UCHAR  RequestCode;                 // IRP IOCTL
    PDRIVER_DISPATCH  DispatchFunc;     // ��ǲ������ָ��
} TDI_REQUEST_TABLE, *PTDI_REQUEST_TABLE;



// TDI�¼������б�
typedef struct _TDI_EVENT_DISPATCH_TABLE
{
    ULONG  EventType;                   // event type
    PVOID  EventHandler;                // ��������ַָ��
} TDI_EVENT_DISPATCH_TABLE, *PTDI_EVENT_DISPATCH_TABLE;


// TDI �¼��ṹ��
typedef struct _TDI_EVENT_CONTEXT
{
    PFILE_OBJECT  FileObject;   // �����ַ�ļ�����
    PVOID  OldHandler;          // ����ɲ�������ָ��
    PVOID  OldContext;          // ����ɲ�����������������

	LIST_ENTRY ReceiveList; //���Ҫ�ϲ������ݰ�
	ULONG ReceiveLength; //�������ݰ����ܳ���
} TDI_EVENT_CONTEXT, *PTDI_EVENT_CONTEXT;


// ��ַ��Ϣ�ṹ��
typedef struct _ADDRESS_ITEM
{
    LIST_ENTRY  ListEntry;                  // ��ַ��Ϣ�ṹ������
    PFILE_OBJECT  FileObject;               // �ļ�ָ��(����)

	//PFILE_OBJECT ConnectFileObject;	//�����ļ�����;
	struct _CONNECTION_ITEM *ConnectItem;

    HANDLE  ProcessID;                      // ����ID
    ULONG  ProtocolType;                    // Э������

    UCHAR  LocalAddress[TA_ADDRESS_MAX];    // ���ص�ַ��Ϣ

    TDI_EVENT_CONTEXT  EventContext[MAX_EVENT]; // �¼�����Ľṹ��������
} ADDRESS_ITEM, *PADDRESS_ITEM;

typedef struct _APP_DATA_BUFFER
{
	PUCHAR Buffer;					// TCP����ָ��
	ULONG Offset;						////����Э��ƫ����
	ULONG length;						//length����Э�鳤�ȣ���Э������޸ģ���С�����ݰ���С
	ULONG MaximumLength;		//MaximumLength TCP���ݵĳ��ȣ�������Э������ı�
	//KSPIN_LOCK  SpinLock;
	//KMUTEX kMutex;
}APP_DATA_BUFFER, *PAPP_DATA_BUFFER;


//����������ݽṹ
typedef struct _APP_FICTION_PROCESS
{
	INT realPid;
	PVOID Context;
	PVOID ReceiveContext;//Э�������ģ��ɾ���Э����䣬��http��smtp����ű����̵�ȫ�ֱ���
	PVOID SendContext;//Э�������ģ��ɾ���Э����䣬��http��smtp����ű����̵�ȫ�ֱ���

	APP_DATA_BUFFER sendBuffer;
	APP_DATA_BUFFER receiveBuffer;

	ULONG SplitLength;//Ӧ�ò����ݵĳ���

}APP_FICTION_PROCESS, *PAPP_FICTION_PROCESS;




// ���������Ķ���ָ��
typedef struct _CONNECTION_ITEM
{
    LIST_ENTRY  ListEntry;                  // ���������Ķ�������
    PFILE_OBJECT  FileObject;               // �ļ�ָ��(����)
    CONNECTION_CONTEXT  ConnectionContext;  // ����������ָ��(���� �¼�������ʹ��)

    UCHAR  ConnectType;                     // ��������״̬(��վ or ��վ)
    UCHAR  RemoteAddress[TA_ADDRESS_MAX];   // Զ�̵�ַ��Ϣ

    PADDRESS_ITEM  AddressItemPtr;          // �����ĵ�ַ��Ϣ�ṹ��

	APP_FICTION_PROCESS AppContext;		//Ӧ�ò�Э��ʹ�õ�������

	//LIST_ENTRY ThreadDataList;				//DATA_INFO����
} CONNECTION_ITEM, *PCONNECTION_ITEM;

typedef unsigned int        UINT;
typedef struct _DATA_INFO
{
	LIST_ENTRY node;
	PETHREAD ThreadId;
	BOOLEAN isSendData;
	USHORT RemoteIpPort;
	KEVENT	WaitEvent;//�̵߳ȴ�������ϲŷ���
	APP_FICTION_PROCESS	threadData;
	PCONNECTION_ITEM ConnectItem;
	UINT uStatus;//������
}DATA_INFO, *PDATA_INFO;
