#include <QtWidgets>
#include "DockCollimator.h"

using namespace LCR;


DockCollimator::DockCollimator(const QString& title, QWidget* parent, Qt::WindowFlags flags)
  : QDockWidget(title, parent, flags)
{
  initialize();

  //data.size.x = 30;
  //data.size.y = 30;
  //data.size.z = 100;

  //data.focus_distance = 500;
  //direction = Converging;

  //data.diameter[0] = 2.0;
  //data.diameter[1] = 2.5;
  //data.septa[0] = 0.2;
  //data.septa[1] = 0.25;
  //data.section_height = 50;
  //data.focus_width = 0;

  //update(data);

  //updateUi();
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

  QGridLayout* grid_dim = new QGridLayout();
  grid_dim->addWidget(newLabel(tr("Length (mm): ")), 0, 0);
  grid_dim->addWidget(newLabel(tr("Width (mm): ")), 1, 0);
  grid_dim->addWidget(newLabel(tr("Height (mm): ")), 2, 0);
  grid_dim->addWidget(dsb_length, 0, 1);
  grid_dim->addWidget(dsb_width, 1, 1);
  grid_dim->addWidget(dsb_height, 2, 1);

  QGroupBox* gb_coll = new QGroupBox(tr("FOV"));
  gb_coll->setLayout(grid_dim);

  // Direction
  rb_direction[0] = new QRadioButton(tr("Convergent"));
  rb_direction[1] = new QRadioButton(tr("Divergent"));
  rb_direction[0]->setChecked(true);

  dsb_focus = new QDoubleSpinBox(this);
  dsb_focus->setRange(200, 100000);
  dsb_focus->setDecimals(0);
  dsb_focus->setSingleStep(10);

  QGridLayout* grid_focus = new QGridLayout();
  grid_focus->addWidget(newLabel(tr("Focus Distance (mm): ")), 0, 0);
  grid_focus->addWidget(dsb_focus, 0, 1);

  QVBoxLayout* vb_dir = new QVBoxLayout;
  vb_dir->addLayout(grid_focus);
  vb_dir->addWidget(rb_direction[0]);
  vb_dir->addWidget(rb_direction[1]);

  QGroupBox* gb_dir = new QGroupBox(tr("Direction"));
  gb_dir->setLayout(vb_dir);


  // Diameter, septa at Exit (Patient side)
  dsb_diameter[0] = new QDoubleSpinBox(this);
  dsb_diameter[0]->setRange(0, 100);
  dsb_diameter[0]->setDecimals(2);
  dsb_diameter[0]->setSingleStep(0.1);

  dsb_septa[0] = new QDoubleSpinBox(this);
  dsb_septa[0]->setRange(0, 100);
  dsb_septa[0]->setDecimals(2);
  dsb_septa[0]->setSingleStep(0.01);

  lb_p_side_open_area = new QLabel(this);
  lb_p_side_hole_num = new QLabel(this);

  QGridLayout* grid_ex = new QGridLayout();
  grid_ex->addWidget(newLabel(tr("Diameter (mm): ")), 0, 0);
  grid_ex->addWidget(newLabel(tr("Septa (mm): ")), 1, 0);
  grid_ex->addWidget(newLabel(tr("Open Area Ratio: ")), 2, 0);
  grid_ex->addWidget(newLabel(tr("Hole #: ")), 3, 0);
  grid_ex->addWidget(dsb_diameter[0], 0, 1);
  grid_ex->addWidget(dsb_septa[0], 1, 1);
  grid_ex->addWidget(lb_p_side_open_area, 2, 1);
  grid_ex->addWidget(lb_p_side_hole_num, 3, 1);

  QGroupBox* gb_ex = new QGroupBox(tr("Patient side"));
  gb_ex->setLayout(grid_ex);


  // Diameter, septa at entrance (X-ray side)
  dsb_diameter[1] = new QDoubleSpinBox(this);
  dsb_diameter[1]->setRange(0, 100);
  dsb_diameter[1]->setDecimals(2);
  dsb_diameter[1]->setSingleStep(0.1);

  dsb_septa[1] = new QDoubleSpinBox(this);
  dsb_septa[1]->setRange(0, 100);
  dsb_septa[1]->setDecimals(2);
  dsb_septa[1]->setSingleStep(0.01);

  lb_x_side_open_area = new QLabel(this);
  lb_x_side_hole_num = new QLabel(this);

  QGridLayout* grid_en = new QGridLayout();
  grid_en->addWidget(newLabel(tr("Diameter (mm): ")), 0, 0);
  grid_en->addWidget(newLabel(tr("Septa (mm): ")), 1, 0);
  grid_en->addWidget(newLabel(tr("Open Area Ratio: ")), 2, 0);
  grid_en->addWidget(newLabel(tr("Hole #: ")), 3, 0);
  grid_en->addWidget(dsb_diameter[1], 0, 1);
  grid_en->addWidget(dsb_septa[1], 1, 1);
  grid_en->addWidget(lb_x_side_open_area, 2, 1);
  grid_en->addWidget(lb_x_side_hole_num, 3, 1);

  QGroupBox* gb_en = new QGroupBox(tr("X-ray side"));
  gb_en->setLayout(grid_en);


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


  test = new DoubleSpinBoxSliderWidget("TEST: ", 1000, 0.4, 10);


  QScrollArea* sc = new QScrollArea();
  QVBoxLayout* vbLayout = new QVBoxLayout(sc);

  vbLayout->setSizeConstraint(QLayout::SetMinimumSize);
  vbLayout->addWidget(gb_coll);
  vbLayout->addWidget(gb_dir);
  vbLayout->addWidget(gb_ex);
  vbLayout->addWidget(gb_en);
  vbLayout->addLayout(grid_sec);
  vbLayout->addWidget(test);
  vbLayout->addStretch();

  connect(dsb_length, SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));
  connect(dsb_width,  SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));
  connect(dsb_height, SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));

  connect(dsb_focus, SIGNAL(valueChanged(double)), this, SLOT(sizeUpdated()));

  connect(rb_direction[0], SIGNAL(clicked(bool)), this, SLOT(convergentClicked(bool)));
  connect(rb_direction[1], SIGNAL(clicked(bool)), this, SLOT(divergentClicked(bool)));

  connect(dsb_diameter[0], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
  connect(dsb_septa[0],    SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));

  connect(dsb_diameter[1], SIGNAL(valueChanged(double)), this, SLOT(parameterUpdated()));
