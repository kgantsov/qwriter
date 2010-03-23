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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QMessageBox>
#include <QFont>
#include <QColor>
#include <QSettings>

class Highlighter : public QSyntaxHighlighter
{	
Q_OBJECT
public:
        Highlighter(const QString &style = 0, QTextDocument *parent = 0);
        ~Highlighter();
protected:
        void highlightBlock(const QString &text);
private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightRules;
        QRegExp commentStartExpression;
        QRegExp commentEndExpression;
        QColor color;
        QTextCharFormat findFormat;
        QTextCharFormat phpOpenCloseFormat;
        QString findText;
        QTextCharFormat digitFormat;
        QTextCharFormat commentFormat;
        QTextCharFormat commentMultFormat;
        QTextCharFormat fFormat;
        QTextCharFormat keywordsFormat;
        QTextCharFormat typeFormat;
        QTextCharFormat qFormat;
        QTextCharFormat preFormat;
        QTextCharFormat qouteFormat;
        QTextCharFormat phpVariableFormat;
        QTextCharFormat phpFormat;
        QTextCharFormat emptyFormat;
        QString styleHighlighter;
        void readSettings();
        void writeSettings();
        void initHighlighter();
};
#endif
