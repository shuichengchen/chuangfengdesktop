#include "FeedStoreManagerWdiget.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QGridLayout>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include "iconhelper.h"

#include "globalVariable.h"
#include "AddFeedStoreWidget.h"
#include "DescFeedStoreWidget.h"
#include "SingletonHttpRequest.h"
#include "MsgPopWidget.h"

FeedStoreManagerWdiget::FeedStoreManagerWdiget(QWidget *parent)
	:MoveableFramelessWindow(parent)
	, ui(new Ui::FeedStore)
{
	ui->setupUi(this);
	connect(ui->feedstore_cose_btn, &QPushButton::clicked, this, &QWidget::close);
	connect(ui->feedstore_max_restore_btn, &QPushButton::clicked, this, &FeedStoreManagerWdiget::updateMaximize);
	connect(ui->feedstore_min_btn, &QPushButton::clicked, this, &QWidget::showMinimized);
	ui->feedstore_max_restore_btn->setToolTip(QString::fromLocal8Bit("最大化"));
	//设置按钮的属性名为"maximizeProperty"
	ui->feedstore_max_restore_btn->setProperty("maximizeProperty", "maximize");
	ui->feedstore_max_restore_btn->setStyle(QApplication::style());
	InitOption();
 	QDateTime current_date_time = QDateTime::currentDateTime();
 	ui->startdateEdit->setCalendarPopup(true);
 	ui->startdateEdit->setDateTime(current_date_time);
 	ui->enddateEdit->setCalendarPopup(true);
 	ui->enddateEdit->setDateTime(current_date_time);
 	
	
	ui->storge_type_combox->addItem(QString::fromLocal8Bit("入库"));
	ui->storge_type_combox->addItem(QString::fromLocal8Bit("出库"));
	ui->storge_type_combox->addItem(QString::fromLocal8Bit("退货"));
	ui->storge_type_combox->addItem(QString::fromLocal8Bit("退库"));
	ui->storge_type_combox->setCurrentText(0);
	for (auto&kvp:g_areaList)
	{
		ui->area_combox->addItem(kvp.second.areaName);
		ui->area3_combox->addItem(kvp.second.areaName);
	}
	ui->area_combox->setCurrentText(0);
	connect(ui->storge_type_combox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxValueChanged()));
	ui->area_combox->setVisible(false);
	initTableView();

	connect(ui->feed_income_btn, &QPushButton::clicked, this, [this]()->void {
		AddFeedStoreWidget*pQtWidget = new AddFeedStoreWidget();
		connect(pQtWidget, SIGNAL(sig_commit(QString&, QString&, QString&, QString&, QString&, QString&, QString&)), this, SLOT(SlotAddFeedStore(QString&, QString&, QString&, QString&, QString&, QString&, QString&)));
		pQtWidget->setAttribute(Qt::WA_DeleteOnClose);
		pQtWidget->setWindowModality(Qt::ApplicationModal);
		pQtWidget->show();
	});

	connect(ui->feed_out_btn, &QPushButton::clicked, this, &FeedStoreManagerWdiget::SlotDescFeedStore);
}


FeedStoreManagerWdiget::~FeedStoreManagerWdiget()
{
}

void FeedStoreManagerWdiget::updateMaximize()
{
	QWidget *pWindow = this->window(); //获得标题栏所在的窗口
	pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();  //窗口最大化/还原显示
	if (pWindow->isTopLevel())
	{
		bool bMaximize = pWindow->isMaximized(); //判断窗口是不是最大化状态，是则返回true，否则返回false
		if (bMaximize)
		{
			//目前窗口是最大化状态，则最大化/还原的toolTip设置为"Restore"
			ui->feedstore_max_restore_btn->setToolTip(QString::fromLocal8Bit("还原"));
			//设置按钮的属性名为"maximizeProperty"
			ui->feedstore_max_restore_btn->setProperty("maximizeProperty", "restore");
		}
		else
		{
			//目前窗口是还原状态，则最大化/还原的toolTip设置为"Maximize"
			ui->feedstore_max_restore_btn->setToolTip(QString::fromLocal8Bit("最大化"));
			//设置按钮的属性名为"maximizeProperty"
			ui->feedstore_max_restore_btn->setProperty("maximizeProperty", "maximize");
		}

		ui->feedstore_max_restore_btn->setStyle(QApplication::style());
	}
}

void FeedStoreManagerWdiget::SlotOptionClick()
{
	NavButton *btn = (NavButton *)sender();
	for (int i = 0; i < m_NavButtonList.count(); i++) {
		if (m_NavButtonList.at(i) == btn)
		{
			ui->feedstore_stackedWidget->setCurrentIndex(i);
			m_NavButtonList.at(i)->setChecked(true);
		}
		else {
			m_NavButtonList.at(i)->setChecked(false);
		}
	}
}

