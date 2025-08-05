        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>
        #include <limits.h>

        #define BOARD_SIZE 3
        #define EMPTY ' '
        #define PLAYER_X 'X'
        #define PLAYER_O 'O'

        // Function prototypes
        void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);
        void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]);
        bool isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]);
        bool checkWinner(char board[BOARD_SIZE][BOARD_SIZE], char player);
        bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
        void makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player);
        void getPlayerMove(char board[BOARD_SIZE][BOARD_SIZE], char player);
        int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, bool isMaximizing, char aiPlayer, char humanPlayer);
        void getAIMove(char board[BOARD_SIZE][BOARD_SIZE], char aiPlayer, char humanPlayer);
        void playGame(int mode);
        void clearScreen();
        void printHeader();

        int main() {
            int choice;
            
            do {
                clearScreen();
                printHeader();
                printf("\n=== TIC TAC TOE GAME ===\n");
                printf("1. 2-Player Mode\n");
                printf("2. Player vs AI Mode\n");
                printf("3. Exit\n");
                printf("Enter your choice (1-3): ");
                scanf("%d", &choice);
                
                switch (choice) {
                    case 1:
                        playGame(1);
                        break;
                    case 2:
                        playGame(2);
                        break;
                    case 3:
                        printf("\nThanks for playing! Goodbye!\n");
                        break;
                    default:
                        printf("\nInvalid choice! Please try again.\n");
                        printf("Press Enter to continue...");
                        getchar();
                        getchar();
                }
            } while (choice != 3);
            
            return 0;
        }

        void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    board[i][j] = EMPTY;
                }
            }
        }

        void displayBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
            printf("\n");
            printf("    1   2   3\n");
            printf("  +---+---+---+\n");
            for (int i = 0; i < BOARD_SIZE; i++) {
                printf("%d |", i + 1);
                for (int j = 0; j < BOARD_SIZE; j++) {
                    printf(" %c |", board[i][j]);
                }
                printf("\n");
                if (i < BOARD_SIZE - 1) {
                    printf("  +---+---+---+\n");
                }
            }
            printf("  +---+---+---+\n");
            printf("\n");
        }

        bool isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] == EMPTY) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool checkWinner(char board[BOARD_SIZE][BOARD_SIZE], char player) {
            // Check rows
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                    return true;
                }
            }
            
            // Check columns
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
                    return true;
                }
            }
            
            // Check diagonals
            if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
                return true;
            }
            if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
                return true;
            }
            
            return false;
        }

        bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
            return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY;
        }

        void makeMove(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, char player) {
            board[row][col] = player;
        }

        void getPlayerMove(char board[BOARD_SIZE][BOARD_SIZE], char player) {
            int row, col;
            
            do {
                printf("Player %c's turn\n", player);
                printf("Enter row (1-3): ");
                scanf("%d", &row);
                printf("Enter column (1-3): ");
                scanf("%d", &col);
                
                row--; // Convert to 0-based indexing
                col--;
                
                if (!isValidMove(board, row, col)) {
                    printf("Invalid move! Please try again.\n");
                }
            } while (!isValidMove(board, row, col));
            
            makeMove(board, row, col, player);
        }

        int minimax(char board[BOARD_SIZE][BOARD_SIZE], int depth, bool isMaximizing, char aiPlayer, char humanPlayer) {
            // Base cases
            if (checkWinner(board, aiPlayer)) {
                return 10 - depth;
            }
            if (checkWinner(board, humanPlayer)) {
                return depth - 10;
            }
            if (isBoardFull(board)) {
                return 0;
            }
            
            if (isMaximizing) {
                int bestScore = INT_MIN;
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        if (board[i][j] == EMPTY) {
                            board[i][j] = aiPlayer;
                            int score = minimax(board, depth + 1, false, aiPlayer, humanPlayer);
                            board[i][j] = EMPTY;
                            if (score > bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            } else {
                int bestScore = INT_MAX;
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        if (board[i][j] == EMPTY) {
                            board[i][j] = humanPlayer;
                            int score = minimax(board, depth + 1, true, aiPlayer, humanPlayer);
                            board[i][j] = EMPTY;
                            if (score < bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }

        void getAIMove(char board[BOARD_SIZE][BOARD_SIZE], char aiPlayer, char humanPlayer) {
            int bestScore = INT_MIN;
            int bestRow = -1, bestCol = -1;
            
            printf("AI is thinking...\n");
            
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = aiPlayer;
                        int score = minimax(board, 0, false, aiPlayer, humanPlayer);
                        board[i][j] = EMPTY;
                        
                        if (score > bestScore) {
                            bestScore = score;
                            bestRow = i;
                            bestCol = j;
                        }
                    }
                }
            }
            
            makeMove(board, bestRow, bestCol, aiPlayer);
            printf("AI placed %c at position (%d, %d)\n", aiPlayer, bestRow + 1, bestCol + 1);
        }

        void playGame(int mode) {
            char board[BOARD_SIZE][BOARD_SIZE];
            char currentPlayer = PLAYER_X;
            char aiPlayer = PLAYER_O;
            char humanPlayer = PLAYER_X;
            
            initializeBoard(board);
            
            if (mode == 2) {
                printf("\nYou will be playing as X, AI will be O\n");
                printf("Press Enter to continue...");
                getchar();
                getchar();
            }
            
            while (true) {
                clearScreen();
                printHeader();
                displayBoard(board);
                
                // Check for game end conditions
                if (checkWinner(board, PLAYER_X)) {
                    if (mode == 1) {
                        printf("Player X wins!\n");
                    } else {
                        printf("You win! Congratulations!\n");
                    }
                    break;
                } else if (checkWinner(board, PLAYER_O)) {
                    if (mode == 1) {
                        printf("Player O wins!\n");
                    } else {
                        printf("AI wins! Better luck next time!\n");
                    }
                    break;
                } else if (isBoardFull(board)) {
                    printf("It's a draw!\n");
                    break;
                }
                
                // Make move
                if (mode == 1) {
                    // 2-player mode
                    getPlayerMove(board, currentPlayer);
                    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                } else {
                    // AI mode
                    if (currentPlayer == humanPlayer) {
                        getPlayerMove(board, currentPlayer);
                    } else {
                        getAIMove(board, aiPlayer, humanPlayer);
                    }
                    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                }
            }
            
            printf("\nPress Enter to return to main menu...");
            getchar();
            getchar();
        }

        void clearScreen() {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }

        void printHeader() {
            printf("===========================================\n");
            printf("|              TIC TAC TOE                |\n");
            printf("|         Classic Game in C               |\n");
            printf("===========================================\n");
        } 