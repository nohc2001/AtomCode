#include <iostream>
#include <string.h>

using namespace std;

class lcstr
{
public:
	char* Arr;
	size_t maxsize = 0;
	size_t up = 0;
	bool islocal = true;

	lcstr()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
		islocal = true;
	}

	virtual ~lcstr()
	{
		if (islocal) {
			delete[]Arr;
			Arr = nullptr;
		}
	}

	void NULLState()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
	}

	void Init(size_t siz, bool local)
	{
		islocal = local;
		char* newArr = new char[siz];
		if (Arr != nullptr)
		{
			for (int i = 0; i < maxsize; ++i)
			{
				newArr[i] = Arr[i];
			}

			delete[]Arr;
			Arr = nullptr;
		}

		Arr = newArr;
		maxsize = siz;
	}

	void operator=(const char* str)
	{
		int len = strlen(str) + 1;
		if (Arr == nullptr)
		{
			Arr = new char[len];
		}

		if (maxsize < len)
		{
			Init(len + 1, islocal);
		}
#if defined(__GNUC__)
		strcpy(Arr, str);
#elif defined (_MSC_VER)
		strcpy_s(Arr, len, str);
#endif
		up = len - 1;
	}

	bool operator==(char* str)
	{
		if (strcmp(Arr, str) == 0)
			return true;
		else
			return false;
	}

	bool operator==(const char* str)
	{
		if (strcmp(Arr, str) == 0)
			return true;
		else
			return false;
	}

	char& at(size_t i)
	{
		return Arr[i];
	}

	char* c_str()
	{
		Arr[up] = 0;
		return Arr;
	}

	char& operator[] (size_t i)
	{
		return Arr[i];
	}

	void push_back(char value)
	{
		if (up < maxsize)
		{
			Arr[up] = value;
			up += 1;
			Arr[up] = 0;
		}
		else
		{
			Init(maxsize * 2 + 1, islocal);
			Arr[up] = value;
			up += 1;
			Arr[up] = 0;
		}
	}

	void pop_back()
	{
		if (up - 1 >= 0)
		{
			up -= 1;
			Arr[up] = 0;
		}
	}

	void erase(size_t i)
	{
		for (int k = i; k < up; ++k)
		{
			Arr[k] = Arr[k + 1];
		}
		up -= 1;
	}

	void insert(size_t i, char value)
	{
		push_back(value);
		for (int k = maxsize - 1; k > i; k--)
		{
			Arr[k] = Arr[k - 1];
		}
		Arr[i] = value;
	}

	size_t size()
	{
		return up;
	}

	void clear()
	{
		if (Arr != nullptr)
			delete[]Arr;
		Arr = nullptr;
		up = 0;

		Init(2, islocal);
	}

	void release()
	{
		if (Arr != nullptr)
			delete[]Arr;
		Arr = nullptr;
		up = 0;
		islocal = false;
	}
};


/*
type0 : 
" Eb, Gb",
" Ev, Gv",
" Gb, Eb",
" Gv, Ev",
" AL, lb",
" rAx, lz",

type1 : 
" eAX",
" eCX",
" eDX",
" eBX",
" eSP",
" eBP",
" eSI",
" eDI",

type2 : 
" rAX/r8",
" rCX/r9",
" rDX/r10",
" rBX/r11",
" rSP/r12",
" rBP/r13",
" rSI/r14",
" rDI/r15",

type3 :
" Eb, Gb"
" Ev, Gv"
*/

