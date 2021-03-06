
#include "SupplierLayoutManager.h"
#include "Common2ParamWidget.h"
#include <thread>
#include "SingletonHttpRequest.h"
#include "globalVariable.h"
#include "commomdef.h"

SupplierLayoutManager::SupplierLayoutManager(Ui::ChuangfengDesktopClass*ui)
	:BaseLayoutManager(ui)
{
	InitLayout();
	connect(m_pUi->supplier_add_btn, &QPushButton::clicked, this, [this]()->void {
		Common2ParamWidget*pQtWidget = new Common2ParamWidget(PopWidgetEnum::enSupplierLayout);
		connect(pQtWidget, SIGNAL(sig_comit(QString&, QString&)), this, SLOT(SlotAddSupplier(QString&, QString&)));
		pQtWidget->setAttribute(Qt::WA_DeleteOnClose);
		pQtWidget->setWindowModality(Qt::ApplicationModal);
		pQtWidget->show();
	});
	connect(ui->supplier_remove_btn, &QPushButton::clicked, this, &SupplierLayoutManager::SlotRemoveSupplierItem);
	std::thread t([this]()->void {
		this->threadGetSupplierInfoCallBack();
	});
	t.detach();
}


SupplierLayoutManager::~SupplierLayoutManager()
{
}

void SupplierLayoutManager::SlotAddSupplier(QString&itemName, QString &remake)
{
	m_addName = itemName;
	m_addRemake = remake;
	QThread *m_pThread = new QThread;
	connect(m_pThread, SIGNAL(started()), this, SLOT(SlotThreadAddItem()));
	connect(m_pThread, SIGNAL(finished()), m_pThread, SLOT(deleteLater()));
	m_pThread->start();
}

void SupplierLayoutManager::SlotRemoveSupplierItem()
{
	QThread *m_pThread = new QThread;
	connect(m_pThread, SIGNAL(started()), this, SLOT(SlotThreadRemoveItem()));
	connect(m_pThread, SIGNAL(finished()), m_pThread, SLOT(deleteLater()));
	m_pThread->start();
}

void SupplierLayoutManager::SlotThreadRemoveItem()
{
	QMap<int, int> qMapSelect;
	bool isFirst = true;
	QString itemList = "";
	for (int i = 0; i < m_pViewModel->rowCount(); ++i)
	{
		if (Qt::Checked == m_pViewModel->item(i, 0)->checkState())
		{
			if (isFirst)
			{
				itemList = m_pViewModel->item(i, 1)->text();
			}
			else {
				itemList += "," + m_pViewModel->item(i, 1)->text();
			}
			isFirst = false;
			qMapSelect.insert(i, m_pViewModel->item(i, 1)->text().toInt());
		}
	}
	if (qMapSelect.count() == 0)
	{
		return;
	}
	QString strParam = "ids=" + itemList;
	QByteArray responseData;
	QString Url = QString(deleteSupplier).arg(g_strIpAddr).arg(g_strIpPort);
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
			QMapIterator<int, int> Iterator(qMapSelect);
			Iterator.toBack();
			while (Iterator.hasPrevious())//利用qmap排序 从大的节点 往小的进行删除。
			{
				Iterator.previous();
				int rowm = Iterator.key();
				m_pViewModel->removeRow(rowm);
				auto iter = g_SupplierList.find(Iterator.value());
				if (iter != g_SupplierList.end())
				{
					g_SupplierList.erase(iter);
				}
			}
			emit sig_NotifyMsg(QString::fromLocal8Bit("删除数据成功！"),0);
		}
		else {//失败
			emit sig_NotifyMsg(strMsg, errorcode);
		}
	}
	else {
		emit sig_NotifyMsg(QString::fromLocal8Bit("网络请求异常！"), 404);
	}
}

void SupplierLayoutManager::SlotThreadAddItem()
{
	QString Url = QString(addSupplier).arg(g_strIpAddr).arg(g_strIpPort);
	QString strParam = QString("name=%1&remake=%2").arg(m_addName).arg(m_addRemake);
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
			AddTableViewItem(id.toInt(), m_addName, m_addRemake);
			g_SupplierList[id.toInt()] = m_addName;
			emit sig_NotifyMsg(QString::fromLocal8Bit("添加数据成功！"), 0);
		}
		else {//失败
			emit sig_NotifyMsg(strMsg, errorcode);
		}
	}
	else {
		emit sig_NotifyMsg(QString::fromLocal8Bit("请求网络异常！"), 0);
	}
}

void SupplierLayoutManager::InitLayout()
{
	m_pViewHeadDeleagte = new CCheckBoxHeaderView(0, Qt::Horizontal, m_pUi->supplier_tableView);
	m_pUi->supplier_tableView->setHorizontalHeader(m_pViewHeadDeleagte);
	connect(m_pViewHeadDeleagte, SIGNAL(sig_AllChecked(bool)), this, SLOT(slotCheckBoxStateChanged(bool)));
	m_pViewModel = new QStandardItemModel();
	m_pUi->supplier_tableView->setModel(m_pViewModel);
	m_pViewModel->setColumnCount(4);
	m_pViewModel->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit(""));
	m_pViewModel->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ID"));
	m_pViewModel->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("供应商名称"));
	m_pViewModel->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("备注"));
	onSetTableAttribute(m_pUi->supplier_tableView, 4);
}

void SupplierLayoutManager::threadGetSupplierInfoCallBack()
{
	QString Url = QString(getSupplier).arg(g_strIpAddr).arg(g_strIpPort);
	QByteArray responseData;
	SingletonHttpRequest::getInstance()->RequestGet(Url, g_token, responseData);
	
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(responseData, &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		if (parse_doucment.isArray())
		{
			QJsonArray array = parse_doucment.array();
			for (int i = 0; i < array.size(); i++)
			{
				QJsonValue userArray = array.at(i);
				QJsonObject userObject = userArray.toObject();
				int id = userObject["id"].toInt();
				QString supplierName = userObject["name"].toString();
				QString remake = userObject["remake"].toString();
				AddTableViewItem(id, supplierName, remake);
				g_SupplierList[id] = supplierName;
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

void SupplierLayoutManager::AddTableViewItem(int id, QString supplierName,QString remake)
{
	int nCount = m_pViewModel->rowCount();
	m_pViewModel->setItem(nCount, 0, new QStandardItem(""));
	m_pViewModel->item(nCount, 0)->setCheckable(true);
	m_pViewModel->setItem(nCount, 0, new QStandardItem(""));
	m_pViewModel->item(nCount, 0)->setCheckable(true);

	m_pViewModel->setItem(nCount, 1, new QStandardItem(QString::number(id)));
	m_pViewModel->setItem(nCount, 2, new QStandardItem(supplierName));
	m_pViewModel->setItem(nCount, 3, new QStandardItem(remake));
	m_pUi->supplier_tableView->setColumnWidth(0, 30);
	m_pUi->supplier_tableView->setColumnWidth(1, 50);
	m_pUi->supplier_tableView->setColumnWidth(2, 180);
}
