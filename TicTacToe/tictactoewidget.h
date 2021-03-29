#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QPushButton>
#include <QWidget>

class TicTacToeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TicTacToeWidget(QWidget *parent = nullptr);
    enum class Player{
        Invalid, Player1, Player2, Draw
    };
    Q_ENUM(Player);
    Player CurrentPlayer() const;
    void SetCurrentPlayer(Player p);
    void InitNewGame();

private:
    QVector<QPushButton*> m_board;
    Player m_currentPlayer;
    Player CheckWinConditions();

signals:
    void CurrentPlayerChanged(Player);
    void GameOver(Player);

private slots:
    void HandleButtonClick(int index);

};

#endif // TICTACTOEWIDGET_H
