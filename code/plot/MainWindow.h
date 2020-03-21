#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTimer>
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
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void updatePlot();
	void onXAxisRangeChanged(const QCPRange &range);

};

#endif