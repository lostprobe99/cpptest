#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAxObject>
#include <QScopedPointer>
#include <QMessageBox>
#include <QFileDialog>
#include <QMetaObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slots_exception(int code, QString source, QString desc, QString help)
{
    qDebug() << __FUNCTION__ << ":" << __LINE__ << "\n";
    qDebug() << "code: " << code << "\n"
             << "source: " << source << "\n"
             << "desc: " << desc << "\n"
             << "help: " << help << "\n";
}

void MainWindow::on_pushButton_clicked()
{
//    QString file = "C:\\Users\\荆棘\\Desktop\\work\\刘沈威_1935001122_开题报告.doc";
//    QString file = "./1935001122.doc";
    QString file = filepath;
    QScopedPointer word(new QAxObject("Word.Application"));
    connect(word.get(), SIGNAL(exception(int,QString,QString,QString)), this, SLOT(slots_exception(int code, QString source, QString desc, QString help)));
    auto doc = word->querySubObject("Documents");
    if(doc == nullptr)
    {
        QMessageBox::information(this, QString("失败"), QString("%1 对象创建失败").arg("Documents"));
        return;
    }
    doc->dynamicCall("Open(const QVariant&)", QVariant(file));
    doc = word->querySubObject("ActiveDocument");
    if(doc == nullptr)
    {
        QMessageBox::information(this, QString("失败"), QString("%1 文档读取失败").arg(file));
        return;
    }
    auto selected = doc->querySubObject("Range()");
    QString text = selected->property("Text").toString();
    ui->textEdit->setText(text);
    doc->dynamicCall("Close()");
    word->dynamicCall("Quit()");
}


void MainWindow::on_pushButton_ChooseFile_clicked()
{
    filepath = QFileDialog::getOpenFileName(nullptr, "选择文件", "", "Word文件(*.doc *.docx)");
    if(filepath.isEmpty())
        qDebug() << "未选择文件\n";
    else
        qDebug() << "已选择: " << filepath << "\n";
    ui->pathLabel->setText(filepath);
}

