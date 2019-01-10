#include "memory.h"
#include <vector>
#include <fstream>

using namespace std;

DWORD enginedll;
DWORD enginedll_size;

int value = 1;

/*Я не уверен, что код андетектед, используйте на свой страх и риск. Автор: ripple. Дискорд: ripple#1337*/

void SetClanTag(const char* tag, const char* name)
{
	unsigned char Shellcode[] =
		"\x51"                    //push ecx 
		"\x52"                    //push edx 
		"\xB9\x00\x00\x00\x00"    //mov ecx,00000000 { 0 } 
		"\xBA\x00\x00\x00\x00"    //mov edx,00000000 { 0 } 
		"\xE8\x00\x00\x00\x00"    //call 0 
		"\x83\x04\x24\x0A"        //add dword ptr [esp],0A { 10 } 
		"\x68\x00\x00\x00\x00"    //push engine.dll+9AC90 
		"\xC3"                    //ret 
		"\x5A"                    //pop edx 
		"\x59"                    //pop ecx 
		"\xC3"                    //ret 
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10] 
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10] 
		;

	static unsigned int SHELLCODE_SIZE = sizeof(Shellcode) - 0x21;
	unsigned int TAG_SIZE = (strlen(tag) > 15) ? 15 : strlen(tag);
	unsigned int NAME_SIZE = (strlen(name) > 15) ? 15 : strlen(name);
	unsigned int DATA_SIZE = TAG_SIZE + NAME_SIZE + 2;

	LPVOID pShellCodeAdress = VirtualAllocEx(
		memory->process,
		0,
		SHELLCODE_SIZE + DATA_SIZE,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	);

	DWORD tagAdress = (DWORD)pShellCodeAdress + SHELLCODE_SIZE;
	DWORD nameAdress = (DWORD)pShellCodeAdress + SHELLCODE_SIZE + TAG_SIZE + 1;
	DWORD fnSetClanAdress = memory->grabSig(enginedll, enginedll_size, (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15", "xxxxxxxxx");  //Engine.dll + 0x9AC90 

	memcpy(Shellcode + 0x3, &tagAdress, sizeof(DWORD));
	memcpy(Shellcode + 0x8, &nameAdress, sizeof(DWORD));
	memcpy(Shellcode + 0x16, &fnSetClanAdress, sizeof(DWORD));
	memcpy(Shellcode + SHELLCODE_SIZE, tag, TAG_SIZE);
	memcpy(Shellcode + SHELLCODE_SIZE + TAG_SIZE + 1, name, NAME_SIZE);

	WriteProcessMemory(memory->process, pShellCodeAdress, Shellcode, SHELLCODE_SIZE + DATA_SIZE, 0);

	HANDLE hThread = CreateRemoteThread(memory->process, NULL, NULL, (LPTHREAD_START_ROUTINE)pShellCodeAdress, NULL, NULL, NULL);
	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(memory->process, pShellCodeAdress, 0, MEM_RELEASE);
}

void main()
{
	memory->Process("csgo.exe");
	enginedll = memory->module("engine.dll");
	enginedll_size = memory->moduleSize("engine.dll");

	printf("RippleHack Clan Tag. Discord: ripple#1337\n\n");
	printf("Loaded.");

	while (true)
	{
		switch (value)
		{
		case 1: {		SetClanTag("r", "AIMWARE.NET");			Sleep(800);		 }
		case 2: {		SetClanTag("ri", "AIMWARE.NET");		Sleep(800);		 }
		case 3: {		SetClanTag("rip", "AIMWARE.NET");		Sleep(800);		 }
		case 4: {		SetClanTag("ripp", "AIMWARE.NET");			Sleep(800);		 }
		case 5: {		SetClanTag("rippl", "AIMWARE.NET");		Sleep(800);		 }
		case 6: {		SetClanTag("ripple", "AIMWARE.NET");	Sleep(800);		 }
		case 7: {		SetClanTag("rippleh", "AIMWARE.NET");		Sleep(800);		 }
		case 8: {		SetClanTag("rippleha", "AIMWARE.NET");	Sleep(800);		 }
		case 9: {		SetClanTag("ripplehac", "AIMWARE.NET");	Sleep(800);		 }
		case 10:{		SetClanTag("ripplehack", "AIMWARE.NET");	Sleep(1200);		 }
		case 11: {		SetClanTag("ripplehac", "AIMWARE.NET");	Sleep(800);		 }
		case 12: {		SetClanTag("rippleha", "AIMWARE.NET");	Sleep(800);		 }
		case 13: {		SetClanTag("rippleh", "AIMWARE.NET");	Sleep(800);		 }
		case 14: {		SetClanTag("ripple", "AIMWARE.NET");	Sleep(800);		 }
		case 15: {		SetClanTag("rippl", "AIMWARE.NET");	Sleep(800);		 }
		case 16: {		SetClanTag("ripp", "AIMWARE.NET");	Sleep(800);		 }
		case 17: {		SetClanTag("rip", "AIMWARE.NET");	Sleep(800);		 }
		case 18: {		SetClanTag("ri", "AIMWARE.NET");	Sleep(800);		 }
		case 19: {		SetClanTag("r", "AIMWARE.NET");	Sleep(800);		 }

		case 20:
		{
			SetClanTag("ripple#1337", "AIMWARE.NET");
			value = 1;

			Sleep(1500);
		}
		value++;
		}
	}
}
