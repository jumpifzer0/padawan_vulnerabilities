Step 1: compile the dll

g++ -c -DPADAWAN_EXPORT padawan.cpp
g++ -shared -o padawan.dll padawan.o -Wl,--out-implib=padawan.a -lws2_32

Step 2: compile the client and server program

g++ client.cpp -lpadawan -L. -lws2_32 -o client.exe
g++ server.cpp -lpadawan -L. -lws2_32 -o server.exe
