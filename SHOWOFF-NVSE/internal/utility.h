#pragma once
#include <string>

#include "PluginAPI.h"


// Inclusions below fuck up the compiler :thonk: :kms:
//#include "GameAPI.h"
//#include "GameData.h"
//#include "PluginAPI.h"
//#include "GameForms.h"
//#include "ShowOffNVSE.h"


class TESForm;


// From JIP
extern const double
kDblZero,
kDblPI,
kDblPIx2,
kDblPIx3d2,
kDblPId2,
kDblPId4,
kDblPId6,
kDblPId12,
kDbl2dPI,
kDbl4dPI,
kDblTanPId6,
kDblTanPId12,
kDblPId180;

// From JIP
extern const float
kFltZero,
kFltHalf,
kFltOne,
kFltTwo,
kFltFour,
kFltSix,
kFlt10,
kFlt100,
kFlt2048,
kFlt4096,
kFlt10000,
kFlt12288,
kFlt40000,
kFltMax;

// JIP assembly definitions.
#define CALL_EAX(addr) __asm mov eax, addr __asm call eax
#define JMP_EAX(addr)  __asm mov eax, addr __asm jmp eax
#define JMP_EDX(addr)  __asm mov edx, addr __asm jmp edx

// These are used for 10h aligning segments in ASM code (massive performance gain, particularly with loops).  -JIP
#define EMIT(bt) __asm _emit bt
#define NOP_0x1 EMIT(0x90)
//	"\x90"
#define NOP_0x2 EMIT(0x66) NOP_0x1
//	"\x66\x90"
#define NOP_0x3 EMIT(0x0F) EMIT(0x1F) EMIT(0x00)
//	"\x0F\x1F\x00"
#define NOP_0x4 EMIT(0x0F) EMIT(0x1F) EMIT(0x40) EMIT(0x00)
//	"\x0F\x1F\x40\x00"
#define NOP_0x5 EMIT(0x0F) EMIT(0x1F) EMIT(0x44) EMIT(0x00) EMIT(0x00)
//	"\x0F\x1F\x44\x00\x00"
#define NOP_0x6 EMIT(0x66) NOP_0x5
//	"\x66\x0F\x1F\x44\x00\x00"
#define NOP_0x7 EMIT(0x0F) EMIT(0x1F) EMIT(0x80) EMIT(0x00) EMIT(0x00) EMIT(0x00) EMIT(0x00)
//	"\x0F\x1F\x80\x00\x00\x00\x00"
#define NOP_0x8 EMIT(0x0F) EMIT(0x1F) EMIT(0x84) EMIT(0x00) EMIT(0x00) EMIT(0x00) EMIT(0x00) EMIT(0x00)
//	"\x0F\x1F\x84\x00\x00\x00\x00\x00"
#define NOP_0x9 EMIT(0x66) NOP_0x8
//	"\x66\x0F\x1F\x84\x00\x00\x00\x00\x00"
#define NOP_0xA EMIT(0x66) NOP_0x9
//	"\x66\x66\x0F\x1F\x84\x00\x00\x00\x00\x00"
#define NOP_0xB EMIT(0x66) NOP_0xA
//	"\x66\x66\x66\x0F\x1F\x84\x00\x00\x00\x00\x00"
#define NOP_0xC NOP_0x8 NOP_0x4
#define NOP_0xD NOP_0x8 NOP_0x5
#define NOP_0xE NOP_0x7 NOP_0x7
#define NOP_0xF NOP_0x8 NOP_0x7


// LightCS definitions taken from JG
class LightCS
{
	UInt32	owningThread;
	UInt32	enterCount;

public:
	LightCS() : owningThread(0), enterCount(0) {}

	void Enter();
	void EnterSleep();
	void Leave();
};

// From JIP
typedef void* (__cdecl* memcpy_t)(void*, const void*, size_t);
extern memcpy_t MemCopy, MemMove;

