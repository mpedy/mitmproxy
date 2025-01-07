#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "psapi.lib")

void PrintProcessInfo(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL) {
        printf("Impossibile aprire il processo con PID %lu\n", processId);
        return;
    }

    // Get the list of process identifiers.  
   DWORD aProcesses[1024], cbNeeded, cProcesses;
   unsigned int i;
  
   //This returns a list of handles to processes running on the system as an array.
   if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
      return;
  
   // Calculate how many process identifiers were returned.  
   cProcesses = cbNeeded / sizeof(DWORD);

   std::cout<<"Numero di processi: "<<cProcesses<<std::endl;

    // Buffer per il nome del processo
    char processName[MAX_PATH];
    std::cout<<"Handle: "<<hProcess<<std::endl;
    int count = GetModuleBaseNameA(hProcess, GetModuleHandle(NULL), processName, MAX_PATH);
    std::cout<<"Count: "<<count<<std::endl;
    if (1==1) {
        std::cout<<"Siamo qui!! Nome: "<<processName<<std::endl;
        printf("PID: %lu, Nome: %s\n", processId, processName);
    } else {
        printf("PID: %lu, Nome non disponibile\n", processId);
    }

    // Chiudi l'handle del processo
    CloseHandle(hProcess);
}

int main() {
    DWORD pid = 34100; // Sostituisci con un PID reale
    PrintProcessInfo(pid);
    return 0;
}
