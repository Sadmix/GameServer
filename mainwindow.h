#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVector>
#include "server.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initDialog();
    void addPlayer(QString &name, int &points);

private slots:
   void onShowDialog(QString answer);
   void onShowQuestion(QString player, QString question, QString answer);
   void onAddPlayer(QString player, int const &points);

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *playersLayout;
    QVector<QLabel*> players;
    QVector<QLabel*> points;
    QLabel *question;
    QLabel *answer;
    QPushButton *skipButton;
    QMessageBox *dialog;
    Server server;
};

#endif // MAINWINDOW_H