union Coordinate
{
	UInt32		xy;
	struct
	{
		SInt16	y;
		SInt16	x;
	};

	Coordinate() {}
	Coordinate(SInt16 _x, SInt16 _y) : x(_x), y(_y) {}

	inline Coordinate& operator =(const Coordinate &rhs)
	{
		xy = rhs.xy;
		return *this;
	}
	inline Coordinate& operator =(const UInt32 &rhs)
	{
		xy = rhs;
		return *this;
	}

	inline bool operator ==(const Coordinate &rhs) {return xy == rhs.xy;}
	inline bool operator !=(const Coordinate &rhs) {return xy != rhs.xy;}

	inline Coordinate operator +(const char *rhs)
	{
		return Coordinate(x + rhs[0], y + rhs[1]);
	}
};

//===Begin JIP math stuff 
template <typename T1, typename T2> inline T1 GetMin(T1 value1, T2 value2)
{
	return (value1 < value2) ? value1 : value2;
}

template <typename T1, typename T2> inline T1 GetMax(T1 value1, T2 value2)
{
	return (value1 > value2) ? value1 : value2;
}

template <typename T> inline T sqr(T value)
{
	return value * value;
}

bool fCompare(float lval, float rval); 

int __stdcall lfloor(float value);
int __stdcall lceil(float value);

float __stdcall fSqrt(float value);
double __stdcall dSqrt(double value);

double dCos(double angle);
double dSin(double angle);
double dTan(double angle);

double dAtan(double value);
double dAsin(double value);
double dAcos(double value);
double dAtan2(double y, double x);

//===End JIP math stuff 

UInt32 __fastcall GetNextPrime(UInt32 num);

UInt32 __fastcall RGBHexToDec(UInt32 rgb);

UInt32 __fastcall RGBDecToHex(UInt32 rgb);

UInt32 __fastcall StrLen(const char *str);

char* __fastcall StrEnd(const char *str);

bool __fastcall MemCmp(const void *ptr1, const void *ptr2, UInt32 bsize);

void __fastcall MemZero(void *dest, UInt32 bsize);

char* __fastcall StrCopy(char *dest, const char *src);

char* __fastcall StrNCopy(char *dest, const char *src, UInt32 length);

char* __fastcall StrCat(char *dest, const char *src);

UInt32 __fastcall StrHash(const char *inKey);

bool __fastcall CmprLetters(const char *lstr, const char *rstr);

bool __fastcall StrEqualCS(const char *lstr, const char *rstr);

bool __fastcall StrEqualCI(const char *lstr, const char *rstr);

char __fastcall StrCompare(const char *lstr, const char *rstr);

char __fastcall StrBeginsCS(const char *lstr, const char *rstr);

char __fastcall StrBeginsCI(const char *lstr, const char *rstr);

void __fastcall FixPath(char *str);

void __fastcall StrToLower(char *str);

void __fastcall ReplaceChr(char *str, char from, char to);

char* __fastcall FindChr(const char *str, char chr);

char* __fastcall FindChrR(const char *str, UInt32 length, char chr);

char* __fastcall SubStr(const char *srcStr, const char *subStr);

char* __fastcall SlashPos(const char *str);

char* __fastcall SlashPosR(const char *str);

char* __fastcall GetNextToken(char *str, char delim);

char* __fastcall GetNextToken(char *str, const char *delims);

char* __fastcall GetNextTokenJIP(char* str, char delim);

char* __fastcall CopyString(const char *key);

char* __fastcall IntToStr(int num, char *str);

char* __fastcall FltToStr(float num, char *str);

int __fastcall StrToInt(const char *str);

double __fastcall StrToDbl(const char *str);

char* __fastcall UIntToHex(UInt32 num, char *str);

UInt32 __fastcall HexToUInt(const char *str);

//===Begin JIP string / char stuff

extern const UInt8 kLwrCaseConverter[], kUprCaseConverter[];
extern char* GetStrArgBuffer();

