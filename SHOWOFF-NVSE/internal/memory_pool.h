﻿#pragma once

// Ripped from JIP LN.

#define MAX_CACHED_BLOCK_SIZE 0x400
#define MEMORY_POOL_SIZE 0x1000

void* __fastcall Pool_Alloc(UInt32 size);
void __fastcall Pool_Free(void* pBlock, UInt32 size);
void* __fastcall Pool_Realloc(void* pBlock, UInt32 curSize, UInt32 reqSize);

#define POOL_ALLOC(count, type) (type*)Pool_Alloc(count * sizeof(type))
#define POOL_FREE(block, count, type) Pool_Free(block, count * sizeof(type))
#define POOL_REALLOC(block, curCount, newCount, type) block = (type*)Pool_Realloc(block, curCount * sizeof(type), newCount * sizeof(type))
#define ALLOC_NODE(type) (type*)Pool_Alloc(sizeof(type))