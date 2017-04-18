#ifndef __LCR_DOCK_COLLIMATOR_H__
#define __LCR_DOCK_COLLIMATOR_H__

#include <QDockWidget>
#include "data_types.h"
#include "DoubleSpinBoxSliderWidget.h"

class QDoubleSpinBox;
class QRadioButton;
class QLabel;

class DockCollimator : public QDockWidget
{
  Q_OBJECT
public:
  DockCollimator(const QString& title, QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);

  void initialize();
  void update(const LCR::Collimator& data);
  const LCR::Collimator& getData() const;

private slots:
  void sizeUpdated();
  void parameterUpdated();
  void sectionUpdated();

signals:
  void updateSize();
  void updateParameters();
  void updateSection();

private:
  QDoubleSpinBox* dsb_length;
  QDoubleSpinBox* dsb_width;
  QDoubleSpinBox* dsb_height;
  QDoubleSpinBox* dsb_focus;

  LCR::DoubleSpinBoxSliderWidget* dsb_diameter[2];
  LCR::DoubleSpinBoxSliderWidget* dsb_septa1;
  QDoubleSpinBox* dsb_septa2;

  QDoubleSpinBox* dsb_section_height;

  QLabel* lb_p_side_open_area;
  QLabel* lb_x_side_open_area;
  QLabel* lb_p_side_hole_num;
  QLabel* lb_x_side_hole_num;
  QLabel* lb_focus_width;

  LCR::Collimator data;
};

#endif // __LCR_DOCK_COLLIMATOR_H__
