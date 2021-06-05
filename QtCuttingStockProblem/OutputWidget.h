#pragma once

#include <QWidget>

#include "CuttingStockAlgorithm.h"

class OutputWidget : public QWidget {

public:
	OutputWidget(QWidget *parent = 0);

	void setStockGeometry(int width, int height);
	void setItems(std::vector<Rect> &items);

protected:
	void paintEvent(QPaintEvent *e);
private:
	int m_stockWidth = 0;
	int m_stockHeight = 0;
	std::vector<Rect> m_items;
};