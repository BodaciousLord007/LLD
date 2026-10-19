
#include <iostream>
using namespace std;

// Abstract Class
class Game
{
protected:
    virtual void init() = 0;
    virtual bool isGameOver() = 0;
    virtual void makeMove() = 0;
    virtual void showResult() = 0;

public:
    virtual ~Game() = default;

    // Template Method
    void play()
    {
        init();

        while (!isGameOver())
        {
            makeMove();
        }

        showResult();
    }
};

// Concrete Class
class TicTacToeGame : public Game
{
private:
    char board[3][3];
    char currentPlayer;
    char winner;
    int moves;

    void printBoard()
    {
        cout << "\n";

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << " " << board[i][j] << " ";

                if (j < 2)
                    cout << "|";
            }

            cout << "\n";

            if (i < 2)
                cout << "---+---+---\n";
        }
    }

protected:
    void init() override
    {
        currentPlayer = 'X';
        winner = ' ';
        moves = 0;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';

        cout << "Tic Tac Toe Started!\n";
        printBoard();
    }

    bool isGameOver() override
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] != ' ' &&
                board[i][0] == board[i][1] &&
                board[i][1] == board[i][2])
            {
                winner = board[i][0];
                return true;
            }

            if (board[0][i] != ' ' &&
                board[0][i] == board[1][i] &&
                board[1][i] == board[2][i])
            {
                winner = board[0][i];
                return true;
            }
        }

        if (board[0][0] != ' ' &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2])
        {
            winner = board[0][0];
            return true;
        }

        if (board[0][2] != ' ' &&
            board[0][2] == board[1][1] &&
            board[1][1] == board[2][0])
        {
            winner = board[0][2];
            return true;
        }

        return moves == 9;
    }

    void makeMove() override
    {
        int row, col;

        while (true)
        {
            cout << "\nPlayer " << currentPlayer
                 << " enter row and column (1-3): ";

            if (!(cin >> row >> col))
                throw runtime_error("Invalid input");

            row--;
            col--;

            if (row >= 0 && row < 3 &&
                col >= 0 && col < 3 &&
                board[row][col] == ' ')
                break;

            cout << "Invalid move! Try again.\n";
        }

        board[row][col] = currentPlayer;
        moves++;

        printBoard();

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void showResult() override
    {
        cout << "\nGame Over!\n";

        if (winner != ' ')
            cout << "Player " << winner << " wins!\n";
        else
            cout << "Game Draw!\n";
    }

};



int main(){
    Game* g = new TicTacToeGame(); 
    g->play();
    return 0;
}