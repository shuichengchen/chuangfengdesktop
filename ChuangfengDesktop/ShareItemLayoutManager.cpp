
#include "ShareItemLayoutManager.h"
#include "CommonDependenceWidget.h"
#include <thread>
#include "SingletonHttpRequest.h"
#include "globalVariable.h"
#include "commomdef.h"

ShareItemLayoutManager::ShareItemLayoutManager(Ui::ChuangfengDesktopClass*ui)
	:BaseLayoutManager(ui)
{
	InitLayout();
	connect(m_pUi->shareitem_add_btn, &QPushButton::clicked, this, [this]()->void {
		CommonDependenceWidget*pQtWidget = new CommonDependenceWidget(PopDependenceWidgetEnum::enShareItemLayout);
		connect(pQtWidget, SIGNAL(sig_comit(QString&, QString&)), this, SLOT(SlotAddShareItem(QString&, QString&)));
		pQtWidget->setAttribute(Qt::WA_DeleteOnClose);
		pQtWidget->setWindowModality(Qt::ApplicationModal);
		pQtWidget->show();
	});

	std::thread t([this]()->void {
		this->threadCostAreaInfoCallBack();
	});
	t.detach();
}

ShareItemLayoutManager::~ShareItemLayoutManager()
{
}

void ShareItemLayoutManager::InitLayout()
{
	m_pViewHeadDeleagte = new CCheckBoxHeaderView(0, Qt::Horizontal, m_pUi->shareitem_tableView);
	m_pUi->shareitem_tableView->setHorizontalHeader(m_pViewHeadDeleagte);
	connect(m_pViewHeadDeleagte, SIGNAL(sig_AllChecked(bool)), this, SLOT(slotCheckBoxStateChanged(bool)));
	m_pViewModel = new QStandardItemModel();
	m_pUi->shareitem_tableView->setModel(m_pViewModel);
	m_pViewModel->setColumnCount(4);
	m_pViewModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit(""));
	m_pViewModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ID"));
	m_pViewModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("费用名称"));
	m_pViewModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("所属区域"));
	onSetTableAttribute(m_pUi->shareitem_tableView, 4);

	int nCount = 0;
	for (auto i = 0; i < 1; i++)
	{
		m_pViewModel->setItem(i, 0, new QStandardItem(""));
		m_pViewModel->item(i, 0)->setCheckable(true);

		m_pViewModel->setItem(i, 1, new QStandardItem(QString::number(1)));
		m_pViewModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit("A区费用")));
		m_pViewModel->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit("A区")));

		nCount++;
	}
	m_pUi->shareitem_tableView->setColumnWidth(0, 30);
	m_pUi->shareitem_tableView->setColumnWidth(1, 50);
	m_pUi->shareitem_tableView->setColumnWidth(2, 180);
}

void ShareItemLayoutManager::SlotAddShareItem(QString &tagName, QString&fromName)
{
	m_addName = tagName;
	m_addfromName = fromName;
	QThread *m_pThread = new QThread;
	connect(m_pThread, SIGNAL(started()), this, SLOT(SlotThreadAddShareItem()));
	connect(m_pThread, SIGNAL(finished()), m_pThread, SLOT(deleteLater()));
	m_pThread->start();
}

void ShareItemLayoutManager::SlotThreadAddShareItem()
{
	QString Url = QString(addCostareas).arg(g_strIpAddr).arg(g_strIpPort);
	QString strParam = QString("name=%1&itemname=%2").arg(m_addfromName).arg(m_addName);
	QByteArray responseData;
	SingletonHttpRequest::getInstance()->RequestPost(Url, g_token, strParam, responseData);
	
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(responseData, &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		QJsonObject rootObject = parse_doucment.object();
		int errorcode = rootObject["error_code"].toInt();
		QString strMsg = rootObject["msg"].toString();
		if (errorcode == 0)//成功
		{
			QString id = rootObject["id"].toString();
			int pid = rootObject["pid"].toInt();
			AddTableViewItem(id.toInt(), m_addName, m_addfromName);
			CostAreaStruct&item = g_CostAreaList[m_addName];
			item.areaId = pid;
			item.areaName = m_addfromName;
			item.costAreaName = m_addName;
			emit  sig_NotifyMsg(QString::fromLocal8Bit("添加成功！"), 0);
		}
		else {//失败
			emit  sig_NotifyMsg(strMsg, errorcode);
		}
	}
	else {
		emit  sig_NotifyMsg(QString::fromLocal8Bit("添加数据失败！"), 404);
	}
}

void ShareItemLayoutManager::AddTableViewItem(int id, QString shareItem, QString AreaName)
{
	int nCount = m_pViewModel->rowCount();
	m_pViewModel->setItem(nCount, 0, new QStandardItem(""));
	m_pViewModel->item(nCount, 0)->setCheckable(true);
	m_pViewModel->setItem(nCount, 1, new QStandardItem(QString::number(id)));
	m_pViewModel->setItem(nCount, 2, new QStandardItem(shareItem));
	m_pViewModel->setItem(nCount, 3, new QStandardItem(AreaName));
	m_pUi->shareitem_tableView->setColumnWidth(0, 30);
	m_pUi->shareitem_tableView->setColumnWidth(1, 50);
	m_pUi->shareitem_tableView->setColumnWidth(2, 180);
}

void ShareItemLayoutManager::threadCostAreaInfoCallBack()
{
	QString Url = QString(getCostareas).arg(g_strIpAddr).arg(g_strIpPort);
	QByteArray responseData;
	SingletonHttpRequest::getInstance()->RequestGet(Url, g_token, responseData);
	
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(responseData, &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		if (parse_doucment.isArray())
		{
			QJsonArray rootarray = parse_doucment.array();
			for (int i = 0; i < rootarray.size(); i++)
			{
				QJsonValue costareaArray = rootarray.at(i);
				QJsonObject costareaObject = costareaArray.toObject();
				int id = costareaObject["id"].toInt();
				QString costareaName = costareaObject["name"].toString();
				QJsonObject areaobject = costareaObject["aquaculture"].toObject();
				QString areaName = areaobject["name"].toString();
				int pid = areaobject["id"].toInt();
				AddTableViewItem(id, costareaName, areaName);
				CostAreaStruct&item = g_CostAreaList[costareaName];
				item.areaId = pid;
				item.areaName = areaName;
				item.costAreaName = costareaName;
			}
		}
		else
		{
			QJsonObject rootObject = parse_doucment.object();
			if (!rootObject["error_code"].isNull())//
			{
				int errorcode = rootObject["error_code"].toInt();
				QString strMsg = rootObject["msg"].toString();
			}
		}
	}
	else {
	}
}
