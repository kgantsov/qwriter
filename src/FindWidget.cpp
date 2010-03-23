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

#include "FindWidget.h"
#define MAX_H_SIZE_BUT 23

FindWidget::FindWidget(QWidget *pard) : QWidget(pard)
{
    //QGridLayout *grdLayout = new QGridLayout;
    findLabel = new QLabel;
    findLabel->setText(tr("Find"));
    replaceLabel = new QLabel;
    replaceLabel->setText(tr("Replace"));
    findLText = new QLineEdit;

    findNextButton = new QPushButton;
    findNextButton->setIcon(QIcon(":/images/Arrow-Left.png"));
    findNextButton->setEnabled(false);
    findNextButton->setMaximumHeight(MAX_H_SIZE_BUT);

    findPrevButton = new QPushButton;
    findPrevButton->setIcon(QIcon(":/images/Arrow-Right.png"));
    findPrevButton->setEnabled(false);
    findPrevButton->setMaximumHeight(MAX_H_SIZE_BUT);

    caseCheckBox = new QCheckBox(this);
    caseCheckBox->setText(tr("Case"));

    wholeWords = new QCheckBox(this);
    wholeWords->setText(tr("Whole word only"));

    findCloseButton = new QPushButton;
    findCloseButton->setIcon(QIcon(":/images/Symbol-Delete.png"));
    findCloseButton->setMaximumHeight(MAX_H_SIZE_BUT);
    findLabel->setBuddy(findLText);

    replaceText = new QLineEdit;
    replaceNextButton = new QPushButton;
    replaceNextButton->setIcon(QIcon(":/images/Arrow-Left.png"));
    replaceNextButton->setMaximumHeight(MAX_H_SIZE_BUT);
    replaceNextButton->setEnabled(false);
    replacePrevButton = new QPushButton;
    replacePrevButton->setIcon(QIcon(":/images/Arrow-Right.png"));
    replacePrevButton->setMaximumHeight(MAX_H_SIZE_BUT);
    replacePrevButton->setEnabled(false);

    horBLayout = new QHBoxLayout;
    vertBLayout = new QVBoxLayout;
    horBLayout->addWidget(findLabel);
    horBLayout->addWidget(findLText);
    horBLayout->addWidget(findPrevButton);
    horBLayout->addWidget(findNextButton);

    vertBLayout->addWidget(caseCheckBox);
    vertBLayout->addWidget(wholeWords);

    horBLayout->addLayout(vertBLayout);
    horBLayout->addWidget(replaceLabel);
    horBLayout->addWidget(replaceText);
    horBLayout->addWidget(replacePrevButton);
    horBLayout->addWidget(replaceNextButton);
    horBLayout->addStretch(2);
    horBLayout->addWidget(findCloseButton);

    setLayout(horBLayout);
    connect(findLText, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(findLText, SIGNAL(returnPressed()), this, SLOT(enterSlot()));
    connect(findNextButton, SIGNAL(clicked()), this, SLOT(findNextClicked()));
    connect(findPrevButton, SIGNAL(clicked()), this, SLOT(findPrevClicked()));
    connect(findCloseButton, SIGNAL(clicked()), this, SLOT(findCloseClicked()));
    connect(replaceText, SIGNAL(textChanged(const QString &)), this, SLOT(enableReplaceButton(const QString &)));
    connect(replaceText, SIGNAL(returnPressed()), this, SLOT(enterReplaceSlot()));

    findNextButton->setAutoDefault(true);
    findNextButton->setDefault(true);
}

void FindWidget::findNextClicked()
{
    QString text = findLText->text();

    QTextDocument::FindFlags find_flags;
    if (caseCheckBox->isChecked()) {
        find_flags |= QTextDocument::FindCaseSensitively;
    }


    if (wholeWords->isChecked()) {
        find_flags |= QTextDocument::FindWholeWords;;

    }
    emit findNext(text, find_flags);
}

void FindWidget::findPrevClicked()
{
    QString text = findLText->text();

    QTextDocument::FindFlags find_flags;
    find_flags |= QTextDocument::FindBackward;
    if (caseCheckBox->isChecked()) {
        find_flags |= QTextDocument::FindCaseSensitively;
    }


    if (wholeWords->isChecked()) {
        find_flags |= QTextDocument::FindWholeWords;;

    }
    emit findNext(text, find_flags);
}

void FindWidget::enableFindButton(const QString &text)
{
    findNextButton->setEnabled(!text.isEmpty());
    findPrevButton->setEnabled(!text.isEmpty());
}

void FindWidget::findCloseClicked()
{
    emit findCloseClick();
}

void FindWidget::enableReplaceButton(const QString &text)
{
    replaceNextButton->setEnabled(!text.isEmpty());
    replacePrevButton->setEnabled(!text.isEmpty());
}

void FindWidget::enterSlot()
{
    findNextButton->click();
}

void FindWidget::enterReplaceSlot()
{
    replaceNextButton->click();
}