void FeedStoreManagerWdiget::comboBoxValueChanged()
{
	ChangeDetailTableView();
}

void FeedStoreManagerWdiget::SlotDescFeedStore()
{
	QString subject = "";
	QString price = "";
	int number = 0;
	QString area = "ytes";
	DescFeedStoreWidget*pQtWidget = new DescFeedStoreWidget(_enIncomStore, subject, price, number, area);
	//connect(pQtWidget, SIGNAL(sig_commit(QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&)), this, SLOT(SlotAddMaterialDetail(QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&, QString&)));
	pQtWidget->setAttribute(Qt::WA_DeleteOnClose);
	pQtWidget->setWindowModality(Qt::ApplicationModal);
	pQtWidget->show();
}

void FeedStoreManagerWdiget::SlotAddFeedStore(QString&time, QString&suplier, QString&subject_name, QString&price, QString&unit, QString&specs, QString&number)
{
	 m_time = time;
	 m_suplier = suplier;
	 m_subject_name = subject_name;
	 m_price = price;
	 m_unit = unit;
	 m_specs = specs;
	 m_number = number;
	 QThread *m_pThread = new QThread;
	 connect(m_pThread, SIGNAL(started()), this, SLOT(SlotThreadAddFeedStore()));
	 connect(m_pThread, SIGNAL(finished()), m_pThread, SLOT(deleteLater()));
	 m_pThread->start();

}

void FeedStoreManagerWdiget::ChangeDetailTableView()
{
	if (ui->storge_type_combox->currentText() == QString::fromLocal8Bit("入库")|| ui->storge_type_combox->currentText() == QString::fromLocal8Bit("退货"))
	{
		ui->area_combox->setVisible(false);
	}
	else {
		
		ui->area_combox->setVisible(true);
	}
}

void FeedStoreManagerWdiget::AddFeedStoreTableView(FeedStoreStruct&item)
{
	int nCount = m_pViewModelTotalDetail->rowCount();
	
	m_pViewModelTotalDetail->item(nCount, 0)->setCheckable(true);
	m_pViewModelTotalDetail->item(nCount, 0)->setData(QString::number(item.id));
	m_pViewModelTotalDetail->setItem(nCount, 1, new QStandardItem(item.supplier));
	m_pViewModelTotalDetail->setItem(nCount, 2, new QStandardItem(item.subject_name));
	m_pViewModelTotalDetail->setItem(nCount, 3, new QStandardItem(item.specs));
	m_pViewModelTotalDetail->setItem(nCount, 4, new QStandardItem(item.unit));
	m_pViewModelTotalDetail->setItem(nCount, 6, new QStandardItem(item.price));
	m_pViewModelTotalDetail->setItem(nCount, 7, new QStandardItem(QString::number(item.number)));
	m_pViewModelTotalDetail->setItem(nCount, 8, new QStandardItem(QString::number(item.price.toDouble()*item.number)));

	ui->area_feed_detail_tableView->setColumnWidth(0, 30);
}

void FeedStoreManagerWdiget::AddFeedStoreIn_out_return_TableView(FeedStoreIn_out_return_Struct&item)
{

	int nCount = m_pViewModelTotalDetail_in_out_return->rowCount();

	m_pViewModelTotalDetail_in_out_return->item(nCount, 0)->setCheckable(true);
	m_pViewModelTotalDetail_in_out_return->item(nCount, 0)->setData(QString::number(item.id));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 1, new QStandardItem(item.time));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 2, new QStandardItem(item.subject_name));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 3, new QStandardItem(QString::number(item.number)));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 4, new QStandardItem(item.price));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 6, new QStandardItem(QString::number(item.surplus)));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 7, new QStandardItem(QString::number(item.price.toDouble()*item.surplus)));
	m_pViewModelTotalDetail_in_out_return->setItem(nCount, 8, new QStandardItem(item.area));

	ui->feedstore_in_out_tableView->setColumnWidth(0, 30);
}

void FeedStoreManagerWdiget::AddAreaFeedStoreTableView(AreaFeedStoreStruct&item)
{
	int nCount = m_pViewModelTotalArea->rowCount();

	m_pViewModelTotalArea->item(nCount, 0)->setCheckable(true);
	m_pViewModelTotalArea->item(nCount, 0)->setData(QString::number(item.id));
	m_pViewModelTotalArea->setItem(nCount, 1, new QStandardItem(item.area));
	m_pViewModelTotalArea->setItem(nCount, 2, new QStandardItem(item.subject_name));
	m_pViewModelTotalArea->setItem(nCount, 3, new QStandardItem(item.price));

	m_pViewModelTotalArea->setItem(nCount, 4, new QStandardItem(QString::number(item.number)));
	m_pViewModelTotalArea->setItem(nCount, 5, new QStandardItem(QString::number(item.price.toDouble()*item.number)));

	ui->area_feed_detail_tableView->setColumnWidth(0, 30);
}

