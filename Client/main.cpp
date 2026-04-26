#define _WIN32_WINNT 0x0600
#include<iostream>
#include<winsock2.h>
#include<tchar.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

/*
Initialize the winsocket library

Create the socket

coonect to server

send/recv

close the socket 

cleanup the winsock

*/

bool Initialize()

{
    WSADATA data;
    return WSAStartup(MAKEWORD(2,2), &data)==0;
}

int main()
{   cout<<"Client code"<<endl;

    if(!Initialize()){
        cout<<"Winsocket initialization failed!"<<endl;
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM , 0);

    if(s == INVALID_SOCKET)
    {
        cout<<"socket creation failed!"<<endl;
        return 1;
    }

    //connect to server
    //string serveraddr = "127.0.0.1";
    int port = 54321;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    //convert ip(0.0.0.0) , put it inside sin_family in binary
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if( serveraddr.sin_addr.s_addr == INADDR_NONE ){
         cout << "Invalid IP address" << endl;
        return 1;
    }

    if(connect(s,reinterpret_cast<sockaddr*>(&serveraddr),sizeof(serveraddr)) ==  SOCKET_ERROR){
        cout<<"not able to connect to server"<<endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout<<"successfully connected to server"<<endl;

    //send/recv
    string message=" Hello there ";

    int bytes_sent=send(s,message.c_str(),message.length(),0);

    if(bytes_sent == SOCKET_ERROR)
    {
        cout<<"sent failed"<<endl;
        return 1;
    }

    closesocket(s);

    WSACleanup();
    return 0;
}