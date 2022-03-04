#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPluginLoader>
#include <interfaces.h>
#include <blenderdialog.h>
#include <mayadialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configure textures menu
    loadTextures();

    // Menú de formas
    menuShapes = ui->menuBar->addMenu(tr("&Formas"));
    shapesGroup = new QActionGroup(this);

    // Load static plugins
    loadStaticPlugins();
    loadDynamicPlugins();

    connect(ui->actionBlender, SIGNAL(triggered()), this, SLOT(openBlenderDialog()));
    connect(ui->actionMaya, SIGNAL(triggered()), this, SLOT(openMayaDialog()));

    connect(ui->px, SIGNAL(valueChanged(double)), this, SLOT(changePosition(double)));
    connect(ui->py, SIGNAL(valueChanged(double)), this, SLOT(changePosition(double)));
    connect(ui->pz, SIGNAL(valueChanged(double)), this, SLOT(changePosition(double)));

}

void MainWindow::openBlenderDialog(){
    BlenderDialog bdialog(this);

    bdialog.show();

    int retval = bdialog.exec();

    if ( retval == QDialog::Accepted ){
        // Do something
    }

}

void MainWindow::openMayaDialog()
{
    MayaDialog mdialog(this);

    mdialog.show();

    int retval = mdialog.exec();

    if ( retval == QDialog::Accepted ){
        // Do something
    }
}

void MainWindow::changePosition(double value)
{
    if ( ui->listOfgeometries->count() <= 0 ) return;

    QModelIndex index = ui->listOfgeometries->currentIndex();

    int row_index = index.row();

    if ( row_index < 0 ) return;

    MainWidget *glWidgetManage = ui->glWidget;

    if (!glWidgetManage) return;

    glWidgetManage->changePosition(row_index, ui->px->value(),
                                              ui->py->value(),
                                              ui->pz->value());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeTexture()
{
    MainWidget *glWidgetManage = ui->glWidget;

    if (!glWidgetManage) return;

    glWidgetManage->changeTexture( tr("textures/") + texturesGroup->checkedAction()->text() );
}

void MainWindow::loadTextures()
{
    // Menú de texturas
    QMenu *menuTextures = ui->menuBar->addMenu(tr("&Texturas"));
    menuTextures->addSeparator()->setText(tr("Elegir textura"));
    texturesGroup = new QActionGroup(this);

    QDir texturesDirectory("./textures");
    QStringList filters;
    filters << "*.png" << "*.jpg";
    texturesDirectory.setNameFilters(filters);
    QStringList fileNames = texturesDirectory.entryList();

    for (int i = 0; i < fileNames.size(); i++){
        QAction *addNewAction = new QAction(menuTextures);
        addNewAction->setText( fileNames.at(i) );
        texturesGroup->addAction( addNewAction );
        menuTextures->addAction( addNewAction );
        addNewAction->setCheckable(true);
        addNewAction->setChecked(true);
        connect(addNewAction, &QAction::triggered, this, &MainWindow::changeTexture);
    }

    menuTextures->addSeparator();
}

void MainWindow::loadStaticPlugins()
{

    // Load static plugins
    foreach (QObject *plugin, QPluginLoader::staticInstances()){
        ShapeInterface *iShape = qobject_cast<ShapeInterface *>(plugin);
        if (iShape){
            addToMenu(plugin, iShape->info(), menuShapes, SLOT(insertShape()), shapesGroup);
        }
    }

    menuShapes->addSeparator();
}

void MainWindow::loadDynamicPlugins()
{
    pluginsDir = QDir( "./plugins" );

    QStringList filters;
    filters << "*.dll";
    pluginsDir.setNameFilters(filters);

    foreach (QString fileName, pluginsDir.entryList()) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

        QObject *plugin = loader.instance();
        if (plugin) {

            ShapeInterface *iShape = qobject_cast<ShapeInterface *>(plugin);
            if (iShape){
                addToMenu(plugin, iShape->info(), menuShapes, SLOT(insertShape()), shapesGroup);
            }
            pluginFileNames += fileName;
            ui->messages->setText(tr("Plugin cargado correctamente...OK!"));
        } else
            ui->messages->setText(loader.errorString());
    }

    menuShapes->addSeparator();
}

void MainWindow::addToMenu(QObject *plugin, const QStringList &texts,
                           QMenu *menu, const char *member,
                           QActionGroup *actionGroup)
{
    foreach (QString text, texts) {
        QAction *action = new QAction(text, plugin);
        connect(action, SIGNAL(triggered()), this, member);
        menu->addAction(action);

        if (actionGroup) {
            action->setCheckable(true);
            actionGroup->addAction(action);
        }
    }
}

void MainWindow::insertShape()
{
    if (!shapesGroup) return;

    QAction *selectedAction = shapesGroup->checkedAction();

    if ( !selectedAction ) return;

    ShapeInterface *iShape = qobject_cast<ShapeInterface *>(selectedAction->parent());

    if ( !iShape ) return;

    MainWidget *glWidgetManage = ui->glWidget;

    if (!glWidgetManage) return;

    Geometry  *g = new Geometry;
    uint nv = 0, ni = 0;
    VertexData *data = iShape->buildVertices(nv);
    uint       *indices = iShape->buildIndices(ni);
    g->build(data, nv, indices, ni);
    // glWidgetManage->changeShape( g );}

    glWidgetManage->addShape( g );

    ui->listOfgeometries->addItems(iShape->info());

}

