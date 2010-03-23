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

#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    plbl = new QLabel(tr("<h3 align='center'>QWriter v0.1.9</h3> <p>Copyright &copy; 2009 - 2010 Gancov Konstantin</p><p align='left'>e-mail: kossne@mail.ru <br>ICQ: 365978665</p>"), this);
    plbl->setWordWrap(true);
    mainLayout = new QGridLayout;
    //plbl->setFixedSize(300,300);
    QGroupBox *groupBox = new QGroupBox(tr("GNU General Public Licence"));
    QLabel *GnuGpl = new QLabel(tr("This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version. \n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details. \n\nYou should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA."));
    GnuGpl->setWordWrap(true);
    GnuGpl->setAlignment(Qt::AlignLeft);
    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(GnuGpl);
    groupBox->setLayout(groupBoxLayout);

    QPushButton *okButton = new QPushButton(tr("OK"));
    okButton->setMaximumWidth(60);
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
    mainLayout->addWidget(plbl, 0, 0);
    mainLayout->addWidget(groupBox, 1, 0);
    mainLayout->addWidget(okButton, 2, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    this->setWindowTitle(tr("About"));
    setFixedWidth(400);
}
