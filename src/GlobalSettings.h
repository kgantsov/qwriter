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

#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QtGui>
#include <QDialog>
#include <QTabWidget>
#include <QComboBox>

class GlobalSettings : public QDialog
{
    Q_OBJECT
public:
    GlobalSettings(QWidget *pard = 0);
    ~GlobalSettings();
    QComboBox *languageComboBox;
    QString languageApp;
    QComboBox *tabPositionComboBox;
    QCheckBox *toolbarVis;
    QCheckBox *statbarVis;
    QCheckBox *WrapText;
    QVBoxLayout *mainLayout;
    QSpinBox *tabSpacesSpinBox;
    QCheckBox *highlightCurLine;
    QCheckBox *highlightCurRow;
    QCheckBox *displayRightMargin;
    QSpinBox *rightMarginSpinBox;
    QTabWidget *tabSetting;
    QCheckBox *numberBlockCheckBox;
    QLabel *rightMarginLabel;
public slots:
    void lang(int langIndex);
    void rightMargVisible(int state);
private:
    void resizeEvent(QResizeEvent *event);
    //QStringList lstHeader;
};

#endif // GLOBALSETTINGS_H
