
#include <QtWidgets>
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Billar Practica 3: GiVD 2014-2015 :: Jaume & Aleix"));
    resize(640, 640);


    glWidget = new GLWidget;
    setCentralWidget(glWidget);

    connect(this->ui->action_Play, SIGNAL(triggered()), glWidget, SLOT(Play()));

    connect(this->ui->action_Pla_Base, SIGNAL(triggered()), glWidget, SLOT(newPlaBase()));
    connect(this->ui->action_Bola_Blanca, SIGNAL(triggered()), glWidget, SLOT(newBola()));
    connect(this->ui->action_15_Boles, SIGNAL(triggered()), glWidget, SLOT(newConjuntBoles()));
    connect(this->ui->action_Obre_Fitxer, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(this->ui->action_Sala_de_Billar, SIGNAL(triggered()), glWidget, SLOT(newSalaBillar()));
    connect(this->ui->action_Exit, SIGNAL(triggered()), this, SLOT(Quit()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Quit(){
    qApp->exit();
}

void MainWindow::newFile()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isNull())
        this->glWidget->newObj(fileName);
}
