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
	textStream(&file),
	realTime(realTime),
	lines(0),
	availableOptions(1),
	graphColors(availableOptions, Qt::black) {

	// Configure initial UI according to the generated UI header file
	ui->setupUi(this);

	// Read options from log file
	readOptions();

	// Initialize plot
	initPlot();
}

MainWindow::~MainWindow() {
	// Close the file
	file.close();

	// Delete UI
	delete ui;
}

void MainWindow::readOptions() {
	// Open the file and make sure it exists and is allowed to be opened
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		printError("Couldn't open file '" + file.fileName() + "'.");
	}

	// Count the amount of lines and extract options
	QTextStream optionsTextStream(&file);
	while(!optionsTextStream.atEnd()) {
		QString line = optionsTextStream.readLine().trimmed();
		if(line.startsWith('!')) {
			QTextStream options(&line);
			char c;
			options >> c >> availableOptions;
			graphColors.fill(Qt::black, availableOptions);
			for(int color = 0; color < availableOptions; color++) {				
				options >> c;				
				graphColors[color] = options.read(9);
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
	setMinimumSize(570, 430);
    setGeometry(screenGeometry.width() - width(), screenGeometry.height() - height(), 570, 430);
	if(realTime) {
		setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	}

	// Actions
	QAction *actionShowLegend = new QAction("Show Legend", this);
	actionShowLegend->setCheckable(true);
	actionShowLegend->setChecked(true);
	actionShowLegend->setShortcut(Qt::Key_L);
	addAction(actionShowLegend);
	connect(actionShowLegend, SIGNAL(toggled(bool)), this, SLOT(actionShowLegendToggled(bool)));
	QAction *actionShowTemperatureSensors = new QAction("Show Temperature Sensors", this);
	actionShowTemperatureSensors->setCheckable(true);
	actionShowTemperatureSensors->setChecked(true);
	actionShowTemperatureSensors->setShortcut(Qt::Key_T);
	addAction(actionShowTemperatureSensors);
	connect(actionShowTemperatureSensors, SIGNAL(toggled(bool)), this, SLOT(actionShowTemperatureSensorsToggled(bool)));
	QAction *actionShowGateGrippers = new QAction("Show Gate Grippers", this);
	actionShowGateGrippers->setCheckable(true);
	actionShowGateGrippers->setChecked(true);
	actionShowGateGrippers->setShortcut(Qt::Key_G);
	addAction(actionShowGateGrippers);
	connect(actionShowGateGrippers, SIGNAL(toggled(bool)), this, SLOT(actionShowGateGrippersToggled(bool)));

	// Title
	ui->customPlot->plotLayout()->insertRow(0);
	ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot, "Collective decision and response history", QFont("sans", 12, QFont::Bold)));

	// Legend	
	ui->customPlot->legend->setVisible(true);
	QCPTextElement *legendTitleColumn1 = new QCPTextElement(ui->customPlot, "Temperature sensors", QFont("sans", 10, QFont::Bold));
	legendTitleColumn1->setLayer(ui->customPlot->legend->layer());
	legendTitleColumn1->setTextFlags(legendTitleColumn1->textFlags() & ~Qt::AlignCenter | Qt::AlignLeft);
	legendTitleColumn1->setMargins(QMargins(0, 0, 20, 0));
	ui->customPlot->legend->addElement(0, 0, legendTitleColumn1);
	QCPTextElement *legendTitleColumn2 = new QCPTextElement(ui->customPlot, "Gate grippers", QFont("sans", 10, QFont::Bold));
	legendTitleColumn2->setLayer(ui->customPlot->legend->layer());
	legendTitleColumn2->setTextFlags(legendTitleColumn2->textFlags() & ~Qt::AlignCenter | Qt::AlignLeft);
	legendTitleColumn2->setMargins(QMargins(0, 0, 0, 0));
	ui->customPlot->legend->addElement(0, 1, legendTitleColumn2);
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

	// Graphs (temperature sensors)
	for(int graph = 0; graph < availableOptions; graph++) {
		QPen pen;
		pen.setColor(graphColors[graph]);
		pen.setWidthF(2.0);
		ui->customPlot->addGraph();
		ui->customPlot->graph(graph)->setName("Exit " + QString(QChar(graph + 'A' - 1))); // Subtract 1, so that the second graphs starts from A (see below)
		ui->customPlot->graph(graph)->setPen(pen);
	}

	// Graphs (gate grippers)
	for(int graph = 0; graph < availableOptions; graph++) {
		QPen pen;
		pen.setColor(graphColors[graph]);
		pen.setWidthF(2.0);
		pen.setStyle(Qt::DotLine);
		ui->customPlot->addGraph();
		ui->customPlot->graph(availableOptions + graph)->setName("Exit " + QString(QChar(graph + 'A' - 1))); // Subtract 1, so that the second graphs starts from A (see below)
		ui->customPlot->graph(availableOptions + graph)->setPen(pen);
		ui->customPlot->legend->addElement(graph + 1, 1, ui->customPlot->legend->element(availableOptions + 1, 0));
	}

	// Give the first graphs of each type a custom name
	if(availableOptions > 0) {
		ui->customPlot->graph(0)->setName("Undecided");
		ui->customPlot->graph(availableOptions)->setName("Undecided");
	}

	// Tags
	for(int tag = 0; tag < availableOptions*2; tag++) {
		QString text(QString::number(0, 'f', 2) + " %");
		AxisTag *axisTag = new AxisTag(ui->customPlot->graph(tag)->valueAxis());
		axisTag->setPen(ui->customPlot->graph(tag)->pen());
		axisTag->setText(text);
		tags.append(axisTag);
		lastTagTexts.append(text);
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
		while(!textStream.atEnd()) {
			updatePlot();
			line++;
			cout << "\rPlotting data from file '" << file.fileName().toStdString() << "': " << static_cast<double>(line)/lines*100 << "%" << flush;
		}
		cout << "\r\e[K" << flush;

		// Redraw plot
		ui->customPlot->replot();
	}
	// Read data from the file in real time
	else {
		// Start update timer with an interval of 2 ms
		connect(&updatePlotTimer, SIGNAL(timeout()), this, SLOT(updatePlot()));
		updatePlotTimer.start(2);
	}
}

