#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "TicTacToe.h"

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 1);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);

    TicTacToe board;
    char player1 = 'x';
    char player2 = 'o';
    char currentplayer = player1;

    while (true) {
        std::string gameState = board.serialize();
        send(clientSocket, gameState.c_str(), gameState.size(), 0);
        int row, col;
        if (currentplayer == player1) {
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            recv(clientSocket, buffer, sizeof(buffer), 0);
            sscanf(buffer, "%d %d", &row, &col);
        } else {
            std::cout << "Player " << currentplayer << ": ";
            std::cin >> row >> col;
        }

        board.set(row, col, currentplayer);
        board.print(); 
        if (board.checkwinner(currentplayer)) {
            send(clientSocket, "WIN", 3, 0);
            break;
        }
        currentplayer = (currentplayer == player1) ? player2 : player1;
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}