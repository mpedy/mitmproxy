#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "psapi.lib")
#include "psapi.h"

void DisplayProcessNameAndID( DWORD processID )
{
   TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
  
   // Get a handle to the process.  
   HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
      PROCESS_VM_READ,
      FALSE, processID );
  
   // Get the process name.  
   if (NULL != hProcess )
   {
      HMODULE hMod;
      DWORD cbNeeded;
     
      //Given a handle to a process, this returns all the modules running within the process.
      //The first module is the executable running the process,
      //and subsequent handles describe DLLs loaded into the process.
      if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
      {
         //This function returns the short name for a module,
         //typically the file name portion of the EXE or DLL
         GetModuleBaseName( hProcess, hMod, szProcessName,
            sizeof(szProcessName)/sizeof(TCHAR) );
      }
   }
  
   // Display the process name and identifier.
   std::cout<<"Text: "<<szProcessName<<", PID : "<< processID<<std::endl;
  
   //close the process handle
   CloseHandle( hProcess );
}

int main()
{
   // Get the list of process identifiers.  
   DWORD aProcesses[1024], cbNeeded, cProcesses;
   unsigned int i;
  
   //This returns a list of handles to processes running on the system as an array.
   if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
      return 0;
  
   // Calculate how many process identifiers were returned.  
   cProcesses = cbNeeded / sizeof(DWORD);
  
   // Display the name and process identifier for each process.  
   for ( i = 0; i < cProcesses; i++ )
      if( aProcesses[i] != 0 )
         DisplayProcessNameAndID( aProcesses[i] );

    return 0;
}