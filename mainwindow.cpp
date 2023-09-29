#include "mainwindow.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include <QStandardItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 1000, 800);
    listView = new QListView(this);
    listView->setGeometry(0, 0, 200, 150);
    QStringList strList;
    strList<<"高一"<<"高二"<<"高三";
    /* 实例化，字符串模型 */
    stringListModel = new QStringListModel(strList);
    /* 向表中插入一段数据 */
    listView->setModel(stringListModel);
    /* 设置为视图为图标模式 */
    listView->setViewMode(QListView::IconMode);
    /* 设置为不可拖动 */
    listView->setDragEnabled(false);


    treeView = new QTreeView(this);
    treeView->setGeometry(200, 0, 200, 150);
    /* 构建 Model */
    QStandardItemModel *sdiModel = new QStandardItemModel(treeView);
    sdiModel->setHorizontalHeaderLabels(
                QStringList()<<QStringLiteral("标题")
                <<QStringLiteral("名称")
                );
    for(int i=0; i<5; i++)
    {
        QList<QStandardItem*>items1;
        QStandardItem* item1 =
                new QStandardItem(QString::number(i));
        QStandardItem* item2 =
                new QStandardItem(QStringLiteral("一级标题"));
        items1.append(item1);
        items1.append(item2);
        sdiModel->appendRow(items1);
        for (int j=0; j<5; j++)
        {
            QList<QStandardItem*> items2;
            QStandardItem* item3 =
                    new QStandardItem(QString::number(j));
            QStandardItem* item4 =
                    new QStandardItem(QStringLiteral("二级标题"));
            items2.append(item3);
            items2.append(item4);
            item1->appendRow(items2);
        }
        treeView->setModel(sdiModel);
    }


    tableView = new QTableView(this);
    tableView->setGeometry(400, 0, 200, 150);
    /* 显示网格线 */
    tableView->setShowGrid(true);
    QStandardItemModel* model = new QStandardItemModel();
    QStringList labels =
            QObject::tr("语文,数学,英语").simplified().split(",");
    /* 设置水平头标签 */
    model->setHorizontalHeaderLabels(labels);
    QStandardItem* item = 0;
    /* model 插入项内容 */
    for(int i=0; i<5; i++)
    {
        item = new QStandardItem("80");
        model->setItem(i, 0, item);
        item = new QStandardItem("90");
        model->setItem(i, 1, item);
        item = new QStandardItem("100");
        model->setItem(i, 2, item);
    }
    /* 将 model 设置给 tableView */
    tableView->setModel(model);
    /* 平均分列 */
    tableView->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);
    /* 平均分行 */
    tableView->verticalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);


    QStandardItemModel *model_columView = new QStandardItemModel;
    QStandardItem *province = new QStandardItem("广东省");
    QStandardItem *city1 = new QStandardItem("茂名市");
    QStandardItem *city2 = new QStandardItem("湛江市");
    province->appendRow(city1);
    province->appendRow(city2);
    QStandardItem *town1 = new QStandardItem("雷州市");
    QStandardItem *town2 = new QStandardItem("沈塘镇");
    city2->appendRow(town1);
    city2->appendRow(town2);
    columnView = new QColumnView;
    model_columView->appendRow(province);
    columnView->setModel(model_columView);
    columnView->setGeometry(600, 0, 200, 150);
//    setCentralWidget(columnView);

    /* 实例一个水平布局，用于左侧按钮区域与右侧历史记录面板 */
    hLayout = new QHBoxLayout();
    /* 实例一个水平布局，用于左侧标签与按钮 */
    vLayout = new QVBoxLayout();
    /* 主 Widget, 因为 MainWindow 自带一个布局，
    * 我们要新建一个 Widget 容纳新布局
    */
    mainWidget = new QWidget();
    /* 用于存放命令行栈 */
    undoStack = new QUndoStack(this);
    /* 用于容纳左侧标签与按钮布局 */
    widget = new QWidget();
    /* 历史记录面板实例化 */
    undoView = new QUndoView(undoStack);
    /* 实例一个按钮，用于加一操作 */
    pushButton = new QPushButton();
    /* 标签，用于显示计算结果 */
    label = new QLabel();
    /* 设置 widget 的大小 */
    widget->setMaximumSize(200, 200);
    /* 将两个 widget 添加到水平布局 */
    hLayout->addWidget(widget);
    hLayout->addWidget(undoView);
    count = 0;
    label->setText("计算结果： "+ QString::number(count));
    label->setAlignment(Qt::AlignCenter);
    /* 垂直左侧布局 */
    vLayout->addWidget(label);
    vLayout->addWidget(pushButton);
    /* 左侧布局控件的高度设置 */
    label->setMaximumHeight(60);
    /* 按钮文件设置 */
    pushButton->setMaximumHeight(60);
    pushButton->setText("加1");
    /* 设置 widget 的布局为 vLayout */
    widget->setLayout(vLayout);
    /* 将主窗体的布局设置为 hLayout */
    mainWidget->setLayout(hLayout);
    /* 设置 mainWidget 为主窗体的居中 widget */
    this->setCentralWidget(mainWidget);
    /* 信号槽连接，按钮点击，执行加一操作 */
    connect(pushButton, SIGNAL(clicked()),
            this, SLOT(pushButtonCicked()));
    /* 信号槽连接，历史记录项 index 发生变化，显示 count 大小 */
    connect(undoStack, SIGNAL(indexChanged(int)),
            this, SLOT(showCountValue(int)));
}
MainWindow::~MainWindow()
{
}

void MainWindow::pushButtonCicked()
{
    count++;
    int *value = &count;
    QUndoCommand *add = new addCommand(value);
    undoStack->push(add);
}

void MainWindow::showCountValue(int)
{
    label->setText("计算结果： " + QString::number(count));
}

