#pragma once
#include "QtCustomBaseWnd.h"
#include "ui_LoginQWidget.h"
class LoginQWidget : public MoveableFramelessWindow
{
	Q_OBJECT

public:
	explicit  LoginQWidget(QWidget *parent = Q_NULLPTR);
	~LoginQWidget();
public slots:
	void SlotCloseMainWidget();
	void SlotThreadLogin();
private:
	QWidget*getDragnWidget();

private:
	Ui::QtLoginWidget* ui;
	bool m_bIsLoginLayout;

};

