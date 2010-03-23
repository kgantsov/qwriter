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

#include "Highlighter.h"

Highlighter::Highlighter(const QString &style, QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    styleHighlighter = style;
    this->readSettings();
    this->initHighlighter();
}

Highlighter::~Highlighter()
{
    this->writeSettings();
}
void Highlighter::readSettings()
{
        QSettings settings("kossinc", "koss");
        settings.beginGroup("highlighter");
        color.setRed(settings.value("digitFormat_ForRed", "255").toInt());
        color.setGreen(settings.value("digitFormat_ForGreen", "162").toInt());
        color.setBlue(settings.value("digitFormat_ForBlue", "0").toInt());
        digitFormat.setForeground(color);
        settings.endGroup();
}

void Highlighter::writeSettings()
{
        QSettings settings("kossinc", "koss");
        settings.beginGroup("highlighter");
        color = digitFormat.foreground().color();
        settings.setValue("digitFormat_ForRed", color.red());
        settings.setValue("digitFormat_ForGreen", color.green());
        settings.setValue("digitFormat_ForBlue", color.blue());
        settings.endGroup();
}

void Highlighter::initHighlighter()
{

    HighlightingRule rule;
    if (styleHighlighter == "cpp") {
        digitFormat.setFontWeight(QFont::Normal);
        keywordsFormat.setForeground(Qt::blue);
        keywordsFormat.setFontWeight(QFont::Bold);
        typeFormat.setForeground(QColor("#8000ff"));
        typeFormat.setFontWeight(QFont::Normal);
        qFormat.setForeground(Qt::darkMagenta);
        qFormat.setFontWeight(QFont::Bold);
        preFormat.setForeground(Qt::darkGreen);
        preFormat.setFontWeight(QFont::Normal);
        qouteFormat.setForeground(Qt::darkGray);
        qouteFormat.setFontWeight(QFont::Normal);
        commentFormat.setForeground(Qt::darkGreen);
        commentFormat.setFontWeight(QFont::Normal);
        commentMultFormat.setForeground(Qt::darkGreen);
        commentMultFormat.setFontWeight(QFont::Normal);
        phpVariableFormat.setForeground(Qt::black);
        phpVariableFormat.setFontWeight(QFont::Normal);
        fFormat.setBackground(Qt::green);
        fFormat.setFontWeight(QFont::Normal);
        //findFormat.setBackground(Qt::green);

        rule.pattern = QRegExp("[0-9]+");
        rule.format = digitFormat;
        highlightRules.append(rule);

        rule.pattern = QRegExp("\\bQ[A-Za-z0-9]+\\b");
        rule.format = qFormat;
        highlightRules.append(rule);

        rule.pattern = QRegExp("\"[^\"]*\"");
        rule.format = qouteFormat;
        highlightRules.append(rule);
        rule.pattern = QRegExp("\'[^\']*\'");
        rule.format = qouteFormat;
        highlightRules.append(rule);

        QStringList keywordsPatterns;
        keywordsPatterns<<QLatin1String("\\btrue\\b")<<QLatin1String("\\bfalse\\b")<<QLatin1String("\\bnamespace\\b")<<QLatin1String("\\boperator\\b")<<QLatin1String("\\btypedef\\b")<<QLatin1String("\\bthrow\\b")<<QLatin1String("\\bthrows\\b")<<QLatin1String("\\btry\\b")<<QLatin1String("\\bfinally\\b")<<QLatin1String("\\bexport\\b")<<QLatin1String("\\bcontinue\\b")<<QLatin1String("\\bcatch\\b")<<QLatin1String("\\bcase\\b")<<QLatin1String("\\bnew\\b")<<QLatin1String("\\bfor\\b")<<QLatin1String("\\bforeach\\b")<<QLatin1String("\\bif\\b")<<QLatin1String("\\belse\\b")<<QLatin1String("\\bwhile\\b")<<QLatin1String("\\bdo\\b")<<QLatin1String("\\breturn\\b")<<QLatin1String("\\bbreak\\b")<<QLatin1String("\\bthis\\b")<<QLatin1String("\\bfunction\\b");
        foreach (QString pattern, keywordsPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = keywordsFormat;
            highlightRules.append(rule);
        }
        QStringList typePatterns;
        typePatterns<<QLatin1String("\\bchar\\b")<<QLatin1String("\\bclass\\b")<<QLatin1String("\\bconst\\b")<<QLatin1String("\\bdouble\\b")<<QLatin1String("\\benum\\b")<<QLatin1String("\\bexplicit\\b")<<QLatin1String("\\bfriend\\b")<<QLatin1String("\\binline\\b")<<QLatin1String("\\bfloat\\b")<<QLatin1String("\\bint\\b")<<QLatin1String("\\benum\\b")<<QLatin1String("\\blong\\b")<<QLatin1String("\\bprivate\\b")<<QLatin1String("\\bprotected\\b")<<QLatin1String("\\bbyte\\b")<<QLatin1String("\\bpublic\\b")<<QLatin1String("\\bshort\\b")<<QLatin1String("\\bsignals\\b")<<QLatin1String("\\bsigned\\b")<<QLatin1String("\\bslots\\b")<<QLatin1String("\\bstatic\\b")<<QLatin1String("\\bstruct\\b")<<QLatin1String("\\btemplate\\b")<<QLatin1String("\\btypename\\b")<<QLatin1String("\\bunion\\b")<<QLatin1String("\\bunsigned\\b")<<QLatin1String("\\bvirtual\\b")<<QLatin1String("\\bvoid\\b")<<QLatin1String("\\bvolatile\\b");
        foreach (QString pattern, typePatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = typeFormat;
            highlightRules.append(rule);
        }

        rule.pattern = QRegExp("#[a-zA-Z0-9_]+");
        rule.format = preFormat;
        highlightRules.append(rule);

        rule.pattern = QRegExp("//[^\n]*");
        rule.format = commentFormat;
        highlightRules.append(rule);

        commentStartExpression = QRegExp("/\\*");
        commentEndExpression = QRegExp("\\*/");
    } else {
        if ((styleHighlighter == "php") || (styleHighlighter == "html")) {
            digitFormat.setFontWeight(QFont::Normal);
            keywordsFormat.setForeground(Qt::blue);
            keywordsFormat.setFontWeight(QFont::Bold);
            typeFormat.setForeground(QColor("#8000ff"));
            typeFormat.setFontWeight(QFont::Normal);
            qFormat.setForeground(Qt::darkMagenta);
            qFormat.setFontWeight(QFont::Bold);
            preFormat.setForeground(Qt::darkGreen);
            preFormat.setFontWeight(QFont::Normal);
            qouteFormat.setForeground(Qt::darkGray);
            qouteFormat.setFontWeight(QFont::Normal);
            commentFormat.setForeground(Qt::darkGreen);
            commentFormat.setFontWeight(QFont::Normal);
            commentMultFormat.setForeground(Qt::darkGreen);
            commentMultFormat.setFontWeight(QFont::Normal);
            phpVariableFormat.setForeground(QColor("#000080"));
            phpVariableFormat.setFontWeight(QFont::Normal);
            phpFormat.setForeground(Qt::blue);
            phpFormat.setFontWeight(QFont::Bold);
            fFormat.setBackground(Qt::green);
            fFormat.setFontWeight(QFont::Normal);
            findFormat.setForeground(Qt::blue);
            phpOpenCloseFormat.setForeground(Qt::red);

            rule.pattern = QRegExp("\\d+");
            rule.format = digitFormat;
            highlightRules.append(rule);

            rule.pattern = QRegExp("\\$[A-Za-z0-9_]+");
            rule.format = phpVariableFormat;
            highlightRules.append(rule);

            QStringList phpPatterns;
            phpPatterns<<QLatin1String("\\becho\\b")<<QLatin1String("\\bas\\b")<<QLatin1String("\\bextends\\b")<<QLatin1String("\\bisset\\b")<<QLatin1String("\\bunset\\b");
            foreach (QString pattern, phpPatterns) {
                rule.pattern = QRegExp(pattern);
                rule.format = phpFormat;
                highlightRules.append(rule);
            }

            QRegExp regexp("<[\\W\\w]*>");
            regexp.setMinimal(true);
            regexp.setPatternSyntax(QRegExp::RegExp2);
            rule.pattern = regexp;
            rule.format  = findFormat;
            highlightRules.append(rule);

            QRegExp regexp1("(<[\?](php)?)|([\?]>)");
            regexp1.setMinimal(false);
            regexp1.setPatternSyntax(QRegExp::RegExp2);
            rule.pattern = regexp1;
            rule.format  = phpOpenCloseFormat;
            highlightRules.append(rule);

            QStringList keywordsPatterns;
            keywordsPatterns<<QLatin1String("\\btrue\\b")<<QLatin1String("\\bfalse\\b")<<QLatin1String("\\bnamespace\\b")<<QLatin1String("\\boperator\\b")<<QLatin1String("\\btypedef\\b")<<QLatin1String("\\bthrow\\b")<<QLatin1String("\\bthrows\\b")<<QLatin1String("\\btry\\b")<<QLatin1String("\\bfinally\\b")<<QLatin1String("\\bexport\\b")<<QLatin1String("\\bcontinue\\b")<<QLatin1String("\\bcatch\\b")<<QLatin1String("\\bcase\\b")<<QLatin1String("\\bnew\\b")<<QLatin1String("\\bfor\\b")<<QLatin1String("\\bforeach\\b")<<QLatin1String("\\bif\\b")<<QLatin1String("\\belse\\b")<<QLatin1String("\\bwhile\\b")<<QLatin1String("\\bdo\\b")<<QLatin1String("\\breturn\\b")<<QLatin1String("\\bbreak\\b")<<QLatin1String("\\bthis\\b")<<QLatin1String("\\bfunction\\b");
            foreach (QString pattern, keywordsPatterns) {
                rule.pattern = QRegExp(pattern);
                rule.format = keywordsFormat;
                highlightRules.append(rule);
            }

            QStringList typePatterns;
            typePatterns<<QLatin1String("\\bchar\\b")<<QLatin1String("\\bclass\\b")<<QLatin1String("\\bconst\\b")<<QLatin1String("\\bdouble\\b")<<QLatin1String("\\benum\\b")<<QLatin1String("\\bexplicit\\b")<<QLatin1String("\\bfriend\\b")<<QLatin1String("\\binline\\b")<<QLatin1String("\\bfloat\\b")<<QLatin1String("\\bint\\b")<<QLatin1String("\\benum\\b")<<QLatin1String("\\blong\\b")<<QLatin1String("\\bprivate\\b")<<QLatin1String("\\bprotected\\b")<<QLatin1String("\\bbyte\\b")<<QLatin1String("\\bpublic\\b")<<QLatin1String("\\bshort\\b")<<QLatin1String("\\bsignals\\b")<<QLatin1String("\\bsigned\\b")<<QLatin1String("\\bslots\\b")<<QLatin1String("\\bstatic\\b")<<QLatin1String("\\bstruct\\b")<<QLatin1String("\\btemplate\\b")<<QLatin1String("\\btypename\\b")<<QLatin1String("\\bunion\\b")<<QLatin1String("\\bunsigned\\b")<<QLatin1String("\\bvirtual\\b")<<QLatin1String("\\bvoid\\b")<<QLatin1String("\\bvolatile\\b");
            foreach (QString pattern, typePatterns) {
                rule.pattern = QRegExp(pattern);
                rule.format = typeFormat;
                highlightRules.append(rule);
            }

            rule.pattern = QRegExp("#[a-zA-Z0-9_]+");
            rule.format = preFormat;
            highlightRules.append(rule);

            rule.pattern = QRegExp("\"[^\"]*\"");
            rule.format = qouteFormat;
            highlightRules.append(rule);

            rule.pattern = QRegExp("\'[^\']*\'");
            rule.format = qouteFormat;
            highlightRules.append(rule);

            rule.pattern = QRegExp("//[^\n]*");
            rule.format = commentFormat;
            highlightRules.append(rule);

            commentStartExpression = QRegExp("/\\*");
            commentEndExpression = QRegExp("\\*/");

        }
    }
}

void Highlighter::highlightBlock(const QString& str)
{
        foreach (HighlightingRule rule, highlightRules) {
            QRegExp expression(rule.pattern);
            int index = str.indexOf(expression);
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = str.indexOf(expression, index + length);
            }
        }


        setCurrentBlockState(0);
        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = str.indexOf(commentStartExpression);

        while (startIndex >= 0) {
            int endIndex = str.indexOf(commentEndExpression, startIndex);
            int commentLength;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = str.length() - startIndex;
            }
            else
            {
                commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
            }
            setFormat(startIndex, commentLength, commentMultFormat);
            startIndex = str.indexOf(commentStartExpression, startIndex + commentLength);
        }
}
