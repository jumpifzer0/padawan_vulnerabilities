g++ -c -DPADAWAN_EXPORT padawan.cpp
g++ -shared -o padawan.dll padawan.o -Wl,--out-implib=padawan.a,--image-base=0x20010000,--disable-dynamicbase -lws2_32
g++ client.cpp -lpadawan -L. -lws2_32 -fset-stack-executable -o client.exe
g++ server.cpp -lpadawan -L. -lws2_32 -fset-stack-executable -o server.exe