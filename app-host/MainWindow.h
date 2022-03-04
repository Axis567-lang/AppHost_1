#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDir>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeTexture();
    void insertShape();

    void openBlenderDialog();
    void openMayaDialog();

    void changePosition(double value);


private:
    void loadTextures();
    void loadStaticPlugins();
    void loadDynamicPlugins();
    void addToMenu(QObject *plugin, const QStringList &texts, QMenu *menu,
                   const char *member, QActionGroup *actionGroup = 0);


protected:
    Ui::MainWindow *ui;

    // texture selector
    QActionGroup *texturesGroup;
    QActionGroup *shapesGroup;
    QMenu        *menuShapes;

    QDir          pluginsDir;
    QStringList   pluginFileNames;
};

#endif // MAINWINDOW_H
