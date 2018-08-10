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
 *         Author:  wujd (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "PETools.h"


PIMAE_DOS_HEADER pDosHeader = NULL;
PIMAE_PE_HEADER pPEHeader = NULL;
PIMAE_OPTION_PE_HEADER pPEOptionHeader = NULL;

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

int readDosHeader(void*	pFileBuffer,PIMAE_DOS_HEADER pDosHeader)
{
	if(pFileBuffer == NULL)
	{
		printf("file buffer is null!\n");
		return -1;
	}

	pDosHeader = (PIMAE_DOS_HEADER)pFileBuffer;
	if(pDosHeader == NULL)
	{
		printf("read dos header failed!\n");
		return -1;
	}
	if(checkPE(pDosHeader) != -1)
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

int ReadFileToRAM(char *pFilePath,void **pFileBuffer)
{
	FILE *pFile;
	int fileSize;
	int fileReadSize;

	if( (pFile=fopen(pFilePath, "rb")) == NULL)
	{
		printf("File Open Failed!\n");
		fclose(pFile);
		return -1;
	}

	fseek(pFile, 0, SEEK_END);
	fileSize = ftell(pFile);
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
	fileReadSize = fread(*pFileBuffer,fileSize,1, pFile);
	if(fileReadSize==0)
	{
		printf("File Read Failed!\n");
		fclose(pFile);
		free(*pFileBuffer);
		return -1;
	}

	printf("malloc %p\n", *pFileBuffer);
	printf("File Read to RAM Success,size=%d\n",fileReadSize);
	return fileReadSize;
}

int main(int argc,char **argv)
{
	FILE *pFile;
	void *pFileBuffer;

	if(argc!=2)
	{
		printf("命令参数错误!\n");
		exit(-1);
	}

	if (ReadFileToRAM(argv[1],&pFileBuffer) ==-1 )
	{
		free(pFileBuffer);
		exit(-1);
	}

	readDosHeader(pFileBuffer,pDosHeader);
	free(pFileBuffer);

	return 0;
}
