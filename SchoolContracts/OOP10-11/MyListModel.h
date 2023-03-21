#pragma once
#pragma once
#include<QAbstractListModel>
#include "domain.h"
#include <vector>
#include <qdebug.h>
class MyListModel :public QAbstractListModel {
	std::vector<Subject> subs;
public:
	MyListModel(const std::vector<Subject>& subs) :subs{ subs } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return subs.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			
			auto sub = subs[index.row()].get_name();
			return QString::fromStdString(sub);
		}
		/*if (role == Qt::UserRole) {
			auto tp = pets[index.row()].getType();
			return QString::fromStdString(tp);
		}
		if (role == Qt::BackgroundRole) {
			if (pets[index.row()].getSpecies()[0] == 'R') {
				return QColor(Qt::red);
			}
		}*/
		return QVariant{};
	}

	void setSubs(const vector<Subject>& subs) {
		this->subs = subs;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), 0);
		emit dataChanged(topLeft, bottomR);
	}


};