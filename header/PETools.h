/*
 * =====================================================================================
 *
 *       Filename:  PETools.h
 *
 *    Description:  WINDOWS PE头文件
 *
 *        Version:  1.0
 *        Created:  2018年08月07日 16时25分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wujd 
 *   Organization:  Alibaba
 *
 * =====================================================================================
 */

/* 
 * DOS头 
 */
typedef struct _IMAE_DOS_HEADER {		
	short e_magic;			
	short e_cblp;                   
	short e_cp;                    
	short e_crlc;                 
	short e_cparhdr;		
	short e_minalloc;       
	short e_maxalloc;
	short e_ss;     
	short e_sp;
	short e_csum;						
	short e_ip;					
	short e_cs;				
	short e_lfarlc;		
	short e_ovno;	
	short e_res[4];
	short e_oemid;						
	short e_oeminfo;					
	short e_res2[10];				
	int e_lfanew;				
}IMAE_DOS_HEADER,*PIMAE_DOS_HEADER;

/* *
 * 标准PE头
 * */
typedef struct _IMAE_PE_HEADER{
	
}IMAE_PE_HEADEER,*PIMAE_PE_HEADER;

/* *
 * 可选PE头
 * */
typedef  struct _IMAE_OPTION_PE_HEADER{

}IMAE_OPTION_PE_HEADER,*PIMAE_OPTION_PE_HEADER;
