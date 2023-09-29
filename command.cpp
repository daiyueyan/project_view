#include <command.h>
#include <QDebug>

addCommand::addCommand(int *value, QUndoCommand *parent)
{
    /* 使用 Q_UNUSED,避免未使用的数据类型 */
    Q_UNUSED(parent);
    /* undoView 显示的操作信息 */
    setText("进行了加1操作");
    /* value 的地址赋值给 new_count */
    new_count = value;
    /* 让构造函数传过来的*new_count 的值赋值给 old_count */
    old_count = *new_count;
}

addCommand::~addCommand()
{

}
/* 执行 stack push 时或者重做操作时会自动调用 */
void addCommand::redo()
{
    /* 重新赋值给 new_count */
    *new_count = old_count;
    qDebug()<<"redo: "<< *new_count<<endl;
}
/* 回撤操作时执行 */
void addCommand::undo()
{
    /* 回撤操作每次应减一 */
    (*new_count)--;
    qDebug()<<"undo: "<< *new_count<<endl;
}