/*
todo : 
1. �𸣴� �ϸ�� ������ �����ϰ� �ش� ���� �ּ��ϱ�. 
*/
constexpr char OneByteOpcode_DecodingTable[255][32] = {
"ADD Eb, Gb",//00  ���ϱ�
"ADD Ev, Gv",
"ADD Gb, Eb",
"ADD Gv, Ev",
"ADD AL, lb",
"ADD rAx, lz",
"PUSH ES^i64",
"POP ES^i64",
"OR Eb, Gb",//08
"OR Ev, Gv",
"OR Gb, Eb",
"OR Gv, Ev",
"OR AL, lb",
"OR rAx, lz",
"PUSH CS^i64",
"2byte Escape", // goto 2byte opcode decoding table
"ADC Eb, Gb",//10   ĳ���÷��׿� ������ �ִ� ���ϱ�
"ADC Ev, Gv",
"ADC Gb, Eb",
"ADC Gv, Ev",
"ADC AL, lb",
"ADC rAx, lz",
"PUSH SS^i64",
"POP SS^i64",
"SBB Eb, Gb",//18   ����� �����϶� ĳ���÷��׿����ִ� ����
"SBB Ev, Gv",
"SBB Gb, Eb",
"SBB Gv, Ev",
"SBB AL, lb",
"SBB rAx, lz",
"PUSH DS^i64",
"POP DS^i64",
"AND Eb, Gb",//20
"AND Ev, Gv",
"AND Gb, Eb",
"AND Gv, Ev",
"AND AL, lb",
"AND rAx, lz",
"SEG=ES(Prefix)",
"DAA^i64",
"SUB Eb, Gb",//28    ����
"SUB Ev, Gv",
"SUB Gb, Eb",
"SUB Gv, Ev",
"SUB AL, lb",
"SUB rAx, lz",
"SEG=SS(Prefix)",
"DAS^i64",
"XOR Eb, Gb",//30
"XOR Ev, Gv",
"XOR Gb, Eb",
"XOR Gv, Ev",
"XOR AL, lb",
"XOR rAx, lz",
"SEG=CS(Prefix)",
"AAA^i64",
"CMP Eb, Gb",//38   �ΰ� �� �� �÷��� ����
"CMP Ev, Gv",
"CMP Gb, Eb",
"CMP Gv, Ev",
"CMP AL, lb",
"CMP rAx, lz",
"SEG=DS(Prefix)",
"AAS^i64",
"INC eAX", //40   += 1;
"INC eCX",
"INC eDX",
"INC eBX",
"INC eSP",
"INC eBP",
"INC eSI",
"INC eDI",
"DEC eAX", //48   -= 1;
"DEC eCX",
"DEC eDX",
"DEC eBX",
"DEC eSP",
"DEC eBP",
"DEC eSI",
"DEC eDI",
"PUSH rAX/r8",//50
"PUSH rCX/r9",
"PUSH rDX/r10",
"PUSH rBX/r11",
"PUSH rSP/r12",
"PUSH rBP/r13",
"PUSH rSI/r14",
"PUSH rDI/r15",
"POP rAX/r8",//58
"POP rCX/r9",
"POP rDX/r10",
"POP rBX/r11",
"POP rSP/r12",
"POP rBP/r13",
"POP rSI/r14",
"POP rDI/r15",
"PUSHA^i64 / PUSHAD^i64", //60 ��� ���뷹�����͸� ���ÿ� Ǫ���Ѵ�.
"POPA^i64 / POPAD^i64", //61 ���ÿ� ����� ���뷹�����Ͱ��� �ε�
"BOUND^i64 Gv, Ma", //62 ?? ��踦 �������� �迭 �ε��� �˻�
"APRL Ew, Gw / MOVSXD Gv, Ev",//63
"PUSH^d64 lz",//68
"IMUL Gv, Ev, lz",//69
"PUSH^d64 lb",//6A
"IMUL Gv, Ev, lb",//6B
"INS/INSB Yb, Dx",
"INS/INSW/INSD Yz, DX",
"OUTS/OUTSB DX, Xb",
"OUTS/OUTSW/OUTSD DX, Xz",
"JO Jb", // 70 jumps -> �ڿ� "opcode�� CB�� �ٴ´�."
"JNO Jb",
"JB/JNAE/JC Jb",
"JNB/JAE/JNC Jb",
"JZ/JE Jb",
"JNZ/JNE Jb",
"JBE/JNA Jb",
"JNBE/JA Jb",
"JS Jb",
"JNS Jb",
"JP/JPE Jb",
"JNP/JPO Jb",
"JL/JNGE Jb",
"JNL/JGE Jb",
"JLE/JNG Jb",
"JNLE/JG Jb",
"ImmGrp1^1A Eb, lb",//80
"ImmGrp1^1A Ev, lz",
"ImmGrp1^1A Eb, lb^i64",
"ImmGrp1^1A Ev, lb",
"TEST",
"XCHG",
"Unallocated",
"MOV Eb, Gb", // 88
"MOV Ev, Gv",
"MOV Gb, Eb",
"MOV Gv, Ev",
"MOV Ev, Sw",
"LEA Gv, M",
"MOV Sw, Ew",
"POP^d64"
"NOP/XCHG rAX/r8", // 90
"XCHG rCX/r9",
"XCHG rDX/r10",
"XCHG rBX/r11",
"XCHG rSP/r12",
"XCHG rBP/r13",
"XCHG rSI/r14",
"XCHG rDI/r15",
"CBW/CWDE/CDQE",//98
"CWD/CDQ/CQO",
"farCALL^i64 Ap",
"FWAIT/WAIT",
"PUSHF/PUSHD/PUSHQ^d64/PUSHFv",
"POPF/POPD/POPQ^d64/POPFv",
"SAHF",
"LAHF",
"MOV AL, Ob",//A0
"MOV rAX, Ov",
"MOV Ob, AL",
"MOV Ov, rAX",
"MOVS/MOVSB Yb, Xb",
"MOVS/MOVSW/MOVSD/MOVSQ Xv, Yv",
"CMPS/CMPSB Xb, Yb",
"CMPS/CMPSW/CMPSD Xv, Yv",
"TEST AL, lb",//A8
"TEST rAX, lz",
"STOS/STOSB Yb, AL",
"STOS/STOSW/STOSD/STOSQ Yv, rAX",
"LODS/LODSB, AL, Xb",
"LODS/LODSW/LODSD/LODSQ rAX, Xv",
"SCAS/SCASB AL, Yb",
"SACS/SCASW/SCASD/SCASQ rAX, Yv",
"MOV AL/r8, lb",//B0
"MOV CL/r9, lb",
"MOV DL/r10, lb",
"MOV BL/r11, lb",
"MOV SP/r12, lb",
"MOV BP/r13, lb",
"MOV SI/r14, lb",
"MOV DI/r15, lb",
"MOV rAX/r8, ls",//B8
"MOV rCX/r9, ls",
"MOV rDX/r10, ls",
"MOV rBX/r11, ls",
"MOV rSP/r12, ls",
"MOV rBP/r13, ls",
"MOV rSI/r14, ls",
"MOV rDI/r15, ls",
"ShiftGrp2^1A Eb, lb", // C0
"ShiftGrp2^1A Ev, lv",
"nearRET lw",
"nearRET",
"LES Gz, Mp", // VEX2byte
"LDS Gz, Mp", // VEX1byte
"Grp11^1A-MOV Eb, lb",
"Grp11^1A-MOV Eb, lb",
"ENTER lw, lb", // C8
"LEAVE",
"farRET lw",
"farRET",
"INT3",
"INT lb",
"INTO",
"IRETD/IRETQ",
"ShiftGrp2^1A Eb, 1", // D0
"ShiftGrp2^1A Ev, 1",
"ShiftGrp2^1A Eb, CL",
"ShiftGrp2^1A Ev, CL",
"AAM lb",
"AAD lb",
"Unallocated",
"XLAT/XLATB",
"ESC", // D8 escape to coprocessor instruction set
"ESC",
"ESC",
"ESC",
"ESC",
"ESC",
"ESC",
"ESC",
"LOOPNE/LOOPNZ Jb",//E0
"LOOPE/LOOPZ Jb",
"LOOP Jb",
"JrCXZ Jb",
"IN AL, lb",
"IN eAX, lb",
"OUT lb, AL",
"OUT lb, eAX",
"nearCALL Jz",//E8
"nearJMP Jz",
"farJMP Ap",
"shortJMP Jb",
"IN AL, DX",
"IN eAX, DX",
"OUT DX, AL",
"OUT DX, eAX",
"Unallocated"//F0
"INT1",//F1
"Unallocated",
"Unallocated",
"HLT",
"CMC",
"UnaryGrp3^1A Eb",
"UnaryGrp3^1A Ev",
"CLC",//F8
"STC",
"CLI",
"STI",
"CLD",
"STD",
"GrpINC/DEC 4^1A",
"GrpINC/DEC 5^1A" //FF
};

constexpr char TwoByteOpcode_DecodingTable[256][32] = {
	"Grp6^1A",//00
	"Grp7^1A",
	"LAR Gv, Ew",
	"LSL Gv, Ew",
	"Unallocated",
	"SYSCALL",
	"CLTS",
	"SYSRET",
	"INVD",
	"WBINVD",
	"Unallocated",
	"2byteIllegalOpcodeUD2",
	"Unallocated",
	"PREFETCHW Ev",
	"Unallocated",
	"Unallocated",

	"__66F3F2",//10
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",

	"MOV Rd, Cd",//20
	"MOV Rd, Dd",
	"MOV Cd, Rd",
	"MOV Dd, Rd",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",

	"WRMSR",//30
	"RDTSC",
	"RDMSR",
	"RDPMC",
	"SYSENTER",
	"SYSEXIT",
	"Unallocated",
	"GETSEC",
	"3byteEscapeA4", // 3byte opcode table A-4�� ����
	"Unallocated",
	"3byteEscapeA5", // 3byte opcode table A-5�� ����
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"CMOVO Gv, Ev",//40
	"CMOVNO Gv, Ev",
	"CMOVB/CMOVC/CMOVNAE Gv, Ev",
	"CMOVAE/CMOVNB/CMOVNC Gv, Ev",
	"CMOVE/CMOVZ Gv, Ev",
	"CMOVNE/CMOVNZ Gv, Ev",
	"CMOVBE/CMOVNA Gv, Ev",
	"CMOVA/CMOVNBE Gv, Ev",
	"CMOVS Gv, Ev",
	"CMOVNS Gv, Ev",
	"CMOVP/CMOVPE Gv, Ev",
	"CMOVNP/CMOVPO Gv, Ev",
	"CMOVL/CMOVNGE Gv, Ev",
	"CMOVNL/CMOVGE Gv, Ev",
	"CMOVLE/CMOVNG Gv, Ev",
	"CMOVNLE/CMOVG Gv, Ev",

	"__66F3F2",//50
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",

	"__66F3",//60
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",
	"__66F3",

	"__66F3F2",//70
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",

	"JO Jz",//80
	"JNO Jz",
	"JB/JCNAE Jz",
	"JAE/JNB/JNC Jz",
	"JE/JZ Jz",
	"JNE/JNZ Jz",
	"JBE/JNA Jz",
	"JA/JNBE Jz",
	"JS Jz",
	"JNS Jz",
	"JP/JPE Jz",
	"JNP/JPO Jz",
	"JL/JNGE Jz",
	"JNL/JGE Jz",
	"JLE/JNG Jz",
	"JNLE/JG Jz",

	"SETO Eb",//90
	"SETNO Eb",
	"SETB/SETC/SETNAE Eb",
	"SETAE/SETNB/SETNC Eb",
	"SETE/SETZ Eb",
	"SETNE/SETNZ Eb",
	"SETBE/SETNA Eb",
	"SETA/SESTNBE Eb",
	"SETS Eb",
	"SETNS Eb",
	"SETP/SETPE Eb",
	"SETNP/SETPO Eb",
	"SETL/SETNGE Eb",
	"SETNL/SETGE Eb",
	"SETLE/SETNG Eb",
	"SETNLG/SETG Eb",

	"PUSH FS",//A0
	"POP FS",
	"CPUID",
	"BT Ev, Gv",
	"SHLD Ev, Gv, lb",
	"SHLD Ev, Gv, CL",
	"Unallocated",
	"Unallocated",
	"PUSH GS",
	"POP GS",
	"RSM",
	"BTS Ev, Gv",
	"SHRD Ev, Gv, lb",
	"SHRD Ev, Gv, CL",
	"Grp15^1A^1C",
	"IMUL Gv, Ev",

	"CMPXCHG Eb, Gb",//B0
	"CMPXCHG Ev, Gv",
	"LSS Gv, Mp",
	"BTR Ev, Gv",
	"LFS Gv, Mp",
	"LGS Gv, Mp",
	"MOVZX Gv, Eb",
	"MOVZX Gv, Ew",
	"__F3",
	"Grp10^1A_InvalidOpcode^1B",
	"Grp8^1A Ev, lb",
	"BTC Ev, Gv",
	"__F3",
	"__F3",
	"MOVSX Gv, Eb",
	"MOVSX Gv, Ew",

	"XADD Eb, Gb",//C0
	"XADD Ev, Gv",
	"__66F3F2",
	"MOVNTI My, Gy",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"Grp9^1A",
	"BSWAP RAX/EAX/R8/R8D",
	"BSWAP RCX/ECX/R9/R9D",
	"BSWAP RDX/EDX/R10/R10D",
	"BSWAP RBX/EBX/R11/R11D",
	"BSWAP RSP/ESP/R12/R12D",
	"BSWAP RBP/EBP/R13/R13D",
	"BSWAP RSI/ESI/R14/R14D",
	"BSWAP RDIX/EDI/R15/R15D",

	"__66F3F2",//D0
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",

	"__66F3F2",//E0
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",
	"__66F3F2",

	"__66F2",//E0
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
	"__66F2",
};

