#include <QPainter>
#include <QFileDialog>
#include <QTextStream>


#include "QtCuttingStockProblem.h"
#include "OutputWidget.h"
#include "CuttingStockAlgorithm.h"

QtCuttingStockProblem::QtCuttingStockProblem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	m_labelRestSpace = new QLabel(ui.centralWidget);
	m_labelRestSpace->setGeometry(0, 0, 300, 20);

	m_widgetOutput = new OutputWidget(ui.centralWidget);
	m_widgetOutput->setObjectName(QStringLiteral("widgetOutput"));
	m_widgetOutput->raise();
	m_widgetOutput->hide();

	connect(ui.actionOutput, SIGNAL(triggered()), this, SLOT(cutAndShow()));
	connect(ui.actionOutput, SIGNAL(triggered()), m_labelRestSpace, SLOT(show()));
	connect(ui.actionInput, SIGNAL(triggered()), m_widgetOutput, SLOT(hide()));
	connect(ui.actionInput, SIGNAL(triggered()), m_labelRestSpace, SLOT(hide()));
	connect(ui.pushButtonLoadFile, SIGNAL(pressed()), this, SLOT(openFile()));
}


void QtCuttingStockProblem::cutAndShow() {
	int stockWidth = ui.lineEditStockWidth->text().toInt();
	int stockHeight = ui.lineEditStockHeight->text().toInt();

	if (stockHeight > stockWidth) {
		std::swap(stockHeight, stockWidth);
	}

	readFile();

	SortType sort = SortType::BYHEIGHT;
	if (ui.radioButtonByHeight->isChecked()) {
		sort = SortType::BYHEIGHT;
	}
	else if (ui.radioButtonByWidth->isChecked()) {
		sort = SortType::BYWIDTH;
	}
	else if (ui.radioButtonBySpace->isChecked()) {
		sort = SortType::BYSPACE;
	}
	SortOrder order = SortOrder::TOLOWER;
	if (ui.radioButtonToLower->isChecked()) {
		order = SortOrder::TOLOWER;
	}
	else {
		order = SortOrder::TOGREATER;
	}

	CuttingStockAlgorithm cuttingAlgorithm;
	cuttingAlgorithm.Init(stockWidth, stockHeight, m_itemVec, sort, order);

	m_itemVec = cuttingAlgorithm.CutStock();

	m_widgetOutput->setStockGeometry(stockWidth, stockHeight);
	m_widgetOutput->setItems(m_itemVec);
	m_widgetOutput->show();
	ui.widgetInputs->hide();

	int packedSpace = 0;
	for (auto &rec : m_itemVec) {
		if (rec.packed) {
			packedSpace += rec.height * rec.width;
		}
	}
	int restSpace = stockHeight * stockWidth - packedSpace;
	m_labelRestSpace->setText(QString::fromLocal8Bit("Площадь оставшегося материала: %1").arg(restSpace));
}

void QtCuttingStockProblem::openFile() {
	m_itemsFileName = QFileDialog::getOpenFileName(
		this, tr("Open file"), "", tr("Text (*.txt)"));

	ui.lineEditFileName->setText(m_itemsFileName);
}

void QtCuttingStockProblem::readFile() {
	m_itemVec.clear();

	QFile file(m_itemsFileName);
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		Rect item;
		in >> item.width >> item.height;
		if (item.width == 0 || item.height == 0) {
			continue;
		}

		if (item.height > item.width) {
			std::swap(item.width, item.height);
		}

		m_itemVec.push_back(item);
	}

}