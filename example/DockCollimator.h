#ifndef __LCR_DOCK_COLLIMATOR_H__
#define __LCR_DOCK_COLLIMATOR_H__

#include <QDockWidget>
#include "data_types.h"
#include "DoubleSpinBoxSliderWidget.h"
#include "UmbraWidget.h"

class QCheckBox;
class QDoubleSpinBox;
class QGroupBox;
class QLabel;
class QRadioButton;

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

protected:
	void resizeEvent(QResizeEvent* event);

private slots:
	void parameterUpdated();
	void sectionUpdated();
    void updateUI();

private:
    QRadioButton* rb_shape_hexagon;
    QRadioButton* rb_shape_square;
    QRadioButton* rb_shape_square_thickness;

    QRadioButton* rb_horizontal;
	QRadioButton* rb_vertical;
    QGroupBox* gb_dir;

    QGroupBox* gb_bottom_plane_;
	LCR::DoubleSpinBoxSliderWidget* dsb_length;
	LCR::DoubleSpinBoxSliderWidget* dsb_width;
	LCR::DoubleSpinBoxSliderWidget* dsb_height;

    QCheckBox* cb_symmetric;
    QCheckBox* cb_iso_focus;

	LCR::DoubleSpinBoxSliderWidget* dsb_focus_coll_l;
    LCR::DoubleSpinBoxSliderWidget* dsb_focus_coll_w;
    LCR::DoubleSpinBoxSliderWidget* dsb_focus_hole_l;
    LCR::DoubleSpinBoxSliderWidget* dsb_focus_hole_w;

	LCR::DoubleSpinBoxSliderWidget* dsb_diameter_l;
    LCR::DoubleSpinBoxSliderWidget* dsb_diameter_w;
    LCR::DoubleSpinBoxSliderWidget* dsb_septa_l;
    LCR::DoubleSpinBoxSliderWidget* dsb_septa_w;
    QGroupBox* gb_transverse;

    QLabel* lb_en_diameter_long;
    QLabel* lb_en_diameter_tran;
    QLabel* lb_en_septa_long;
    QLabel* lb_en_septa_tran;

	QCheckBox* cb_conv_div_mix;

	LCR::DoubleSpinBoxSliderWidget* dsb_section_height;
	QLabel* lb_sec_diameter_long;
    QLabel* lb_sec_diameter_tran;
    QLabel* lb_sec_septa_long;
    QLabel* lb_sec_septa_tran;

    LCR::DoubleSpinBoxSliderWidget* dsb_anode_depth;
    QLabel* lb_anode_diameter_long;
    QLabel* lb_anode_diameter_tran;

	QLabel* lb_x_side_open_area;
	QLabel* lb_x_side_hole_num;
    QGroupBox* gb_info_;

	QLabel* lb_umbra;
	QLabel* lb_mid_penumbra;
	QLabel* lb_penumbra;

	LCR::UmbraWidget* umbra_widget;

    QGroupBox* gb_umbra_;

	LCR::CollimatorEx data;
};

#endif // __LCR_DOCK_COLLIMATOR_H__
