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
		QVector<QString> lastTagTexts;
		QVector<qreal> lastTagPositions;
		QTimer updatePlotTimer;
		QFile file;
		QTextStream textStream;
		bool realTime;
		bool top;
		int lines;
		int availableOptions;
		QVector<QColor> graphColors;

		// Methods
		void readOptions();
		void initPlot();
		void initData();

	public:
		// Constructors
		MainWindow(QString fileName, bool realTime, bool top);

		// Destructor
		~MainWindow();

	private slots:
		// Plot methods
		void onXAxisRangeChanged(const QCPRange &range);
		void updatePlot();

		// Action methods
		void actionShowLegendToggled(bool toggled);
		void actionShowDecisionDataToggled(bool toggled);
		void actionShowResponseDataToggled(bool toggled);
		void actionClearDataTriggered();
};

#endif