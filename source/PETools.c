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

void shortArrayToString(short* shortArray)
{
	int i=0;
	for(;i<sizeof(shortArray);i++)
	{
		printf("e_res:%04x",shortArray[i]);
	}
	printf("\n");
}

void printfDosHeader(PIMAE_DOS_HEADER pDosHeader)
{
	if(pDosHeader==NULL)
	{
		printf("读取Dos头时指针为NULL!\n");
		return;
	}

	printf("--------------------------------\n");
	printf("           DOS头部分            \n");
	printf("--------------------------------\n");
	printf("e_magic:%x\n",pDosHeader->e_magic);
	printf("e_cblp:%04x\n",pDosHeader->e_cblp);
	printf("e_cp:%04x\n",pDosHeader->e_cp);
	printf("e_crlc:%04x\n",pDosHeader->e_crlc);
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
	printf("e_res:%04x\n",pDosHeader->e_res[0]);
	printf("e_oemid:%04x\n",pDosHeader->e_oemid);
	printf("e_oeminfo:%04x\n",pDosHeader->e_oeminfo);
	printf("e_res2:%04x\n",pDosHeader->e_res2[0]);
	printf("e_lfanew:%08x\n",pDosHeader->e_lfanew);
	shortArrayToString(pDosHeader->e_res);
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
