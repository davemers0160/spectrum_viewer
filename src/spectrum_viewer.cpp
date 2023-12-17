#pragma once

#include <cmath>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <fstream>

#include "spectrum_viewer.h"
#include "ui_spectrum_viewer.h"

//#include <QProgressDialog>
//#include <qtimer.h>

// #include "utilities.h"
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
}



///////////////////////////////////////////////////////
// Destructor
spectrum_viewer::~spectrum_viewer()
{
  delete ui;
}


