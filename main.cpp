#include "cipher.h"
#include "base64.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
    Cipher test;

    RSA* rsapub = test.get_public_key();
    RSA* rsapri = test.get_private_key();

    //create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        cerr << "It's fucked from the getgo bro." << endl;
        return -1;
    }
    //allow for quick rebinding
    int optval = 1;
    if(setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1){
        close(listening);
        cerr << "Failed to set socket operation" << endl;
        return -99;
    }
    //bind the socket to a ip and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1){
        cerr << "Failed to bind..." << endl;
        return -2;
    }

    //mark the socket for listening
    if(listen(listening, SOMAXCONN) == -1){
        cerr << "Cannot create socket..." << endl;
        return -3;
    }

    cout << "Waiting for connections on: " << "0.0.0.0" << ":" << hint.sin_port << endl;

    while (1){
        //accept a call
        sockaddr_in client;
        socklen_t client_size = sizeof(sockaddr_in);
        char host[NI_MAXHOST];
        char svc[NI_MAXSERV];
        int client_socket = accept(listening, (sockaddr*)&client, &client_size);

        if(client_socket == -1){
            cerr << "client couldn't connect" << endl;
            return -4;
        }

        memset(host, 0, NI_MAXHOST);
        memset(svc, 0, NI_MAXSERV);

        int result = getnameinfo((sockaddr*) &client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

        if(result){
            cout << host << " connected on " << svc << endl;
        }else{
            inet_ntop(AF_INET, (sockaddr_in*) &client.sin_addr, host, NI_MAXHOST);
            cout << host << " connected on " << ntohs(client.sin_port) << endl;
        }

        //while receiving - do things
        char buf[4096];
        while(1){
            //clear buffer
            memset(buf, 0, 4096);
            //wait msg
            int bytes_recv = recv(client_socket, buf, 4096, 0);
            if(bytes_recv == -1){
                cerr << "connection issue..." << endl;
                break;
            }

            if(bytes_recv == 0){
                cerr << host << " disconnected..." << endl;
                break;
            }

            cout << "Recieved from: " << host << ": " << buf << endl << "DECRYPT: " << test.decryptRSA(rsapri, buf) << endl;

        }
    }

    return 0;
}
////
//
