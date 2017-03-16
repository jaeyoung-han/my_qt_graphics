#ifndef __LCR_DOCK_COLLIMATOR_H__
#define __LCR_DOCK_COLLIMATOR_H__

#include <QDockWidget>
#include "data_types.h"

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

protected:
  void updateUi();

private slots:
  void sizeUpdated();
  void parameterUpdated();
  void sectionUpdated();
  void convergentClicked(bool);
  void divergentClicked(bool);

signals:
  void updateSize();
  void updateParameters();
  void updateSection();

private:
  QDoubleSpinBox* dsb_length;
  QDoubleSpinBox* dsb_width;
  QDoubleSpinBox* dsb_height;

  QDoubleSpinBox* dsb_focus;
  QRadioButton* rb_direction[2];

  QDoubleSpinBox* dsb_diameter[2];
  QDoubleSpinBox* dsb_septa[2];

  QDoubleSpinBox* dsb_section_height;

  QLabel* lb_focus_width;

  int direction;

  LCR::Collimator data;
};

#endif // __LCR_DOCK_COLLIMATOR_H__
