#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual bool eventFilter(QObject *o, QEvent *e);

private:
    Ui::MainWindow *ui;

    QString parseFile(const QString &filePath);
    QString expenseToString(const QDate &date, const QRegularExpressionMatch &match);
    QString expenseFCToString(const QDate &date, const QRegularExpressionMatch &match);

private slots:
    void on_selectFilePushButton_clicked();
    void on_parsePushButton_clicked();

};

#endif // MAINWINDOW_H
