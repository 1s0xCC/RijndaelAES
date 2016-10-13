#pragma once

#include <Windows.h>
#include "IntelAES.h"

//#include "emmintrin.h"
//////////////////////////////////////
// �������뱾ģʽ
// ����ͬ����Կ�ֱ�����ķ������
//////////////////////////////////////
#define STDAES_MODE_ECB    0

//////////////////////////////////////
// �����������ģʽ
// �����㷨����������һ�����ķ������һ�����ķ�������
//////////////////////////////////////
#define STDAES_MODE_CBC    1

//////////////////////////////////////
// ���뷴��ģʽ
// һ�δ���Jλ����һ������������Ϊ����һ��α�����
// ����ļ����㷨�����룬����������������Ϊ��һ�����������
//////////////////////////////////////
#define STDAES_MODE_CFB   2

//////////////////////////////////////
// �������ģʽ
// ��CFB������ͬ��ֻ�Ǽ����㷨����������һ��AES�����
//////////////////////////////////////
#define STDAES_MODE_OFB   3

//////////////////////////////////////
// ����ģʽ
// ÿ�����ķ���������ܼ���������򣬶�ÿ���������飬���������ۼӵ�
//////////////////////////////////////
#define STDAES_MODE_CTR   4

#define STDAES_PADDING_PKCS5     0
#define STDAES_PADDING_ISO10126  1


////////////////////////////////////////////////////////////////////////////
//  ģʽ/���             16�ֽڼ��ܺ����ݳ���          ����16�ֽڼ��ܺ󳤶�
// CBC / NoPadding               16                          <��֧��>
// CBC / PKCS5Padding            32                          16
// CBC / ISO10126Padding         32                          16
// CFB / NoPadding               16                          ԭʼ���ݳ���
// CFB / PKCS5Padding            32                          16
// CFB / ISO10126Padding         32                          16
// ECB / NoPadding               16                          <��֧��>
// ECB / PKCS5Padding            32                          16
// ECB / ISO10126Padding         32                          16
// OFB / NoPadding               16                          ԭʼ���ݳ���
// OFB / PKCS5Padding            32                          16
// OFB / ISO10126Padding         32                          16
// PCBC / NoPadding              16                          <��֧��>
// PCBC / PKCS5Padding           32                          16
// PCBC / ISO10126Padding        32                          16
/////////////////////////////////////////////////////////////////////////////

#define STDAES_KEY_128BIT 16
#define STDAES_KEY_192BIT 24
#define STDAES_KEY_256BIT 32

class StdAES {
public:
	StdAES(INT keyMode, INT AESMode, INT padding);
	~StdAES();

private:
	INT mKeyLength;
	INT mKeyColumn;
	INT mRounds;
	INT mMode;
	INT mPadding;
	INT mExpansionTableLength;
	/*__declspec(align(16)) */PDWORD32 mExpansionTable;

public:
	void setKey(LPBYTE key);

	INT getBufferLen(INT dataLen);
	void padding(LPBYTE buffer, INT buffLen, LPBYTE data, INT dataLen);
	void deletePadding(LPBYTE buffer, LPINT buffLen);

	////////////////////////////////////////////////
	// ��������С����ʹ��getBufferLen�������
	// ���Ϸ��Ļ�������С����ɻ����������
	////////////////////////////////////////////////
	void encrypt(LPBYTE buffer, INT buffLen);
	void encrypt(LPBYTE buffer, INT buffLen, LPBYTE iv);

	////////////////////////////////////////////////
	// �ú�������ȷ�����ܺ����������ȷ�ģ�
	// ��������������Ƿ�AES�㷨���ܵģ����������Ϸ�����
	// ��ȷ���������ݵĺϷ���
	////////////////////////////////////////////////
	void decrypt(LPBYTE data, INT dataLen, LPBYTE iv);


private:
	//StdAES();
	//void encrypt(LPBYTE buffer, INT buffLen, LPBYTE iv);
	void keyExpansion(PDWORD32 key);

	void subWord(LPBYTE c);

	void addRoundKey(PDWORD32 data, UINT round);

	void subBytes_ShiftRows(LPBYTE data);
	void invSubBytes_ShiftRows(LPBYTE data);

	void subBytes_ShiftRows_MixColumns(LPBYTE data);
	void invSubBytes_ShiftRows_MixColumns(LPBYTE data);

	void cipher(LPBYTE data);
	void invCipher(LPBYTE data);
};

BOOL Check_CPU_support_AES();
