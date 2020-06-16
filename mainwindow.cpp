#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    centralWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    playersLayout = new QHBoxLayout;
    question = new QLabel;
    answer = new QLabel;
    skipButton = new QPushButton;

    initDialog();
    skipButton->hide();
    skipButton->setText("Skip question");

    centralWidget->setLayout(mainLayout);
    mainLayout->addLayout(playersLayout);
    mainLayout->addWidget(question);
    mainLayout->addWidget(answer);
    mainLayout->addWidget(skipButton);
    setCentralWidget(centralWidget);

    server.startServer();
    connect(&server, SIGNAL(showDialog(QString)), this, SLOT(onShowDialog(QString)));
    connect(&server, SIGNAL(showQuestion(QString, QString, QString)), this, SLOT(onShowQuestion(QString, QString, QString)));
    connect(&server, SIGNAL(addPlayer(QString, const int&)), this, SLOT(onAddPlayer(QString, const int&)));

    connect(skipButton, SIGNAL(clicked()), &server, SLOT(nextQuestion()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onShowDialog(QString answer){
    dialog->setText("Answer: " + answer);
    dialog->show();
}

void MainWindow::onShowQuestion(QString player, QString question, QString answer){
    this->question->setText(question);
    this->answer->setText(answer);
    for(auto p : players){
        if(p->text() == player){
            QFont font;
            font.setBold(true);
            p->setFont(font);
        }
    }
}

void MainWindow::onAddPlayer(QString player, int const &point){
    QLabel *newPlayer = new QLabel(player);
    QLabel *newPoints = new QLabel(QString::number(point));
    players.append(newPlayer);
    points.append(newPoints);
    QVBoxLayout *playerLayout = new QVBoxLayout;
    playerLayout->addWidget(players.last());
    playerLayout->addWidget(points.last());
    playersLayout->addLayout(playerLayout);
}

void MainWindow::initDialog(){
    dialog = new QMessageBox;
    dialog->addButton("Yes", QMessageBox::ButtonRole::AcceptRole);
    dialog->addButton("No", QMessageBox::ButtonRole::RejectRole);
    dialog->setWindowTitle("Answer is correct?");
    connect(dialog, SIGNAL(accepted()), &server, SLOT(correctAnswer()));
    connect(dialog, SIGNAL(rejected()), &server, SLOT(wrongAnswer()));
}
