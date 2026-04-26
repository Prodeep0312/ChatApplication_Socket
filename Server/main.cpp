#define _WIN32_WINNT 0x0600
#include<iostream>
#include<winsock2.h>
#include<tchar.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

/*
Initialize the winsocket library

Create the socket

Get the ip and port

Bind the ip/port with socket

Listen on the socket

Accept (Blocking)

recv and send

close the connection

cleanup the winsock

*/

bool Initialize()

{
    WSADATA data;
    return WSAStartup(MAKEWORD(2,2), &data)==0;
}

int main()
{   cout<<"Server code"<<endl;

    if(!Initialize()){
        cout<<"Winsocket initialization failed!"<<endl;
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM , 0);

    if(listenSocket == INVALID_SOCKET)
    {
        cout<<"socket creation failed!"<<endl;
        return 1;
    }

    //create address structure
    int port = 54321;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    //convert ip(0.0.0.0) , put it inside sin_family in binary
    serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if( serveraddr.sin_addr.s_addr == INADDR_NONE ){
        cout<<"setting address structure failed"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    //bind
   if(bind(listenSocket,reinterpret_cast<sockaddr*>(&serveraddr) , sizeof(serveraddr))== SOCKET_ERROR){
    cout<<"binding failed!"<<endl;
     closesocket(listenSocket);
        WSACleanup();
        return 1;
   }

   //listen
   if(listen(listenSocket,SOMAXCONN) == SOCKET_ERROR){
     cout<<"Listen failed!"<<endl;
     closesocket(listenSocket);
        WSACleanup();
        return 1;
   }

   cout<<"Server has started listening on port: "<<port<<endl;

   //accept
   SOCKET clientSocket=accept(listenSocket, nullptr, nullptr);

   if(clientSocket == INVALID_SOCKET)
   {
    cout<<"Invalid client socket"<<endl;
    return 1;
   }

   //recv
   char buffer[4096];
   int bytes_received=recv(clientSocket,buffer,sizeof(buffer),0);

   string message(buffer,bytes_received);
   cout<<"message from client: "<<message<<endl;

   closesocket(clientSocket);
   closesocket(listenSocket);

    WSACleanup();
    return 0;
}