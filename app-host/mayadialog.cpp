#include "mayadialog.h"
#include "ui_mayadialog.h"

#include <QFileDialog>

#include <QProcess>
#include <QDebug>

void MayaDialog::saveMELScript()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save MEL File"),
                               "myMEL.mel",
                               tr("MEL File (*.mel)"));

    if ( fileName.isEmpty() ) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << "select -all;\n";
    out << "doDelete;\n";

    out << "for ($radius = " << ui->radMin->value() << "; $radius < "<< ui->radMax->value() <<"; $radius+="<< ui->radStep->value() <<"){\n";
    out << "    for ($theta = "<< ui->thMin->value() <<"; $theta < "<< ui->thMax->value() <<"; $theta += " << ui->thStep->value() << "){\n";
    out << "        polyCube -w 1 -h 1 -d 1 -sx 1 -sy 1 -sz 1 -ax 0 1 0;\n";
    out << "        move -relative ($radius*cos(deg_to_rad($theta))) ($radius*sin(deg_to_rad($theta))) 10;\n";
    out << "        // rotate -relative ($radius*10) ($radius*20) ($radius*30);\n";
    out << "    }\n";
    out << "}\n";

    file.close();
}

void MayaDialog::savePythonScript()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Python File"),
                               "myPython.py",
                               tr("Python File (*.py)"));

    if ( fileName.isEmpty() ) return;


    buildCity(fileName);
}

void MayaDialog::runMELScript()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Script"), ".", tr("Files (*.mel)"));
    if ( fileName.isEmpty() ) return;
    fileName.replace("\\","/");

    QProcess mayaProgram;
    // MEL run
    mayaProgram.execute("C:/Program Files/Autodesk/Maya2020/bin/maya.exe", QStringList() << "-script" << fileName );

    if (!mayaProgram.waitForStarted())
        return;

    mayaProgram.write("Qt rocks!");

    if (!mayaProgram.waitForFinished())
        return;
}

void MayaDialog::runPythonScript()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Script"), ".", tr("Files (*.py)"));
    if ( fileName.isEmpty() ) return;
    fileName.replace("\\","/");

    QProcess mayaProgram;
    // Python run
    mayaProgram.execute("C:/Program Files/Autodesk/Maya2020/bin/maya.exe", QStringList() << "-command" << QString("python(\"execfile('"+ fileName +"')\")") );
    if (!mayaProgram.waitForStarted())
        return;

    mayaProgram.write("Qt rocks!");

    if (!mayaProgram.waitForFinished())
        return;
}

void MayaDialog::buildCity(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << "import maya.cmds as cmds\n";
    out << "import math\n";
    out << "import random\n";
    out << "from math import radians\n";

    out << "def buildTower(buildType, locx, locy, locz):\n";

    out << "    if buildType == 1:\n";
    out << "        before = set(cmds.ls(assemblies=True))\n";
    out << "        setImportPath = '"<< ui->model1Path->text() <<"'\n";
    out << "        model=cmds.file(setImportPath, i=True, mergeNamespacesOnClash=True, namespace=':')\n";
    out << "        after  =set(cmds.ls(assemblies=True))\n";
    out << "        imported = after.difference(before)\n";
    out << "        cmds.select(imported)\n";
    out << "        cmds.move(locx, locy, locz)\n";
    out << "        cmds.scale(" << ui->model1Scale->value() << ", " << ui->model1Scale->value() << ", " << ui->model1Scale->value() << ")\n";

    out << "    elif buildType == 2:\n";
    out << "        before = set(cmds.ls(assemblies=True))\n";
    out << "        setImportPath = '"<< ui->model2Path->text()  <<"'\n";
    out << "        model=cmds.file(setImportPath, i=True, mergeNamespacesOnClash=True, namespace=':')\n";
    out << "        after  =set(cmds.ls(assemblies=True))\n";
    out << "        imported = after.difference(before)\n";
    out << "        cmds.select(imported)\n";
    out << "        cmds.move(locx, locy, locz)\n";
    out << "        cmds.scale(" << ui->model2Scale->value() << ", " << ui->model2Scale->value() << ", " << ui->model2Scale->value() << ")\n";

    out << "    else:\n";
    out << "        before = set(cmds.ls(assemblies=True))\n";
    out << "        setImportPath = '"<< ui->model1Path->text() <<"'\n";
    out << "        model=cmds.file(setImportPath, i=True, mergeNamespacesOnClash=True, namespace=':')\n";
    out << "        after  =set(cmds.ls(assemblies=True))\n";
    out << "        imported = after.difference(before)\n";
    out << "        cmds.select(imported)\n";
    out << "        cmds.move(locx, locy, locz)\n";
    out << "        cmds.scale(" << ui->model1Scale->value() << ", " << ui->model1Scale->value() << ", " << ui->model1Scale->value() << ")\n";

    out << "def buildCity(num_builds):\n";
    out << "    for coord_x in range(0,num_builds):\n";
    out << "        for coord_y in range(0,num_builds):\n";
    out << "            buildType = random.randint(1,2)\n";
    out << "            myBuild = buildTower(buildType, 3*coord_x, 1, 3*coord_y)\n";

    out << "buildCity(5)\n";

    file.close();
}

void MayaDialog::searchModel1()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open model"), ".", tr("Files (*.obj)"));
    if ( fileName.isEmpty() ) return;
    fileName.replace("\\","/");

    ui->model1Path->setText(fileName);
}

void MayaDialog::searchModel2()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open model"), ".", tr("Files (*.obj)"));
    if ( fileName.isEmpty() ) return;
    fileName.replace("\\","/");

    ui->model2Path->setText(fileName);
}

MayaDialog::MayaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MayaDialog)
{
    ui->setupUi(this);

    connect(ui->saveScript, SIGNAL(clicked()), this, SLOT(savePythonScript()));
    connect(ui->runScript,  SIGNAL(clicked()), this, SLOT(runPythonScript()));

    connect(ui->model1Btn, SIGNAL(clicked()), this, SLOT(searchModel1()));
    connect(ui->model2Btn, SIGNAL(clicked()), this, SLOT(searchModel2()));
}

MayaDialog::~MayaDialog()
{
    delete ui;
}
