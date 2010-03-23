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

#ifndef GOTOLINEDIALOG_H
#define GOTOLINEDIALOG_H
#include <QtGui>
#include <QDialog>

class GoToLineDialog : public QDialog
{
Q_OBJECT
public:
    GoToLineDialog(QWidget *parent = 0, int curLine = 0, int lineCount = 0);
    int toLine(){return line;}
private:
    QLabel *curPosTitle;
    QLabel *curPosValue;
    QLabel *goToLineTitle;
    QLineEdit *goToLineValue;
    QLabel *maxPosTitle;
    QLabel *maxPosValue;
    QPushButton *goToLineButton;
    QGridLayout *gridLayout;
    int linCount;
    int line;
public slots:
    void txtChanged(const QString &text);
    void goToLineButClick();
};

#endif // GOTOLINEDIALOG_H
