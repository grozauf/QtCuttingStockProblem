#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCuttingStockProblem.h"

#include "OutputWidget.h"
#include "CuttingStockAlgorithm.h"

#include <vector>


class QtCuttingStockProblem : public QMainWindow
{
    Q_OBJECT

public:
    QtCuttingStockProblem(QWidget *parent = Q_NULLPTR);

	void readFile();

public Q_SLOTS:
	void cutAndShow();
    void openFile();

private:
	void saveResults(SortType sort, SortOrder order, int restSpace);

private:
    Ui::QtCuttingStockProblemClass ui;
	QLabel* m_labelRestSpace;
	QString m_itemsFileName;
	OutputWidget *m_widgetOutput;
	std::vector<Rect> m_itemVec;
};
