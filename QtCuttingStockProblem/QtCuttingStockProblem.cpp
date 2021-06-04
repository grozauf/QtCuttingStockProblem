#include <QPainter>
#include <QFileDialog>

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
	connect(ui.pushButtonLoadFile, SIGNAL(pressed()), this, SLOT(openFile()));
}


void QtCuttingStockProblem::cutAndShow() {
	m_widgetOutput->setStockGeometry(ui.lineEditStockWidth->text().toInt(), ui.lineEditStockHeight->text().toInt());
	m_widgetOutput->show();
	ui.widgetInputs->hide();
}

void QtCuttingStockProblem::openFile() {
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("Open file"), "", tr("Text (*.txt)"));

	ui.lineEditFileName->setText(fileName);

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
}