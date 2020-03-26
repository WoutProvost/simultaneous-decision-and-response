#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {

	// Configure initial UI according to the generated UI header file
	ui->setupUi(this);

	// Initialize plot
	initPlot();
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::initPlot() {
	// Window
	setWindowTitle("Collective decision history");
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	setMinimumSize(400, 300);
	setGeometry(screenGeometry.width() - width(), screenGeometry.height() - height(), 400, 300);

	// Title
	ui->customPlot->plotLayout()->insertRow(0);
	ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot, "Experiment " + QString::number(1) + " (100 bots)", QFont("sans", 12, QFont::Bold)));

	// Legend
	ui->customPlot->legend->setVisible(true);
	ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

	// Top and right borders
	ui->customPlot->xAxis2->setVisible(true);
	ui->customPlot->yAxis2->setVisible(true);
	ui->customPlot->xAxis2->setTicks(false);
	ui->customPlot->yAxis2->setTicks(false);

	// User interactions (drag X axis, zoom X axis)
	ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
	ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());

	// X axis
	ui->customPlot->xAxis->setLabel("Time");
	ui->customPlot->xAxis->setLabelFont(QFont("sans", 10, QFont::Bold));
	ui->customPlot->xAxis->setRange(0, 60);
	ui->customPlot->xAxis->setTickLengthIn(0);
	ui->customPlot->xAxis->setSubTickLength(0);
	QSharedPointer<QCPAxisTickerTime> xAxisTicker(new QCPAxisTickerTime);
	xAxisTicker->setTimeFormat("%m:%s");
	ui->customPlot->xAxis->setTicker(xAxisTicker);

	// Y axis
	ui->customPlot->yAxis->setLabel("Percentage");
	ui->customPlot->yAxis->setLabelFont(QFont("sans", 10, QFont::Bold));
	ui->customPlot->yAxis->setRange(0, 100);
	ui->customPlot->yAxis->setTickLengthIn(0);
	ui->customPlot->yAxis->setSubTickLength(0);
	QSharedPointer<QCPAxisTickerText> yAxisTicker(new QCPAxisTickerText);
	for(int position = 0; position <= 100; position += 20) {
		yAxisTicker->addTick(position, QString::number(position) + " %");
	}
	ui->customPlot->yAxis->setTicker(yAxisTicker);

	// Graphs
	for(int graph = 0, size = 2; graph < size; graph++) {
		ui->customPlot->addGraph();
		ui->customPlot->graph(graph)->setName("Choice " + QString(QChar(graph + 'A')));
		ui->customPlot->graph(graph)->setPen(QPen(static_cast<Qt::GlobalColor>(Qt::red + graph)));
	}

	// Tags
	for(int tag = 0, size = ui->customPlot->graphCount(); tag < size; tag++) {
		AxisTag *axisTag = new AxisTag(ui->customPlot->graph(tag)->valueAxis());
		axisTag->setPen(ui->customPlot->graph(tag)->pen());
		tags.append(axisTag);
	}
	ui->customPlot->axisRect()->axis(QCPAxis::atRight)->setPadding(75);

	// Prevent dragging and zooming X axis to negative time
	connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onXAxisRangeChanged(QCPRange)));

	// Set current time and last know value on the X axis
	time = QTime(QTime::currentTime());
	lastX = 0;

	// Start update timer
	connect(&updatePlotTimer, SIGNAL(timeout()), this, SLOT(updatePlot()));
	updatePlotTimer.start(0);

	// TODO
	// - titel
	// - aantal graphs
	// - y value
}

void MainWindow::updatePlot() {
	// Calculate X axis and Y axis values
	double x = time.elapsed()/1000.0;
	double y = 50.0;

	// Add at most a point every 2 ms
	if(x - lastX > 0.002) {
		// Update graphs
		for(int graph = 0, size = ui->customPlot->graphCount(); graph < size; graph++) {
			y = (graph == 0 ? 60.0 : 40.0);
			ui->customPlot->graph(graph)->addData(x, y);
		}

		// Update tags
		for(int tag = 0, size = ui->customPlot->graphCount(); tag < size; tag++) {
			y = (tag == 0 ? 60.0 : 40.0);
			tags[tag]->updatePosition(y);
			tags[tag]->setText(QString::number(y) + " %");
		}

		// Update last know value on the X axis
		lastX = x;
	}

	// Make the X axis range scroll to the right with the data, but only when the graph is touching the right border
	if(fabs(ui->customPlot->xAxis->range().upper - x) < 0.01) {
		ui->customPlot->xAxis->setRange(x, ui->customPlot->xAxis->range().size(), Qt::AlignRight);
	}

	// Redraw plot
	ui->customPlot->replot();
}

void MainWindow::onXAxisRangeChanged(const QCPRange &range) {
	QCPRange boundedRange = range;

	// Prevent range from going negative
	if(range.lower < 0) {
		boundedRange.lower = 0;
		boundedRange.upper = range.size();
	}

	ui->customPlot->xAxis->setRange(boundedRange);
}