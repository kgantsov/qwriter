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

#ifndef FINDWIDGET_H
#define FINDWIDGET_H

#include <QtGui>

class FindWidget : public QWidget
{
    Q_OBJECT

public:
    FindWidget(QWidget *pard = 0);
    QLabel *findLabel;
    QLabel *replaceLabel;
    QLineEdit *findLText;
    QLineEdit *replaceText;
    QPushButton *findNextButton;
    QPushButton *findPrevButton;
    QPushButton *findCloseButton;
    QPushButton *replaceNextButton;
    QPushButton *replacePrevButton;
    QHBoxLayout *horBLayout;
    QVBoxLayout *vertBLayout;
    QCheckBox *caseCheckBox;
    QCheckBox *wholeWords;
signals:
    void findNext(const QString &text, QTextDocument::FindFlags findFlags = 0);
    void findPrev(const QString &text, QTextDocument::FindFlags findFlags = 0);
    void findCloseClick();
private slots:
    void findNextClicked();
    void findPrevClicked();
    void findCloseClicked();
    void enableFindButton(const QString &text);
    void enableReplaceButton(const QString &text);
    void enterSlot();
    void enterReplaceSlot();
};

#endif // FINDWIDGET_H
