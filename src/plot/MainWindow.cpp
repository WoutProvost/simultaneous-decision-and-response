#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Application.h"

using std::cout;
using std::flush;

MainWindow::MainWindow(QString fileName, int maxGraphs, int experiment, int maxExperiments, int gateGrippingRobots, int temperatureSensingRobots) :
	// Call base class method and initialize attributes and set default values
	QMainWindow(),
	ui(new Ui::MainWindow),
	file(fileName),
	maxGraphs(maxGraphs),
	experiment(experiment),
	maxExperiments(maxExperiments),
	gateGrippingRobots(gateGrippingRobots),
	temperatureSensingRobots(temperatureSensingRobots),
	useRealTimeData(file.fileName() == "-") {

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
	setGeometry(screenGeometry.width() - width(), screenGeometry.height() - height(), 570, 430);

	// Title
	ui->customPlot->plotLayout()->insertRow(0);
	ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot,
		"Experiment " + QString::number(experiment) +
		"/" + QString::number(maxExperiments) +
		": [" + QString::number(gateGrippingRobots) +
		"g, " + QString::number(temperatureSensingRobots) +
		"s]",
		QFont("sans", 12, QFont::Bold))
	);

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
	QVector<Qt::GlobalColor> graphColors = {
		Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta,
		Qt::darkRed, Qt::darkBlue, Qt::darkGreen, Qt::darkYellow, Qt::darkCyan, Qt::darkMagenta
	};
	QVector<Qt::PenStyle> graphStyle = {
		Qt::SolidLine,
		Qt::DotLine
	};
	for(int graph = 0; graph < maxGraphs; graph++) {
		QPen pen;
		pen.setColor(graphColors[graph%graphColors.size()]);
		pen.setStyle(graphStyle[graph/graphColors.size()%graphStyle.size()]);
		pen.setWidthF(2);
		ui->customPlot->addGraph();
		ui->customPlot->graph(graph)->setName("Exit " + QString(QChar(graph + 'A')));
		ui->customPlot->graph(graph)->setPen(pen);
	}

	// Tags
	for(int tag = 0; tag < maxGraphs; tag++) {
		AxisTag *axisTag = new AxisTag(ui->customPlot->graph(tag)->valueAxis());
		axisTag->setPen(ui->customPlot->graph(tag)->pen());
		axisTag->setText(QString::number(0, 'f', 2) + " %");
		tags.append(axisTag);
	}
	ui->customPlot->axisRect()->axis(QCPAxis::atRight)->setPadding(75);

	// Prevent dragging and zooming X axis to negative time
	connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onXAxisRangeChanged(QCPRange)));

	// Use file for data input
	if(!useRealTimeData) {
		// Open the file and make sure it exists and is allowed to be opened
		if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			printError("Couldn't open file '" + file.fileName() + "'.");
		}

		// Count the amount of lines
		int lines = 0;
		QTextStream textStream(&file);
		while(!textStream.atEnd()) {
			textStream.readLine();
			lines++;
		}
		textStream.seek(0);

		// Update the plot with the data included in the file and show a progress precentage in the console
		int line = 0;
		cout.setf(std::ios::fixed);
		cout.precision(2);
		while(!textStream.atEnd()) {
			updatePlot(textStream);
			line++;
			cout << "\rPlotting data from file '" << file.fileName().toStdString() << "': " << float(line)/lines*100 << "%" << flush;
		}
		cout << "\r\e[K" << flush;

		// Close the file
		file.close();

		// Set X axis range to show whole set of data
		ui->customPlot->xAxis->setRange(0, ceil(float(lines)/1000));

		// Redraw plot
		ui->customPlot->replot();
	}
	// Use stdin for real time generated data input
	else {
	// 	QTextStream textStream(stdin);
	// 	// Start update timer
	// 	connect(&updatePlotTimer, SIGNAL(timeout()), this, SLOT(updatePlot()));
	// 	updatePlotTimer.start(0);
	}
}

void MainWindow::updatePlot(QTextStream &textStream) {
	// Extract data and calculate X and Y axis values
	char c;
	double x;
	QVector<double> y(maxGraphs, 0.0);
	textStream >> x;
	x /= 1000.0;
	for(int graph = 0; graph < maxGraphs; graph++) {
		textStream >> c >> y[graph];
		y[graph] *= 100.0;
	}

	// Update graphs and tags
	for(int graph = 0; graph < maxGraphs; graph++) {
		ui->customPlot->graph(graph)->addData(x, y[graph]);
		tags[graph]->updatePosition(y[graph]);
		tags[graph]->setText(QString::number(y[graph], 'f', 2) + " %");
	}

	// Make the X axis range scroll to the right with the data, but only when the graph is touching the right border
	if(fabs(ui->customPlot->xAxis->range().upper - x) < 0.01) {
		ui->customPlot->xAxis->setRange(x, ui->customPlot->xAxis->range().size(), Qt::AlignRight);
	}

	// Redraw plot
	if(useRealTimeData) {
		ui->customPlot->replot();
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