#ifndef EXAMPLE_H
#define EXAMPLE_H

#ifdef PADAWAN_EXPORT
#define PADAWAN_API __declspec(dllexport)
#else
#define PADAWAN_API __declspec(dllimport)
#endif


#include <stdbool.h>
#define CALL __cdecl

// add all the functions over here

/*
* FormatMsg()
* ValidateMsg(Header Check)
* Connect()
* Disconnect()
* Receive()
* Send()
*/


extern "C" PADAWAN_API void formatMsg(char* src, char* dest);

extern "C" PADAWAN_API bool validateMsg(char* msg);

extern "C" PADAWAN_API void parseMsg(char* src,char* dest);




#include <winsock2.h>

// #ifdef __cplusplus
// extern "C" {
// #endif

	// Initializes Winsock
	extern "C" PADAWAN_API int  InitWinsock();

	// Cleans up Winsock
	extern "C" PADAWAN_API void  CleanupWinsock();

	// Server-side: Binds a socket to a port
	extern "C" PADAWAN_API int  BindSocket(SOCKET* sock, const char* ip, unsigned short port);

	// Client-side: Connects to the server
	extern "C" PADAWAN_API int  ConnectToServer(SOCKET* sock, const char* ip, unsigned short port);

	// Server-side: Listens for incoming connections
	extern "C" PADAWAN_API int  ListenForConnections(SOCKET* sock, int backlog);

	// Accept an incoming connection (Server-side)
	extern "C" PADAWAN_API SOCKET  AcceptConnection(SOCKET* serverSocket);

	// Send data through the socket
	extern "C" PADAWAN_API int  SendData(SOCKET sock, const char* data, int len);

	// Receive data from the socket
	extern "C" PADAWAN_API int  ReceiveData(SOCKET sock, char* buffer, int len);

	// Close a socket
	extern "C" PADAWAN_API void  CloseSocket(SOCKET sock);

	extern "C" PADAWAN_API void printCharArray(char* src);

	extern "C" PADAWAN_API void assemblycode();

// #ifdef __cplusplus
// }
// #endif
#endif




