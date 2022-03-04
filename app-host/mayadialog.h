#ifndef MAYADIALOG_H
#define MAYADIALOG_H

#include <QDialog>
#include <QTextStream>

namespace Ui {
class MayaDialog;
}

class MayaDialog : public QDialog
{
    Q_OBJECT

public slots:
    void saveMELScript();
    void savePythonScript();
    void runMELScript();
    void runPythonScript();

    void buildCity(QString fileName);

    void searchModel1();
    void searchModel2();

public:
    explicit MayaDialog(QWidget *parent = nullptr);
    ~MayaDialog();

private:
    Ui::MayaDialog *ui;
};

#endif // MAYADIALOG_H
