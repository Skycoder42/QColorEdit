#ifndef QCOLOREDIT_H
#define QCOLOREDIT_H

#include <QColorDialog>
class ColorButton;
class QLineEdit;
class QRegularExpressionValidator;
class QSettings;

class QColorEdit : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(bool useAlphaChannel READ useAlphaChannel WRITE setUseAlphaChannel NOTIFY useAlphaChannelChanged)

public:
	static void saveCustomColors(QSettings *settings);
	static void restoreCustomColors(QSettings *settings);

	explicit QColorEdit(QWidget *parent = Q_NULLPTR);
	explicit QColorEdit(const QColor &color, QWidget *parent = Q_NULLPTR);
	virtual ~QColorEdit();

	QColor color() const;

	bool useAlphaChannel() const;

public slots:
	void setColor(const QColor &color);
	void setUseAlphaChannel(bool useAlphaChannel);

signals:
	void colorChanged(const QColor &color);
	void useAlphaChannelChanged(bool useAlphaChannel);

private slots:
	void buttonClicked();
	void textChanged();

private:
	static const QString colorRegexBase;

	ColorButton *button;
	QLineEdit *edit;
	QRegularExpressionValidator *validator;
	QColorDialog *colorDialog;

	QColor currentColor;
	bool useAlpha;
};

#endif // QCOLOREDIT_H
