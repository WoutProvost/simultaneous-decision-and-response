#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "lib/axistag.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

private:
	// General variables and constants
	Ui::MainWindow *ui;
	QVector<AxisTag*> tags;
	QTimer updatePlotTimer;
	QTime time;
	double lastX;
	QFile file;
	int maxGraphs;
	int experiment;
	int maxExperiments;
	int gateGrippingRobots;
	int temperatureSensingRobots;

	// Methods
	void initPlot();

public:
	// Constructors
	MainWindow(QString fileName, int maxGraphs, int experiment, int maxExperiments, int gateGrippingRobots, int temperatureSensingRobots);

	// Destructor
	~MainWindow();

private slots:
	// Plot methods
	void updatePlot();
	void onXAxisRangeChanged(const QCPRange &range);

};

#endif