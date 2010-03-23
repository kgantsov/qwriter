/***************************************************************************
 *   Copyright (C) 2009 by Gancov Kostya                                   *
 *   kossne@mail.ru                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QtGui>

class FindDialog : public QDialog
{
Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    void setSearchedText(const QString &searchedText);
private:
    QLabel *findLabel;
    QLabel *replaceLabel;
    QLineEdit *findLText;
    QLineEdit *replaceLText;
    QPushButton *findButton;
    QPushButton *replaceButton;
    QPushButton *cancelButton;
    QHBoxLayout *horBLayout;
    QVBoxLayout *vertBLayout;
    QCheckBox *caseCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QCheckBox *backwardCheckBox;
    QCheckBox *regexpCheckBox;
private slots:
    void find();
    void replace();
signals:
    void findFirst(const QString &expr, bool re, bool cs, bool wo, bool wrap,
                   bool forward = true, int line = -1, int index = -1, bool show = true);
    void replace(const QString &text);
};

#endif // FINDDIALOG_H
