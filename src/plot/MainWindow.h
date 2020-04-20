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
		QFile file;
		bool realTime;
		int lines;
		int maxGraphs;
		QVector<QColor> graphColors;

		// Methods
		void readOptions();
		void initPlot();
		void updatePlot(QTextStream &textStream);

	public:
		// Constructors
		MainWindow(QString fileName, bool realTime);

		// Destructor
		~MainWindow();

	private slots:
		// Plot methods
		void onXAxisRangeChanged(const QCPRange &range);

};

#endif