#include <iostream>
#include <memory>
#include "assert.h"

#include <QApplication>
#include <QLabel>
#include <QtWidgets>

int main(int argv, char **args) {
	char text[] = "Hello World!";

	QApplication application(argv, args);
	QWidget window;
	
	QLabel label;
	label.setText(text);

	QHBoxLayout layout;
	layout.addWidget(&label);
	
	window.setLayout(&layout);
	window.show();

	/*
	QLabel *label = new QLabel;
	label->setText(text);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(&label2);
	window.setLayout(layout);
	window.show();
	*/

	return application.exec();
}
