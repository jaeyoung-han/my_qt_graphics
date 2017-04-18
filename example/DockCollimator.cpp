#include <QtWidgets>
#include "DockCollimator.h"

using namespace LCR;


DockCollimator::DockCollimator(const QString& title, QWidget* parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
  initialize();
}

QLabel* newLabel(const QString& text, QWidget* parent = 0)
{
  QLabel* _nlbl = new QLabel(text, parent);
  _nlbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
  _nlbl->setWordWrap(false);
  return _nlbl;
}

void DockCollimator::initialize()
{
  // Overall size (L, W, H)
  dsb_length = new QDoubleSpinBox(this);
  dsb_length->setRange(10, 1000);
  dsb_length->setDecimals(0);
  dsb_length->setSingleStep(1);

  dsb_width = new QDoubleSpinBox(this);
  dsb_width->setRange(10, 100);
  dsb_width->setDecimals(0);
  dsb_width->setSingleStep(1);

  dsb_height = new QDoubleSpinBox(this);
  dsb_height->setRange(0, 150);
  dsb_height->setDecimals(0);
  dsb_height->setSingleStep(1);

  dsb_focus = new QDoubleSpinBox(this);
  dsb_focus->setRange(200, 100000);
  dsb_focus->setDecimals(0);
  dsb_focus->setSingleStep(10);

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

  // Diameter, septa at Exit (Patient side)
  dsb_diameter[0] = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.5, 10);
  dsb_diameter[1] = new DoubleSpinBoxSliderWidget(tr("Diameter (mm): "), 100, 0.5, 10);
  dsb_septa1 = new DoubleSpinBoxSliderWidget(tr("Thickness (mm):"), 100, 0.1, 10);

  lb_p_side_open_area = new QLabel(this);
  lb_p_side_hole_num = new QLabel(this);

  QGridLayout* grid_ex = new QGridLayout();
  grid_ex->addWidget(newLabel(tr("Open Area Ratio: ")), 2, 0);
  grid_ex->addWidget(newLabel(tr("Hole #: ")), 3, 0);
  grid_ex->addWidget(lb_p_side_open_area, 2, 1);
  grid_ex->addWidget(lb_p_side_hole_num, 3, 1);

  QVBoxLayout* vblayout2 = new QVBoxLayout();
  vblayout2->addWidget(dsb_diameter[0]);
  vblayout2->addWidget(dsb_septa1);
  vblayout2->addLayout(grid_ex);

  QGroupBox* gb_ex = new QGroupBox(tr("Patient side"));
  gb_ex->setLayout(vblayout2);


  // Diameter, septa at entrance (X-ray side)

  dsb_septa2 = new QDoubleSpinBox(this);
  dsb_septa2->setRange(0, 100);
  dsb_septa2->setDecimals(2);
  dsb_septa2->setSingleStep(0.01);

  lb_x_side_open_area = new QLabel(this);
  lb_x_side_hole_num = new QLabel(this);

  QGridLayout* grid_en = new QGridLayout();
  grid_en->addWidget(newLabel(tr("Septa (mm): ")), 1, 0);
  grid_en->addWidget(newLabel(tr("Open Area Ratio: ")), 2, 0);
  grid_en->addWidget(newLabel(tr("Hole #: ")), 3, 0);
  // grid_en->addWidget(dsb_diameter[1], 0, 1);
  grid_en->addWidget(dsb_septa2, 1, 1);
  grid_en->addWidget(lb_x_side_open_area, 2, 1);
  grid_en->addWidget(lb_x_side_hole_num, 3, 1);

  QVBoxLayout* vblayout3 = new QVBoxLayout();
  vblayout3->addWidget(dsb_diameter[1]);
  vblayout3->addLayout(grid_en);

  QGroupBox* gb_en = new QGroupBox(tr("X-ray side"));
  gb_en->setLayout(vblayout3);


  // Section Height
  dsb_section_height = new QDoubleSpinBox(this);
  dsb_section_height->setRange(0, 100);
  dsb_section_height->setDecimals(0);
  dsb_section_height->setSingleStep(1.0);

  lb_focus_width = new QLabel(this);

  QGridLayout* grid_sec = new QGridLayout();
  grid_sec->addWidget(newLabel(tr("Section Height (mm): ")), 0, 0);
  grid_sec->addWidget(dsb_section_height, 0, 1);
  grid_sec->addWidget(newLabel(tr("Width at Focus (mm): ")), 1, 0);
  grid_sec->addWidget(lb_focus_width, 1, 1);


  QScrollArea* sc = new QScrollArea();
  QVBoxLayout* vbLayout = new QVBoxLayout(sc);

  vbLayout->setSizeConstraint(QLayout::SetMinimumSize);
  vbLayout->addWidget(gb_coll);
  vbLayout->addWidget(gb_ex);
  vbLayout->addWidget(gb_en);
  vbLayout->addLayout(grid_sec);
  vbLayout->addStretch();

  connect(dsb_length, SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));
  connect(dsb_width,  SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));
  connect(dsb_height, SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));

  connect(dsb_focus, SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));

  connect(dsb_diameter[0], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
  connect(dsb_septa1,    SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

  connect(dsb_diameter[1], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

  connect(dsb_section_height, SIGNAL(valueChanged(double)), this, SLOT(sectionUpdated()));

  setWidget(sc);
}

void DockCollimator::update(const Collimator& new_data)
{
  this->data = new_data;
  dsb_length->setValue(data.size.x);
  dsb_width->setValue(data.size.y);
  dsb_height->setValue(data.size.z);
  dsb_focus->setValue(data.focus_distance);

  dsb_diameter[0]->setRange(0.5, qMin(data.size.x, data.size.y));
  dsb_diameter[1]->setRange(0.5, qMin(data.size.x, data.size.y));
  dsb_diameter[0]->setValue(data.diameter[0]);
  dsb_diameter[1]->setValue(data.diameter[1]);
  dsb_septa1->setValue(data.septa[0]);
  dsb_septa2->setValue(data.septa[1]);

  double oar = 1 / (data.septa[0] / data.diameter[0] + 1);
  lb_p_side_open_area->setText(QString::number(oar*oar));
  oar = 1 / (data.septa[1] / data.diameter[1] + 1);
  lb_x_side_open_area->setText(QString::number(oar*oar));

  //if (data.diameter[0] * data.diameter[1] * data.septa[0] * data.septa[1])
  {
	  oar = 2 * 100 / (sqrt(3) * (data.diameter[0] + data.septa[0]) * (data.diameter[0] + data.septa[0]));
	  lb_p_side_hole_num->setText(QString::number(oar));
	  oar = 2 * 100 / (sqrt(3) * (data.diameter[1] + data.septa[1]) * (data.diameter[1] + data.septa[1]));
	  lb_x_side_hole_num->setText(QString::number(oar));
  }

  lb_focus_width->setText(QString::number(data.focus_width));
}

const Collimator& DockCollimator::getData() const
{
  return data;
}

void DockCollimator::sizeUpdated()
{
  data.size.x = dsb_length->value();
  data.size.y = dsb_width->value();
  data.size.z = dsb_height->value();
  data.focus_distance = dsb_focus->value();

  dsb_section_height->setRange(0, data.size.z);

  emit updateSize();
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
