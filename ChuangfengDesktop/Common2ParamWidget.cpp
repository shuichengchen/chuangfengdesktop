#include "Common2ParamWidget.h"

Common2ParamWidget::Common2ParamWidget(PopWidgetEnum type, QWidget *parent)
	:MoveableFramelessWindow(parent)
	,ui(new Ui::Common2ParamWidget)
	,m_enWidgetType(type)
{
	ui->setupUi(this);
	ui->error_lab->setVisible(false);
	connect(ui->pop_close_btn, &QPushButton::clicked, this, &QWidget::close);
	connect(ui->pop_cancle_btn, &QPushButton::clicked, this, &QWidget::close);
	connect(ui->pop_min_btn, &QPushButton::clicked, this, &QWidget::showMinimized);
	connect(ui->pop_commit_btn, &QPushButton::clicked, this, [this]()->void {
	 if (ui->tag_name_Edit->text() == "")
	 {
		 ui->error_lab->setVisible(true);
		 return;
	 }
	 emit this->sig_comit(ui->tag_name_Edit->text(), ui->remake_Edit->text());
	 emit ui->pop_close_btn->clicked();
	
	});
	switch (m_enWidgetType)
	{
	case enCategoryLayout:
	{
		ui->tagName_lab->setText(QString::fromLocal8Bit("账目名称："));
		setWindowTitle(QString::fromLocal8Bit("账目管理"));
		ui->title_lab->setText(QString::fromLocal8Bit("账目管理"));
		break;
	}
	case enAreaLayout:
	{
		ui->tagName_lab->setText(QString::fromLocal8Bit("区域名称："));
		setWindowTitle(QString::fromLocal8Bit("区域管理"));
		ui->title_lab->setText(QString::fromLocal8Bit("区域管理"));
		break;
	}
	case enSupplierLayout:
	{
		ui->tagName_lab->setText(QString::fromLocal8Bit("供应商名称："));
		setWindowTitle(QString::fromLocal8Bit("供应商管理"));
		ui->title_lab->setText(QString::fromLocal8Bit("供应商管理"));
		break;
	}
	default:
		break;
	}
}


Common2ParamWidget::~Common2ParamWidget()
{
}

QWidget* Common2ParamWidget::getDragnWidget()
{
	return ui->pop_widget_title;
}
