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

#include "GlobalSettings.h"

GlobalSettings::GlobalSettings(QWidget *pard) : QDialog(pard)
{
    tabSetting = new QTabWidget(this);
    QLabel *language = new QLabel(tr("Language interface"));
    languageComboBox = new QComboBox;
    languageComboBox->addItem(tr("English"));
    languageComboBox->addItem(tr("Russian"));
    connect(languageComboBox, SIGNAL(activated(int)), this, SLOT(lang(int)));

    QGroupBox *languageGroupBox = new QGroupBox(tr("Language"));

    QGroupBox *viewGroupBox = new QGroupBox(tr("View"));

    toolbarVis = new QCheckBox(tr("Tool bar"), this);
    statbarVis = new QCheckBox(tr("Status bar"), this);
    
    QGroupBox *tabPositionGroupBox = new QGroupBox(tr("Tab position"));
    QLabel *tabPositionLabel = new QLabel(tr("Tab position"));
    tabPositionComboBox = new QComboBox;
    tabPositionComboBox->addItem(tr("Top"));
    tabPositionComboBox->addItem(tr("Bottom"));
    tabPositionComboBox->addItem(tr("Left"));
    tabPositionComboBox->addItem(tr("Right"));

    QHBoxLayout *tabPositionHLayout = new QHBoxLayout;
    tabPositionHLayout->addWidget(tabPositionLabel);
    tabPositionHLayout->addWidget(tabPositionComboBox);
    tabPositionHLayout->addStretch(2);

    tabPositionGroupBox->setLayout(tabPositionHLayout);

    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(toolbarVis);
    viewLayout->addWidget(statbarVis);

    viewGroupBox->setLayout(viewLayout);


    QHBoxLayout *horBoxLayout = new QHBoxLayout;
    horBoxLayout->addWidget(language);
    horBoxLayout->addWidget(languageComboBox);
    horBoxLayout->addStretch(2);

    languageGroupBox->setLayout(horBoxLayout);

    mainLayout = new QVBoxLayout();

    mainLayout->addWidget(languageGroupBox);
    mainLayout->addWidget(viewGroupBox);
    mainLayout->addWidget(tabPositionGroupBox);
    mainLayout->addStretch(2);
    //gridLayout->addWidget(WrapText, 4, 0);

    QWidget *mainSett = new QWidget;
    mainSett->setLayout(mainLayout);
    tabSetting->addTab(mainSett, tr("General"));
    tabSetting->resize(width(),height());

    QWidget *editSett = new QWidget;

    QGroupBox *highlightGroupBox = new QGroupBox(tr("Hightlighting"));

    QGroupBox *numberBlockGroupBox = new QGroupBox(tr("Line Numbers"));

    QGroupBox *wrapGroupBox = new QGroupBox(tr("Text wrapping"));

    highlightCurLine = new QCheckBox(tr("Highlight curent line"), this);
    highlightCurRow = new QCheckBox(tr("Highlight curent row"), this);

    WrapText = new QCheckBox(tr("Enable text wrapping"), this);

    QVBoxLayout *highlightLayout = new QVBoxLayout;
    highlightLayout->addWidget(highlightCurLine);
    highlightLayout->addWidget(highlightCurRow);
    highlightGroupBox->setLayout(highlightLayout);

    QVBoxLayout *wrapLayout = new QVBoxLayout;
    wrapLayout->addWidget(WrapText);
    wrapGroupBox->setLayout(wrapLayout);

    numberBlockCheckBox = new QCheckBox(tr("Display line numbers"), this);

    QVBoxLayout *numberBlockLayout = new QVBoxLayout;
    numberBlockLayout->addWidget(numberBlockCheckBox);
    numberBlockGroupBox->setLayout(numberBlockLayout);

    QGroupBox *tabSpacesGroupBox = new QGroupBox(tr("Tab Stops"));
    QLabel *tabWidthLabel = new QLabel(tr("Tab width"), this);
    tabSpacesSpinBox = new QSpinBox;
    tabSpacesSpinBox->setRange(1, 10);
    tabSpacesSpinBox->setFixedWidth(50);

    QGroupBox *rightMarginGroupBox = new QGroupBox(tr("Right Margin"));
    displayRightMargin = new QCheckBox(tr("Display right margin"), this);
    connect(displayRightMargin, SIGNAL(stateChanged(int)), this, SLOT(rightMargVisible(int)));
    rightMarginLabel = new QLabel(tr("Right margin at column"), this);
    rightMarginSpinBox = new QSpinBox;
    rightMarginSpinBox->setRange(1, 160);
    QHBoxLayout *rightMarginHLayout = new QHBoxLayout;
    rightMarginHLayout->addWidget(rightMarginLabel);
    rightMarginHLayout->addWidget(rightMarginSpinBox);
    rightMarginHLayout->addStretch(2);

    QVBoxLayout *rightMarginLayout = new QVBoxLayout;
    rightMarginLayout->addWidget(displayRightMargin);
    rightMarginLayout->addLayout(rightMarginHLayout);
    rightMarginGroupBox->setLayout(rightMarginLayout);

    QHBoxLayout *tabWidthLayout = new QHBoxLayout;
    tabWidthLayout->addWidget(tabWidthLabel);
    tabWidthLayout->addWidget(tabSpacesSpinBox);
    tabWidthLayout->addStretch(2);

    QVBoxLayout *tabSpacesVBoxLayout = new QVBoxLayout;
    //tabSpacesVBoxLayout->addWidget(tabSpacesSpinBox);
    tabSpacesVBoxLayout->addLayout(tabWidthLayout);
    tabSpacesVBoxLayout->addStretch(2);
    tabSpacesGroupBox->setLayout(tabSpacesVBoxLayout);
    //QRadioButton *tabRadioButton = new QRadioButton(tr(""));

    QHBoxLayout *oneHBLayout = new QHBoxLayout;
    oneHBLayout->addWidget(numberBlockGroupBox);
    oneHBLayout->addWidget(wrapGroupBox);

    QVBoxLayout *mainVBoxLayout = new QVBoxLayout(editSett);
    mainVBoxLayout->addWidget(tabSpacesGroupBox);
    mainVBoxLayout->addWidget(highlightGroupBox);
    //mainVBoxLayout->addWidget(numberBlockGroupBox);
    //mainVBoxLayout->addWidget(wrapGroupBox);
    mainVBoxLayout->addLayout(oneHBLayout);
    mainVBoxLayout->addWidget(rightMarginGroupBox);
    mainVBoxLayout->addStretch(3);

    tabSetting->addTab(editSett, tr("Edit"));

    QWidget *fontAndColorsSett = new QWidget;
    QVBoxLayout *fontVBoxLayout = new QVBoxLayout(fontAndColorsSett);

    //fontVBoxLayout->addWidget();
    tabSetting->addTab(fontAndColorsSett, tr("Font & Colors"));

    //resize(400, 350);
    setFixedSize(420, 370);
    //setMinimumSize(300, 300);
    setWindowTitle(tr("QWriter"));
}

GlobalSettings::~GlobalSettings()
{

}

void GlobalSettings::rightMargVisible(int state) {
    rightMarginLabel->setEnabled((state == Qt::Checked) ? true : false);
    rightMarginSpinBox->setEnabled((state == Qt::Checked) ? true : false);
}

void GlobalSettings::lang(int langIndex)
{
    if (langIndex == 0) {
        languageApp = tr("EN");
    }
    if (langIndex == 1) {
        languageApp = tr("RU");
    }
}

void GlobalSettings::resizeEvent(QResizeEvent *event)
{
    QSize sz = event->size();
    tabSetting->resize(sz);
}
