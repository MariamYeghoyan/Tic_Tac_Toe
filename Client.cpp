#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "TicTacToe.h"

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); 
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    TicTacToe board;
    char player1 = 'x';
    char player2 = 'o';
    char currentplayer = player2;

    while (true) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);
        std::string gameState = buffer;

        std::cout << gameState << std::endl;
        int row, col;
        std::cout << "Player x: ";
        std::cin >> row >> col;
        std::string move = std::to_string(row) + " " + std::to_string(col);
        send(clientSocket, move.c_str(), move.size(), 0);
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);
        if (std::string(buffer) == "WIN") {
            std::cout << "You won!" << std::endl;
            break;
        }
    }

    close(clientSocket);

    return 0;
}