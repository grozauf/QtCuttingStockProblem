#include "OutputWidget.h"

#include <QPainter>

OutputWidget::OutputWidget(QWidget *parent)
	: QWidget(parent)
{ }

void OutputWidget::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	doPainting();
}

void OutputWidget::doPainting() {
	setGeometry(((QWidget *)parent())->geometry());

	QPainter painter(this);
	painter.setPen(Qt::NoPen);

	int heightTotal = ((QWidget *)parent())->height();
	int widthTotal = ((QWidget *)parent())->width();

	int heightScale = m_stockHeight/heightTotal;
	int widthScale = m_stockWidth/widthTotal;

	int maxScale = (heightScale > widthScale) ? heightScale : widthScale;

	painter.setBrush(Qt::HorPattern);
	painter.drawRect(0, 0, m_stockWidth/maxScale, m_stockHeight/maxScale);
}

void OutputWidget::setStockGeometry(int width, int height) {
	m_stockWidth = width;
	m_stockHeight = height;
}