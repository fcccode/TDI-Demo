#ifndef _HASH_FID_
#define  _HASH_FID_

#define HASH_BUFFER_LENGTH	10240
#define HASH_MAGIC	10007

#include <ndis.h>

typedef struct _SMB_READ_INFOR
{
	BOOLEAN isFirstRead;
	ULONGLONG Offset;
	ULONG DataLength;
	//BOOLEAN encryptData;//����û������ͷ��ֻ������

	ULONGLONG FirstOffset;//�洢�����ƫ��
	ULONG FirstLength;

	//�޸��������
	BOOLEAN bChangeRequest;
	ULONGLONG requestOffset;
	ULONG requestDataLength;
}SMB_READ_INFOR, *PSMB_READ_INFOR;

typedef struct _SMB_WRITE_INFOR
{
	ULONGLONG Offset;
	ULONG DataLength;
	//BOOLEAN decryptData;
}SMB_WRITE_INFOR, *PSMB_WRITE_INFOR;

typedef struct _FID_NET_FILE
{
	BOOLEAN valide;
	USHORT Fid;
	BOOLEAN isEncryptFile;
	//BOOLEAN WriteDecrypt; //����ͬһ���ļ��Ĳ�ͬƫ��
	//BOOLEAN ReadEncrypt;
	UNICODE_STRING FileName;

	SMB_READ_INFOR read;
	SMB_WRITE_INFOR write;
	UCHAR FileHeader[512];
	UCHAR SendBuffer[512];//��������
	UINT SendBufferLen;//���泤��
	UCHAR ReceiveBuffer[512];//��������
	UINT ReceiveBufferLen;//���泤��
}FID_NET_FILE, *PFID_NET_FILE;

BOOLEAN hfInsertFid(PFID_NET_FILE FidNode);
PFID_NET_FILE hfFindFid(USHORT Fid);
BOOLEAN hfDeleteFid(USHORT Fid);


#endif

