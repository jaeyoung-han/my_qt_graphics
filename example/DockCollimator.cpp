#include <QtWidgets>
#include "DockCollimator.h"

using namespace LCR;


QLabel* newLabel(const QString& text, QWidget* parent = 0)
{
	QLabel* _nlbl = new QLabel(text, parent);
	_nlbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	_nlbl->setWordWrap(false);
	return _nlbl;
}

DockCollimator::DockCollimator(const QString& title, QWidget* parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
	data.size.x = 10;
	data.size.y = 10;
	data.size.z = 100;

	data.focus_distance = 500;
	data.diameter[0] = 2.0;
	data.diameter[1] = 2.4;
	data.septa[0] = 0.3;
	data.septa[1] = 0.375;
	data.section_height = 0;

	data.sec_diameter = 0;
	data.sec_thickness = 0;
	data.umbra_width = 0;
	data.penumbra_width = 0;

	initialize();
}

DockCollimator::DockCollimator(const QString& title, const LCR::CollimatorEx& _data, QWidget* parent, Qt::WindowFlags flags)
	: QDockWidget(title, parent, flags)
{
	data = _data;
	initialize();
}

void DockCollimator::initialize()
{
	// Overall size (L, W, H), focus
	dsb_length = new QDoubleSpinBox(this);
	dsb_length->setRange(10, 1000);
	dsb_length->setDecimals(0);
	dsb_length->setSingleStep(1);
	dsb_length->setValue(data.size.x);

	dsb_width = new QDoubleSpinBox(this);
	dsb_width->setRange(10, 100);
	dsb_width->setDecimals(0);
	dsb_width->setSingleStep(1);
	dsb_width->setValue(data.size.y);

	dsb_height = new QDoubleSpinBox(this);
	dsb_height->setRange(0, 150);
	dsb_height->setDecimals(0);
	dsb_height->setSingleStep(1);
	dsb_height->setValue(data.size.z);

	dsb_focus = new QDoubleSpinBox(this);
	dsb_focus->setRange(200, 100000);
	dsb_focus->setDecimals(0);
	dsb_focus->setSingleStep(10);
	dsb_focus->setValue(data.focus_distance);

	QGridLayout* grid_dim = new QGridLayout();
	grid_dim->addWidget(newLabel(tr("Length (mm): ")), 0, 0);
	grid_dim->addWidget(newLabel(tr("Width (mm): ")), 1, 0);
	grid_dim->addWidget(newLabel(tr("Height (mm): ")), 2, 0);
	grid_dim->addWidget(newLabel(tr("Focus Distance (mm): ")), 3, 0);
	grid_dim->addWidget(dsb_length, 0, 1);
	grid_dim->addWidget(dsb_width, 1, 1);
	grid_dim->addWidget(dsb_height, 2, 1);
	grid_dim->addWidget(dsb_focus, 3, 1);

	QGroupBox* gb_coll = new QGroupBox(tr("FOV"));
	gb_coll->setLayout(grid_dim);



	// PATIENT SIDE
	// Diameter, septa at Exit (Patient side)
	dsb_diameter[0] = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.5, 10);
	dsb_diameter[0]->setDecimals(1);
	dsb_diameter[0]->setSingleStep(0.1);
	dsb_diameter[0]->setValue(data.diameter[0]);

	dsb_septa1 = new DoubleSpinBoxSliderWidget(tr("Thickness (mm):"), 100, 0.1, 10);
	dsb_septa1->setDecimals(1);
	dsb_septa1->setSingleStep(0.1);
	dsb_septa1->setValue(data.septa[0]);

	QVBoxLayout* vblayout2 = new QVBoxLayout();
	vblayout2->addWidget(dsb_diameter[0]);
	vblayout2->addWidget(dsb_septa1);

	QGroupBox* gb_ex = new QGroupBox(tr("Patient side"));
	gb_ex->setLayout(vblayout2);



	// X-RAY SIDE
	dsb_diameter[1] = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.5, 10);
	dsb_diameter[1]->setDecimals(1);
	dsb_diameter[1]->setSingleStep(0.1);
	dsb_diameter[1]->setValue(data.diameter[1]);

	dsb_septa2 = new QLabel(this);
	dsb_septa2->setText(QString::number(data.septa[1]));

	QGridLayout* grid_en = new QGridLayout();
	grid_en->addWidget(newLabel(tr("Thickness (mm): ")), 1, 0);
	grid_en->addWidget(dsb_septa2, 1, 1);

	QVBoxLayout* vblayout3 = new QVBoxLayout();
	vblayout3->addWidget(dsb_diameter[1]);
	vblayout3->addLayout(grid_en);

	QGroupBox* gb_en = new QGroupBox(tr("X-ray side"));
	gb_en->setLayout(vblayout3);



	// MIDDLE SECTION
	dsb_section_height = new DoubleSpinBoxSliderWidget(tr("Section Height (mm): "), 100, 0, 10);
	dsb_section_height->setDecimals(0);
	dsb_section_height->setSingleStep(1);
	dsb_section_height->setValue(data.section_height);

	lb_sec_diameter = new QLabel(this);
	lb_sec_thickness = new QLabel(this);

	QGridLayout* grid_sec = new QGridLayout();
	grid_sec->addWidget(newLabel(tr("Diameter (mm): ")), 0, 0);
	grid_sec->addWidget(newLabel(tr("Thickness (mm): ")), 1, 0);
	grid_sec->addWidget(lb_sec_diameter, 0, 1);
	grid_sec->addWidget(lb_sec_thickness, 1, 1);

	QVBoxLayout* vblayout4 = new QVBoxLayout();
	vblayout4->addWidget(dsb_section_height);
	vblayout4->addLayout(grid_sec);

	QGroupBox* gb_section = new QGroupBox(tr("Middle Section"));
	gb_section->setLayout(vblayout4);



	// INFO
	lb_x_side_open_area = new QLabel(this);
	lb_x_side_hole_num = new QLabel(this);

	lb_umbra = new QLabel(this);
	lb_mid_penumbra = new QLabel(this);
	lb_penumbra = new QLabel(this);

	QGridLayout* grid_info = new QGridLayout();
	grid_info->addWidget(newLabel(tr("Open Area Ratio: ")), 0, 0);
	grid_info->addWidget(newLabel(tr("# of holes per cm2: ")), 1, 0);
	grid_info->addWidget(newLabel(tr("Umbra: ")), 2, 0);
	grid_info->addWidget(newLabel(tr("Penumbra (mid): ")), 3, 0);
	grid_info->addWidget(newLabel(tr("Penumbra (full): ")), 4, 0);
	grid_info->addWidget(lb_x_side_open_area, 0, 1);
	grid_info->addWidget(lb_x_side_hole_num, 1, 1);
	grid_info->addWidget(lb_umbra, 2, 1);
	grid_info->addWidget(lb_mid_penumbra, 3, 1);
	grid_info->addWidget(lb_penumbra, 4, 1);

	QGroupBox* gb_info = new QGroupBox(tr("Info"));
	gb_info->setLayout(grid_info);


	QScrollArea* sc = new QScrollArea();
	QVBoxLayout* vbLayout = new QVBoxLayout(sc);

	vbLayout->setSizeConstraint(QLayout::SetMinimumSize);
	vbLayout->addWidget(gb_coll);
	vbLayout->addWidget(gb_ex);
	vbLayout->addWidget(gb_section);
	vbLayout->addWidget(gb_en);
	vbLayout->addWidget(gb_info);
	vbLayout->addStretch();

	connect(dsb_length, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_width,  SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_height, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_focus,  SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	connect(dsb_diameter[0], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_diameter[1], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	connect(dsb_septa1, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_section_height, SIGNAL(valueChanged(double)), this, SLOT(sectionUpdated()));

	setWidget(sc);
}

void DockCollimator::update(const CollimatorEx& new_data)
{
	data = new_data;

	dsb_diameter[0]->setRange(0.5, qMin(data.size.x, data.size.y));
	dsb_diameter[1]->setRange(0.5, qMin(data.size.x, data.size.y));

	dsb_septa2->setText(QString::number(data.septa[1], 'f', 2));

	dsb_section_height->setRange(0, data.size.z);
	lb_sec_diameter->setText(QString::number(data.sec_diameter, 'f', 2));
	lb_sec_thickness->setText(QString::number(data.sec_thickness, 'f', 2));

	if (data.septa[1] > 0) {
		double oar = 1 / (data.septa[1] / data.diameter[1] + 1);
		lb_x_side_open_area->setText(QString::number(oar*oar, 'f', 2));
		oar = 2 * 100 / (sqrt(3) * (data.diameter[1] + data.septa[1]) * (data.diameter[1] + data.septa[1]));
		lb_x_side_hole_num->setText(QString::number(oar, 'f', 2));
	}
	else {
		lb_x_side_open_area->setText("1");
		lb_x_side_hole_num->setText("-");
	}


	lb_umbra->setText(QString::number(data.umbra_width, 'f', 2));
	lb_mid_penumbra->setText(QString::number((qAbs(data.umbra_width) + qAbs(data.penumbra_width)) * 0.5, 'f', 2));
	lb_penumbra->setText(QString::number(data.penumbra_width, 'f', 2));
}

const CollimatorEx& DockCollimator::getData() const
{
	return data;
}

void DockCollimator::parameterUpdated()
{
	data.size.x = dsb_length->value();
	data.size.y = dsb_width->value();
	data.size.z = dsb_height->value();
	data.focus_distance = dsb_focus->value();

	data.diameter[0] = dsb_diameter[0]->value();
	data.diameter[1] = dsb_diameter[1]->value();
	data.septa[0] = dsb_septa1->value();

	emit updateParameters();
}

void DockCollimator::sectionUpdated()
{
	data.section_height = dsb_section_height->value();

	emit updateSection();
}
