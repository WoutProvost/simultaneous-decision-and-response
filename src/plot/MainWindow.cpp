#include "MainWindow.h"
#include <iostream>
#include "ui_mainwindow.h"
#include "Application.h"

using std::string;
using std::cout;
using std::flush;

MainWindow::MainWindow(QString fileName, bool realTime) :
	// Call base class method and initialize attributes and set default values
	QMainWindow(),
	ui(new Ui::MainWindow),
	file(fileName),
	realTime(realTime),
	lines(0),
	maxGraphs(1),
	graphColors(maxGraphs, Qt::black) {

	// Configure initial UI according to the generated UI header file
	ui->setupUi(this);

	// Read options from log file
	readOptions();

	// Initialize plot
	initPlot();
}

MainWindow::~MainWindow() {
	delete ui;

	// Close the file
	file.close();
}

void MainWindow::readOptions() {
	// Open the file and make sure it exists and is allowed to be opened
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		printError("Couldn't open file '" + file.fileName() + "'.");
	}

	// Count the amount of lines and extract options
	QTextStream textStream(&file);
	while(!textStream.atEnd()) {
		QString line = textStream.readLine().trimmed();
		if(line.startsWith('!')) {
			QTextStream options(&line);
			char c;
			options >> c >> maxGraphs;
			graphColors.fill(Qt::black, maxGraphs);
			for(int graph = 0; graph < maxGraphs; graph++) {				
				options >> c;				
				graphColors[graph] = options.read(9);
			}
		}
		lines++;
	}

	// Close the file
	file.close();
}

void MainWindow::initPlot() {
	// Window
	string fileName = file.fileName().toStdString();
	size_t pos = fileName.find_last_of('/');
	if(pos != string::npos) {
		fileName.erase(0, pos + 1);
	}
	QString title(fileName.c_str());
	if(realTime) {
		title = "Real Time Data";
	}
	setWindowTitle(title + " - Collective Decision Plot");
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	setMinimumSize(400, 300);
	setGeometry(screenGeometry.width() - width(), screenGeometry.height() - height(), 570, 430);

	// Title
	ui->customPlot->plotLayout()->insertRow(0);
	ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot, "Collective decision history", QFont("sans", 12, QFont::Bold)));

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
	ui->customPlot->xAxis->setLabel("Time (mm:ss)");
	ui->customPlot->xAxis->setLabelFont(QFont("sans", 10, QFont::Bold));
	ui->customPlot->xAxis->setRange(0, 60);
	ui->customPlot->xAxis->setTickLengthIn(0);
	ui->customPlot->xAxis->setSubTickLength(0);
	QSharedPointer<QCPAxisTickerTime> xAxisTicker(new QCPAxisTickerTime);
	xAxisTicker->setTimeFormat("%m:%s");
	ui->customPlot->xAxis->setTicker(xAxisTicker);

	// Y axis
	ui->customPlot->yAxis->setLabel("Percentage (%)");
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
	for(int graph = 0; graph < maxGraphs; graph++) {
		QPen pen;
		pen.setColor(graphColors[graph]);
		pen.setWidthF(2.0);
		ui->customPlot->addGraph();
		ui->customPlot->graph(graph)->setName("Exit " + QString(QChar(graph + 'A' - 1))); // Subtract 1, so that the second graphs starts from A (see below)
		ui->customPlot->graph(graph)->setPen(pen);
	}

	// Give the first graph a custom name
	if(maxGraphs > 0) {
		ui->customPlot->graph(0)->setName("Undecided");
	}

	// Tags
	for(int tag = 0; tag < maxGraphs; tag++) {
		AxisTag *axisTag = new AxisTag(ui->customPlot->graph(tag)->valueAxis());
		axisTag->setPen(ui->customPlot->graph(tag)->pen());
		axisTag->setText(QString::number(0, 'f', 2) + " %");
		tags.append(axisTag);
	}
	ui->customPlot->axisRect()->axis(QCPAxis::atRight)->setPadding(90);

	// Prevent dragging and zooming X axis to negative time
	connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onXAxisRangeChanged(QCPRange)));

	// Open the file and make sure it exists and is allowed to be opened
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		printError("Couldn't open file '" + file.fileName() + "'.");
	}

	// Read all data from the file immediately
	if(!realTime) {
		// Update the plot with the data included in the file and show a progress precentage in the console
		int line = 0;
		cout.setf(std::ios::fixed);
		cout.precision(2);
		QTextStream textStream(&file);
		while(!textStream.atEnd()) {
			updatePlot(textStream);
			line++;
			cout << "\rPlotting data from file '" << file.fileName().toStdString() << "': " << static_cast<double>(line)/lines*100 << "%" << flush;
		}
		cout << "\r\e[K" << flush;

		// Redraw plot
		ui->customPlot->replot();
	}
	// Read data from the file in real time
	else {
	// 	QTextStream textStream(stdin);
	// 	// Start update timer
	// 	connect(&updatePlotTimer, SIGNAL(timeout()), this, SLOT(updatePlot()));
	// 	updatePlotTimer.start(0);
	}
}

void MainWindow::updatePlot(QTextStream &textStream) {
	QString line = textStream.readLine().trimmed();
	if(!line.isEmpty() && !line.startsWith('#') && !line.startsWith('!')) {		
		// Extract data and calculate X and Y axis values
		QTextStream data(&line);
		char c;
		double x;
		QVector<double> y(maxGraphs, 0.0);
		data >> x;
		x /= 1000.0;
		for(int graph = 0; graph < maxGraphs; graph++) {
			data >> c >> y[graph];
			y[graph] *= 100.0;
		}

		// Update graphs and tags
		for(int graph = 0; graph < maxGraphs; graph++) {
			ui->customPlot->graph(graph)->addData(x, y[graph]);
			tags[graph]->updatePosition(y[graph]);
			tags[graph]->setText(QString::number(y[graph], 'f', 2) + " %");
		}

		if(!realTime) {
			// Set X axis range to show whole set of data
			ui->customPlot->xAxis->setRange(0, x);
		} else {
			// Make the X axis range scroll to the right with the data, but only when the graph is touching the right border
			if(fabs(ui->customPlot->xAxis->range().upper - x) < 0.01) {
				ui->customPlot->xAxis->setRange(x, ui->customPlot->xAxis->range().size(), Qt::AlignRight);
			}

			// Redraw plot
			ui->customPlot->replot();
		}
	}
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