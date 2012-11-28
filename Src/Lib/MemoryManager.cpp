/*
 *	I don't remember where I download this code, and who author.
 *  If anybody know who author of this code, mail me to except134@gmail.com please.
 */

#define _CRT_SECURE_NO_WARNINGS	
//#define _WIN32_WINNT 0x0403 
#include "MemoryManager.h"
#ifdef USE_MMGR
#include <stdio.h>
#include <new>

#ifdef USE_STACKTRACE
	#include <dbghelp.h>
	#pragma comment(lib,"dbghelp.lib")
#endif 

#ifdef _WIN64
	static const size_t s_nHeadSentinalFill=0xFDFDFDFDFDFDFDFD;
	static const size_t s_nTailSentinalFill=0xFDFDFDFDFDFDFDFD;
#else
	static const size_t s_nHeadSentinalFill=0xFDFDFDFD;
	static const size_t s_nTailSentinalFill=0xFDFDFDFD;
#endif

typedef VOID (WINAPI *LPRtlCaptureContext)(PCONTEXT ContextRecord);
MemoryManager* MemoryManager::ms_pInstance=NULL;

static void Log(FILE* pFile,const char* psz)
{
	OutputDebugStringA(psz);
	if(pFile)
		fwrite(psz,1,strlen(psz),pFile);
}

static void Format(FILE* pFile,const char* szFormat,...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg,szFormat);
	_vsnprintf(szBuff,sizeof(szBuff),szFormat,arg);
	va_end(arg);
	Log(pFile,szBuff);
}

inline static void Assert(bool bExpression,const char* szMsg)
{
	if(!bExpression) {
		Log(NULL,szMsg);
		__debugbreak();
	}
};

#pragma warning(disable:4074) // warning C4074: initializers put in compiler reserved initialization area
#pragma init_seg(compiler)
struct MemoryInitialiser
{
	MemoryInitialiser()		{ MemoryManager::Create(); }
	~MemoryInitialiser()	{ MemoryManager::Destroy(); }
}g_theMemoryInitialiser;

void* operator new(size_t nSize)
{
	void* pMemory=MemoryManager::Instance().Allocate(nSize);
	Assert(!!pMemory,"Memory allocator failed!");
	return pMemory;
}

void* operator new[](size_t nSize)
{
	void* pMemory=MemoryManager::Instance().AllocateArray(nSize);
	Assert(!!pMemory,"Memory allocator failed!");
	return pMemory;
}

void operator delete(void* pAddress)
{
	MemoryManager::Instance().Deallocate(pAddress);
}

void operator delete[](void* pAddress)
{
	MemoryManager::Instance().DeallocateArray(pAddress);
}

MemoryManager::MemoryManager() :	m_pHead(NULL),
									m_pTail(NULL),
									m_nAllocations(0),
									m_nAllocationsSinceMarker(0),
									m_nAllocatedBytes(0),
									m_nNextID(1),
									m_nBreakOnAllocID(0),
									m_nHighWatermark(0),
									m_nAllocationTag(0)
{
	InitializeCriticalSectionAndSpinCount(&m_theMutex,4096|0x80000000);
#ifdef USE_STACKTRACE
	SymInitialize(GetCurrentProcess(),NULL,TRUE);
#endif
}

MemoryManager::~MemoryManager()
{
	Format(NULL,"MEMORY  : High watermark was %d bytes (%dKB,%dMB)\n",m_nHighWatermark,m_nHighWatermark/1024,m_nHighWatermark/(1024*1024));
	if(m_nAllocations!=0) {
		Log(NULL,"MEMORY  : Memory leaks detected!\n");
		DumpAllAllocations(true);
	} else
		Log(NULL,"MEMORY  : No memory leaks detected\n");
	DeleteCriticalSection(&m_theMutex);
	Assert(m_nAllocations==0,"Memory leaks were found");
}

void MemoryManager::Create()
{
	void* pBuff=malloc(sizeof(MemoryManager));
	MemoryManager* pMemory=new(pBuff) MemoryManager();
	ms_pInstance=pMemory;
}

void MemoryManager::Destroy()
{
	if(ms_pInstance) {
		ms_pInstance->~MemoryManager();
		free(ms_pInstance);
		ms_pInstance=0;
	}
}

void MemoryManager::DumpAllAllocations(bool bDumpToFile)
{
	FILE* pFile=bDumpToFile?fopen("memleaks.log","w"):NULL;

	EnterCriticalSection(&m_theMutex);
	Format(pFile,"%d active allocations totalling %d bytes:\n",m_nAllocations,m_nAllocatedBytes);
	AllocHeader* pAlloc=m_pHead;
	while(pAlloc) {
		Format(pFile,"+ ID %08d,tag ID 0x%08x: 0x%p %d bytes [%s]\n",pAlloc->nAllocID,pAlloc->nTagID,((unsigned char*)pAlloc)+sizeof(AllocHeader)+sizeof(size_t),pAlloc->nLength,GetCallerForAllocation(pAlloc));
		pAlloc=pAlloc->pNext;
	}
	Log(pFile,"End of allocations\n");
	LeaveCriticalSection(&m_theMutex);

	if(pFile)
		fclose(pFile);
}

