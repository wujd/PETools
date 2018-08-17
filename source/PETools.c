/*
 * =====================================================================================
 *
 *       Filename:  PETools.c
 *
 *    Description:  PE文件解析
 *
 *        Version:  1.0
 *        Created:  2018年08月06日 17时04分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wujd 
 *   Organization:  Alibaba
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "../header/PETools.h"



int checkPE(PIMAE_DOS_HEADER pDosHeader)
{
	if(pDosHeader->e_magic != 0x5A4D)			
	{
		printf("%x\n", pDosHeader->e_magic);
		printf("This File is Not a DOS File!\n");
		return -1;
	}

	return 0;
}

int readDosHeader(void*	pFileBuffer,PIMAE_DOS_HEADER *pDosHeader)
{
	if(pFileBuffer == NULL)
	{
		printf("File Buffer Is Null!\n");
		return -1;
	}

	*pDosHeader = (PIMAE_DOS_HEADER)pFileBuffer;
	if(*pDosHeader == NULL)
	{
		printf("read dos header failed!\n");
		return -1;
	}
	if(checkPE(*pDosHeader) != -1)
	{
		printf("Dos头读取成功!\n");
	}
	return 0;
}


int readPEHeader(void* pFileBuffer,PIMAE_PE_HEADER pPEHeader)
{
	pPEHeader = (PIMAE_PE_HEADER)pFileBuffer;
	return 0;
}

int readFileToRAM(char *pFilePath,void **pFileBuffer)
{
	FILE *pFile;
	int fileSize;

	if( (pFile=fopen(pFilePath, "rb")) == NULL)
	{
		printf("File Open Failed!\n");
		fclose(pFile);
		return -1;
	}

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
	printf("File Size=%d\n",fileSize);
	*pFileBuffer = malloc(fileSize);
	if(*pFileBuffer == NULL)
	{
		printf("Memory Alloc Failed!\n");
		fclose(pFile);
		free(*pFileBuffer);
		return -1;
	}
	memset(*pFileBuffer,0,fileSize);

	fseek(pFile, 0, SEEK_SET);
	if(fread(*pFileBuffer,fileSize,1, pFile)==0)
	{
		printf("File Read Failed!\n");
		fclose(pFile);
		free(*pFileBuffer);
		return -1;
	}

	printf("File Read to RAM Success,size=%d\n",fileSize);
	return 0;
}

void shortArrayToHexString(short shortArray[],int shortArrayLen,char** stringBuf)
{
	short *str = (short*)shortArray;

	int i=0;
	for(;i<shortArrayLen/2;i++)	
	{
		char k[4];
		sprintf(k,"%x",*str);
		strcat(*stringBuf,k);
		str++;
	}
	int hexStrLen = (int)strlen(*stringBuf);
	int needZeroCount = shortArrayLen*2-hexStrLen;
	char *stringBufTemp = malloc(shortArrayLen*2);
	for(i=0;i<needZeroCount;i++)
	{
		char k[2];
		sprintf(k,"%x",0);
		strcat(stringBufTemp,k);
	}
	strcat(stringBufTemp,*stringBuf);
	*stringBuf = stringBufTemp;
}

void printfDosHeader(PIMAE_DOS_HEADER pDosHeader)
{
	if(pDosHeader==NULL)
	{
		printf("读取Dos头时指针为NULL!\n");
		return;
	}

	char *hexString = NULL;

	printf("--------------------------------\n");
	printf("           DOS头部分            \n");
	printf("--------------------------------\n");
	printf("e_magic:%x\n",pDosHeader->e_magic);
	printf("e_cblp:%04x\n",pDosHeader->e_cblp);
	printf("e_cp:%04x\n",pDosHeader->e_cp);
	printf("e_crlc:%04x\n",pDosHeader->e_crlc);
	printf("e_cparhdr:%04x\n",pDosHeader->e_cparhdr);
	printf("e_minalloc:%04x\n",pDosHeader->e_minalloc);
	printf("e_maxalloc:%04x\n",pDosHeader->e_maxalloc);
	printf("e_ss:%04x\n",pDosHeader->e_ss);
	printf("e_sp:%04x\n",pDosHeader->e_sp);
	printf("e_csum:%04x\n",pDosHeader->e_csum);
	printf("e_ip:%04x\n",pDosHeader->e_ip);
	printf("e_cs:%04x\n",pDosHeader->e_cs);
	printf("e_lfarlc:%04x\n",pDosHeader->e_lfarlc);
	printf("e_ovno:%04x\n",pDosHeader->e_ovno);
	hexString = malloc(sizeof(pDosHeader->e_res)*sizeof(short));
	shortArrayToHexString(pDosHeader->e_res,sizeof(pDosHeader->e_res),&hexString);
	printf("e_res:%s\n",hexString);
	free(hexString);
	printf("e_oemid:%04x\n",pDosHeader->e_oemid);
	printf("e_oeminfo:%04x\n",pDosHeader->e_oeminfo);
	hexString = malloc(sizeof(pDosHeader->e_res2)*sizeof(short));
	shortArrayToHexString(pDosHeader->e_res2,sizeof(pDosHeader->e_res2),&hexString);
	printf("e_res2:%s\n",hexString);
	free(hexString);
	printf("e_lfanew:%08x\n",pDosHeader->e_lfanew);
}


int main(int argc,char **argv)
{
	PIMAE_DOS_HEADER pDosHeader = NULL;
	PIMAE_PE_HEADER pPEHeader = NULL;
	PIMAE_OPTION_PE_HEADER pPEOptionHeader = NULL;

	void *pFileBuffer;

	if(argc!=2)
	{
		printf("命令参数错误!\n");
		exit(-1);
	}

	if (readFileToRAM(argv[1],&pFileBuffer) ==-1 )
	{
		free(pFileBuffer);
		exit(-1);
	}

	readDosHeader(pFileBuffer,&pDosHeader);
	printfDosHeader(pDosHeader);
	free(pFileBuffer);

	return 0;
}
