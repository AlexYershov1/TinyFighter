#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "55001"

#include "network.h"

//--------------------------------------------//
void init_socket_library() {
    WSADATA wsaData;

    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(-1);
    }
}

//--------------------------------------------//
void* server_wait_for_client() {
    int iResult;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(-1);
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        exit(-1);
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        exit(-1);
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        exit(-1);
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        exit(-1);
    }

    // No longer need server socket
    closesocket(ListenSocket);

    return (void*)ClientSocket;
}

//--------------------------------------------//
void* client_connect_to_server() {
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(-1);
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            exit(-1);
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        exit(-1);
    }

    return (void*)ConnectSocket;
}
//--------------------------------------------//
void socket_send(void* socket, const int buffer) {
    // Send an initial buffer
    SOCKET s = (SOCKET)socket;

    // translate buffer from int to char
    char* updated_buff = translate_buff(buffer);

    int iResult = send(s, (const char*)updated_buff, 2, 0);
    delete[] updated_buff;
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        exit(-1);
    }
}

//--------------------------------------------//
void socket_send(void* socket, bool another_turn) {
    // Send an initial buffer
    SOCKET s = (SOCKET)socket;

    if (another_turn)
        send(s, "-1", 2, 0);
    else
        send(s, "-2", 2, 0);
}
//--------------------------------------------//
char* translate_buff(const int buffer) {
    char* updated_buff = new (std::nothrow) char[2];

    if (updated_buff == NULL) {
        std::cerr << "couldn't allocate memory\n";
        exit(EXIT_FAILURE);
    }

    updated_buff[0] = (buffer / 10) + '0';
    updated_buff[1] = (buffer % 10) + '0';

    return updated_buff;
}

//--------------------------------------------//
int socket_recv(void* socket) {
    int updated_buff;
    char buffer[3];
    int iResult = recv((SOCKET)socket, buffer, 2, 0);
    buffer[2] = '\0';
    if (iResult == 0) {
        printf("Connection closed\n");
        return EXIT_FAILURE;
    }

    if (iResult < 0) {
        printf("recv failed with error: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // receiving result
    if (strcmp(buffer, "-1") == 0)
        return -1;
    else if (strcmp(buffer, "-2") == 0)
        return -2;

    // translate buffer from char to int
    updated_buff = (int)(buffer[0] - '0') * 10 + (int)(buffer[1] - '0');

    return updated_buff;
}