#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void SetLabelBold(QLabel *label, bool isBold);

private slots:
    void StartNewGame();
    void UpdateNameLabels();
    void HandleGameOver(TicTacToeWidget::Player winner);
};
#endif // MAINWINDOW_H