constexpr char TwoByteOpcode_DecodingTable__[256][32] = {
	"Unallocated",//00
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"VMOVUPS Vps, Wps",//10
	"VMOVUPS Wps, Vps",
	"VMOVLPS Vq, Hq, Mq", // VMOVHLPS Vq, Hq, Uq �� ��
	"VMOVLPS Mq, Vq",
	"VUNPCKLPS Vx, Hx, Wx",
	"VUNPCKHPS Vx, Hx, Wx",
	"VMOVHPS Vdq, Hq, Mq",
	"VMOVHPS Mq, Vq",
	"Unallocated",
	"Unallocated",
	"BNDLDX",
	"BNDSTX",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//20
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//30
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//40
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"VMOVMSKPS Gy, Ups",//50
	"VSQRTPS Vps, Wps",
	"VRSQRTPS Vps, Wps",
	"VECCPPS Vps, Wps",
	"VANDPS Vps, Hps, Wps",
	"VANDNPS Vps, Hps, Wps",
	"VORPS Vps, Hps, Wps",
	"VXORPS Vps, Hps, Wps",
	"VADDPS Vps, Hps, Wps",
	"VMULPS Vps, Hps, Wps",
	"VCVTPS2PD Vpd, Wps",
	"VCTDQ2PS Vps, Wdq",
	"VSUBPS Vps, Hps, Wps",
	"VMINPS Vps, Hps, Wps",
	"VDIVPS Vps, Hps, Wps",
	"VMAXPS Vps, Hps, Wps",

	"PUNPCKLBW Pq, Qd",//60
	"PUNPCKLWD Pq, Qd",
	"PUNPCKLDQ Pq, Qd",
	"PACKSSWB Pq, Qq",
	"PCMPGTB Pq, Qq",
	"PCMPGTW Pq, Qq",
	"PCMPGTD Pq, Qq",
	"PACKUSWB Pq, Qq",
	"PUNPCKHBW Pq, Qd",
	"PUNPCKHWD Pq, Qd",
	"PUNPCKHDQ Pq, Qd",
	"PACKSSDW Pq, Qd",
	"Unallocated",
	"Unallocated",
	"MOVD/MOVQ Pd, Ev",
	"MOVq Pq, Qq",

	"PSHUFW Pq, Qq, lb",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"PCMPEQB Pq, Qq",
	"PCMPEQW Pq, Qq",
	"PCMPEQD Pq, Qq",
	"EMMS_VZEROUPPER_VZEROALL",
	"VMREAD Ey, Gy",
	"VMWRITE Gy, Ey",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"MOVD/MOVQ Ey, Pd",
	"MOVQ Qq, Pq",

	"Unallocated",//80
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//90
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"XADD Eb, Gb",//C0
	"XADD Ev, Gv",
	"VCMPPS Vps, Hps, Wps, lb",
	"MOVNTI My, Gy",
	"PINSRW Pq, Ry/Mw, lb",
	"PEXTRW Gd, Nq, lb",
	"VSHUFPS Vps, Hps, Wps, lb",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//D0
	"PSRAW Pq, Qq",
	"PSRAD Pq, Qq",
	"PAVGW Pq, Qq",
	"PMULHUW Pq, Qq",
	"PMULHW Pq, Qq",
	"Unallocated",
	"MOVNTQ Mq, Pq",
	"PSUBSUB Pq, Qq",
	"PSUBUSW Pq, Qq",
	"PMINUB Pq, Qq",
	"PAND Pq, Qq",
	"PADDUSB Pq, Qq",
	"PADDUSW Pq, Qq",
	"PMAXUB Pq, Qq",
	"PANDN Pq, Qq",

	"PAVGB Pq, Qq",//E0
	"PSRAW Pq, Qq",
	"PSRAD Pq, Qq",
	"PAVGW Pq, Qq",
	"PMULHUW Pq, Qq",
	"PMULHW Pq, Qq",
	"Unallocated",
	"MOVTQ Mq, Pq",
	"PSUBSB Pq, Qq",
	"PSUBSW Pq, Qq",
	"PMINSW Pq, Qq",
	"POR Pq, Qq",
	"PADDSB Pq, Qq",
	"PADDSW Pq, Qq",
	"PMAXSW Pq, Qq",
	"PXOR Pq, Qq",

	"Unallocated",//F0
	"PSLLW Pq, Qq",
	"PSLLD Pq, Qq",
	"PSLLQ Pq, Qq",
	"PMULUDQ Pq, Qq",
	"PMADDWD Pq, Qq",
	"PSADBW Pq, Qq",
	"MASKMOVQ Pq, Nq",
	"PSUBB Pq, Qq",
	"PSUBW Pq, Qq",
	"PSUBD Pq, Qq",
	"PSUBQ Pq, Qq",
	"PADDB Pq, Qq",
	"PADDW Pq, Qq",
	"PADDD Pq, Qq",
	"Unallocated",
};
constexpr char TwoByteOpcode_DecodingTable66[256][32] = {
	"Unallocated",//00
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"VMOVUPD Vpd, Wpd",//10
	"VMOVUPD Wpd, Vpd",
	"VMOVLPD Vqm Hq, Mq",
	"VMOVLPD Mq, Vq",
	"VUNPCKLPD Vx, Hx, Wx",
	"vunpckhpd Vx, Hx, Wx",
	"vmovhpd Vdq, Hq, Mq",
	"vmovhpd Mq, Vq",
	"Unallocated",
	"Unallocated",
	"bndmov",
	"bndmov",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//20
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vmovapd Vpd, Wpd",
	"vmovapd Wpd,Vpd",
	"cvtpi2pd Vpd, Qpi",
	"vmovntpd Mpd, Vpd",
	"cvttpd2pi Ppi, Wpd",
	"cvtpd2pi Qpi, Wpd",
	"vucomisd Vsd, Wsd",
	"vcomisd Vsd, Wsd",

	"Unallocated",//30
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//40
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vmovmskpd Gy,Upd",//50
	"vsqrtpd Vpd, Wpd",
	"Unallocated",
	"Unallocated",
	"vandpd Vpd, Hpd, Wpd",
	"vandnpd Vpd, Hpd, Wpd",
	"vorpd Vpd, Hpd, Wpd",
	"vxorpd Vpd, Hpd, Wpd",
	"vaddpd Vpd, Hpd, Wpd",
	"vmulpd Vpd, Hpd, Wpd",
	"vcvtpd2ps Vps, Wpd",
	"vcvtps2dq Vdq, Wps",
	"vsubpd Vpd, Hpd, Wpd",
	"vminpd Vpd, Hpd, Wpd",
	"vdivpd Vpd, Hpd, Wpd",
	"vmaxpd Vpd, Hpd, Wpd",

	"vpunpcklbw Vx, Hx, Wx",//60
	"vpunpcklwd Vx, Hx, Wx",
	"vpunpckldq Vx, Hx, Wx",
	"vpacksswb Vx, Hx, Wx",
	"vpcmpgtb Vx, Hx, Wx",
	"vpcmpgtw Vx, Hx, Wx",
	"vpcmpgtd Vx, Hx, Wx",
	"vpackuswb Vx, Hx, Wx",
	"vpunpckhbw Vx, Hx, Wx",
	"vpunpckhwd Vx, Hx, Wx",
	"vpunpckhdq Vx, Hx, Wx",
	"vpackssdw Vx, Hx, Wx",
	"vpunpcklqdq Vx, Hx, Wx",
	"vpunpckhqdq Vx, Hx, Wx",
	"vmovd/q Vy, Ey",
	"vmovdqa Vx, Wx",

	"vpshufd Vx, Wx, Ib",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vpcmpeqb Vx, Hx, Wx",
	"vpcmpeqw Vx, Hx, Wx",
	"vpcmpeqd Vx, Hx, Wx",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vhaddpd Vpd, Hpd, Wpd",
	"vhsubpd Vpd, Hpd, Wpd",
	"vmovd/vmovq Ey, Vy",
	"vmovdqa Wx,Vx",

	"Unallocated",//80
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//90
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//C0
	"Unallocated",
	"vcmppd Vpd, Hpd, Wpd, Ib",
	"Unallocated",
	"vpinsrw Vdq,Hdq,Ry/Mw,Ib",
	"vpextrw Gd, Udq, Ib",
	"vshufpd Vpd, Hpd, Wpd, Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vaddsubpd Vpd, Hpd, Wpd",//D0
	"vpsrlw Vx, Hx, Wx",
	"vpsrld Vx, Hx, Wx",
	"vpsrlq Vx, Hx, Wx",
	"vpaddq Vx, Hx, Wx",
	"vpmullw Vx, Hx, Wx",
	"vmovq Wq, Vq",
	"vpmovmskb Gd, Ux",
	"vpsubusb Vx, Hx, Wx",
	"vpsubusw Vx, Hx, Wx",
	"vpminub Vx, Hx, Wx",
	"vpand Vx, Hx, Wx",
	"vpaddusb Vx, Hx, Wx",
	"vpaddusw Vx, Hx, Wx",
	"vpmaxub Vx, Hx, Wx",
	"vpandn Vx, Hx, Wx",

	"vpavgb Vx, Hx, Wx",//E0
	"vpsraw Vx, Hx, Wx",
	"vpsrad Vx, Hx, Wx",
	"vpavgw Vx, Hx, Wx",
	"vpmulhuw Vx, Hx, Wx",
	"vpmulhw Vx, Hx, Wx",
	"vcvttpd2dq Vx, Wpd",
	"vmovntdq Mx, Vx",
	"vpsubsb Vx, Hx, Wx",
	"vpsubsw Vx, Hx, Wx",
	"vpminsw Vx, Hx, Wx",
	"vpor Vx, Hx, Wx",
	"vpaddsb Vx, Hx, Wx",
	"vpaddsw Vx, Hx, Wx",
	"vpmaxsw Vx, Hx, Wx",
	"vpxor Vx, Hx, Wx",

	"Unallocated",//F0
	"vpsllw Vx, Hx, Wx",
	"vpslld Vx, Hx, Wx",
	"vpsllq Vx, Hx, Wx",
	"vpmuludq Vx, Hx, Wx",
	"vpmaddwd Vx, Hx, Wx",
	"vpsadbw Vx, Hx, Wx",
	"vmaskmovdqu Vdq, Udq",
	"vpsubb Vx, Hx, Wx",
	"vpsubw Vx, Hx, Wx",
	"vpsubd Vx, Hx, Wx",
	"vpsubq Vx, Hx, Wx",
	"vpaddb Vx, Hx, Wx",
	"vpaddw Vx, Hx, Wx",
	"vpaddd Vx, Hx, Wx",
	"LD0",
};
constexpr char TwoByteOpcode_DecodingTableF3[256][32] = {
	"Unallocated",//00
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vmovss Vx, Hx, Wss",//10
	"vmovss Wss, Hx, Vss",
	"vmovsldup Vx, Wx",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vmovshdup Vx, Wx",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"bndcl",
	"bndmk",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//20
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vcvtsi2ss Vss, Hss, Ey",
	"Unallocated",
	"vcvttss2si Gy, Wss",
	"vcvtss2si Gy, Wss",
	"Unallocated",
	"Unallocated",

	"Unallocated",//30
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//40
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//50
	"vsqrtss Vss, Hss, Wss",
	"vrsqrtss Vss, Hss, Wss",
	"vrcpss Vss, Hss, Wss",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vaddss Vss, Hss, Wss",
	"vmulss Vss, Hss, Wss",
	"vcvtss2sd Vsd, Hx, Wss",
	"vcvttps2dq Vdq, Wps",
	"vsubss Vss, Hss, Wss",
	"vminss Vss, Hss, Wss",
	"vdivss Vss, Hss, Wss",
	"vmaxss Vss, Hss, Wss",

	"Unallocated",//60
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vmovdqu Vx, Wx",

	"vpshufhw Vx, Wx, Ib",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vmovq Vq, Wq",
	"vmovdqu Wx,Vx",

	"Unallocated",//80
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//90
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//C0
	"Unallocated",
	"vcmpss Vss,Hss,Wss,Ib",
	"Unallocated",
	"vpinsrw Vdq,Hdq,Ry/Mw,Ib",
	"vpextrw Gd, Udq, Ib",
	"vshufpd Vpd,Hpd,Wpd,Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//D0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"movq2dq Vdq, Nq",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//E0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vcvtdq2pd Vx, Wpd",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//F0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};
constexpr char TwoByteOpcode_DecodingTableF2[256][32] = {
	"Unallocated",//00
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vmovsd Vx, Hx, Wsd",//10
	"vmovsd Wsd, Hx, Vsd",
	"vmovddup Vx, Wx",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"bndcu",
	"bndcn",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//20
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vcvtsi2sd Vsd, Hsd, Ey",
	"Unallocated",
	"vcvttsd2si Gy, Wsd",
	"vcvtsd2si Gy, Wsd",
	"Unallocated",
	"Unallocated",

	"Unallocated",//30
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//40
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//50
	"vsqrtsd Vsd, Hsd, Wsd",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vaddsd Vsd, Hsd, Wsd",
	"vmulsd Vsd, Hsd, Wsd",
	"vcvtsd2ss Vss, Hx, Wsd",
	"Unallocated",
	"vsubsd Vsd, Hsd, Wsd",
	"vminsd Vsd, Hsd, Wsd",
	"vdivsd Vsd, Hsd, Wsd",
	"vmaxsd Vsd, Hsd, Wsd",

	"Unallocated",//60
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vpshuflw Vx, Wx, Ib",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vhaddps Vps, Hps, Wps",
	"vhsubps Vps, Hps, Wps",
	"Unallocated",
	"Unallocated",

	"Unallocated",//80
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//90
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//C0
	"Unallocated",
	"vcmpsd Vsd,Hsd,Wsd,Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vaddsubps Vps, Hps, Wps",//D0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"movdq2q Pq, Uq",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//E0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vcvtpd2dq Vx, Wpd",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vlddqu Vx, Mx",//F0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"UD0",
};

constexpr char ThreeByteOpcode_DecodingTableA4[256][32] = {
	"pshufb Pq, Qq",//00
	"phaddw Pq, Qq",
	"phaddd Pq, Qq",
	"phaddsw Pq, Qq",
	"pmaddubsw Pq, Qq",
	"phsubw Pq, Qq",
	"phsubd Pq, Qq",
	"phsubsw Pq, Qq",
	"psignb Pq, Qq",
	"psignw Pq, Qq",
	"psignd Pq, Qq",
	"pmulhrsw Pq, Qq",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//10
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"pabsb Pq, Qq",
	"pabsw Pq, Qq",
	"pabsd Pq, Qq",
	"Unallocated",

	"Unallocated",//20
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//30
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//40
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//50
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//60
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//80
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//90
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//C0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"sha1nexte Vdq,Wdq",
	"sha1msg1 Vdq,Wdq",
	"sha1msg2 Vdq,Wdq",
	"sha256rnds2 Vdq,Wdq",
	"sha256msg1 Vdq,Wdq",
	"sha256msg2 Vdq,Wdq",
	"Unallocated",
	"Unallocated",

	"Unallocated",//D0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//E0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"MOVBE Gy, My",//F0
	"MOVBE My, Gy",
	"ANDN Gy, By, Ey",
	"Unallocated",
	"BZHI Gy, Ey, By",
	"Unallocated",
	"BEXTR Gy, Ey, By",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};
constexpr char ThreeByteOpcode_DecodingTableA466[256][32] = {
	"vpshufb Vx, Hx, Wx",//00
	"vphaddw Vx, Hx, Wx",
	"vphaddd Vx, Hx, Wx",
	"vphaddsw Vx, Hx, Wx",
	"vpmaddubsw Vx, Hx, Wx",
	"vphsubw Vx, Hx, Wx",
	"vphsubd Vx, Hx, Wx",
	"vphsubsw Vx, Hx, Wx",
	"vpsignb Vx, Hx, Wx",
	"vpsignw Vx, Hx, Wx",
	"vpsignd Vx, Hx, Wx",
	"vpmulhrsw Vx, Hx, Wx",
	"vpermilps Vx,Hx,Wx",
	"vpermilpd Vx,Hx,Wx",
	"vtestps Vx, Wx",
	"vtestpd Vx, Wx",

	"pblendvb Vdq, Wdq",//10
	"Unallocated",
	"Unallocated",
	"vcvtph2ps Vx, Wx, Ib",
	"blendvps Vdq, Wdq",
	"blendvpd Vdq, Wdq",
	"vpermps Vqq, Hqq, Wqq",
	"vptest Vx, Wx",
	"vbroadcastss Vx, Wd",
	"vbroadcastsd Vqq, Wq",
	"vbroadcastf128 Vqq, Mdq",
	"Unallocated",
	"vpabsb Vx, Wx",
	"vpabsw Vx, Wx",
	"vpabsd Vx, Wx",
	"Unallocated",

	"vpmovsxbw Vx, Ux/Mq",//20
	"vpmovsxbd Vx, Ux/Md",
	"vpmovsxbq Vx, Ux/Mw",
	"vpmovsxwd Vx, Ux/Mq",
	"vpmovsxwq Vx, Ux/Md",
	"vpmovsxdq Vx, Ux/Mq",
	"Unallocated",
	"Unallocated",
	"vpmuldq Vx, Hx, Wx",
	"vpcmpeqq Vx, Hx, Wx",
	"vmovntdqa Vx, Mx",
	"vpackusdw Vx, Hx, Wx",
	"vmaskmovps Vx,Hx,Mx",
	"vmaskmovpd Vx,Hx,Mx",
	"vmaskmovps Mx,Hx,Vx",
	"vmaskmovpd Mx,Hx,Vx",

	"vpmovzxbw Vx, Ux/Mq",//30
	"vpmovzxbd Vx, Ux/Md",
	"vpmovzxbq Vx, Ux/Mw",
	"vpmovzxwd Vx, Ux/Mq",
	"vpmovzxwq Vx, Ux/Md",
	"vpmovzxdq Vx, Ux/Mq",
	"vpermd Vqq, Hqq, Wqq",
	"vpcmpgtq Vx, Hx, Wx",
	"vpminsb Vx, Hx, Wx",
	"vpminsd Vx, Hx, Wx",
	"vpminuw Vx, Hx, Wx",
	"vpminud Vx, Hx, Wx",
	"vpmaxsb Vx, Hx, Wx",
	"vpmaxsd Vx, Hx, Wx",
	"vpmaxuw Vx, Hx, Wx",
	"vpmaxud Vx, Hx, Wx",

	"vpmulld Vx, Hx, Wx",//40
	"vphminposuw Vdq, Wdq",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vpsrlvd/vpsrlvq Vx, Hx, Wx",
	"vpsravd Vx, Hx, Wx",
	"vpsllvd/vpsllvq Vx, Hx, Wx",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//50
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vpbroadcastd Vx, Wx",
	"vpbroadcastq Vx, Wx",
	"vbroadcasti128 Vqq, Mdq",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//60
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vpbroadcastb Vx, Wx",
	"vpbroadcastw Vx, Wx",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"INVEPT Gy, Mdq",//80
	"INVVPID Gy, Mdq",
	"INVPCID Gy, Mdq",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vpmaskmovd/q Vx, Hx, Mx",
	"Unallocated",
	"vpmaskmovd/q Mx, Vx, Hx",
	"Unallocated",

	"vgatherdd/q Vx, Hx, Wx",//90
	"vgatherqd/q Vx, Hx, Wx",
	"vgatherdps/d Vx, Hx, Wx",
	"vgatherqps/d Vx, Hx, Wx",
	"Unallocated",
	"Unallocated",
	"vfmaddsub132ps/d Vx, Hx, Wx",
	"vfmsubadd132ps/d Vx, Hx, Wx",
	"vfmadd132ps/d Vx, Hx, Wx",
	"vfmadd132ss/d Vx, Hx, Wx",
	"vfmsub132ps/d Vx, Hx, Wx",
	"vfmsub132ss/d Vx, Hx, Wx",
	"vfnmadd132ps/d Vx, Hx, Wx",
	"vfnmadd132ss/d Vx, Hx, Wx",
	"vfnmsub132ps/d Vx, Hx, Wx",
	"vfnmsub132ss/d Vx, Hx, Wx",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vfmaddsub213ps/d Vx, Hx, Wx",
	"vfmsubadd213ps/d Vx, Hx, Wx",
	"vfmadd213ps/d Vx, Hx, Wx",
	"vfmadd213ss/d Vx, Hx, Wx",
	"vfmsub213ps/d Vx, Hx, Wx",
	"vfmsub213ss/d Vx, Hx, Wx",
	"vfnmadd213ps/d Vx, Hx, Wx",
	"vfnmadd213ss/d Vx, Hx, Wx",
	"vfnmsub213ps/d Vx, Hx, Wx",
	"vfnmsub213ss/d Vx, Hx, Wx",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vfmaddsub231ps/d Vx, Hx, Wx",
	"vfmsubadd231ps/d Vx, Hx, Wx",
	"vfmadd231ps/d Vx, Hx, Wx",
	"vfmadd231ss/d Vx, Hx, Wx",
	"vfmsub231ps/d Vx, Hx, Wx",
	"vfmsub231ss/d Vx, Hx, Wx",
	"vfnmadd231ps/d Vx, Hx, Wx",
	"vfnmadd231ss/d Vx, Hx, Wx",
	"vfnmsub231ps/d Vx, Hx, Wx",
	"vfnmsub231ss/d Vx, Hx, Wx",

	"Unallocated",//C0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//D0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"VAESIMC Vdq, Wdq",
	"VAESENC Vdq, Hdq, Wdq",
	"VAESENCLAST Vdq, Hdq, Wdq",
	"VAESDEC Vdq, Hdq, Wdq",
	"VAESDECLAST Vdq, Hdq, Wdq",

	"Unallocated",//E0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"MOVBE Gw, Mw",//F0
	"MOVBE Mw, Gw",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"ADCX Gy, Ey",
	"SHLX Gy, Ey, By",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};
constexpr char ThreeByteOpcode_DecodingTableA4F3_Fx[16][32] = {
	"Unallocated",//F0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"PEXT Gy, By, Ey",
	"ADOX Gy, Ey",
	"SARX Gy, Ey, By",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};
constexpr char ThreeByteOpcode_DecodingTableA4F2_Fx[16][32] = {
	"CRC32 Gd, Eb",//F0
	"CRC32 Gd, Ey",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"PDEP Gy, By, Ey",
	"MULX By, Gy, rDX, Ey",
	"SARX Gy, Ey, By",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};
constexpr char ThreeByteOpcode_DecodingTableA466F2_Fx[16][32] = {
	"CRC32 Gd, Eb",//F0
	"CRC32 Gd, Ew",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};

constexpr char ThreeByteOpcode_DecodingTableA566[256][32]{
	"vpermq Vqq, Wqq, Ib",//00
	"vpermpd Vqq, Wqq, Ib",
	"vpblendd Vx,Hx,Wx,Ib",
	"Unallocated",
	"vpermilps Vx, Wx, Ib",
	"vpermilpd Vx, Wx, Ib",
	"vperm2f128 Vqq,Hqq,Wqq,Ib",
	"Unallocated",
	"vroundps Vx, Wx, Ib",
	"vroundpd Vx, Wx, Ib",
	"vroundss Vss, Wss, Ib",
	"vroundsd Vsd, Wsd, Ib",
	"vblendps Vx, Hx, Wx, Ib",
	"vblendpd Vx, Hx, Wx, Ib",
	"vpblendw Vx, Hx, Wx, Ib",
	"vpalignr Vx, Hx, Wx, Ib",

	"Unallocated",//10
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vpextrb Rd/Mb, Vdq, Ib",
	"vpextrw Rd/Mw, Vdq, Ib",
	"vpextrd/q Ey, Vdq, Ib",
	"vextractps Ed, Vdq, Ib",
	"vinsertf128 Vqq, Hqq, Wqq, Ib",
	"vextractf128 Wdq, Vqq, Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vcvtps2ph Wx, Vx, Ib",
	"Unallocated",
	"Unallocated",

	"vpinsrb Vdq, Hdq, Ry/Mb, Ib",//20
	"vinsertps Vdq, Hdq, Udq/Md, Ib",
	"vpinsrd/q Vdq, Hdq, Ey, Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//30
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vinserti128 Vqq, Hqq, Wqq, Ib",
	"vextracti128 Wdq, Vqq, Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vdpps Vx, Hx, Wx, Ib",//40
	"vdppd Vdq, Hdq, Wdq, Ib",
	"vmpsadbw Vx, Hx, Wx, Ib",
	"Unallocated",
	"vpclmulqdq Vdq, Hdq, Wdq, Ib",
	"Unallocated",
	"vperm2i128 Vqq, Hqq, Wqq, Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"vblendvps Vx, Hx, Wx, Lx",
	"vblendvpd Vx, Hx, Wx, Lx",
	"vpblendvb Vx, Hx, Wx, Lx",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//50
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"vpcmpestrm Vdq, Wdq, Ib",//60
	"vpcmpestri Vdq, Wdq, Ib",
	"vpcmpistrm Vdq, Wdq, Ib",
	"vpcmpistri Vdq, Wdq, Ib",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//70
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//80
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//90
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//A0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//B0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//C0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//D0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"VAESKEYGEN Vdq, Wdq, Ib",

	"Unallocated",//E0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",

	"Unallocated",//F0
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
	"Unallocated",
};
constexpr char ThreeByteOpcode_DecodingTableA5_0F[32] = "palignr Pq, Qq, Ib";
constexpr char ThreeByteOpcode_DecodingTableA5_CC[32] = "sha1rnds4 Vdq, Wdq, Ib";
constexpr char ThreeByteOpcode_DecodingTableA5F2_F0[32] = "RORX Gy, Ey, Ib";

//addressing replace string

/*
1. regA -> rax / eax / mmx0 ...
2. disp8 -> 1byte disp
3. SIB -> SIB addressing
*/

// 5bit (r/m 3bit) + (mod 2 bit)
constexpr char Addressing16_DecodingTable[32][32] = {
	"[BX + SI]", // mod == 00
	"[BX + DI]",
	"[BP + SI]",
	"[BP + DI]",
	"[SI]",
	"[DI]",
	"[disp16]",
	"[BX]",

	"[BX + SI + disp8]", // mod == 01
	"[BX + DI + disp8]",
	"[BP + SI + disp8]",
	"[BP + DI + disp8]",
	"[SI + disp8]",
	"[DI + disp8]",
	"[BP + disp8]",
	"[BX + disp8]",

	"[BX + SI + disp16]", // mod == 10
	"[BX + DI + disp16]",
	"[BP + SI + disp16]",
	"[BP + DI + disp16]",
	"[SI + disp16]",
	"[DI + disp16]",
	"[BP + disp16]",
	"[BX + disp16]",

	"AX", // mod == 11
	"CX",
	"DX",
	"BX",
	"SP",
	"BP",
	"SI",
	"DI",
};

// 6bit (r/m 4bit) + (mod 2 bit)
constexpr char Addressing86_DecodingTable[64][32] = {
	"[reg00]", // mod == 00
	"[reg01]",
	"[reg02]",
	"[reg03]",
	"[SIB]",
	"[RIP/EIP + disp32]",
	"[reg06]",
	"[reg07]",
	"[reg08]",
	"[reg09]",
	"[reg10]",
	"[reg11]",
	"[SIB]",
	"[RIP/EIP + disp32]",
	"[reg14]",
	"[reg15]",

	"[reg00 + disp8]", // mod == 01
	"[reg01 + disp8]",
	"[reg02 + disp8]",
	"[reg03 + disp8]",
	"[SIB + disp8]",
	"[reg05 + disp8]",
	"[reg06 + disp8]",
	"[reg07 + disp8]",
	"[reg08 + disp8]",
	"[reg09 + disp8]",
	"[reg10 + disp8]",
	"[reg11 + disp8]",
	"[SIB + disp8]",
	"[reg13 + disp8]",
	"[reg14 + disp8]",
	"[reg15 + disp8]",

	"[reg00 + disp32]", // mod == 10
	"[reg01 + disp32]",
	"[reg02 + disp32]",
	"[reg03 + disp32]",
	"[SIB + disp32]",
	"[reg05 + disp32]",
	"[reg06 + disp32]",
	"[reg07 + disp32]",
	"[reg08 + disp32]",
	"[reg09 + disp32]",
	"[reg10 + disp32]",
	"[reg11 + disp32]",
	"[SIB + disp32]",
	"[reg13 + disp32]",
	"[reg14 + disp32]",
	"[reg15 + disp32]",

	"reg00", // mod == 11
	"reg01",
	"reg02",
	"reg03",
	"reg04",
	"reg05",
	"reg06",
	"reg07",
	"reg08",
	"reg09",
	"reg10",
	"reg11",
	"reg12",
	"reg13",
	"reg14",
	"reg15",
};

// addressing sib -> RangeArr / base -> baseregister / index->indexregister / s -> 2^scalenum
constexpr unsigned char AddressingSIB_BaseTable[16] = {
	1, 1, 1, 1, 1,
	2,
	3, 3, 3, 3, 3, 3, 3,
	4,
	5, 5
};
constexpr unsigned char AddressingSIB_IndexTable[16] = {
	1, 1, 1, 1,
	2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};
constexpr char AddressingSIB_MOD00Table[15][32] = {
	"base + index * s",
	"index * s + disp32",
	"base + index * s",
	"index * s + disp32",
	"base + index * s",

	"base",
	"disp32",
	"base",
	"disp32",
	"base",

	"base + index * s",
	"index * s + disp32",
	"base + index * s",
	"index * s + disp32",
	"base + index * s",
};
constexpr char AddressingSIB_MOD01Table[3][32] = {
	"base + index * s + disp8",
	"base + disp8",
	"base + index * s + disp8",
};
constexpr char AddressingSIB_MOD10Table[3][32] = {
	"base + index * s + disp32",
	"base + disp32",
	"base + index * s + disp32",
};
//MOD != 11
//AddressingSIB_MOD00Table[5 * indextable[index] + basetable[base]] -> access way;

struct asmtext{
	lcstr codetxt;
};

struct mcode_x64{
	unsigned char data[16] = {};
};

enum class x86_PrefixType{
	G1_LOCK = 0xf0,
	G1_REPNE_REPNZ = 0xf2,
	G1_REP_REPE_REPZ = 0xf3,
	
	G2_CS_SegmentOverride = 0x2e,
	G2_SS_SegmentOverride = 0x36,
	G2_DS_SegmentOverride = 0x3e,
	G2_ES_SegmentOverride = 0x26,
	G2_FS_SegmentOverride = 0x65,
	G2_GS_SegmentOverride = 0x65,
	G2_BranchNotTaken = 0x2e,
	G2_BranchTaken = 0x3e,

	G3_OperandSizeOverride = 0x66,
	
	G4_AddressSizeOverride = 0x67,

	Mandatory_66 = 0x66,
	Mandatory_F3 = 0xf3,
	Mandatory_F2 = 0xf2,
	//REX - 0x4?
	VEX3byte = 0xc4,
	VEX2byte = 0xc5,
	XOP3byte = 0x8f,
	//3D Now! - 0x0f + 0x0f
};

int seekstr(const char* seek_str, char* big_str, int biglen) {
	int slen = strlen(seek_str);
	for (int i = 0; i < biglen-slen; ++i) {
		char* ptr = &big_str[i];
		bool match = true;
		for (int k = 0; k < slen; ++k) {
			if (seek_str[k] != ptr[k]) {
				match = false;
				break;
			}
		}

		if (match) {
			return i;
		}
	}

	return -1;
}

void replace_str(char* seek_str, char* replace_str, lcstr* big_str) {
	int slen = strlen(replace_str);
	int seeklen = strlen(seek_str);
	int seekindex = seekstr(seek_str, big_str->c_str(), big_str->size());
	int bl = big_str->size();
	for (int i = seekindex; i < seekindex + seeklen; ++i) {
		big_str->erase(i);
	}
	for (int i = 0; i < slen; ++i) {
		big_str->insert(seekindex + i, replace_str[i]);
	}
}

asmtext GetASM(mcode_x64 mcode){
	asmtext r;
	for(int i=0;i<32;++i){
		r.codetxt[i] = 0;
	}
	//g1
	unsigned int pivot = 0;
	bool Prefix_LOCK = mcode.data[pivot] == (unsigned char)x86_PrefixType::G1_LOCK;
	bool Prefix_REPNE_PEPNZ = mcode.data[pivot] == (unsigned char)x86_PrefixType::G1_REPNE_REPNZ;
	bool Prefix_REP_REPE_REPZ = mcode.data[pivot] == (unsigned char)x86_PrefixType::G1_REP_REPE_REPZ;
	if((Prefix_LOCK || Prefix_REPNE_PEPNZ) || Prefix_REP_REPE_REPZ) pivot += 1;
	//g2
	bool Prefix_CS = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_CS_SegmentOverride;
	bool Prefix_SS = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_SS_SegmentOverride;
	bool Prefix_DS = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_DS_SegmentOverride;
	bool Prefix_ES = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_ES_SegmentOverride;
	bool Prefix_FS = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_FS_SegmentOverride;
	bool Prefix_GS = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_GS_SegmentOverride;
	bool Prefix_BranchNotTaken = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_BranchNotTaken;
	bool Prefix_BranchTaken = mcode.data[pivot] == (unsigned char)x86_PrefixType::G2_BranchTaken;
	if(((Prefix_CS || Prefix_SS) || (Prefix_DS || Prefix_ES)) || ((Prefix_FS|| Prefix_GS) || (Prefix_BranchNotTaken || Prefix_BranchTaken))) {
		pivot += 1;
	}
	//g3
	bool Prefix_OperandSizeOverride = mcode.data[pivot] == (unsigned char)x86_PrefixType::G3_OperandSizeOverride;
	if(Prefix_OperandSizeOverride) pivot += 1;
	//g4
	bool Prefix_AddressSizeOverride = mcode.data[pivot] == (unsigned char)x86_PrefixType::G4_AddressSizeOverride;
	if(Prefix_AddressSizeOverride) pivot += 1;
	
	//mandatory prefix
	bool Prefix_Mandatory66 = mcode.data[pivot] == (unsigned char)x86_PrefixType::Mandatory_66;
	if(Prefix_Mandatory66) pivot += 1;
	bool Prefix_MandatoryF3 = mcode.data[pivot] == (unsigned char)x86_PrefixType::Mandatory_F3;
	if(Prefix_MandatoryF3) pivot += 1;
	bool Prefix_MandatoryF2 = mcode.data[pivot] == (unsigned char)x86_PrefixType::Mandatory_F2;
	if(Prefix_MandatoryF2) pivot += 1;

	//REX
	bool Prefix_REX = mcode.data[pivot] & 0xF0 == 0x40;
	bool REX_Wbit = false;
	bool REX_Rbit = false;
	bool REX_Xbit = false;
	bool REX_Bbit = false;
	
	bool Prefix_3byteVEX = mcode.data[pivot] == (unsigned char)x86_PrefixType::VEX3byte;
	bool Prefix_2byteVEX = mcode.data[pivot] == (unsigned char)x86_PrefixType::VEX2byte;
	bool Prefix_3byteXOP = mcode.data[pivot] == (unsigned char)x86_PrefixType::XOP3byte;
	bool Prefix_3dnow = mcode.data[pivot] == 0x0f;
	bool VEXXOP_Rbit = false;
	bool VEXXOP_Xbit = false;
	bool VEXXOP_Bbit = false;
	unsigned char VEXXOP_MapSelect = 0; // 5bit
	bool VEXXOP_W_or_E = false;
	unsigned char VEXXOP_VVVV = 0; // 4bit
	bool VEXXOP_L = false;
	unsigned char VEXXOP_pp = 0; // 2bit

	if(Prefix_REX){
		REX_Wbit = !!(mcode.data[pivot] & 0x80);
		REX_Rbit = !!(mcode.data[pivot] & 0x40);
		REX_Xbit = !!(mcode.data[pivot] & 0x20);
		REX_Bbit = !!(mcode.data[pivot] & 0x10);
		pivot += 1;
		goto GETASMTEXT_OPCODE;
	}
	else if(Prefix_3byteVEX || Prefix_3byteXOP){
		pivot += 1;
		VEXXOP_Rbit = !!(mcode.data[pivot] & 0x80);
		VEXXOP_Xbit = !!(mcode.data[pivot] & 0x40);
		VEXXOP_Bbit = !!(mcode.data[pivot] & 0x20);
		VEXXOP_MapSelect = mcode.data[pivot] & 0x1F;
		pivot += 1;
		VEXXOP_W_or_E = !!(mcode.data[pivot] & 0x80);
		VEXXOP_VVVV = (mcode.data[pivot] & 0x78) >> 3;
		VEXXOP_L = !!(mcode.data[pivot] & 0x04);
		VEXXOP_pp = mcode.data[pivot] & 0x03;
		pivot += 1;
		goto GETASMTEXT_OPCODE;
	}
	else if(Prefix_2byteVEX){
		pivot += 1;
		VEXXOP_W_or_E = !!(mcode.data[pivot] & 0x80);
		VEXXOP_VVVV = (mcode.data[pivot] & 0x78) >> 3;
		VEXXOP_L = !!(mcode.data[pivot] & 0x04);
		VEXXOP_pp = mcode.data[pivot] & 0x03;
		pivot += 1;
		goto GETASMTEXT_OPCODE;
	}
	else if(Prefix_3dnow){
		pivot += 1;
		if(mcode.data[pivot] == 0x0f){
			goto GETASMTEXT_OPCODE;
		}
		else return r;
	}

	GETASMTEXT_OPCODE:
	char* sudo = (char*)OneByteOpcode_DecodingTable[mcode.data[pivot]];
	if(strcmp(sudo, "2byte Escape") == 0){
		pivot += 1;
		sudo = (char*)TwoByteOpcode_DecodingTable[mcode.data[pivot]];
		goto GETASMTEXT_TWOBYTEOPCODE;
	}
	else{
		// r = sudo;
	}

	GETASMTEXT_TWOBYTEOPCODE:
	if(mcode.data[pivot] == 0x38){
		//3byte opcode A4 table
		goto GETASMTEXT_THREEBYTEOPCODE_A4;
	}
	else if(mcode.data[pivot] == 0x3A){
		//3byte opcode A5 table
		goto GETASMTEXT_THREEBYTEOPCODE_A5;
	}
	else if(strcmp(sudo, "__66F3F2") == 0){
		if(Prefix_Mandatory66){
			sudo = (char*)TwoByteOpcode_DecodingTable66[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
		else if(Prefix_MandatoryF3){
			sudo = (char*)TwoByteOpcode_DecodingTableF3[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
		else if(Prefix_MandatoryF2){
			sudo = (char*)TwoByteOpcode_DecodingTableF2[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
	}
	else if(strcmp(sudo, "__66F3") == 0){
		if(Prefix_Mandatory66){
			sudo = (char*)TwoByteOpcode_DecodingTable66[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
		else if(Prefix_MandatoryF3){
			sudo = (char*)TwoByteOpcode_DecodingTableF3[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
	}
	else if(strcmp(sudo, "__66F2") == 0){
		if(Prefix_Mandatory66){
			sudo = (char*)TwoByteOpcode_DecodingTable66[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
		else if(Prefix_MandatoryF2){
			sudo = (char*)TwoByteOpcode_DecodingTableF2[mcode.data[pivot]];
			pivot+=1;
			goto GETASMTEXT_MODRM;
		}
	}

	GETASMTEXT_THREEBYTEOPCODE_A4:

	GETASMTEXT_THREEBYTEOPCODE_A5:

GETASMTEXT_MODRM:
	r.codetxt.NULLState();
	r.codetxt.Init(32, false);
	r.codetxt = sudo;

	bool requireMODRM = false;
	int len = strlen(sudo);
	for (int i = 0; i < len; ++i) {
		if (sudo[i] == ' ') {
			requireMODRM = true;
			break;
		}
	}

	if (requireMODRM) {
		unsigned char MODRM_mod = (mcode.data[pivot] & 0xC0) >> 6;
		unsigned char MODRM_reg = (mcode.data[pivot] & 0x38) >> 3;
		unsigned char MODRM_rm = (mcode.data[pivot] & 0x07);
		char* addstr;
		if (Prefix_REX) {
			//32bit addressing
			if (REX_Rbit) {
				MODRM_reg += 8;
			}
			if (REX_Bbit) {
				MODRM_rm += 8;
			}
			addstr = (char*)Addressing86_DecodingTable[(MODRM_mod << 4) + MODRM_rm];
			bool SIBMOD = seekstr("SIB", addstr, 32);
			bool disp8Mod = seekstr("disp8", addstr, 32);
			bool disp16Mod = seekstr("disp16", addstr, 32);
			bool disp32Mod = seekstr("disp32", addstr, 32);
			bool reg = seekstr("reg", addstr, 32);

			if (SIBMOD) {
				pivot += 1;
				unsigned char sibbyte = mcode.data[pivot];
				unsigned char scale = sibbyte >> 6;
				unsigned char index = (sibbyte & 0x3F) >> 3;
				unsigned char base = sibbyte & 0x07;
				char* replaceStr;
				if (REX_Xbit) {
					index += 8;
				}
				if (REX_Bbit) {
					base += 8;
				}
				unsigned char basei = AddressingSIB_BaseTable[base];
				unsigned char indexi = AddressingSIB_IndexTable[index];
				if (MODRM_mod == 0) {
					replaceStr = (char*)AddressingSIB_MOD00Table[5 * indexi + basei];
				}
				else if (MODRM_mod == 1) {
					replaceStr = (char*)AddressingSIB_MOD01Table[indexi];
				}
				else if (MODRM_mod == 2) {
					replaceStr = (char*)AddressingSIB_MOD10Table[indexi];
				}

				replace_str((char*)"SIB", replaceStr, &r.codetxt);
			}
		}
		else {
			//16bit addressing
			addstr = (char*)Addressing16_DecodingTable[(MODRM_mod << 3) + MODRM_rm];
		}
	}
	
	GETASMTEXT_SIB:
}

mcode_x64 GetMcode(asmtext text){

}

int main() {

	return 0;
}