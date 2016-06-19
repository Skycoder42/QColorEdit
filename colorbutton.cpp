#include "colorbutton.h"
#include <QMouseEvent>

ColorButton::ColorButton(QWidget *parent) :
	QFrame(parent)
{
	this->setFrameShape(QFrame::Panel);
	this->setFrameShadow(QFrame::Raised);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	this->setLineWidth(1);
	this->setAutoFillBackground(true);
}

QSize ColorButton::sizeHint() const
{
	return QSize(50, 20);
}

void ColorButton::setColor(const QColor &color)
{
	QPalette pal = this->palette();
	pal.setColor(QPalette::Window, color);
	this->setPalette(pal);
}

void ColorButton::mousePressEvent(QMouseEvent *event)
{
	this->setFrameShadow(QFrame::Sunken);
	QFrame::mousePressEvent(event);
}

void ColorButton::mouseReleaseEvent(QMouseEvent *event)
{
	this->setFrameShadow(QFrame::Raised);
	QFrame::mouseReleaseEvent(event);

	if(QRect(QPoint(0, 0), this->size()).contains(event->pos()))
		emit clicked();
}
