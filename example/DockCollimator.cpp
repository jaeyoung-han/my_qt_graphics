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
    rb_shape_square_thickness = new QRadioButton(tr("Square (thick)"));

    QHBoxLayout* hb_shape = new QHBoxLayout();
    hb_shape->addWidget(rb_shape_hexagon);
    hb_shape->addWidget(rb_shape_square);
    hb_shape->addWidget(rb_shape_square_thickness);

    QGroupBox* gb_shape = new QGroupBox(tr("Hole Shape"));
    gb_shape->setLayout(hb_shape);
    gb_shape->setEnabled(false);

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
	dsb_length->setSingleStep(10);
	dsb_length->setValue(data.size.x);
	dsb_length->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_width = new DoubleSpinBoxSliderWidget(tr("Width (mm): "), 100, 10, 1000);
	dsb_width->setDecimals(0);
	dsb_width->setSingleStep(10);
	dsb_width->setValue(data.size.y);
	dsb_width->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	dsb_height = new DoubleSpinBoxSliderWidget(tr("Height (mm): "), 100, 10, 1000);
	dsb_height->setDecimals(0);
	dsb_height->setSingleStep(10);
	dsb_height->setValue(data.size.z);
	dsb_height->setItemMinimumWidth(w_label, w_slider, w_spinbox);

	QVBoxLayout* vblayout1 = new QVBoxLayout();
	vblayout1->addWidget(dsb_length);
	vblayout1->addWidget(dsb_width);
	vblayout1->addWidget(dsb_height);

	QGroupBox* gb_dimension = new QGroupBox(tr("Dimension"));
    gb_dimension->setLayout(vblayout1);


    cb_symmetric = new QCheckBox(tr("Symmetric"));
    cb_symmetric->setChecked(false);
    cb_iso_focus = new QCheckBox(tr("Iso-focus"));
    cb_iso_focus->setChecked(false);

    QHBoxLayout* hbl_select = new QHBoxLayout;
    hbl_select->addWidget(cb_symmetric);
    hbl_select->addWidget(cb_iso_focus);

    // Longitudinal
    dsb_focus_coll_l = new DoubleSpinBoxSliderWidget(tr("Collimator focus (mm): "), 101, -1000, 1000);
    dsb_focus_coll_l->setDecimals(0);
    dsb_focus_coll_l->setSingleStep(10);
    dsb_focus_coll_l->setValue(data.focus_coll_long);
    dsb_focus_coll_l->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    dsb_focus_hole_l = new DoubleSpinBoxSliderWidget(tr("Hole focus (mm): "), 201, -1000, 1000);
    dsb_focus_hole_l->setDecimals(0);
    dsb_focus_hole_l->setSingleStep(10);
    dsb_focus_hole_l->setValue(data.focus_hole_long);
    dsb_focus_hole_l->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    dsb_diameter_l = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.1, 10);
    dsb_diameter_l->setDecimals(3);
    dsb_diameter_l->setSingleStep(0.1);
    dsb_diameter_l->setValue(data.hole_ex.diameter_long);
    dsb_diameter_l->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    dsb_septa_l = new DoubleSpinBoxSliderWidget(tr("Thickness (mm): "), 100, 0.1, 10);
    dsb_septa_l->setDecimals(3);
    dsb_septa_l->setSingleStep(0.1);
    dsb_septa_l->setValue(data.hole_ex.septa_long);
    dsb_septa_l->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    QVBoxLayout* vbl_longitudinal = new QVBoxLayout;
    vbl_longitudinal->addWidget(dsb_focus_coll_l);
    vbl_longitudinal->addWidget(dsb_focus_hole_l);
    vbl_longitudinal->addWidget(dsb_diameter_l);
    vbl_longitudinal->addWidget(dsb_septa_l);

    QGroupBox* gb_longitudinal = new QGroupBox(tr("Longitudinal"));
    gb_longitudinal->setLayout(vbl_longitudinal);


    dsb_focus_coll_w = new DoubleSpinBoxSliderWidget(tr("Collimator focus (mm): "), 201, -1000, 1000);
    dsb_focus_coll_w->setDecimals(0);
    dsb_focus_coll_w->setSingleStep(10);
    dsb_focus_coll_w->setValue(data.focus_coll_tran);
    dsb_focus_coll_w->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    dsb_focus_hole_w = new DoubleSpinBoxSliderWidget(tr("Hole focus (mm): "), 201, -1000, 1000);
    dsb_focus_hole_w->setDecimals(0);
    dsb_focus_hole_w->setSingleStep(10);
    dsb_focus_hole_w->setValue(data.focus_hole_tran);
    dsb_focus_hole_w->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    dsb_diameter_w = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.1, 10);
    dsb_diameter_w->setDecimals(3);
    dsb_diameter_w->setSingleStep(0.1);
    dsb_diameter_w->setValue(data.hole_ex.diameter_tran);
    dsb_diameter_w->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    dsb_septa_w = new DoubleSpinBoxSliderWidget(tr("Thickness (mm): "), 100, 0.1, 10);
    dsb_septa_w->setDecimals(3);
    dsb_septa_w->setSingleStep(0.1);
    dsb_septa_w->setValue(data.hole_ex.septa_tran);
    dsb_septa_w->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    QVBoxLayout* vbl_transverse = new QVBoxLayout;
    vbl_transverse->addWidget(dsb_focus_coll_w);
    vbl_transverse->addWidget(dsb_focus_hole_w);
    vbl_transverse->addWidget(dsb_diameter_w);
    vbl_transverse->addWidget(dsb_septa_w);

    gb_transverse = new QGroupBox(tr("Transverse"));
    gb_transverse->setLayout(vbl_transverse);

    QVBoxLayout* vbl_exit = new QVBoxLayout;
    vbl_exit->addLayout(hbl_select);
    vbl_exit->addWidget(gb_longitudinal);
    vbl_exit->addWidget(gb_transverse);
    QGroupBox* gb_exit = new QGroupBox(tr("Exit Plane"));
    gb_exit->setLayout(vbl_exit);

	// X-RAY SIDE
    lb_en_diameter_long = new QLabel(this);
    lb_en_diameter_long->setMinimumWidth(w_spinbox);
    lb_en_diameter_long->setMinimumHeight(22);
    lb_en_diameter_long->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_en_diameter_long->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_en_diameter_long->setLineWidth(1);
    lb_en_diameter_long->setText(QString::number(data.hole_en.diameter_long));

    lb_en_diameter_tran = new QLabel(this);
    lb_en_diameter_tran->setMinimumWidth(w_spinbox);
    lb_en_diameter_tran->setMinimumHeight(22);
    lb_en_diameter_tran->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_en_diameter_tran->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_en_diameter_tran->setLineWidth(1);
    lb_en_diameter_tran->setText(QString::number(data.hole_en.diameter_tran));

	lb_en_septa_long = new QLabel(this);
	lb_en_septa_long->setMinimumWidth(w_spinbox);
	lb_en_septa_long->setMinimumHeight(22);
	lb_en_septa_long->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_en_septa_long->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_en_septa_long->setLineWidth(1);
	lb_en_septa_long->setText(QString::number(data.hole_en.septa_long));

    lb_en_septa_tran = new QLabel(this);
    lb_en_septa_tran->setMinimumWidth(w_spinbox);
    lb_en_septa_tran->setMinimumHeight(22);
    lb_en_septa_tran->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_en_septa_tran->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_en_septa_tran->setLineWidth(1);
    lb_en_septa_tran->setText(QString::number(data.hole_en.septa_tran));
    
    cb_conv_div_mix = new QCheckBox(tr("Mix converging-divering hole"));
	cb_conv_div_mix->setChecked(false);

    QHBoxLayout* hblayout0 = new QHBoxLayout();
    hblayout0->addWidget(newLabel(tr("Diameter (mm): "), w_label));
    hblayout0->addStretch();
    hblayout0->addWidget(lb_en_diameter_long);
    hblayout0->addWidget(lb_en_diameter_tran);
    
    QHBoxLayout* hblayout1 = new QHBoxLayout();
	hblayout1->addWidget(newLabel(tr("Thickness (mm): "), w_label));
	hblayout1->addStretch();
	hblayout1->addWidget(lb_en_septa_long);
    hblayout1->addWidget(lb_en_septa_tran);

	QVBoxLayout* vblayout3 = new QVBoxLayout();
	vblayout3->addLayout(hblayout0);
	vblayout3->addLayout(hblayout1);
