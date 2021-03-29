#include "configurationdialog.h"
#include "mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNewGame, &QAction::triggered,
            this, &MainWindow::StartNewGame);
    connect(ui->GameBoard, &TicTacToeWidget::CurrentPlayerChanged,
            this, &MainWindow::UpdateNameLabels);
    connect(ui->GameBoard, &TicTacToeWidget::GameOver,
            this, &MainWindow::HandleGameOver);
    connect(ui->actionQuit, &QAction::triggered,
            qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetLabelBold(QLabel *label, bool isBold)
{
    QFont f = label->font();
    f.setBold(isBold);
    label->setFont(f);
}

void MainWindow::StartNewGame()
{
    ConfigurationDialog dialog(this);

    if(dialog.exec() == QDialog::Rejected) {
        return; //do nothing if dialog rejected
    }

    ui->Player1Name->setText(dialog.Player1Name());
    ui->Player2Name->setText(dialog.Player2Name());
    ui->GameBoard->InitNewGame();
}

void MainWindow::UpdateNameLabels()
{
    SetLabelBold(ui->Player1Name,
        ui->GameBoard->CurrentPlayer() ==
            TicTacToeWidget::Player::Player1);
    SetLabelBold(ui->Player2Name,
        ui->GameBoard->CurrentPlayer() ==
                 TicTacToeWidget::Player::Player2);
}

void MainWindow::HandleGameOver(TicTacToeWidget::Player winner)
{
    QString message;

    if(winner == TicTacToeWidget::Player::Draw) {
        message = tr("Game ended with a draw");
    }
    else {
        QString winnerName = winner == TicTacToeWidget::Player::Player1 ? ui->Player1Name->text() : ui->Player2Name->text();
        message = tr("%1 wins").arg(winnerName);
    }

    QMessageBox::information(this, tr("Info"), message);
    ui->GameBoard->InitNewGame();
}

