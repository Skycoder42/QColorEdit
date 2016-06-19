#include "qcoloredit.h"
#include "colorbutton.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QRegularExpressionValidator>
#include <QSettings>

const QString QColorEdit::colorRegexBase(QStringLiteral(R"__(^#([0-9a-fA-F]{%1}(?:[0-9a-fA-F]{%1})?)$)__"));

void QColorEdit::saveCustomColors(QSettings *settings)
{
	int max = QColorDialog::customCount();
	settings->remove(QStringLiteral("customColors"));
	settings->beginWriteArray(QStringLiteral("customColors"), max);
	for(int i = 0; i < max; ++i) {
		settings->setArrayIndex(i);
		settings->setValue(QStringLiteral("color"), QColorDialog::customColor(i));
	}
	settings->endArray();
}

void QColorEdit::restoreCustomColors(QSettings *settings)
{
	for(int i = 0, max = settings->beginReadArray(QStringLiteral("customColors")); i < max; ++i) {
		settings->setArrayIndex(i);
		QColorDialog::setCustomColor(i, settings->value(QStringLiteral("color")).value<QColor>());
	}
	settings->endArray();
}

QColorEdit::QColorEdit(QWidget *parent) :
	QColorEdit(QColor(), parent)
{}

QColorEdit::QColorEdit(const QColor &color, QWidget *parent) :
	QWidget(parent),
	button(new ColorButton(this)),
	edit(new QLineEdit(this)),
	validator(new QRegularExpressionValidator(this)),
	colorDialog(new QColorDialog(color, this)),
	currentColor(color),
	useAlpha(false)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(this->button);
	layout->addWidget(this->edit);
	this->setLayout(layout);

	this->button->setColor(color);
	connect(this->button, &ColorButton::clicked,
			this, &QColorEdit::buttonClicked);

	this->validator->setRegularExpression(QRegularExpression(colorRegexBase.arg(3)));
	this->edit->setValidator(this->validator);
	connect(this->edit, &QLineEdit::editingFinished,
			this, &QColorEdit::textChanged);

	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
}

QColorEdit::~QColorEdit() {}

QColor QColorEdit::color() const
{
	return this->currentColor;
}

bool QColorEdit::useAlphaChannel() const
{
	return this->useAlpha;
}

void QColorEdit::setColor(const QColor &color)
{
	if(this->currentColor != color) {
		this->currentColor = color;
		this->edit->setText(color.name().toUpper());
		this->button->setColor(color);
		emit colorChanged(color);
	}
}

void QColorEdit::setUseAlphaChannel(bool useAlphaChannel)
{
	if (this->useAlpha == useAlphaChannel)
		return;

	this->useAlpha = useAlphaChannel;
	this->colorDialog->setOption(QColorDialog::ShowAlphaChannel, useAlphaChannel);
	this->validator->setRegularExpression(QRegularExpression(colorRegexBase.arg(useAlphaChannel ? 4 : 3)));
	emit useAlphaChannelChanged(useAlphaChannel);
}

void QColorEdit::buttonClicked()
{
	this->colorDialog->setCurrentColor(this->color());
	if(this->colorDialog->exec())
		this->setColor(this->colorDialog->currentColor());
}

void QColorEdit::textChanged()
{
	QColor c = QColor(this->edit->text());
	if(c.isValid())
		this->setColor(c);
}