//	vblayout3->addWidget(cb_conv_div_mix);

    gb_bottom_plane_ = new QGroupBox(tr("Entrance Plane (X-ray side)"));
    gb_bottom_plane_->setLayout(vblayout3);



	// MIDDLE SECTION
	dsb_section_height = new DoubleSpinBoxSliderWidget(tr("Section Height (mm): "), 100, 0, 10);
	dsb_section_height->setDecimals(0);
	dsb_section_height->setSingleStep(1);
	dsb_section_height->setValue(data.hole_sec.z);
	dsb_section_height->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    lb_sec_diameter_long = new QLabel(this);
	lb_sec_diameter_long->setMinimumWidth(w_spinbox);
	lb_sec_diameter_long->setMinimumHeight(22);
	lb_sec_diameter_long->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_sec_diameter_long->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_sec_diameter_long->setLineWidth(1);

    lb_sec_diameter_tran = new QLabel(this);
    lb_sec_diameter_tran->setMinimumWidth(w_spinbox);
    lb_sec_diameter_tran->setMinimumHeight(22);
    lb_sec_diameter_tran->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_sec_diameter_tran->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_sec_diameter_tran->setLineWidth(1);

	lb_sec_septa_long = new QLabel(this);
	lb_sec_septa_long->setMinimumWidth(w_spinbox);
	lb_sec_septa_long->setMinimumHeight(22);
	lb_sec_septa_long->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	lb_sec_septa_long->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	lb_sec_septa_long->setLineWidth(1);

    lb_sec_septa_tran = new QLabel(this);
    lb_sec_septa_tran->setMinimumWidth(w_spinbox);
    lb_sec_septa_tran->setMinimumHeight(22);
    lb_sec_septa_tran->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_sec_septa_tran->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_sec_septa_tran->setLineWidth(1);

	QHBoxLayout* hblayout2 = new QHBoxLayout();
	hblayout2->addWidget(newLabel(tr("Diameter (mm): "), w_label));
	hblayout2->addStretch();
    hblayout2->addWidget(lb_sec_diameter_long);
    hblayout2->addWidget(lb_sec_diameter_tran);

	QHBoxLayout* hblayout3 = new QHBoxLayout();
	hblayout3->addWidget(newLabel(tr("Thickness (mm): "), w_label));
	hblayout3->addStretch();
	hblayout3->addWidget(lb_sec_septa_long);
    hblayout3->addWidget(lb_sec_septa_tran);

	QVBoxLayout* vblayout4 = new QVBoxLayout();
	vblayout4->addWidget(dsb_section_height);
	vblayout4->addLayout(hblayout2);
	vblayout4->addLayout(hblayout3);

	QGroupBox* gb_section = new QGroupBox(tr("Mid Plane"));
	gb_section->setLayout(vblayout4);



	// INFO
    dsb_anode_depth = new DoubleSpinBoxSliderWidget(tr("Anode depth (mm): "), 100, 0, 100);
    dsb_anode_depth->setDecimals(1);
    dsb_anode_depth->setSingleStep(0.1);
    dsb_anode_depth->setValue(41.7);
    dsb_anode_depth->setPrefix("- ");
    dsb_anode_depth->setItemMinimumWidth(w_label, w_slider, w_spinbox);

    lb_anode_diameter_long = new QLabel(this);
    lb_anode_diameter_long->setMinimumWidth(w_spinbox);
    lb_anode_diameter_long->setMinimumHeight(22);
    lb_anode_diameter_long->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_anode_diameter_long->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_anode_diameter_long->setLineWidth(1);

    lb_anode_diameter_tran = new QLabel(this);
    lb_anode_diameter_tran->setMinimumWidth(w_spinbox);
    lb_anode_diameter_tran->setMinimumHeight(22);
    lb_anode_diameter_tran->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    lb_anode_diameter_tran->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lb_anode_diameter_tran->setLineWidth(1);
    
    QHBoxLayout* hblayout4 = new QHBoxLayout();
    hblayout4->addWidget(newLabel(tr("Diameter (mm): "), w_label));
    hblayout4->addStretch();
    hblayout4->addWidget(lb_anode_diameter_long);
    hblayout4->addWidget(lb_anode_diameter_tran);

    QVBoxLayout* vblayout6 = new QVBoxLayout;
    vblayout6->addWidget(dsb_anode_depth);
    vblayout6->addLayout(hblayout4);

    QGroupBox* gb_anode = new QGroupBox(tr("Anode"));
    gb_anode->setLayout(vblayout6);

    lb_x_side_open_area = new QLabel(this);
	lb_x_side_open_area->setMinimumHeight(22);
	lb_x_side_hole_num = new QLabel(this);
	lb_x_side_hole_num->setMinimumHeight(22);

	QGridLayout* grid_info = new QGridLayout();
    grid_info->addWidget(gb_anode, 0, 0, 1, 2);
	grid_info->addWidget(newLabel(tr("Open Area Ratio: "), w_label), 1, 0);
	grid_info->addWidget(newLabel(tr("# of holes per cm2: "), w_label), 2, 0);
	grid_info->addWidget(lb_x_side_open_area, 1, 1);
	grid_info->addWidget(lb_x_side_hole_num, 2, 1);

    gb_info_ = new QGroupBox(tr("Info"));
    gb_info_->setLayout(grid_info);



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

    gb_umbra_ = new QGroupBox(tr("Umbra"));
    gb_umbra_->setLayout(vblayout5);

	// Main
	QScrollArea* sc = new QScrollArea();

    QWidget *widget = new QWidget;
	QVBoxLayout* vbLayout = new QVBoxLayout;
    widget->setLayout(vbLayout);
    sc->setWidget(widget);
    sc->setWidgetResizable(true);

	vbLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    vbLayout->addWidget(gb_shape);
	vbLayout->addWidget(gb_dir);
	vbLayout->addWidget(gb_dimension);
    vbLayout->addWidget(gb_exit);
	vbLayout->addWidget(gb_bottom_plane_);
    vbLayout->addWidget(gb_section);
    vbLayout->addWidget(gb_info_);
	vbLayout->addWidget(gb_umbra_);
    vbLayout->addStretch();

    connect(rb_shape_hexagon, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));
    connect(rb_shape_square, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));
    connect(rb_shape_square_thickness, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));

	connect(rb_horizontal, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));
	connect(rb_vertical, SIGNAL(clicked(bool)), this, SLOT(parameterUpdated()));

	connect(dsb_length, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_width,  SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
	connect(dsb_height, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	connect(dsb_focus_coll_l,  SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
    connect(dsb_focus_hole_l, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
    connect(dsb_diameter_l, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
    connect(dsb_septa_l, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

    connect(dsb_focus_coll_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
    connect(dsb_focus_hole_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
    connect(dsb_diameter_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
    connect(dsb_septa_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	connect(cb_conv_div_mix, SIGNAL(stateChanged(int)), this, SLOT(parameterUpdated()));

    connect(dsb_section_height, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

    connect(cb_symmetric, SIGNAL(clicked(bool)), this, SLOT(updateUI()));
    connect(cb_iso_focus, SIGNAL(clicked(bool)), this, SLOT(updateUI()));

    connect(dsb_anode_depth, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

	setWidget(sc);
}

void DockCollimator::update(const CollimatorEx& new_data)
{
	double area_1cm_circle = 0.5 * 0.5 * M_PI;
	data = new_data;

    switch (data.shape) {
    default:
    case 1:
        rb_shape_hexagon->setChecked(true);
        gb_dir->setVisible(true);
        gb_bottom_plane_->setVisible(true);
        gb_info_->setVisible(true);
        gb_umbra_->setVisible(true);
        break;
    case 2:
        rb_shape_square->setChecked(true);
        gb_dir->setVisible(false);
        gb_bottom_plane_->setVisible(true);
        gb_info_->setVisible(true);
        gb_umbra_->setVisible(true);
        break;
    case 12:
        rb_shape_square_thickness->setChecked(true);
        gb_dir->setVisible(false);
        gb_bottom_plane_->setVisible(false);
        gb_info_->setVisible(false);
        gb_umbra_->setVisible(false);
        break;
    }

	rb_horizontal->setChecked(data.direction == 0);
	rb_vertical->setChecked(data.direction != 0);

	dsb_diameter_l->setRange(0.1, qMin(data.size.x, data.size.y));
	dsb_diameter_w->setRange(0.1, qMin(data.size.x, data.size.y));

    dsb_section_height->setRange(0, data.size.z);



	


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
        gb_dir->setVisible(true);
        gb_bottom_plane_->setVisible(true);
        gb_info_->setVisible(true);
        gb_umbra_->setVisible(true);
    }
    else if (rb_shape_square->isChecked()) {
        data.shape = 2;
        gb_dir->setVisible(false);
        gb_bottom_plane_->setVisible(true);
        gb_info_->setVisible(true);
        gb_umbra_->setVisible(true);
    }
    else if (rb_shape_square_thickness->isChecked()) {
        data.shape = 12;
        gb_dir->setVisible(false);
        gb_bottom_plane_->setVisible(false);
        gb_info_->setVisible(false);
        gb_umbra_->setVisible(false);
    }


    data.direction = rb_horizontal->isChecked() ? 0 : 1;

	data.size.x = dsb_length->value();
	data.size.y = dsb_width->value();
	data.size.z = dsb_height->value();

    if (sender() == dsb_height) {
        dsb_section_height->setRange(0, data.size.z);
    }

    data.focus_coll_long = dsb_focus_coll_l->value();
    data.focus_coll_tran = dsb_focus_coll_w->value();
    data.focus_hole_long = dsb_focus_hole_l->value();
    data.focus_hole_tran = dsb_focus_hole_w->value();

    data.hole_ex.z = dsb_height->value();
    data.hole_ex.diameter_long = dsb_diameter_l->value();
    data.hole_ex.diameter_tran = dsb_diameter_w->value();
    data.hole_ex.septa_long = dsb_septa_l->value();
    data.hole_ex.septa_tran = dsb_septa_w->value();

    data.hole_en.z = 0;
    data.hole_sec.z = dsb_section_height->value();
    data.update();

    lb_en_diameter_long->setText(QString::number(data.hole_en.diameter_long, 'f', 3));
    lb_en_diameter_tran->setText(QString::number(data.hole_en.diameter_tran, 'f', 3));
    lb_en_septa_long->setText(QString::number(data.hole_en.septa_long, 'f', 3));
    lb_en_septa_tran->setText(QString::number(data.hole_en.septa_tran, 'f', 3));
 
    if (data.hole_ex.septa_long < 0.2 || data.hole_ex.septa_tran < 0.2) {
        dsb_septa_l->setStyleSheet("QDoubleSpinBox { background-color : #FF5555;}");
        dsb_septa_w->setStyleSheet("QDoubleSpinBox { background-color : #FF5555;}");
    }
    else {
        dsb_septa_l->setStyleSheet("QDoubleSpinBox { background-color : white;}");
        dsb_septa_w->setStyleSheet("QDoubleSpinBox { background-color : white;}");
    }
    
    if (data.hole_en.septa_long < 0.2) {
        lb_en_septa_long->setStyleSheet("QLabel { background-color : #FF5555;}");
    }
    else {
        lb_en_septa_long->setStyleSheet("QLabel { background-color : white;}");
    }

    if (data.hole_en.septa_tran < 0.2) {
        lb_en_septa_tran->setStyleSheet("QLabel { background-color : #FF5555;}");
    }
    else {
        lb_en_septa_tran->setStyleSheet("QLabel { background-color : white;}");
    }

    lb_sec_diameter_long->setText(QString::number(data.hole_sec.diameter_long, 'f', 3));
    lb_sec_diameter_tran->setText(QString::number(data.hole_sec.diameter_tran, 'f', 3));
    lb_sec_septa_long->setText(QString::number(data.hole_sec.septa_long, 'f', 3));
    lb_sec_septa_tran->setText(QString::number(data.hole_sec.septa_tran, 'f', 3));

    if (data.hole_sec.septa_long < 0.2) {
        lb_sec_septa_long->setStyleSheet("QLabel { background-color : #FF5555;}");
    }
    else {
        lb_sec_septa_long->setStyleSheet("QLabel { background-color : white;}");
    }

    if (data.hole_sec.septa_tran < 0.2) {
        lb_sec_septa_tran->setStyleSheet("QLabel { background-color : #FF5555;}");
    }
    else {
        lb_sec_septa_tran->setStyleSheet("QLabel { background-color : white;}");
    }

    //if (data.septa[1] > 0) {
    //	double oar = 1 / (data.septa[1] / data.diameter[1] + 1);
    //	lb_x_side_open_area->setText(QString::number(oar*oar, 'f', 3));
    //	oar = 2 * 100 / (sqrt(3) * (data.diameter[1] + data.septa[1]) * (data.diameter[1] + data.septa[1]));
    //	lb_x_side_hole_num->setText(QString::number(oar * area_1cm_circle, 'f', 3));
    //}
    //else 
    {
        lb_x_side_open_area->setText("1");
        lb_x_side_hole_num->setText("-");
    }

    double anode_z = -1.0 * dsb_anode_depth->value();
    double anode_long = data.getLongitudinalDiameter(anode_z);
    double anode_tran = data.getTransverseDiameter(anode_z);

    lb_anode_diameter_long->setText(QString::number(anode_long, 'f', 3));
    lb_anode_diameter_tran->setText(QString::number(anode_tran, 'f', 3));

    lb_umbra->setText(QString::number(data.umbra_width, 'f', 2));
    lb_mid_penumbra->setText(QString::number((qAbs(data.umbra_width) + qAbs(data.penumbra_width)) * 0.5, 'f', 2));
    lb_penumbra->setText(QString::number(data.penumbra_width, 'f', 2));

    umbra_widget->update(data.umbra_width, data.penumbra_width);

	emit updateParameters();
}

void DockCollimator::sectionUpdated()
{
}

void DockCollimator::updateUI()
{
    if (sender() == cb_symmetric) {
        if (cb_symmetric->isChecked()) {
            gb_transverse->setEnabled(false);

            connect(dsb_focus_coll_l, SIGNAL(valueChanged(double)), dsb_focus_coll_w, SLOT(setValue(double)));
            connect(dsb_focus_hole_l, SIGNAL(valueChanged(double)), dsb_focus_hole_w, SLOT(setValue(double)));
            connect(dsb_diameter_l, SIGNAL(valueChanged(double)), dsb_diameter_w, SLOT(setValue(double)));
            connect(dsb_septa_l, SIGNAL(valueChanged(double)), dsb_septa_w, SLOT(setValue(double)));

            dsb_focus_coll_w->setValue(dsb_focus_coll_l->value());
            dsb_focus_hole_w->setValue(dsb_focus_hole_l->value());
            dsb_diameter_w->setValue(dsb_diameter_l->value());
            dsb_septa_w->setValue(dsb_septa_l->value());
        }
        else {
            gb_transverse->setEnabled(true);

            disconnect(dsb_focus_coll_l, SIGNAL(valueChanged(double)), dsb_focus_coll_w, SLOT(setValue(double)));
            disconnect(dsb_focus_hole_l, SIGNAL(valueChanged(double)), dsb_focus_hole_w, SLOT(setValue(double)));
            disconnect(dsb_diameter_l, SIGNAL(valueChanged(double)), dsb_diameter_w, SLOT(setValue(double)));
            disconnect(dsb_septa_l, SIGNAL(valueChanged(double)), dsb_septa_w, SLOT(setValue(double)));

            if (cb_iso_focus->isChecked()) {
                disconnect(dsb_focus_hole_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
                connect(dsb_focus_coll_w, SIGNAL(valueChanged(double)), dsb_focus_hole_w, SLOT(setValue(double)));
            }
        }
    }
    else if (sender() == cb_iso_focus) {
        if (cb_iso_focus->isChecked()) {
            dsb_focus_hole_l->setEnabled(false);
            dsb_focus_hole_w->setEnabled(false);

            disconnect(dsb_focus_hole_l, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
            connect(dsb_focus_coll_l, SIGNAL(valueChanged(double)), dsb_focus_hole_l, SLOT(setValue(double)));

            if (!cb_symmetric->isChecked()) {
                disconnect(dsb_focus_hole_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
                connect(dsb_focus_coll_w, SIGNAL(valueChanged(double)), dsb_focus_hole_w, SLOT(setValue(double)));
            }

            dsb_focus_hole_l->setValue(dsb_focus_coll_l->value());
            dsb_focus_hole_w->setValue(dsb_focus_coll_w->value());
        }
        else {
            dsb_focus_hole_l->setEnabled(true);
            dsb_focus_hole_w->setEnabled(true);

            connect(dsb_focus_hole_l, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
            disconnect(dsb_focus_coll_l, SIGNAL(valueChanged(double)), dsb_focus_hole_l, SLOT(setValue(double)));

            if (!cb_symmetric->isChecked()) {
                connect(dsb_focus_hole_w, SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
            }
            disconnect(dsb_focus_coll_w, SIGNAL(valueChanged(double)), dsb_focus_hole_w, SLOT(setValue(double)));
        }
    }
    parameterUpdated();
    emit updateParameters();
}
