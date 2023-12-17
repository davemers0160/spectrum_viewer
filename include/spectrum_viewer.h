#pragma once

//#include <ryml_all.hpp>

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include <cstdint>
#include <vector>
#include <string>
//#include "utils.h"
//#include "binary_params.h"
//#include "search_settings.h"
//#include "tile_img.h"
//#include "matched_template.h"


QT_BEGIN_NAMESPACE
namespace Ui { class spectrum_viewer; }
QT_END_NAMESPACE



class spectrum_viewer : public QMainWindow
{
	Q_OBJECT

public:
	//Attributes
	QString image_dir;
	bool mwterminate = false;

	//Methods
	spectrum_viewer(QWidget* parent = nullptr);

	~spectrum_viewer();
	
private:
	//Attributes
	Ui::spectrum_viewer *ui;
	uint8_t struct_elem_size = 5;
	uint16_t binary_threshold = 120;

	double corebox_area;
	bool files_parsed = false;
	bool display_all_cells = false;
	int32_t offset = 0;



	//Methods


private slots:
	//void on_action_Image_Directory_Location();

};
