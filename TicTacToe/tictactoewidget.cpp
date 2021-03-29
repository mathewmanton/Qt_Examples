#include "tictactoewidget.h"

#include <QGridLayout>
#include <QSignalMapper>

TicTacToeWidget::TicTacToeWidget(QWidget *parent) : QWidget(parent)
{
    m_currentPlayer = Player::Invalid;

    QGridLayout *gridLayout = new QGridLayout(this);
    QSignalMapper *mapper = new QSignalMapper(this);

    for(int row = 0; row < 3; ++row){
        for(int column = 0; column < 3; ++column){
            QPushButton *button = new QPushButton(" ");
            button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            gridLayout->addWidget(button, row, column);
            m_board.append(button);
            mapper->setMapping(button, m_board.count() - 1);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        }
    }

    connect(mapper, SIGNAL(mappedInt(int)),
            this,   SLOT(HandleButtonClick(int)));
}

TicTacToeWidget::Player TicTacToeWidget::CurrentPlayer() const
{
    return m_currentPlayer;
}

void TicTacToeWidget::SetCurrentPlayer(TicTacToeWidget::Player p)
{
    if(m_currentPlayer == p) {
        return;
    }

    m_currentPlayer = p;
    emit CurrentPlayerChanged(p);
}

void TicTacToeWidget::InitNewGame()
{
    for(QPushButton *button : m_board) {
        button->setText(" ");
    }

    SetCurrentPlayer(Player::Player1);
}

TicTacToeWidget::Player TicTacToeWidget::CheckWinConditions()
{
    QString playerMarker = CurrentPlayer() == Player::Player1 ? "X" : "O";

    //Check rows
    for(int i = 0; i < m_board.count(); i += 3) {
        if(m_board[i]->text() == playerMarker && m_board[i + 1]->text() == playerMarker &&
                m_board[i + 2]->text() == playerMarker) {
            return CurrentPlayer();
        }
    }

    //Check columns
    for(int i = 0; i < 3; ++i) {
        if(m_board[i]->text() == playerMarker && m_board[i + 3]->text() == playerMarker &&
                m_board[i + 6]->text() == playerMarker) {
            return CurrentPlayer();
        }
    }

    //Check diagonals
    if((m_board[0]->text() == playerMarker && m_board[4]->text() == playerMarker && m_board[8]->text() == playerMarker)
            || (m_board[2]->text() == playerMarker && m_board[4]->text() == playerMarker && m_board[6]->text() == playerMarker)) {
        return CurrentPlayer();
    }

   //Check if game needs to continue
   for(QPushButton *button : m_board) {
       if(button->text() == " ") {
           return Player::Invalid;
       }
   }

   //Otherwise all spaces are used up. It's a draw
   return Player::Draw;
}

void TicTacToeWidget::HandleButtonClick(int index)
{
    if(m_currentPlayer == Player::Invalid) {
        return; //Game is not started
    }

    if(index < 0 || index >= m_board.size()) {
        return; //out of bounds check
    }

    QPushButton *button = m_board[index];

    if(button->text() != " ") {
        return; //Invalid move
    }

    button->setText(CurrentPlayer() == Player::Player1 ? "X" : "O");
    Player winner = CheckWinConditions();

    if(winner == Player::Invalid) {
        SetCurrentPlayer(CurrentPlayer() == Player::Player1 ? Player::Player2 : Player::Player1);
        return;
    }
    else {
        emit GameOver(winner);
    }
}
