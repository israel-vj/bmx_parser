
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDateTime>
#include <QClipboard>
#include <QFileDialog>
#include <QLocale>
#include <QRegularExpression>
#include <string>
#include "TextExtractor.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->installEventFilter(this);

    QLocale::setDefault( QLocale(QLocale::Spanish, QLocale::Mexico) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->textEdit && e->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = dynamic_cast<QKeyEvent*>(e);
        if(ke != 0 && ke->modifiers() == Qt::ControlModifier && ke->key() == Qt::Key_C )
        {
            QClipboard *clipboard = QApplication::clipboard();
            if(ui->textEdit->textCursor().hasSelection())
            {
                int begin = ui->textEdit->textCursor().selectionStart();
                int size = ui->textEdit->textCursor().selectionEnd() - begin;
                QString text = ui->textEdit->toPlainText().mid(begin, size);
                clipboard->setText(text);
            }
            else
            {
                clipboard->setText(ui->textEdit->toPlainText());
            }
            return true;
        }
    }
    return false;
}

QString MainWindow::shortMonthTextToMonthNumber(QString shortMonth)
{
    static QString shortMonths[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
    static QString monthNumbers[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};

    for(int i=0; i<(int)(sizeof(shortMonths)/sizeof(QString)); ++i)
    {
        if(shortMonth == shortMonths[i])
            return monthNumbers[i];
    }

    return "unknown";
}

QString MainWindow::parseFile(const QString &filePath)
{
    string rawText;
    TextExtractor extractor;
    try
    {
        rawText = extractor.Init( filePath.toUtf8().data(), "<PASSWORD>" );
    }
    catch( PdfError & e )
    {
        return QString();
    }

    QString primerText = QString::fromUtf8(rawText.c_str(), rawText.size());

    //get document date
    QRegularExpression dateExpr("Del (\\d{1,2}) de (.+) al \\d{1,2} de .+ de (\\d{4,4})");
    QRegularExpressionMatch dateMatch = dateExpr.match(primerText);
    QDate documentDate = QDate::currentDate();
    if(dateMatch.hasMatch())
    {
        QString dateString = QString("%1/%2/%3").arg(dateMatch.captured(1)).arg(dateMatch.captured(2)).arg(dateMatch.captured(3));
        //date = QDate::fromString(dateString, "d/MMMM/yyyy");
        documentDate = QLocale().toDate(dateString, "d/MMMM/yyyy");
        if(documentDate.month() == 12)
        {
            documentDate = documentDate.addYears(-1);
        }
    }

    //trim text region of interest
    primerText.replace(QRegularExpression(" +"), " ");
    QRegularExpression trimBegExpr = QRegularExpression("Detalle de operaciones|Detalle de Operaciones");
    int trimBegIndex = primerText.indexOf(trimBegExpr);
    if(trimBegIndex>0)
        primerText.replace(0, trimBegIndex, "");
    QRegularExpression trimEndExpr = QRegularExpression("Mensualidades sin intereses|MENSUALIDADES\\sSIN\\sINTERESES");
    int trimEndIndex = primerText.indexOf(trimEndExpr);
    if(trimEndIndex>0)
        primerText.replace(trimEndIndex, primerText.size()-trimEndIndex, "");

    QString output;
    QString buffer = primerText;
    //QRegularExpression margaritaExpr("Por su Tarjeta Adicional: MARGARITA ESTRADA LERMA");
    QRegularExpression subDateExpr("([A-Z][a-z][a-z]) (\\d{1,2})");
    QRegularExpression expenseExpr("(.+)\n([\\d{1,3},]+\\.\\d\\d)\n");
    QRegularExpression expenseFCExpr("(.+)\n( \n){0,1}(.+)\n([\\d{1,3},]+.\\d\\d)\n([\\d{1,3},]+\\.\\d\\d)\n");

    QDate expenseDate = documentDate;
    QRegularExpressionMatch subDateMatch, expenseMatch, expenseFCMatch;

    //iterate document; search expenses (local and foreing country) and add them to parsed result
    do
    {
//        int margaritaIndex = buffer.indexOf(margaritaExpr);
        subDateMatch = subDateExpr.match(buffer);
        expenseMatch = expenseExpr.match(buffer);
        expenseFCMatch = expenseFCExpr.match(buffer);

//DEBUG
//        if(expenseMatch.hasMatch())
//        {
//            cout << "Expense" << expenseMatch.captured(0).toStdString() << endl;
//        }
//        if(expenseFCMatch.hasMatch())
//        {
//            cout << "ExpenseFC" << expenseFCMatch.captured(0).toStdString() << endl;
//        }

        if(subDateMatch.hasMatch() && (!expenseMatch.hasMatch() || subDateMatch.capturedStart() < expenseMatch.capturedStart()) && (!expenseFCMatch.hasMatch() || subDateMatch.capturedStart() < expenseFCMatch.capturedStart()) )
        {
            QString newDateString = QString("%1/%2/%3").arg(subDateMatch.captured(2)).arg(shortMonthTextToMonthNumber(subDateMatch.captured(1))).arg(documentDate.year());
            //QDate newDate = QDate::fromString(newDateString, "d/MM/yyyy");
            QDate newDate = QLocale().toDate(newDateString, "d/MM/yyyy");
            if(newDate.month() < documentDate.month())
            {
                newDate = newDate.addYears(1);
            }
            expenseDate = newDate;
            buffer.replace(subDateMatch.capturedStart(), subDateMatch.capturedLength(), "");
//            if(margaritaIndex>=0 && margaritaIndex < subDateMatch.capturedStart())
//            {
//                output.append("\nMARGARITA ESTRADA LERMA\n\n");
//                buffer.replace(margaritaExpr, "");
//            }
        }
        else if(expenseFCMatch.hasMatch() && (!expenseMatch.hasMatch() || expenseFCMatch.capturedStart() <= expenseMatch.capturedStart()) )
        {
            output.append( expenseFCToString(expenseDate, expenseFCMatch) ).append('\n');
            buffer.replace(expenseFCMatch.capturedStart(), expenseFCMatch.capturedLength(), "");
        }
        else if(expenseMatch.hasMatch() && (!expenseFCMatch.hasMatch() || expenseMatch.capturedStart() < expenseFCMatch.capturedStart()) )
        {
            output.append( expenseToString(expenseDate, expenseMatch) ).append('\n');
            buffer.replace(expenseMatch.capturedStart(), expenseMatch.capturedLength(), "");
        }

    }
    while(subDateMatch.hasMatch() || expenseMatch.hasMatch() || expenseFCMatch.hasMatch());

    return output;
}

QString MainWindow::expenseToString(const QDate &date, const QRegularExpressionMatch &match)
{
    return date.toString("dd/MM/yyyy\t").append(match.captured(1)).append("\t").append(match.captured(2));
}

QString MainWindow::expenseFCToString(const QDate &date, const QRegularExpressionMatch &match)
{
    return date.toString("dd/MM/yyyy\t").append(match.captured(1)).append(' ').append(match.captured(3)).append(' ').append(match.captured(4)).append("\t").append(match.captured(5));
}

void MainWindow::on_selectFilePushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Seleccione un archivo", QString(), "*.pdf");
    if(filePath.isEmpty())
    {
        return;
    }
    ui->filePathLineEdit->setText(filePath);

    on_parsePushButton_clicked();
}

void MainWindow::on_parsePushButton_clicked()
{
    ui->textEdit->clear();

    QString filePath = ui->filePathLineEdit->text();

    QString parsedText = parseFile(filePath);

    ui->textEdit->setPlainText(parsedText);
}
