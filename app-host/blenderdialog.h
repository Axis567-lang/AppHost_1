#ifndef BLENDERDIALOG_H
#define BLENDERDIALOG_H

#include <QDialog>

namespace Ui {
class BlenderDialog;
}

class BlenderDialog : public QDialog
{
    Q_OBJECT

public slots:
    void savePythonScript();
    void runBlenderScript();

public:
    explicit BlenderDialog(QWidget *parent = nullptr);
    ~BlenderDialog();

private:
    Ui::BlenderDialog *ui;
};

#endif // BLENDERDIALOG_H
