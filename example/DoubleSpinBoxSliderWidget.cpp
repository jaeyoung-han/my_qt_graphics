#include "DoubleSpinBoxSliderWidget.h"

#include <QLabel>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QLayout>

using namespace LCR;

DoubleSpinBoxSliderWidget::DoubleSpinBoxSliderWidget(const QString& label, int slider_range, double min, double max) 
{
	initialize();

	_label->setText(label);
	_slider->setRange(0, slider_range);
	_spinBox->setRange(min, max);
}

void DoubleSpinBoxSliderWidget::setSliderRange(int min, int max) 
{
	_slider->setRange(min, max);
	changeSlider(_spinBox->value());
}

void DoubleSpinBoxSliderWidget::setRange(double min, double max) 
{
	_spinBox->setRange(min, max);
	changeSlider(_spinBox->value());
}

void DoubleSpinBoxSliderWidget::setValue(double value) 
{
	_spinBox->setValue(value);
	_slider->setValue(convertSpinBoxValueToSlider(value));
}

void DoubleSpinBoxSliderWidget::setText(const QString& text) 
{
	_label->setText(text);
}

double DoubleSpinBoxSliderWidget::value() const
{
	return _spinBox->value();
}


void DoubleSpinBoxSliderWidget::changeSpinBox(int sliderValue) 
{
	if (convertSpinBoxValueToSlider(_spinBox->value()) != sliderValue) {
		_spinBox->setValue(convertSliderValueToSpinBox(sliderValue));
		emit valueChanged(_spinBox->value());
	}
}

void DoubleSpinBoxSliderWidget::changeSlider(double spinBoxValue) 
{
	_slider->setValue(convertSpinBoxValueToSlider(spinBoxValue));
}

double DoubleSpinBoxSliderWidget::convertSliderValueToSpinBox(int value) 
{
	return (_spinBox->maximum() - _spinBox->minimum()) / (_slider->maximum() - _slider->minimum()) * (value - _slider->minimum()) + _spinBox->minimum();
}

int DoubleSpinBoxSliderWidget::convertSpinBoxValueToSlider(double value) 
{
	return qRound(
		(_slider->maximum() - _slider->minimum()) / (_spinBox->maximum() - _spinBox->minimum()) * (value - _spinBox->minimum()) + _slider->minimum()
	);
}

void DoubleSpinBoxSliderWidget::initialize() 
{
	_label = new QLabel(this);
	_slider = new QSlider(Qt::Horizontal, this);
	_spinBox = new QDoubleSpinBox(this);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(_label);
	layout->addWidget(_slider);
	layout->addWidget(_spinBox);

	setLayout(layout);

	connect(_slider, SIGNAL(valueChanged(int)), SLOT(changeSpinBox(int)));
	connect(_spinBox, SIGNAL(valueChanged(double)), SLOT(changeSlider(double)));
	connect(_spinBox, SIGNAL(valueChanged(double)), SIGNAL(valueChanged(double)));
}
