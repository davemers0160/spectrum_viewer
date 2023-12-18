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

    fft_size = pow(2, ui->fft_size_slider->value());
    ui->fft_size_le->setText(QString::number(fft_size));

    full_scale = pow(2, ui->full_scale_slider->value());
    ui->full_scale_le->setText(QString::number(full_scale));


    //-----------------------------------------------------------------------------
    connect(ui->actionOpen_File, SIGNAL(triggered()), this, SLOT(file_select_clicked()));
    connect(ui->fft_size_slider, SIGNAL(valueChanged(int)), this, SLOT(update_fft_size()));
    connect(ui->full_scale_slider, SIGNAL(valueChanged(int)), this, SLOT(update_full_scale()));

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
        // use the filename and create the input source for the iq data
        try {
            input_source_ptr.read_file(iq_filename.toStdString());
        }
        catch (std::exception& ex)
        {
            QMessageBox msgBox(QMessageBox::Critical, "Spectrum Viewer Open File error", QString("%1: %2").arg(iq_filename).arg(ex.what()));
            msgBox.exec();
        }
    }

    int bp = 0;
}   // end of file_select_clicked

//-----------------------------------------------------------------------------
void spectrum_viewer::update_fft_size()
{
    fft_size = pow(2, ui->fft_size_slider->value());
    ui->fft_size_le->setText(QString::number(fft_size));
}

//-----------------------------------------------------------------------------
void spectrum_viewer::update_full_scale()
{
    full_scale = pow(2, ui->full_scale_slider->value());
    QString full_scale_text;
    full_scale_text.sprintf("%d", (uint64_t)full_scale);
    ui->full_scale_le->setText(full_scale_text);
}

//-----------------------------------------------------------------------------
// Destructor
spectrum_viewer::~spectrum_viewer()
{
  delete ui;
}


