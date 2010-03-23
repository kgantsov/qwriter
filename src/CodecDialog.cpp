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


#include "CodecDialog.h"

CodecDialog::CodecDialog(QWidget *pard) : QDialog(pard)
{
    cbo = new QComboBox;
    cbo->clear();
    QObject::connect(cbo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setCodec(QString)));
    ok = new QPushButton(tr("&OK"));
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(cbo, 0, 0);
    mainLayout->addWidget(ok, 0, 1);
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(close()));
    setLayout(mainLayout);
    setFixedSize(230,50);
    this->setWindowTitle(tr("Change encoding"));
}

void CodecDialog::setCodecList( const QStringList &newLst)
{
    lst = newLst;
    cbo->insertItems(0, lst);
}

void CodecDialog::closeEvent(QCloseEvent *event)
{

}

void CodecDialog::setCodec(const QString selectedCodec)
{
    this->curentCodec = selectedCodec;
}

void CodecDialog::setCodecCombo(const QString &codec)
{
    this->curentCodec = codec;
    cbo->setCurrentIndex(cbo->findText(this->curentCodec));
}
