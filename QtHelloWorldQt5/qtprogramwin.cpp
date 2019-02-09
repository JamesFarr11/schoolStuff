#include "qtprogramwin.h"
#include "ui_qtprogramwin.h"
#include <qkeyevent>
#include "qshortcut.h"

double firstNum;
bool secondNumberInput = false;

QtProgramWin::QtProgramWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtProgramWin)
{
    ui->setupUi(this);
	connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
	connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

	connect(ui->pushButton_plusminus, SIGNAL(released()), this, SLOT(unary_operation()));
	connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation()));

	connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operations()));
	connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operations()));
	connect(ui->pushButton_times, SIGNAL(released()), this, SLOT(binary_operations()));
	connect(ui->pushButton_division, SIGNAL(released()), this, SLOT(binary_operations()));

	connect(ui->pushButton_equals, SIGNAL(released()), this, SLOT(equals_released()));

	connect(ui->pushButton_clear, SIGNAL(released()), this, SLOT(clear_released()));

	ui->pushButton_plus->setCheckable(true);
	ui->pushButton_minus->setCheckable(true);
	ui->pushButton_times->setCheckable(true);
	ui->pushButton_division->setCheckable(true);
}

QtProgramWin::~QtProgramWin()
{
    delete ui;
}

void QtProgramWin::digit_pressed()
{
	QPushButton * button = (QPushButton*)sender();
	double labNumber;
	QString newLabel;

	if ((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() || ui->pushButton_minus->isChecked() || ui->pushButton_division->isChecked())
		&& (!secondNumberInput))
	{
		labNumber = button->text().toDouble();
		secondNumberInput = true;
		newLabel = QString::number(labNumber, 'g', 15);
	}
	else
	{
		if (ui->label->text().contains('.') && button->text() == "0")
		{
			newLabel = ui->label->text() + button->text();
		}
		else
		{
			labNumber = (ui->label->text() + button->text()).toDouble();
			newLabel = QString::number(labNumber, 'g', 15);
		}
	}
	
	
	ui->label->setText(newLabel);
}

void QtProgramWin::on_pushButton_period_released()
{
	ui->label->setText(ui->label->text() + ".");
}

void QtProgramWin::unary_operation()
{
	QPushButton * button = (QPushButton*)sender();
	double labNumber;
	QString newLabel;
	if (button->text() == "+/-")
	{
		labNumber = ui->label->text().toDouble();
		labNumber = labNumber * -1;
		newLabel = QString::number(labNumber, 'g', 15);
		ui->label->setText(newLabel);
	}

	if (button->text() == "%")
	{
		labNumber = ui->label->text().toDouble();
		labNumber = labNumber * 0.01;
		newLabel = QString::number(labNumber, 'g', 15);
		ui->label->setText(newLabel);
	}
}

void QtProgramWin::clear_released()
{
	ui->pushButton_plus->setChecked(false);
	ui->pushButton_minus->setChecked(false);
	ui->pushButton_times->setChecked(false);
	ui->pushButton_division->setChecked(false);

	secondNumberInput = false;
	ui->label->setText("0");
}

void QtProgramWin::equals_released()
{
	double labNumber;
	double secondNum;
	QString newLabel;

	secondNum = ui->label->text().toDouble();

	if (ui->pushButton_plus->isChecked())
	{
		labNumber = firstNum + secondNum;
		newLabel = QString::number(labNumber, 'g', 15);
		ui->label->setText(newLabel);
		ui->pushButton_plus->setChecked(false);
	}
	else if (ui->pushButton_minus->isChecked())
	{
		labNumber = firstNum - secondNum;
		newLabel = QString::number(labNumber, 'g', 15);
		ui->label->setText(newLabel);
		ui->pushButton_minus->setChecked(false);
	}
	else if (ui->pushButton_times->isChecked())
	{
		labNumber = firstNum * secondNum;
		newLabel = QString::number(labNumber, 'g', 15);
		ui->label->setText(newLabel);
		ui->pushButton_times->setChecked(false);
	}
	else if (ui->pushButton_division->isChecked())
	{
		labNumber = firstNum / secondNum;
		newLabel = QString::number(labNumber, 'g', 15);
		ui->label->setText(newLabel);
		ui->pushButton_division->setChecked(false);
	}
	secondNumberInput = false;
}

void QtProgramWin::binary_operations()
{
	QPushButton * button = (QPushButton*)sender();
	firstNum = ui->label->text().toDouble();


	button->setChecked(true);
}

void QtProgramWin::keyPressEvent(QKeyEvent * i)
{
	QString text = ui->label->text();
	text += int(i->key());
	ui->label->setText(text);
}
