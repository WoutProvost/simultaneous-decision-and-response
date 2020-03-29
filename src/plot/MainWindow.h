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

	// Methods
	void initPlot();

public:
	// Constructors
	explicit MainWindow(QWidget *parent = 0);

	// Destructor
	~MainWindow();

private slots:
	// Plot methods
	void updatePlot();
	void onXAxisRangeChanged(const QCPRange &range);

};

#endif