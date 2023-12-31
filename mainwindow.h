#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QTreeView>
#include <QTableView>
#include <QColumnView>
#include <QUndoView>
#include <QUndoStack>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <command.h>
#include <QObject>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QListView *listView;
    /* 字符串模型对象 */
    QStringListModel *stringListModel;

    QTreeView *treeView;

    QTableView *tableView;

    QColumnView *columnView;
    /* 水平布局 */
    QHBoxLayout *hLayout;
    /* 垂直布局 */
    QVBoxLayout *vLayout;
    /* 用于容纳 hLayout 布局 */
    QWidget *mainWidget;
    /* 容器作用 QWidget,用于容纳标签与按钮 */
    QWidget *widget;
    /* 存放 QUndoCommand 命令的栈 */
    QUndoStack *undoStack;
    /* 历史记录面板 */
    QUndoView *undoView;
    /* 用于显示计算结果 */
    QLabel *label;
    /* 按钮 */
    QPushButton *pushButton;
    /* 计算结果 */
    int count;

private slots:
    void pushButtonCicked();
    void showCountValue(int);
};
#endif // MAINWINDOW_H
