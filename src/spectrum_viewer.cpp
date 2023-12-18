#pragma once

#include <cmath>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <fstream>

#include <QtWidgets>
#include <QPixmapCache>
#include <QFileDialog>
#include <QSettings>
#include <QString>

#include "spectrum_viewer.h"
#include "ui_spectrum_viewer.h"

//#include <QProgressDialog>
//#include <qtimer.h>

#include "utilities.h"
// #include "utils.h"
// #include "display.h"
// #include "html_tags.h"
// #include "search_settings.h"


// void Debug_Console()
// {
    // AllocConsole();
    // FILE* pFileCon = NULL;
    // pFileCon = freopen("CONOUT$", "w", stdout);

    // COORD coordInfo;
    // coordInfo.X = 130;
    // coordInfo.Y = 9000;

    // SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    // SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
// }


///////////////////////////////////////////////////////
// Constructor
spectrum_viewer::spectrum_viewer(QWidget* parent)
    : QMainWindow(parent), 
    ui(new Ui::spectrum_viewer)
{
    ui->setupUi(this);
    // ui->checkBox->setCheckState(Qt::Unchecked);
    // this->connect(ui2->action_Image_Directory_Location, SIGNAL(triggered()), this, SLOT(on_action_Image_Directory_Location()));
    // this->connect(ui2->action_Search_Settings, SIGNAL(triggered()), this, SLOT(on_action_Search_Settings()));
    
    //this->connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(file_select_clicked()));


    connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(file_select_clicked()));

}



//-----------------------------------------------------------------------------
void spectrum_viewer::file_select_clicked()
{
    QSettings settings;
    QString iq_filename;
    QFileDialog file_select;
    file_select.setNameFilter(("All files (*);;"
        "complex<float> file (*.cfile *.cf32 *.fc32);;"
        "complex<int16> file (*.cs16 *.sc16 *.c16);;"
        "complex<int8> file (*.cs8 *.sc8 *.c8);;"
        "complex<uint8> file (*.cu8 *.uc8)"));

    // Try and load a saved state  
    QByteArray saved_state = settings.value("OpenFileState").toByteArray();
    file_select.restoreState(saved_state);

    // Filter doesn't seem to be considered part of the saved state
    QString last_used_filter = settings.value("OpenFileFilter").toString();
    if (last_used_filter.size())
        file_select.selectNameFilter(last_used_filter);
    

    if (file_select.exec())
    {
        iq_filename = file_select.selectedFiles()[0];

        // Remember the state of the dialog for the next time
        QByteArray dialog_state = file_select.saveState();
        settings.setValue("OpenFileState", dialog_state);
        settings.setValue("OpenFileFilter", file_select.selectedNameFilter());
    }

    if (!iq_filename.isEmpty())
    {
        //read_iq_file(iq_filename.toStdString(), full_scale, samples, iq_data);
        input_source_ptr.read_file(iq_filename.toStdString());
    }

    int bp = 0;
}

///////////////////////////////////////////////////////
// Destructor
spectrum_viewer::~spectrum_viewer()
{
  delete ui;
}


