#ifndef __DOUBLE_SPINBOX_SLIDER_WIDGET_H__
#define __DOUBLE_SPINBOX_SLIDER_WIDGET_H__

#include <QWidget>

class QLabel;
class QSlider;
class QDoubleSpinBox;

namespace LCR {

	class DoubleSpinBoxSliderWidget : public QWidget
	{
		Q_OBJECT
	public:
		DoubleSpinBoxSliderWidget(const QString& label, int slider_range, double min, double max);

		void setItemMinimumWidth(int label, int slider, int spinbox);
		void setSliderRange(int min, int max);
		void setRange(double min, double max);
		void setDecimals(int prec);
		void setSingleStep(double val);
		void setText(const QString& text);
        void setPrefix(const QString& prefix);
		double value() const;

    public slots:
        void setValue(double value);

	signals:
		void valueChanged(double value);

	private slots:
		void changeSpinBox(int sliderValue);
		void changeSlider(double spinBoxValue);

	private:
		double convertSliderValueToSpinBox(int value);
		int convertSpinBoxValueToSlider(double value);

		void initialize();

		QLabel* _label;
		QSlider* _slider;
		QDoubleSpinBox* _spinBox;
	};

};

#endif // __DOUBLE_SPINBOX_SLIDER_WIDGET_H__
