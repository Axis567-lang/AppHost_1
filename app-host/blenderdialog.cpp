#include "blenderdialog.h"
#include "ui_blenderdialog.h"

#include <QFileDialog>
#include <QTextStream>
#include <QProcess>

void BlenderDialog::savePythonScript()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Python File"),
                               "mypython.py",
                               tr("Python File (*.py)"));

    if ( fileName.isEmpty() ) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << "import bpy\n";

    out << "from math import *\n";

    out << "scene = bpy.context.scene\n";

    out << "bpy.ops.object.select_all(action='SELECT')\n";
    out << "bpy.ops.object.delete(use_global=False, confirm=False)\n";

    out << "for theta in range(" << ui->th1->value() << "," << ui->th2->value() << "," << ui->th3->value() << "):\n";
    out << "    for phi in range(" << ui->ph1->value() << "," << ui->ph2->value() << "," << ui->ph3->value() << "):\n";
    out << "        scene = bpy.context.scene\n";
    out << "        bpy.ops.mesh.primitive_monkey_add(size=2.0, \n";
    out << "        calc_uvs=True, enter_editmode=False,\n";
    out << "        align='WORLD', \n";
    out << "        location=(10*pow(cos(radians(phi)),3)*pow(cos(radians(theta)),1), \n";
    out << "        10*pow(sin(radians(phi)),3), \n";
    out << "        10*pow(cos(radians(phi)),3)*pow(sin(radians(theta)),1)), rotation=(0.0, 0.0, 0.0))\n";

    file.close();

}

void BlenderDialog::runBlenderScript()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Python Script"), ".", tr("Python Files (*.py)"));

    if ( fileName.isEmpty() ) return;

    QProcess blenderProgram;
    blenderProgram.execute("C:/Program Files/Blender Foundation/Blender 2.82/blender.exe", QStringList() << "-P" << fileName );
    if (!blenderProgram.waitForStarted())
        return;

    blenderProgram.write("Qt rocks!");
    //blenderProgram.closeWriteChannel();

    if (!blenderProgram.waitForFinished())
        return;

    //QByteArray result = blenderProgram.readAll();

}

BlenderDialog::BlenderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlenderDialog)
{
    ui->setupUi(this);

    connect(ui->savePythonBtn, SIGNAL(clicked()), this, SLOT(savePythonScript()));
    connect(ui->runScriptBtn, SIGNAL(clicked()), this, SLOT(runBlenderScript()));
}

BlenderDialog::~BlenderDialog()
{
    delete ui;
}