void* MemoryManager::Allocate(size_t nSize)
{
	return InternalAlloc(nSize,ALLOC_NEW);
}

void* MemoryManager::AllocateArray(size_t nSize)
{
	return InternalAlloc(nSize,ALLOC_NEWARRAY);
}

void MemoryManager::Deallocate(void* pAddress)
{
	InternalDealloc(pAddress,ALLOC_NEW);
}

void MemoryManager::DeallocateArray(void* pAddress)
{
	InternalDealloc(pAddress,ALLOC_NEWARRAY);
}

void* MemoryManager::InternalAlloc(size_t nSize,ALLOC eType)
{
	++m_nNextID;
	Assert(m_nNextID-1!=m_nBreakOnAllocID,"Break on this allocation requested");

	unsigned char* pRawData=(unsigned char*)malloc(nSize+sizeof(AllocHeader)+sizeof(size_t)*2);
	if(!pRawData) {
		Assert(false,"Memory manager out of memory");
		return NULL;
	}

	AllocHeader* pHeader=(AllocHeader*)pRawData;
	size_t* pHeadSentinal=(size_t*)(pRawData+sizeof(AllocHeader));
	size_t* pTailSentinal=(size_t*)(pRawData+sizeof(AllocHeader)+sizeof(size_t)+nSize);

	*pHeadSentinal=s_nHeadSentinalFill;
	*pTailSentinal=s_nTailSentinalFill;

	#ifdef USE_STACKTRACE
		RecordStackTrace(pHeader);
	#endif

	EnterCriticalSection(&m_theMutex);
	{
		pHeader->pNext=NULL;
		pHeader->pPrev=m_pTail;
		pHeader->eType=eType;
		pHeader->nLength=nSize;
		pHeader->nAllocID=m_nNextID;
		pHeader->nTagID=m_nAllocationTag;

		++m_nAllocations;
		++m_nAllocationsSinceMarker;
		m_nAllocatedBytes+=nSize;
		if(m_nAllocatedBytes>m_nHighWatermark)
			m_nHighWatermark=m_nAllocatedBytes;

		if(!m_pHead) 
			m_pHead=pHeader;
		if(m_pTail)
			m_pTail->pNext=pHeader;
		m_pTail=pHeader;
	}
	LeaveCriticalSection(&m_theMutex);
	return pRawData+sizeof(AllocHeader)+sizeof(size_t);
}

void MemoryManager::InternalDealloc(void* p,ALLOC eType)
{
	if(!p)
		return;

	unsigned char* pRawData=(unsigned char*)p;
	size_t* pHeadSentinal=(size_t*)(pRawData-sizeof(size_t));
	AllocHeader* pHeader=(AllocHeader*)(pRawData-sizeof(size_t)-sizeof(AllocHeader));
	size_t* pTailSentinal=(size_t*)(pRawData+pHeader->nLength);

	Assert(*pHeadSentinal==s_nHeadSentinalFill,"Head sentinal damaged!");
	Assert(pHeader->eType==eType,"Incorrect deallocation used");
	Assert(*pTailSentinal==s_nTailSentinalFill,"Tail sentinal damaged!");

	EnterCriticalSection(&m_theMutex);
	{
		if(pHeader->pPrev)
			pHeader->pPrev->pNext=pHeader->pNext;
		else {
			Assert(pHeader==m_pHead,"Allocator broken!");
			m_pHead=pHeader->pNext;
		}

		if(pHeader->pNext)
			pHeader->pNext->pPrev=pHeader->pPrev;
		else {
			Assert(pHeader==m_pTail,"Allocator broken!");
			m_pTail=pHeader->pPrev;
		}
	}
	LeaveCriticalSection(&m_theMutex);

	--m_nAllocations;
	m_nAllocatedBytes-=pHeader->nLength;

	free(pHeader);
}

