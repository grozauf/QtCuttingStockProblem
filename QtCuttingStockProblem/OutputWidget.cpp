#include "OutputWidget.h"

#include <QPainter>
#include <QLabel>

OutputWidget::OutputWidget(QWidget *parent)
	: QWidget(parent)
{ }

void OutputWidget::paintEvent(QPaintEvent* e) {

	Q_UNUSED(e);

	setGeometry(((QWidget*)parent())->geometry());

	if (m_stockWidth == 0 || m_stockHeight == 0 || m_items.size() == 0) {
		return;
	}


	QPainter painter(this);
	painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));

	int margin = 20;

	int heightTotal = ((QWidget*)parent())->height() - 2 * margin;
	int widthTotal = ((QWidget*)parent())->width() - 2 * margin;

	double heightScale = ((double)m_stockHeight) / heightTotal;
	double widthScale = ((double)m_stockWidth) / widthTotal;


	double maxScale = (heightScale > widthScale) ? heightScale : widthScale;

	painter.setBrush(Qt::HorPattern);
	painter.drawRect(margin, margin, m_stockWidth / maxScale, m_stockHeight / maxScale);

	for (int i = 0; i < m_items.size(); ++i) {
		if (m_items[i].packed) {
			painter.setBrush(Qt::BDiagPattern);
			painter.drawRect(
				margin + m_items[i].x / maxScale,
				margin + m_items[i].y / maxScale,
				m_items[i].width / maxScale, m_items[i].height / maxScale);
		}
	}
}

void OutputWidget::setStockGeometry(int width, int height) {
	m_stockWidth = width;
	m_stockHeight = height;
}

void OutputWidget::setItems(std::vector<Rect> &items) {
	m_items = items;
}