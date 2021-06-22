#pragma once
#include "macros.h"



void init_socket_library();
void* server_wait_for_client();
void* client_connect_to_server();

void initialSocketSendServer(InitialServerInfo&);
InitialServerInfo initialSocketReceiveClient();
void initialSocketSendClient();
void socket_send(void* socket, const int buffer); // sending a target
void socket_send(void* socket, bool another_turn);// sending result
char* translate_buff(const int buffer);

int socket_recv(void* socket);