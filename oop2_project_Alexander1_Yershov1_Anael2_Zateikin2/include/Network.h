#pragma once
#include "macros.h"
#include "Arena.h"
#include <winsock2.h>


void init_socket_library();
void* server_wait_for_client();
void* client_connect_to_server();

//--------------------------------------------//
template <typename T>
void sending(T& info)
{
    SOCKET s = (SOCKET)Arena::m_socket;

    int iResult = send(s, (TCHAR*)&info, sizeof(T), 0);

    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        exit(-1);
    }
}

//--------------------------------------------//
template <typename T>
T receive()
{
    T buffer;

    int iResult = recv((SOCKET)Arena::m_socket, (TCHAR*)&buffer, sizeof(T), 0);

    if (iResult == 0)
        throw std::exception("Connection closed\n");

    if (iResult < 0)
        throw std::exception("recv failed with error: %d\n", WSAGetLastError());

    return buffer;
}