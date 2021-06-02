#pragma once

#include <QWidget>

class OutputWidget : public QWidget {

public:
	OutputWidget(QWidget *parent = 0);

	void setStockGeometry(int width, int height);

protected:
	void paintEvent(QPaintEvent *e);
private:
	void doPainting();
private:
	int m_stockWidth = 0;
	int m_stockHeight = 0;
};