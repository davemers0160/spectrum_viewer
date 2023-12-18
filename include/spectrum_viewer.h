#pragma once

//#include <ryml_all.hpp>

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include <cstdint>
#include <vector>
#include <string>
#include "utilities.h"
#include "input_source.h"

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

	bool files_parsed = false;
	bool display_all_cells = false;
	int32_t offset = 0;

	float full_scale = 2048.0f;
	uint32_t fft_size = 4096;

	std::unique_ptr<data_samples_impl> samples;

	input_source input_source_ptr;


	//Methods


private slots:
	//void on_action_Image_Directory_Location();
	void file_select_clicked();
	void update_fft_size();
	void update_full_scale();

};