//===End JIP string / char stuff

bool __fastcall FileExists(const char *path);


//===Begin JIP File stuff

class FileStreamJIP
{
	FILE* theFile;

public:
	FileStreamJIP() : theFile(NULL) {}
	~FileStreamJIP() { if (theFile) fclose(theFile); }

	bool Open(const char* filePath);
	bool OpenAt(const char* filePath, UInt32 inOffset);
	bool OpenWrite(char* filePath, bool append);
	bool Create(const char* filePath);
	void SetOffset(UInt32 inOffset);

	void Close()
	{
		fclose(theFile);
		theFile = NULL;
	}

	UInt32 GetLength();
	char ReadChar();
	void ReadBuf(void* outData, UInt32 inLength);
	void WriteChar(char chr);
	void WriteStr(const char* inStr);
	void WriteBuf(const void* inData, UInt32 inLength);

	static void MakeAllDirs(char* fullPath);
};

bool FileToBuffer(const char *filePath, char *buffer);

//===End JIP File stuff

void __fastcall GetTimeStamp(char *buffer);

// ConsolePrint() limited to 512 chars; use this to print longer strings to console
void Console_Print_Long(const std::string& str);

UInt32 __fastcall ByteSwap(UInt32 dword);

void DumpMemImg(void *data, UInt32 size, UInt8 extra = 0);


//===Begin JIP AuxBuffer stuff

#define AUX_BUFFER_INIT_SIZE 0x8000

class AuxBuffer
{
	UInt8	*ptr;
	UInt32	size;

public:
	AuxBuffer() : ptr(NULL), size(AUX_BUFFER_INIT_SIZE) {}
};

extern AuxBuffer s_auxBuffers[3];

UInt8* __fastcall GetAuxBuffer(AuxBuffer& buffer, UInt32 reqSize);

//===End JIP AuxBuffer stuff


// From kNVSE
void Log(const std::string& msg);
int HexStringToInt(const std::string& str);
std::string GetCurPath();

#if 0
// From kNVSE
void DebugPrint(const std::string& str)
{
#if _DEBUG
	Console_Print(str.c_str());
#endif
	Log(str);
}
#endif

double TryConvertStrToDouble(std::string const& str);
TESForm* StringToForm_Subroutine(const std::string& modName, const std::string& formIdStr);
TESForm* __fastcall StringToForm(const std::string& str);  //calls upon _Subroutine
ArrayElementR __fastcall ConvertStrToElem(std::string dataStr);

//	Assign rhs to lhs, bypassing operator=
template <typename T> __forceinline void RawAssign(const T& lhs, const T& rhs)
{
	struct Helper
	{
		UInt8	bytes[sizeof(T)];
	};
	*(Helper*)&lhs = *(Helper*)&rhs;
}

//	Swap lhs and rhs, bypassing operator=
template <typename T> __forceinline void RawSwap(const T& lhs, const T& rhs)
{
	struct Helper
	{
		UInt8	bytes[sizeof(T)];
	}
	temp = *(Helper*)&lhs;
	*(Helper*)&lhs = *(Helper*)&rhs;
	*(Helper*)&rhs = temp;
}

bool IsFormPlayable(TESForm* form);
bool IsItemPlayable(TESForm* form);

enum EquipableObjects
{
	kEquipType_Weapon = 1,
	kEquipType_Armor = 2,
};
short GetEquipType(TESForm* form);
bool IsEquipableItemPlayable(TESForm* form);

UInt32 GetFormEquipSlotMask(TESForm* form);
bool MatchAnySlotForForm(TESForm* form, UInt32 slotMask);
bool MatchAnyEquipSlots(UInt32 slotMask1, UInt32 slotMask2);

float GetFltGameSetting(UInt32 addr);
SInt32 GetIntGameSetting(UInt32 addr);

bool IsDllRunning(const char* dll);

