#pragma once
#pragma warning(disable:4996)

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//1.������ת��Ϊʮ������ֵͬ���ַ���
//��ȡ�����е����֣���ӡ���ַ�����ʱ����2λ��д�ĸ�ʽ��
int arrayToStr(unsigned char* buf, unsigned int buflen, char* out)
{
    char strBuf[33] = { 0 };
    char pbuf[32];
    int i;
    for (i = 0; i < buflen; i++)
    {
        sprintf(pbuf, "%02X", buf[i]);
        strncat(strBuf, pbuf, 2);
    }
    strncpy(out, strBuf, buflen * 2);
    //printf("out = %s\n", out);
    return buflen * 2;
}


//2.��ʮ�����Ƶ��ַ���ת��Ϊʮ����������
//��һ�ַ�ʽ�����涨����ַ����е��ַ�ֻ����0-F���ַ������ǲ����ִ�Сд�ģ�
//ǰ���ǰ�װ��λΪһ�����ֽ���ת�������һ���������������λ��������ת�������ֻʣһλ�Ļ�����ǰ�油�������
int StringToHex(char* str, unsigned char* out, int* outlen)
{
    char* p = str;
    char high = 0, low = 0;
    int tmplen = strlen(p), cnt = 0;
    tmplen = strlen(p);
    while (cnt < (tmplen / 2))
    {
        high = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;
        low = (*(++p) > '9' && ((*p <= 'F') || (*p <= 'f'))) ? *(p)-48 - 7 : *(p)-48;
        out[cnt] = ((high & 0x0f) << 4 | (low & 0x0f));
        p++;
        cnt++;
    }
    if (tmplen % 2 != 0) out[cnt] = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;

    if (outlen != NULL) *outlen = tmplen / 2 + tmplen % 2;
    return tmplen / 2 + tmplen % 2;
}


//3.�ڶ��ַ�ʽ�����һ�ַ�ʽ��ͬ��ֻ����ʹ�ÿ⺯��ʵ�֣�ʵ�ִ������£�
int StringHextoHex(char* str, unsigned char* out, int* outlen)
{
    if (str == NULL || out == NULL)
        return -1;

    int i = 0, ret = 0;

    ret = (strlen(str) / (2 * sizeof(char))) + strlen(str) % (2 * sizeof(char));

    for (i = 0; i < ret; i++)
        sscanf(str + 2 * i, "%02X", (unsigned int*)(out + i));

    if (outlen != NULL)
        *outlen = ret;

    return ret;
}


//4.��ʮ�����ַ���ת��Ϊʮ��������
int StringToCom(char* str, unsigned char* out, int* outlen)
{
    char* p = str;
    char high = 0, low = 0;
    int tmplen = strlen(p), cnt = 0;
    tmplen = strlen(p);
    if (tmplen % 2 != 0) return -1;
    while (cnt < tmplen / 2) //1213141516171819
    {
        out[cnt] = (*p - 0x30) * 10 + (*(++p) - 0x30);
        p++;
        cnt++;
    }
    *outlen = tmplen / 2;
    return tmplen / 2;
}


//5.�򵥵�ʹ�÷���
/*
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

unsigned char ArrayCom[16] = {
    11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 26 };
unsigned char ArrayHex[16] = {
    0x2c, 0x57, 0x8f, 0x79, 0x27, 0xa9, 0x49, 0xd3,
    0xb5, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

char* strHex = "01aa0304050607083f0add0c0d0e0f00";
char* strCom = "1D1213AB6FC1718B19202122232425A6";

int main(int argc, const char* argv)
{
    char str[33] = { 0 };
    unsigned char out[33];
    arrayToStr(ArrayCom, 16, str);

    unsigned int outlen = 0;
    StringToHex(strCom, out, &outlen);
    for (int cnt = 0; cnt < outlen; cnt++)
        printf("%02X ", out[cnt]);

    putchar(10);

    int outlen2 = 0;
    StringHextoHex(strHex, out, &outlen2);
    for (int i = 0; i < outlen; i++)
        printf("%02X ", out[i]);
    putchar(10);

    return 0;
}
*/