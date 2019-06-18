#pragma once
#include "ui_ChuangfengDesktop.h"
#include "CCheckBoxHeaderView.h"
#include <QObject>
class BaseLayoutManager:public QObject
{
	Q_OBJECT
public:
	BaseLayoutManager(Ui::ChuangfengDesktopClass*ui);
	~BaseLayoutManager();
public:
	virtual void InitLayout();
	virtual void onSetTableAttribute(QTableView *pTableView, const int cloum);
protected slots:
	void slotCheckBoxStateChanged(bool status);
protected:
	Ui::ChuangfengDesktopClass*m_pUi;
	CCheckBoxHeaderView * m_pViewHeadDeleagte;
	QStandardItemModel *m_pViewModel;
};

