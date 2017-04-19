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
	DockCollimator(const QString& title, const LCR::CollimatorEx& data, QWidget* parent = Q_NULLPTR, Qt::WindowFlags flags = 0);

	void initialize();
	void update(const LCR::CollimatorEx& data);
	const LCR::CollimatorEx& getData() const;

signals:
	void updateSize();
	void updateParameters();
	void updateSection();

private slots:
	void parameterUpdated();
	void sectionUpdated();

private:
	QDoubleSpinBox* dsb_length;
	QDoubleSpinBox* dsb_width;
	QDoubleSpinBox* dsb_height;
	QDoubleSpinBox* dsb_focus;

	LCR::DoubleSpinBoxSliderWidget* dsb_diameter[2];
	LCR::DoubleSpinBoxSliderWidget* dsb_septa1;
	QLabel* dsb_septa2;

	LCR::DoubleSpinBoxSliderWidget* dsb_section_height;
	QLabel* lb_sec_diameter;
	QLabel* lb_sec_thickness;

	QLabel* lb_x_side_open_area;
	QLabel* lb_x_side_hole_num;

	QLabel* lb_umbra;
	QLabel* lb_mid_penumbra;
	QLabel* lb_penumbra;

	LCR::CollimatorEx data;
};

#endif // __LCR_DOCK_COLLIMATOR_H__
