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

#include "GoToLineDialog.h"

GoToLineDialog::GoToLineDialog(QWidget *parent, int curLine, int lineCount) : QDialog(parent)
{
    line = -1;
    linCount = lineCount;
    curPosTitle = new QLabel(tr("Curent line"));
    curPosValue = new QLabel(tr("%1").arg(curLine));
    goToLineTitle = new QLabel(tr("Go to line:"));
    goToLineValue = new QLineEdit;
    QRegExp intValidator("\\d+");
    goToLineValue->setValidator(new QRegExpValidator(intValidator, this));
    connect(goToLineValue, SIGNAL(textChanged(QString)), this, SLOT(txtChanged(QString)));
    maxPosTitle = new QLabel(tr("Amount line:"));
    maxPosValue = new QLabel(tr("%1").arg(linCount));
    goToLineButton = new QPushButton(tr("Go"));
    connect(goToLineButton, SIGNAL(clicked()), this, SLOT(goToLineButClick()));
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(curPosTitle, 0, 0);
    gridLayout->addWidget(curPosValue, 0, 1);
    gridLayout->addWidget(goToLineTitle, 1, 0);
    gridLayout->addWidget(goToLineValue, 1, 1);
    gridLayout->addWidget(maxPosTitle, 2, 0);
    gridLayout->addWidget(maxPosValue, 2, 1);
    gridLayout->addWidget(goToLineButton, 3, 0, 1, 0);
    setLayout(gridLayout);
    setWindowTitle(tr("Go to line"));
}

void GoToLineDialog::txtChanged(const QString & text)
{
    goToLineButton->setEnabled((linCount >= text.toInt()));
}

void GoToLineDialog::goToLineButClick()
{
    line = goToLineValue->text().toInt();
    close();
}
