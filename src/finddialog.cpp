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

#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent) : QDialog(parent)
{
    findLabel = new QLabel(tr("Find"));
    replaceLabel = new QLabel(tr("Replace"));

    findLText = new QLineEdit;
    findLabel->setBuddy(findLText);
    replaceLText = new QLineEdit;
    replaceLabel->setBuddy(replaceLText);

    findButton = new QPushButton(tr("Find"), this);
    connect(findButton, SIGNAL(clicked()), this, SLOT(find()));
    replaceButton = new QPushButton(tr("Replace"), this);
    connect(replaceButton, SIGNAL(clicked()), this, SLOT(replace()));
    cancelButton = new QPushButton(tr("Cancel"), this);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    caseCheckBox = new QCheckBox(this);
    caseCheckBox->setText(tr("Case sensitivity"));
    wholeWordsCheckBox = new QCheckBox(this);
    wholeWordsCheckBox->setText(tr("Whole words"));
    backwardCheckBox = new QCheckBox(this);
    backwardCheckBox->setText(tr("Backward"));
    regexpCheckBox = new QCheckBox(this);
    regexpCheckBox->setText(tr("Regular expressoin"));

    /*
    QHBoxLayout *findLayout = new QHBoxLayout;
    findLayout->addWidget(findLabel);
    findLayout->addWidget(findLText);

    QHBoxLayout *replaceLayout = new QHBoxLayout;
    replaceLayout->addWidget(replaceLabel);
    replaceLayout->addWidget(replaceLText);
    //*/

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(findLabel, 0, 0);
    gridLayout->addWidget(findLText, 0, 1);
    gridLayout->addWidget(replaceLabel, 1, 0);
    gridLayout->addWidget(replaceLText, 1, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(replaceButton);
    buttonsLayout->addWidget(findButton);

    vertBLayout = new QVBoxLayout;
    //vertBLayout->addLayout(findLayout);
    //vertBLayout->addLayout(replaceLayout);
    vertBLayout->addLayout(gridLayout);
    vertBLayout->addWidget(caseCheckBox);
    vertBLayout->addWidget(wholeWordsCheckBox);
    vertBLayout->addWidget(backwardCheckBox);
    vertBLayout->addWidget(regexpCheckBox);
    vertBLayout->addLayout(buttonsLayout);

    setLayout(vertBLayout);

    findLText->setFocus();
}

void FindDialog::setSearchedText(const QString &searchedText) {
    findLText->setText(searchedText);
    findLText->setFocus();
}

void FindDialog::find() {
    emit findFirst(findLText->text(), regexpCheckBox->isChecked(), caseCheckBox->isChecked(),
                   wholeWordsCheckBox->isChecked(), false, !backwardCheckBox->isChecked(), -1, -1, true);
}

void FindDialog::replace() {
    find();
    emit replace(replaceLText->text());
}
