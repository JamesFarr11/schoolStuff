#ifndef QTPROGRAMWIN_H
#define QTPROGRAMWIN_H

#include <QMainWindow>

namespace Ui {
class QtProgramWin;
}

class QtProgramWin : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QtProgramWin(QWidget *parent = 0);
    ~QtProgramWin();
    
private:
    Ui::QtProgramWin *ui;

private slots:
	void digit_pressed();
	void on_pushButton_period_released();
	void unary_operation();
	void clear_released();
	void equals_released();
	void binary_operations();

protected:
	void keyPressEvent(QKeyEvent *i);

};

#endif // QTPROGRAMWIN_H