void MemoryManager::RecordStackTrace(AllocHeader* pAllocation)
{
#ifdef USE_STACKTRACE
	LPRtlCaptureContext pfnRtlCaptureContext=(LPRtlCaptureContext)GetProcAddress(GetModuleHandleW(L"kernel32.dll"),"RtlCaptureContext");
	if(!pfnRtlCaptureContext) {
		return;
	}

	CONTEXT ctx;
	pfnRtlCaptureContext(&ctx);

	STACKFRAME64 theStackFrame;
	memset(&theStackFrame,0,sizeof(theStackFrame));
	#ifdef _M_IX86
		DWORD dwMachineType=IMAGE_FILE_MACHINE_I386;
		theStackFrame.AddrPC.Offset=ctx.Eip;
		theStackFrame.AddrPC.Mode=AddrModeFlat;
		theStackFrame.AddrFrame.Offset=ctx.Ebp;
		theStackFrame.AddrFrame.Mode=AddrModeFlat;
		theStackFrame.AddrStack.Offset=ctx.Esp;
		theStackFrame.AddrStack.Mode=AddrModeFlat;
	#elif _M_X64
		DWORD dwMachineType=IMAGE_FILE_MACHINE_AMD64;
		theStackFrame.AddrPC.Offset=ctx.Rip;
		theStackFrame.AddrPC.Mode=AddrModeFlat;
		theStackFrame.AddrFrame.Offset=ctx.Rsp;
		theStackFrame.AddrFrame.Mode=AddrModeFlat;
		theStackFrame.AddrStack.Offset=ctx.Rsp;
		theStackFrame.AddrStack.Mode=AddrModeFlat;
	#elif _M_IA64
		DWORD dwMachineType=IMAGE_FILE_MACHINE_IA64;
		theStackFrame.AddrPC.Offset=ctx.StIIP;
		theStackFrame.AddrPC.Mode=AddrModeFlat;
		theStackFrame.AddrFrame.Offset=ctx.IntSp;
		theStackFrame.AddrFrame.Mode=AddrModeFlat;
		theStackFrame.AddrBStore.Offset=ctx.RsBSP;
		theStackFrame.AddrBStore.Mode=AddrModeFlat;
		theStackFrame.AddrStack.Offset=ctx.IntSp;
		theStackFrame.AddrStack.Mode=AddrModeFlat;
	#else
	#	error "Platform not supported!"
	#endif

	memset(pAllocation->nPC,0,sizeof(pAllocation->nPC));
	for(int i=0;i<AllocHeader::cnMaxStackFrames;++i) {
		pAllocation->nPC[i]=theStackFrame.AddrPC.Offset;
		if(!StackWalk64(dwMachineType,GetCurrentProcess(),GetCurrentThread(),&theStackFrame,&ctx,NULL,SymFunctionTableAccess64,SymGetModuleBase64,NULL)) {
			break;
		}
	}
#endif
	UNREFERENCED_PARAMETER(pAllocation);
}

const char* MemoryManager::GetCallerForAllocation(AllocHeader* pAllocation)
{
#ifdef USE_STACKTRACE
	const size_t cnBufferSize=512;
	char szFile[cnBufferSize];
	char szFunc[cnBufferSize];
	unsigned int nLine;
	static char szBuff[cnBufferSize*3];

	strcpy(szFile,"??");
	nLine=0;

	DWORD64 nPC;
	for(int i=0;i<AllocHeader::cnMaxStackFrames;++i) {
		nPC=pAllocation->nPC[i];
		if(nPC==0)
			break;

		unsigned char byBuffer[sizeof(IMAGEHLP_SYMBOL64)+cnBufferSize];
		IMAGEHLP_SYMBOL64* pSymbol=(IMAGEHLP_SYMBOL64*)byBuffer;
		DWORD64 dwDisplacement;
		memset(pSymbol,0,sizeof(IMAGEHLP_SYMBOL64)+cnBufferSize);
		pSymbol->SizeOfStruct=sizeof(IMAGEHLP_SYMBOL64);
		pSymbol->MaxNameLength=cnBufferSize;
		if(!SymGetSymFromAddr64(GetCurrentProcess(),nPC,&dwDisplacement,pSymbol))
			strcpy(szFunc,"??");
		else {
			pSymbol->Name[cnBufferSize-1]='\0';
			if(strncmp(pSymbol->Name,"MemMgr::",8)==0) {
				// In MemMgr,keep going...
			} else if(strncmp(pSymbol->Name,"operator new",12)==0) {
				// In operator new or new[],keep going...
			} else if(strncmp(pSymbol->Name,"std::",5)==0) {
				// In STL code,keep going...
			} else {
				// Found the allocator (Or near to it)
				strcpy(szFunc,pSymbol->Name);
				break;
			}
		}
	}

	if(nPC!=0) {
		IMAGEHLP_LINE64 theLine;
		DWORD dwDisplacement;
		memset(&theLine,0,sizeof(theLine));
		theLine.SizeOfStruct=sizeof(theLine);
		if(!SymGetLineFromAddr64(GetCurrentProcess(),nPC,&dwDisplacement,&theLine)) {
			strcpy(szFile,"??");
			nLine=0;
		} else {
			const char* pszFile=strrchr(theLine.FileName,'\\');
			if(!pszFile) pszFile=theLine.FileName;
			else ++pszFile;
			strncpy(szFile,pszFile,cnBufferSize);
			nLine=theLine.LineNumber;
		}
	}

	sprintf(szBuff,"%s:%d (%s)",szFile,nLine,szFunc);
	return szBuff;
#else
	UNREFERENCED_PARAMETER(pAllocation);
	return "Stack trace unavailable";
#endif
}

#endif 
