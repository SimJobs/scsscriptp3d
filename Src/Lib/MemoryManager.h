/*
 *	I don't remember where I download this code, and who author.
 *  If anybody know who author of this code, mail me to except134@gmail.com please.
 */

#pragma once

#include <windows.h>

#ifdef _DEBUG
#define USE_MMGR
#endif

#ifdef USE_MMGR

#define USE_STACKTRACE

class MemoryManager
{
private:
	enum ALLOC {
		ALLOC_NEW,
		ALLOC_NEWARRAY,
	};

	struct AllocHeader {
		AllocHeader*		pNext;
		AllocHeader*		pPrev;
		ALLOC				eType;
		size_t				nLength;
		size_t				nAllocID;
		size_t				nTagID;
#ifdef USE_STACKTRACE
		static const size_t	cnMaxStackFrames=16;
		DWORD64				nPC[cnMaxStackFrames];
#endif
	};

private:
	static MemoryManager*	ms_pInstance;
	CRITICAL_SECTION		m_theMutex;
	AllocHeader*			m_pHead;
	AllocHeader*			m_pTail;
	size_t					m_nAllocations;
	size_t					m_nAllocationsSinceMarker;
	size_t					m_nAllocatedBytes;
	size_t					m_nNextID;
	size_t					m_nBreakOnAllocID;
	size_t					m_nHighWatermark;
	size_t					m_nAllocationTag;

private:
	void*					InternalAlloc(size_t nSize,ALLOC eType);
	void					InternalDealloc(void* p,ALLOC eType);
	static void				RecordStackTrace(AllocHeader* pAllocation);
	static const char*		GetCallerForAllocation(AllocHeader* pAllocation);

public:
	MemoryManager();
	~MemoryManager();

	static MemoryManager&	Instance() { return *ms_pInstance; }
	static void				Create();
	static void				Destroy();

	void					DumpAllAllocations(bool bDumpToFile);
	size_t					GetNextAllocID()			const	{ return m_nNextID; }
	size_t					GetNumActiveAllocations()	const	{ return m_nAllocations; }
	size_t					GetAllocatedBytes()			const	{ return m_nAllocatedBytes; }
	size_t					GetHighWatermark()			const	{ return m_nHighWatermark; }
	size_t					GetAllocationCount()		const	{ return m_nAllocationsSinceMarker; }
	void					BeginAllocationCount()				{ m_nAllocationsSinceMarker=0; }
	void					SetAllocationTagID(size_t nTag)		{ m_nAllocationTag=nTag; }
	void					SetBreakOnAllocID(size_t nID)		{ m_nBreakOnAllocID=nID; }

	void*					Allocate(size_t nSize);
	void*					AllocateArray(size_t nSize);
	void					Deallocate(void* pAddress);
	void					DeallocateArray(void* pAddress);
};

#endif