void MainWindow::updatePlot() {
	QString line = textStream.readLine().trimmed();
	if(!line.isEmpty() && !line.startsWith('#') && !line.startsWith('!')) {		
		// Extract data and calculate X and Y axis values
		QTextStream data(&line);
		char c;
		double x;
		QVector<double> y(availableOptions*2, 0.0);
		data >> x;
		x /= 1000.0;
		for(int graph = 0; graph < availableOptions*2; graph++) {
			data >> c >> y[graph];
			y[graph] *= 100.0;
		}

		// Update graphs and tags
		for(int graph = 0; graph < availableOptions*2; graph++) {
			QString text(QString::number(y[graph], 'f', 2) + " %");
			ui->customPlot->graph(graph)->addData(x, y[graph]);
			tags[graph]->updatePosition(y[graph]);
			if(ui->customPlot->graph(graph)->visible()) {
				tags[graph]->setText(text);
			}
			lastTagTexts[graph] = text;
		}

		if(!realTime) {
			// Set X axis range to show whole set of data
			ui->customPlot->xAxis->setRange(0, x);
		} else {
			// Make the X axis range scroll to the right with the data, but only when the graph is touching the right border
			if(fabs(ui->customPlot->xAxis->range().upper - x) < 0.3) {
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

void MainWindow::actionShowLegendToggled(bool toggled) {
	ui->customPlot->legend->setVisible(toggled);
	ui->customPlot->replot();
}

void MainWindow::actionShowTemperatureSensorsToggled(bool toggled) {
	for(int graph = 0; graph < availableOptions; graph++) {
		ui->customPlot->graph(graph)->setVisible(toggled);
		if(!toggled) {
			tags[graph]->setPen(QPen(QColor("#00000000")));
			tags[graph]->setText("");
		} else {
			tags[graph]->setPen(ui->customPlot->graph(graph)->pen());
			tags[graph]->setText(lastTagTexts[graph]);
		}
	}
	ui->customPlot->replot();
}

void MainWindow::actionShowGateGrippersToggled(bool toggled) {
	for(int graph = 0; graph < availableOptions; graph++) {
		ui->customPlot->graph(availableOptions + graph)->setVisible(toggled);
		if(!toggled) {
			tags[availableOptions + graph]->setPen(QPen(QColor("#00000000")));
			tags[availableOptions + graph]->setText("");
		} else {
			tags[availableOptions + graph]->setPen(ui->customPlot->graph(availableOptions + graph)->pen());
			tags[availableOptions + graph]->setText(lastTagTexts[availableOptions + graph]);
		}
	}
	ui->customPlot->replot();
}