void FeedStoreManagerWdiget::SlotThreadAddFeedStore()
{
	QString strParam = QString("operat_time=%1&supplier=%2&subject_name=%3&specs=%4&price=%5&unit=%6&number=%7")
		.arg(m_time).arg(m_suplier).arg(m_subject_name).arg(m_specs).arg(m_price).arg(m_unit).
		arg(m_number);
	QByteArray responseData;
	SingletonHttpRequest::getInstance()->RequestPost("http://127.0.0.1:80/zerg/public/index.php/InComFeedStore"
		, TempToken, strParam, responseData);
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(responseData, &json_error);
	if (json_error.error == QJsonParseError::NoError)
	{
		if (parse_doucment.isArray())
		{
			QJsonArray array = parse_doucment.array();
			for (int i = 0; i < array.size(); i++)
			{
				
				QJsonValue materialArray = array.at(i);
				QJsonObject materialObject = materialArray.toObject();
				FeedStoreStruct item;
				
			
			}
			emit sig_NotifyMsg(QString::fromLocal8Bit("添加成功！"), 0);
		}
		else
		{
			QJsonObject rootObject = parse_doucment.object();
			if (!rootObject["error_code"].isNull())//
			{
				int errorcode = rootObject["error_code"].toInt();
				QString strMsg = rootObject["msg"].toString();
				emit sig_NotifyMsg(strMsg, errorcode);
			}
		}
	}
	else {
		int errorcode = 404;
		emit sig_NotifyMsg(QString::fromLocal8Bit("网络请求异常！"), errorcode);
	}
}

void FeedStoreManagerWdiget::SlotPopMsg(QString msg, int errorCode)
{
	MsgPopWidget*pQtWidget = new MsgPopWidget(msg, errorCode);
	pQtWidget->setAttribute(Qt::WA_DeleteOnClose);
	pQtWidget->setWindowModality(Qt::ApplicationModal);
	pQtWidget->show();
}

void FeedStoreManagerWdiget::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event); //没有实质性的作用，只是用来允许event可以不使用，用来避免编译器警告
	emit ui->feedstore_max_restore_btn->clicked();
}

void FeedStoreManagerWdiget::paintEvent(QPaintEvent *event)
{
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(0, 0, this->width(), 40);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(QColor(41, 57, 85)));
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(0, 40, this->width(), this->height());
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);
		//painter.fillPath(path, QBrush(QColor(68, 71, 77)));
		painter.fillPath(path, QBrush(QColor(54, 78, 111)));
	}
}

QWidget* FeedStoreManagerWdiget::getDragnWidget()
{
	return ui->child_widget_title;
}

void FeedStoreManagerWdiget::InitOption()
{
	m_NavButtonList << ui->feedstore_detail_opt << ui->feedstore_in_out_opt
		<< ui->area_detail_opt;
	QList<QChar> pixChar;
	pixChar << 0xf509 << 0xf1fe << 0xf2a3;
	QColor normalBgColor = QColor("#364E6F");
	QColor hoverBgColor = QColor("#478CB6");
	QColor checkBgColor = QColor("#478CB6");
	QColor normalTextColor = QColor("#FFFFFF");
	QColor hoverTextColor = QColor("#FFFFFF");
	QColor checkTextColor = QColor("#FFFFFF");

	for (int i = 0; i < m_NavButtonList.count(); i++) {

		m_NavButtonList.at(i)->setLineColor(QColor("#029FEA"));
		///mNavButtonList.at(i)->setShowLine(true);
		m_NavButtonList.at(i)->setTextAlign(NavButton::TextAlign_Left);
		m_NavButtonList.at(i)->setTrianglePosition(NavButton::TrianglePosition_Right);
		//mNavButtonList.at(i)->setLinePosition(NavButton::LinePosition_Top);

		m_NavButtonList.at(i)->setPaddingLeft(5);
		m_NavButtonList.at(i)->setLineSpace(1);
		m_NavButtonList.at(i)->setLineWidth(5);
		m_NavButtonList.at(i)->setLineColor(QColor(255, 107, 107));
		m_NavButtonList.at(i)->setShowTriangle(true);

		m_NavButtonList.at(i)->setShowIcon(true);
		m_NavButtonList.at(i)->setIconSpace(ICOSPACE);
		m_NavButtonList.at(i)->setIconSize(QSize(ICONSIZE, ICONSIZE));

		//分开设置图标
		QChar icon = pixChar.at(i);
		QPixmap iconNormal = IconHelper::Instance()->getPixmap(normalTextColor.name(), icon, ICONFONTSIZE, PIXMAPSIZE, PIXMAPSIZE);
		QPixmap iconHover = IconHelper::Instance()->getPixmap(hoverTextColor.name(), icon, ICONFONTSIZE, PIXMAPSIZE, PIXMAPSIZE);
		QPixmap iconCheck = IconHelper::Instance()->getPixmap(checkTextColor.name(), icon, ICONFONTSIZE, PIXMAPSIZE, PIXMAPSIZE);

		m_NavButtonList.at(i)->setIconNormal(iconNormal);
		m_NavButtonList.at(i)->setIconHover(iconHover);
		m_NavButtonList.at(i)->setIconCheck(iconCheck);

		m_NavButtonList.at(i)->setNormalBgColor(normalBgColor);
		m_NavButtonList.at(i)->setHoverBgColor(hoverBgColor);
		m_NavButtonList.at(i)->setCheckBgColor(checkBgColor);
		m_NavButtonList.at(i)->setNormalTextColor(normalTextColor);
		m_NavButtonList.at(i)->setHoverTextColor(hoverTextColor);
		m_NavButtonList.at(i)->setCheckTextColor(checkTextColor);

		connect(m_NavButtonList.at(i), &QPushButton::clicked, this, &FeedStoreManagerWdiget::SlotOptionClick);
	}
	m_NavButtonList.at(0)->setChecked(true);
}

