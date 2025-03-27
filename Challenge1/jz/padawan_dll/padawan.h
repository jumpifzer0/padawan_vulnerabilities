#ifndef PADAWANDLL_H
#define PADAWANDLL_H

#include <winsock2.h>

#ifdef PADAWAN_EXPORTS
#define PADAWAN_API __declspec(dllexport)
#else
#define PADAWAN_API __declspec(dllimport)
#endif 


// [Functions that handle messaging capabilities]
extern "C" PADAWAN_API void formatMsg(char* src, char* dest);
extern "C" PADAWAN_API bool validateMsgHeader(char* msg);
extern "C" PADAWAN_API void parseMsg(char* src,char* dest);


// [Functions for other capabilities]
extern "C" PADAWAN_API void printCharArray(char* src);
extern "C" PADAWAN_API void assemblycode();


// [Functions that handle networking capabilities]
// [ >> General Networking Functions ]
// Initializes Winsock
extern "C" PADAWAN_API int  InitWinsock();
// Cleans up Winsock
extern "C" PADAWAN_API void  CleanupWinsock();
// Close a socket
extern "C" PADAWAN_API void  CloseSocket(SOCKET sock);
// Send data through the socket
extern "C" PADAWAN_API int  SendData(SOCKET sock, const char* data, int len);
// Receive data from the socket
extern "C" PADAWAN_API int  ReceiveData(SOCKET sock, char* bufferToSaveTo, int len);

// [ >> Server Networking Functions ]
// Accept an incoming connection (Server-side)
extern "C" PADAWAN_API SOCKET  AcceptConnection(SOCKET* serverSocket);
// Server-side: Listens for incoming connections
extern "C" PADAWAN_API int  ListenForConnections(SOCKET* sock, int backlog);
// Server-side: Binds a socket to a port
extern "C" PADAWAN_API int  BindSocket(SOCKET* sock, const char* ip, unsigned short port);

// [ >> Client Networking Functions ]
// Client-side: Connects to the server
extern "C" PADAWAN_API int  ConnectToServer(SOCKET* sock, const char* ip, unsigned short port);


#endif // PADAWANDLL_H