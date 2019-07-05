#pragma once
#include "QtCustomBaseWnd.h"
#include "ui_FeedStoreQwidget.h"
#include "CCheckBoxHeaderView.h"
class FeedStoreManagerWdiget :
	public MoveableFramelessWindow
{
	Q_OBJECT
public:
	FeedStoreManagerWdiget(QWidget *parent = Q_NULLPTR);
	~FeedStoreManagerWdiget();
private slots:
	void updateMaximize();
	void SlotOptionClick();
	void comboBoxValueChanged();
	void SlotDescFeedStore();
	
private:
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	virtual QWidget*getDragnWidget();
	void InitOption();
	void initTableView();
	void ChangeDetailTableView();
private:
	Ui::FeedStore*ui;
	QList< NavButton*> m_NavButtonList;
	CCheckBoxHeaderView * m_pViewHeadDeleagteTotalDetail;
	QStandardItemModel *m_pViewModelTotalDetail;
	CCheckBoxHeaderView * m_pViewHeadDeleagteTotal_in_out_return;
	QStandardItemModel *m_pViewModelTotalDetail_in_out_return;

	CCheckBoxHeaderView * m_pViewHeadDeleagteTotalArea;
	QStandardItemModel *m_pViewModelTotalArea;
};