void FeedStoreManagerWdiget::initTableView()
{
	m_pViewHeadDeleagteTotalDetail = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->total_feed_store_tableView);
	ui->total_feed_store_tableView->setHorizontalHeader(m_pViewHeadDeleagteTotalDetail);
	m_pViewModelTotalDetail = new QStandardItemModel();
	ui->total_feed_store_tableView->setModel(m_pViewModelTotalDetail);
	m_pViewModelTotalDetail->setColumnCount(8);
	m_pViewModelTotalDetail->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit(""));
	m_pViewModelTotalDetail->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("供应商"));
	m_pViewModelTotalDetail->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("物品名称"));
	m_pViewModelTotalDetail->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("物品规格"));
	m_pViewModelTotalDetail->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("单位"));
	m_pViewModelTotalDetail->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("成本单价"));
	m_pViewModelTotalDetail->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("数量"));
	m_pViewModelTotalDetail->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("总价值"));
	onSetTableAttribute(ui->total_feed_store_tableView, 8, false);
	ui->total_feed_store_tableView->setColumnWidth(0, 30);
	ui->total_feed_store_tableView->setColumnWidth(1, 100);
	ui->total_feed_store_tableView->setColumnWidth(2, 180);

	m_pViewHeadDeleagteTotal_in_out_return = new CCheckBoxHeaderView(0, Qt::Horizontal, ui->feedstore_in_out_tableView);
	ui->feedstore_in_out_tableView->setHorizontalHeader(m_pViewHeadDeleagteTotal_in_out_return);
	m_pViewModelTotalDetail_in_out_return = new QStandardItemModel();
	ui->feedstore_in_out_tableView->setModel(m_pViewModelTotalDetail_in_out_return);
	m_pViewModelTotalDetail_in_out_return->setColumnCount(8);
	m_pViewModelTotalDetail_in_out_return->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit(""));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("时间"));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("物品名称"));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("数量"));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("成本单价"));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("剩余数量"));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("剩余总额"));
	m_pViewModelTotalDetail_in_out_return->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("区域"));
	onSetTableAttribute(ui->feedstore_in_out_tableView, 8, false);
	ui->feedstore_in_out_tableView->setColumnWidth(0, 30);
	ui->feedstore_in_out_tableView->setColumnWidth(1, 100);
	ui->feedstore_in_out_tableView->setColumnWidth(2, 180);


	m_pViewHeadDeleagteTotalArea= new CCheckBoxHeaderView(0, Qt::Horizontal, ui->area_feed_detail_tableView);
	ui->area_feed_detail_tableView->setHorizontalHeader(m_pViewHeadDeleagteTotalArea);
	m_pViewModelTotalArea = new QStandardItemModel();
	ui->area_feed_detail_tableView->setModel(m_pViewModelTotalArea);
	m_pViewModelTotalArea->setColumnCount(6);
	m_pViewModelTotalArea->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit(""));
	m_pViewModelTotalArea->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("区域"));
	m_pViewModelTotalArea->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("物品名称"));
	m_pViewModelTotalArea->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("成本单价"));
	m_pViewModelTotalArea->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("数量"));
	m_pViewModelTotalArea->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("总价值"));
	onSetTableAttribute(ui->area_feed_detail_tableView, 6, false);
	ui->area_feed_detail_tableView->setColumnWidth(0, 30);
	ui->area_feed_detail_tableView->setColumnWidth(1, 100);
	ui->area_feed_detail_tableView->setColumnWidth(2, 180);
}
