/********************************************************************************
** Form generated from reading UI file 'FeedingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEEDINGWIDGET_H
#define UI_FEEDINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qnavbutton.h>

QT_BEGIN_NAMESPACE

class Ui_FeedingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *child_widget_title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *feedstore_min_btn;
    QPushButton *feedstore_max_restore_btn;
    QPushButton *feedstore_cose_btn;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    NavButton *feeding_opt;
    NavButton *feeding_detail_opt;
    QLabel *label;
    QStackedWidget *feeding_stackedWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_5;
    QPushButton *area_feed_search_btn;
    QLineEdit *area_feed_edit;
    QLabel *label_3;
    QPushButton *feeding_btn;
    QComboBox *area3_combox;
    QTableView *area_feedstore_tableView;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDateEdit *startdateEdit;
    QLabel *label_5;
    QDateEdit *enddateEdit;
    QComboBox *area_combox;
    QComboBox *area_item_combox;
    QPushButton *detail_search_btn;
    QTableView *feeding_detail_tableView;

    void setupUi(QWidget *FeedingWidget)
    {
        if (FeedingWidget->objectName().isEmpty())
            FeedingWidget->setObjectName(QStringLiteral("FeedingWidget"));
        FeedingWidget->resize(960, 640);
        FeedingWidget->setMinimumSize(QSize(960, 640));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/test.png"), QSize(), QIcon::Normal, QIcon::Off);
        FeedingWidget->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(FeedingWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        child_widget_title = new QWidget(FeedingWidget);
        child_widget_title->setObjectName(QStringLiteral("child_widget_title"));
        child_widget_title->setMinimumSize(QSize(0, 40));
        child_widget_title->setMaximumSize(QSize(16777215, 40));
        child_widget_title->setStyleSheet(QStringLiteral(""));
        horizontalLayout_2 = new QHBoxLayout(child_widget_title);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(child_widget_title);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        feedstore_min_btn = new QPushButton(child_widget_title);
        feedstore_min_btn->setObjectName(QStringLiteral("feedstore_min_btn"));
        feedstore_min_btn->setMinimumSize(QSize(32, 23));

        horizontalLayout_2->addWidget(feedstore_min_btn);

        feedstore_max_restore_btn = new QPushButton(child_widget_title);
        feedstore_max_restore_btn->setObjectName(QStringLiteral("feedstore_max_restore_btn"));
        feedstore_max_restore_btn->setMinimumSize(QSize(32, 23));

        horizontalLayout_2->addWidget(feedstore_max_restore_btn);

        feedstore_cose_btn = new QPushButton(child_widget_title);
        feedstore_cose_btn->setObjectName(QStringLiteral("feedstore_cose_btn"));
        feedstore_cose_btn->setMinimumSize(QSize(32, 23));

        horizontalLayout_2->addWidget(feedstore_cose_btn);


        verticalLayout->addWidget(child_widget_title);

        widget = new QWidget(FeedingWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(160, 0));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(54, 78, 111);"));
        feeding_opt = new NavButton(widget_2);
        feeding_opt->setObjectName(QStringLiteral("feeding_opt"));
        feeding_opt->setGeometry(QRect(10, 60, 140, 35));
        feeding_detail_opt = new NavButton(widget_2);
        feeding_detail_opt->setObjectName(QStringLiteral("feeding_detail_opt"));
        feeding_detail_opt->setGeometry(QRect(10, 110, 140, 35));

        horizontalLayout->addWidget(widget_2);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(1, 0));
        label->setMaximumSize(QSize(1, 16777215));
        label->setStyleSheet(QStringLiteral("background-color: rgb(41, 57, 86);"));

        horizontalLayout->addWidget(label);

        feeding_stackedWidget = new QStackedWidget(widget);
        feeding_stackedWidget->setObjectName(QStringLiteral("feeding_stackedWidget"));
        feeding_stackedWidget->setMinimumSize(QSize(768, 581));
        feeding_stackedWidget->setStyleSheet(QStringLiteral("background-color: rgb(54, 78, 111);"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        verticalLayout_4 = new QVBoxLayout(page_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_5 = new QWidget(page_3);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setMinimumSize(QSize(0, 60));
        area_feed_search_btn = new QPushButton(widget_5);
        area_feed_search_btn->setObjectName(QStringLiteral("area_feed_search_btn"));
        area_feed_search_btn->setGeometry(QRect(310, 20, 80, 28));
        area_feed_edit = new QLineEdit(widget_5);
        area_feed_edit->setObjectName(QStringLiteral("area_feed_edit"));
        area_feed_edit->setGeometry(QRect(90, 20, 113, 28));
        area_feed_edit->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 71, 28));
        label_3->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        feeding_btn = new QPushButton(widget_5);
        feeding_btn->setObjectName(QStringLiteral("feeding_btn"));
        feeding_btn->setGeometry(QRect(400, 20, 80, 28));
        area3_combox = new QComboBox(widget_5);
        area3_combox->setObjectName(QStringLiteral("area3_combox"));
        area3_combox->setGeometry(QRect(220, 20, 80, 28));
        area3_combox->setMinimumSize(QSize(80, 28));
        area3_combox->setMaximumSize(QSize(80, 28));
        area3_combox->setStyleSheet(QLatin1String("color: rgb(171, 171, 171);\n"
"border-color: rgb(255, 255, 255);"));

        verticalLayout_4->addWidget(widget_5);

        area_feedstore_tableView = new QTableView(page_3);
        area_feedstore_tableView->setObjectName(QStringLiteral("area_feedstore_tableView"));

        verticalLayout_4->addWidget(area_feedstore_tableView);

        feeding_stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_4 = new QWidget(page_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(0, 60));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(70, 28));
        label_4->setMaximumSize(QSize(70, 28));
        label_4->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(label_4);

        startdateEdit = new QDateEdit(widget_4);
        startdateEdit->setObjectName(QStringLiteral("startdateEdit"));
        startdateEdit->setMinimumSize(QSize(0, 28));
        startdateEdit->setMaximumSize(QSize(100, 28));
        startdateEdit->setStyleSheet(QLatin1String("color: rgb(171, 171, 171);\n"
"border-color: rgb(255, 255, 255);\n"
"border-style: solid;\n"
"border-width: 1px;"));

        horizontalLayout_3->addWidget(startdateEdit);

        label_5 = new QLabel(widget_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(70, 28));
        label_5->setMaximumSize(QSize(70, 28));
        label_5->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(label_5);

        enddateEdit = new QDateEdit(widget_4);
        enddateEdit->setObjectName(QStringLiteral("enddateEdit"));
        enddateEdit->setMinimumSize(QSize(0, 28));
        enddateEdit->setMaximumSize(QSize(110, 28));
        enddateEdit->setStyleSheet(QLatin1String("color: rgb(171, 171, 171);\n"
"border-color: rgb(255, 255, 255);\n"
"border-style: solid;\n"
"border-width: 1px;"));

        horizontalLayout_3->addWidget(enddateEdit);

        area_combox = new QComboBox(widget_4);
        area_combox->setObjectName(QStringLiteral("area_combox"));
        area_combox->setMinimumSize(QSize(80, 28));
        area_combox->setMaximumSize(QSize(80, 28));
        area_combox->setStyleSheet(QLatin1String("color: rgb(171, 171, 171);\n"
"border-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(area_combox);

        area_item_combox = new QComboBox(widget_4);
        area_item_combox->setObjectName(QStringLiteral("area_item_combox"));
        area_item_combox->setMaximumSize(QSize(80, 28));
        area_item_combox->setStyleSheet(QLatin1String("color: rgb(171, 171, 171);\n"
"border-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(area_item_combox);

        detail_search_btn = new QPushButton(widget_4);
        detail_search_btn->setObjectName(QStringLiteral("detail_search_btn"));
        detail_search_btn->setMinimumSize(QSize(80, 28));
        detail_search_btn->setMaximumSize(QSize(80, 28));

        horizontalLayout_3->addWidget(detail_search_btn);


        verticalLayout_3->addWidget(widget_4);

        feeding_detail_tableView = new QTableView(page_2);
        feeding_detail_tableView->setObjectName(QStringLiteral("feeding_detail_tableView"));

        verticalLayout_3->addWidget(feeding_detail_tableView);

        feeding_stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(feeding_stackedWidget);


        verticalLayout->addWidget(widget);


        retranslateUi(FeedingWidget);

        QMetaObject::connectSlotsByName(FeedingWidget);
    } // setupUi

    void retranslateUi(QWidget *FeedingWidget)
    {
        FeedingWidget->setWindowTitle(QApplication::translate("FeedingWidget", "\345\226\202\346\226\231\347\256\241\347\220\206", Q_NULLPTR));
        label_2->setText(QApplication::translate("FeedingWidget", "\345\226\202\346\226\231\347\256\241\347\220\206", Q_NULLPTR));
        feedstore_min_btn->setText(QString());
        feedstore_max_restore_btn->setText(QString());
        feedstore_cose_btn->setText(QString());
        feeding_opt->setText(QApplication::translate("FeedingWidget", "\345\226\202\346\226\231", Q_NULLPTR));
        feeding_detail_opt->setText(QApplication::translate("FeedingWidget", "\345\226\202\346\226\231\346\230\216\347\273\206", Q_NULLPTR));
        label->setText(QApplication::translate("FeedingWidget", "TextLabel", Q_NULLPTR));
        area_feed_search_btn->setText(QString());
        label_3->setText(QApplication::translate("FeedingWidget", "\347\211\251\345\223\201\345\220\215\347\247\260\357\274\232", Q_NULLPTR));
        feeding_btn->setText(QString());
        label_4->setText(QApplication::translate("FeedingWidget", "\345\274\200\345\247\213\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("FeedingWidget", "\347\273\223\346\235\237\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        detail_search_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FeedingWidget: public Ui_FeedingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEEDINGWIDGET_H
