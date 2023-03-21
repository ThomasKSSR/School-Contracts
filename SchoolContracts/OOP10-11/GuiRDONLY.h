#pragma once
#include <qpainter.h>
#include "service.h"
#include "Observer.h"
#include <qwidget.h>

class Imgdraw: public QWidget,public Observer {
private:
	SubjectSrv& srv;

	void update() override {
		repaint(); 
	}
public:
	Imgdraw(SubjectSrv& srv) :srv{ srv } {
		srv.addObserver(this);
		this->show();
	};
	void paintEvent(QPaintEvent* event) override{

		QPainter p{ this };

		for (auto sub : srv.get_all_contract()) {
			int x = rand() % 300;
			int y = rand() % 300;
			p.drawImage(x, y, QImage("hasbulla.jfif"));
		}
	}


};