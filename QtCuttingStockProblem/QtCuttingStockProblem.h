#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCuttingStockProblem.h"

#include "OutputWidget.h"

class QtCuttingStockProblem : public QMainWindow
{
    Q_OBJECT

public:
    QtCuttingStockProblem(QWidget *parent = Q_NULLPTR);

public Q_SLOTS:
	void cutAndShow();

private:
    Ui::QtCuttingStockProblemClass ui;
	OutputWidget *m_widgetOutput;
};
