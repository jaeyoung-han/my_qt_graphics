#include <QtWidgets>
#include "DockCollimator.h"

using namespace LCR;


QLabel* newLabel(const QString& text, int width = 0, QWidget* parent = 0)
{
	QLabel* _nlbl = new QLabel(text, parent);
	_nlbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
	if (width > 0)
		_nlbl->setFixedWidth(width);

	_nlbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	_nlbl->setWordWrap(false);
	return _nlbl;
}


DockCollimator::DockCollimator(const QString& title, QWidget* parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
	data.direction = 0;

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
	setObjectName("DockCollimator");

	int w_label = 108;
	int w_slider = 108;
	int w_spinbox = 64;

    rb_shape_hexagon = new QRadioButton(tr("Hexagon"));
    rb_shape_hexagon->setChecked(true);
    rb_shape_square = new QRadioButton(tr("Square"));

    QHBoxLayout* hb_shape = new QHBoxLayout();
    hb_shape->addWidget(rb_shape_hexagon);
    hb_shape->addWidget(rb_shape_square);

    QGroupBox* gb_shape = new QGroupBox(tr("Hole Shape"));
    gb_shape->setLayout(hb_shape);

	rb_horizontal = new QRadioButton(tr("Horizontal"));
	rb_horizontal->setChecked(true);
	rb_vertical = new QRadioButton(tr("Vertical"));

	QHBoxLayout* hb_dir = new QHBoxLayout();
	hb_dir->addWidget(rb_horizontal);
	hb_dir->addWidget(rb_vertical);

	gb_dir = new QGroupBox(tr("Hexagon Direction"));
	gb_dir->setLayout(hb_dir);
    gb_dir->setEnabled(true);

	// Overall size (L, W, H), focus
	dsb_length = new DoubleSpinBoxSliderWidget(tr("Lengh (mm): "), 100, 10, 1000);
	dsb_length->setDecimals(0);
	dsb_length->setSingleStep(1);
	dsb_length->setValue(data.size.x);
	dsb_length->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_width = new DoubleSpinBoxSliderWidget(tr("Width (mm): "), 100, 10, 100);
	dsb_width->setDecimals(0);
	dsb_width->setSingleStep(1);
	dsb_width->setValue(data.size.y);
	dsb_width->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_height = new DoubleSpinBoxSliderWidget(tr("Height (mm): "), 100, 10, 400);
	dsb_height->setDecimals(0);
	dsb_height->setSingleStep(10);
	dsb_height->setValue(data.size.z);
	dsb_height->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_focus = new DoubleSpinBoxSliderWidget(tr("Focus Distance (mm): "), 101, 10, 1000);
	dsb_focus->setDecimals(0);
	dsb_focus->setSingleStep(10);
	dsb_focus->setValue(data.focus_distance);
	dsb_focus->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	QVBoxLayout* vblayout1 = new QVBoxLayout();
	vblayout1->addWidget(dsb_length);
	vblayout1->addWidget(dsb_width);
	vblayout1->addWidget(dsb_height);
	vblayout1->addWidget(dsb_focus);

	QGroupBox* gb_coll = new QGroupBox(tr("FOV"));
	gb_coll->setLayout(vblayout1);



	// PATIENT SIDE
	// Diameter, septa at Exit (Patient side)
	dsb_diameter[0] = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.1, 10);
	dsb_diameter[0]->setDecimals(2);
	dsb_diameter[0]->setSingleStep(0.1);
	dsb_diameter[0]->setValue(data.diameter[0]);
	dsb_diameter[0]->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_septa1 = new DoubleSpinBoxSliderWidget(tr("Thickness (mm): "), 100, 0.1, 10);
	dsb_septa1->setDecimals(2);
	dsb_septa1->setSingleStep(0.1);
	dsb_septa1->setValue(data.septa[0]);
	dsb_septa1->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	QVBoxLayout* vblayout2 = new QVBoxLayout();
	vblayout2->addWidget(dsb_diameter[0]);
	vblayout2->addWidget(dsb_septa1);

	QGroupBox* gb_ex = new QGroupBox(tr("Top Plane (Patient side)"));
	gb_ex->setLayout(vblayout2);



	// X-RAY SIDE
	dsb_diameter[1] = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.1, 10);
	dsb_diameter[1]->setDecimals(2);
	dsb_diameter[1]->setSingleStep(0.1);
	dsb_diameter[1]->setValue(data.diameter[1]);
	dsb_diameter[1]->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_septa2 = new QLabel(this);
	dsb_septa2->setMinimumWidth(w_spinbox);
	dsb_septa2->setMinimumHeight(22);
	dsb_septa2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	dsb_septa2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	dsb_septa2->setLineWidth(1);
	dsb_septa2->setText(QString::number(data.septa[1]));

	cb_conv_div_mix = new QCheckBox(tr("Mix converging-divering hole"));
	cb_conv_div_mix->setChecked(false);

	QHBoxLayout* hblayout1 = new QHBoxLayout();
	hblayout1->addWidget(newLabel(tr("Thickness (mm): "), w_label));
	hblayout1->addStretch();
	hblayout1->addWidget(dsb_septa2);

	QVBoxLayout* vblayout3 = new QVBoxLayout();
	vblayout3->addWidget(dsb_diameter[1]);
	vblayout3->addLayout(hblayout1);
	vblayout3->addWidget(cb_conv_div_mix);

	QGroupBox* gb_en = new QGroupBox(tr("Bottom Plane (X-ray side)"));
	gb_en->setLayout(vblayout3);



	// MIDDLE SECTION
	dsb_section_height = new DoubleSpinBoxSliderWidget(tr("Section Height (mm): "), 100, 0, 10);
	dsb_section_height->setDecimals(0);
	dsb_section_height->setSingleStep(1);
	dsb_section_height->setValue(data.section_height);
	dsb_section_height->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	lb_sec_diameter = new QLabel(this);
	lb_sec_diameter->setMinimumWidth(w_spinbox);
	lb_sec_diameter->setMinimumHeight(22);
	lb_sec_diameter->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_sec_diameter->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_sec_diameter->setLineWidth(1);

	lb_sec_thickness = new QLabel(this);
	lb_sec_thickness->setMinimumWidth(w_spinbox);
	lb_sec_thickness->setMinimumHeight(22);
	lb_sec_thickness->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_sec_thickness->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_sec_thickness->setLineWidth(1);

	QHBoxLayout* hblayout2 = new QHBoxLayout();
	hblayout2->addWidget(newLabel(tr("Diameter (mm): "), w_label));
	hblayout2->addStretch();
	hblayout2->addWidget(lb_sec_diameter);

	QHBoxLayout* hblayout3 = new QHBoxLayout();
	hblayout3->addWidget(newLabel(tr("Thickness (mm): "), w_label));
	hblayout3->addStretch();
	hblayout3->addWidget(lb_sec_thickness);

	QVBoxLayout* vblayout4 = new QVBoxLayout();
	vblayout4->addWidget(dsb_section_height);
	vblayout4->addLayout(hblayout2);
	vblayout4->addLayout(hblayout3);

	QGroupBox* gb_section = new QGroupBox(tr("Mid Plane (btw Top and Bottom)"));
	gb_section->setLayout(vblayout4);



	// INFO
	lb_x_side_open_area = new QLabel(this);
	lb_x_side_open_area->setMinimumHeight(22);
	lb_x_side_hole_num = new QLabel(this);
	lb_x_side_hole_num->setMinimumHeight(22);

	QGridLayout* grid_info = new QGridLayout();
	grid_info->addWidget(newLabel(tr("Open Area Ratio: "), w_label), 0, 0);
	grid_info->addWidget(newLabel(tr("# of holes per cm2: "), w_label), 1, 0);
	grid_info->addWidget(lb_x_side_open_area, 0, 1);
	grid_info->addWidget(lb_x_side_hole_num, 1, 1);

	QGroupBox* gb_info = new QGroupBox(tr("Info"));
	gb_info->setLayout(grid_info);



	// Umbra graphic
	umbra_widget = new UmbraWidget();
	umbra_widget->setMinimumHeight(180);

	lb_umbra = new QLabel(this);
	lb_umbra->setMinimumWidth(40);
	lb_umbra->setMinimumHeight(22);
	lb_umbra->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_umbra->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_umbra->setLineWidth(1);

	lb_mid_penumbra = new QLabel(this);
	lb_mid_penumbra->setMinimumWidth(40);
	lb_mid_penumbra->setMinimumHeight(22);
	lb_mid_penumbra->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_mid_penumbra->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_mid_penumbra->setLineWidth(1);

	lb_penumbra = new QLabel(this);
	lb_penumbra->setMinimumWidth(40);
	lb_penumbra->setMinimumHeight(22);
	lb_penumbra->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_penumbra->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_penumbra->setLineWidth(1);

	QHBoxLayout* hblayout = new QHBoxLayout();
	hblayout->addWidget(newLabel(tr("Umbra: ")));
	hblayout->addWidget(lb_umbra);
	hblayout->addStretch();
	hblayout->addWidget(newLabel(tr("/ FWHM: ")));
	hblayout->addWidget(lb_mid_penumbra);
	hblayout->addStretch();
	hblayout->addWidget(newLabel(tr("/ Penum: ")));
	hblayout->addWidget(lb_penumbra);
	hblayout->addStretch();

	QVBoxLayout* vblayout5 = new QVBoxLayout();
	vblayout5->addLayout(hblayout);
	vblayout5->addWidget(umbra_widget);

	QGroupBox* gb_umbra = new QGroupBox(tr("Umbra"));
	gb_umbra->setLayout(vblayout5);

	// Main
	QScrollArea* sc = new QScrollArea();
	QVBoxLayout* vbLayout = new QVBoxLayout(sc);

	vbLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    vbLayout->addWidget(gb_shape);
	vbLayout->addWidget(gb_dir);
	vbLayout->addWidget(gb_coll);
	vbLayout->addWidget(gb_ex);
	vbLayout->addWidget(gb_section);
	vbLayout->addWidget(gb_en);
	vbLayout->addWidget(gb_info);
	vbLayout->addWidget(gb_umbra);

    connect(rb_shape_hexagon, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));
    connect(rb_shape_square, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));

	connect(rb_horizontal, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));
	connect(rb_vertical, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));

	connect(dsb_length, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_width,  SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_height, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_focus,  SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	connect(dsb_diameter[0], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_diameter[1], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	connect(cb_conv_div_mix, SIGNAL(stateChanged(int)), this, SLOT(parameterUpdated()));

	connect(dsb_septa1, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_section_height, SIGNAL(valueChanged(double)), this, SLOT(sectionUpdated()));

	setWidget(sc);
}

void DockCollimator::update(const CollimatorEx& new_data)
{
	double area_1cm_circle = 0.5 * 0.5 * M_PI;
	data = new_data;

	rb_horizontal->setChecked(data.direction == 0);
	rb_vertical->setChecked(data.direction != 0);

	dsb_focus->setRange(data.size.z + 1, 1000);
	dsb_diameter[0]->setRange(0.1, qMin(data.size.x, data.size.y));
	dsb_diameter[1]->setRange(0.1, qMin(data.size.x, data.size.y));

	dsb_septa2->setText(QString::number(data.septa[1], 'f', 2));

	if (data.septa[0] < 0.3) {
		dsb_septa1->setStyleSheet("QDoubleSpinBox { background-color : #FF5555;}");
	}
	else {
		dsb_septa1->setStyleSheet("QDoubleSpinBox { background-color : white;}");
	}


	if (data.septa[1] < 0.3) {
		dsb_septa2->setStyleSheet("QLabel { background-color : #FF5555;}");
	}
	else {
		dsb_septa2->setStyleSheet("QLabel { background-color : white;}");
	}

	dsb_section_height->setRange(0, data.size.z);
	lb_sec_diameter->setText(QString::number(data.sec_diameter, 'f', 2));
	lb_sec_thickness->setText(QString::number(data.sec_thickness, 'f', 2));

	if (data.sec_thickness < 0.3) {
		lb_sec_thickness->setStyleSheet("QLabel { background-color : #FF5555;}");
	}
	else {
		lb_sec_thickness->setStyleSheet("QLabel { background-color : white;}");
	}

	if (data.septa[1] > 0) {
		double oar = 1 / (data.septa[1] / data.diameter[1] + 1);
		lb_x_side_open_area->setText(QString::number(oar*oar, 'f', 2));
		oar = 2 * 100 / (sqrt(3) * (data.diameter[1] + data.septa[1]) * (data.diameter[1] + data.septa[1]));
		lb_x_side_hole_num->setText(QString::number(oar * area_1cm_circle, 'f', 2));
	}
	else {
		lb_x_side_open_area->setText("1");
		lb_x_side_hole_num->setText("-");
	}


	lb_umbra->setText(QString::number(data.umbra_width, 'f', 2));
	lb_mid_penumbra->setText(QString::number((qAbs(data.umbra_width) + qAbs(data.penumbra_width)) * 0.5, 'f', 2));
	lb_penumbra->setText(QString::number(data.penumbra_width, 'f', 2));

	umbra_widget->update(data.umbra_width, data.penumbra_width);
}

const CollimatorEx& DockCollimator::getData() const
{
	return data;
}

void DockCollimator::resizeEvent(QResizeEvent* event)
{
	//QRect rect = umbra_widget->rect();

	//umbra_widget->resize(rect.width(), rect.width());

	QDockWidget::resizeEvent(event);
}

void DockCollimator::parameterUpdated()
{
    if (rb_shape_hexagon->isChecked()) {
        data.shape = 1;
        gb_dir->setEnabled(true);
    }
    else if (rb_shape_square->isChecked()) {
        data.shape = 2;
        gb_dir->setEnabled(false);
    }
	data.direction = rb_horizontal->isChecked() ? 0 : 1;

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
