#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QFrame>

class ColorButton : public QFrame
{
	Q_OBJECT

public:
	ColorButton(QWidget *parent = Q_NULLPTR);

	QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
	void setColor(const QColor &color);

signals:
	void clicked();

protected:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // COLORBUTTON_H