//  connect(dsb_septa[1],    SIGNAL(editingFinished()), this, SLOT(parameterUpdated()));

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
  rb_direction[0]->setChecked(data.direction == Converging);
  rb_direction[1]->setChecked(data.direction == Diverging);

  dsb_diameter[0]->setValue(data.diameter[0]);
  dsb_diameter[1]->setValue(data.diameter[1]);
  dsb_septa[0]->setValue(data.septa[0]);
  dsb_septa[1]->setValue(data.septa[1]);

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

void DockCollimator::updateUi()
{
  if (data.direction == Converging) {
    dsb_diameter[1]->setReadOnly(true);
    dsb_septa[1]->setReadOnly(true);
  }
  else {
    dsb_diameter[1]->setReadOnly(false);
    dsb_septa[1]->setReadOnly(true);
  }
}

void DockCollimator::convergentClicked(bool checked)
{
  if (checked) {
    data.direction = Converging;
    updateUi();
    emit updateParameters();
  }
}

void DockCollimator::divergentClicked(bool checked)
{
  if (checked) {
    data.direction = Diverging;
    updateUi();
    emit updateParameters();
  }
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
  data.septa[0] = dsb_septa[0]->value();

  if (data.direction == Diverging)
    data.diameter[1] = dsb_diameter[1]->value();


  emit updateParameters();
}

void DockCollimator::sectionUpdated()
{
  data.section_height = dsb_section_height->value();

  emit updateSection();
}
