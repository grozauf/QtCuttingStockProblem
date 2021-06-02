#include <QPainter>
#include "QtCuttingStockProblem.h"
#include "OutputWidget.h"

QtCuttingStockProblem::QtCuttingStockProblem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	m_widgetOutput = new OutputWidget(ui.centralWidget);
	m_widgetOutput->setObjectName(QStringLiteral("widgetOutput"));
	m_widgetOutput->raise();
	m_widgetOutput->hide();

	connect(ui.actionOutput, SIGNAL(triggered()), this, SLOT(cutAndShow()));
	connect(ui.actionInput, SIGNAL(triggered()), m_widgetOutput, SLOT(hide()));
}


void QtCuttingStockProblem::cutAndShow() {
	m_widgetOutput->setStockGeometry(ui.lineEditStockWidth->text().toInt(), ui.lineEditStockHeight->text().toInt());
	m_widgetOutput->show();
	ui.widgetInputs->hide();
}