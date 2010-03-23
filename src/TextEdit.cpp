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
#include "TextEdit.h"

TextEdit::TextEdit(QWidget *pard)
        : QsciScintilla(pard)
{
    initSettings();
}

TextEdit::~TextEdit() {

}

void TextEdit::initSettings() {
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    this->setCaretLineBackgroundColor(QColor("#e4e4e4"));
    this->setCaretLineVisible(true);
    //lexer = new QsciLexerCPP(this);
    //this->setLexer(cpp);
    //this->markerAdd(0, 0);


    this->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    //this->setMarginType(1, QsciScintilla::NumberMargin);
    //this->setMarginMarkerMask(10, 10);
    //this->setMarginsBackgroundColor(QColor("#e4e4e4"));

    //this->setMarginLineNumbers(0, true);
    //this->setMarginWidth(0, QString("---------"));
    this->setMarginWidth(0, 42);
    this->setMarginSensitivity(1, true);
    
    //this->setProperty("marker","2");
    //this->setMarginMarkerMask(1, 1);
    this->markerDefine(QsciScintilla::RightTriangle);
    this->setMarkerBackgroundColor(QColor("#00ff00"));

    this->setIndentationGuides(true);
    this->setTabIndents(true);
    this->setBackspaceUnindents(false);
    this->setAutoIndent(true);
    this->setIndentationsUseTabs(false);
    this->zoomTo(0);
    this->setUtf8(true);
    this->selectAll(true);

    this->setAutoCompletionSource(QsciScintilla::AcsAll);
    //this->setAutoCompletionThreshold(3);
    this->setAutoCompletionCaseSensitivity(true);
    this->setAutoCompletionShowSingle(true);
    this->setAutoCompletionFillupsEnabled(true);

    #ifdef Q_WS_WIN
    defaultFont.setFamily("Courier New");
    defaultFont.setPointSize(10);
    defaultFont.setWeight(50);
    #endif

    #ifdef Q_WS_X11
    defaultFont.setFamily("Monospace");
    defaultFont.setPointSize(10);
    #endif


}

void TextEdit::setSyntaxHighlighter(QString style) {
    styleSyntax = style;

    if (styleSyntax == "none")
        lexer = 0;

    if (styleSyntax == "bash")
        lexer = new QsciLexerBash(this);

    if (styleSyntax == "batch")
        lexer = new QsciLexerBatch(this);

    if (styleSyntax == "cmake")
        lexer = new QsciLexerCMake(this);

    if (styleSyntax == "cpp")
        lexer = new QsciLexerCPP(this);

    if (styleSyntax == "csharp")
        lexer = new QsciLexerCSharp(this);

    if (styleSyntax == "css")
        lexer = new QsciLexerCSS(this);

    if (styleSyntax == "d")
        lexer = new QsciLexerBatch(this);

    if (styleSyntax == "diff")
        lexer = new QsciLexerDiff(this);

    if (styleSyntax == "fortran77")
        lexer = new QsciLexerFortran77(this);

    if (styleSyntax == "html")
        lexer = new QsciLexerHTML(this);

    if (styleSyntax == "java")
        lexer = new QsciLexerJava(this);

    if (styleSyntax == "javascript")
        lexer = new QsciLexerJavaScript(this);

    if (styleSyntax == "lua")
        lexer = new QsciLexerLua(this);

    if (styleSyntax == "pascal")
        lexer = new QsciLexerPascal(this);

    if (styleSyntax == "perl")
        lexer = new QsciLexerPerl(this);

    if (styleSyntax == "php")
        lexer = new QsciLexerHTML(this);

    if (styleSyntax == "postscript")
        lexer = new QsciLexerPostScript(this);

    if (styleSyntax == "pov")
        lexer = new QsciLexerPOV(this);

    if (styleSyntax == "properties")
        lexer = new QsciLexerProperties(this);

    if (styleSyntax == "python")
        lexer = new QsciLexerPython(this);

    if (styleSyntax == "ruby")
        lexer = new QsciLexerRuby(this);

    if (styleSyntax == "spice")
        lexer = new QsciLexerSpice(this);

    if (styleSyntax == "sql")
        lexer = new QsciLexerSQL(this);

    if (styleSyntax == "tcl")
        lexer = new QsciLexerTCL(this);

    if (styleSyntax == "tex")
        lexer = new QsciLexerTeX(this);

    if (styleSyntax == "verilog")
        lexer = new QsciLexerVerilog(this);

    if (styleSyntax == "vhdl")
        lexer = new QsciLexerVHDL(this);

    if (styleSyntax == "xml")
        lexer = new QsciLexerXML(this);

    if (styleSyntax == "yaml")
        lexer = new QsciLexerYAML(this);

    this->setLexer(lexer);

    if (styleSyntax != "none") {
        lexer->setFont(defaultFont);
        apis = new QsciAPIs(lexer);
        apis->load(QApplication::applicationDirPath() + "/apis/" + styleSyntax + ".api");
        //qDebug() << QApplication::applicationDirPath() + "/apis/" + styleSyntax + ".api";
        apis->prepare();
        lexer->setAPIs(apis);
    }


}

QString TextEdit::syntaxHighlighter() {
    return styleSyntax;
}

void TextEdit::keyPressEvent(QKeyEvent *event) {
    QMessageBox ms;
    ms.setText(tr("%1").arg(event->key()));
    //ms.exec(); //47 d68
    //qDebug() << event->key() << Qt::Key_Enter;
    switch (event->key()) {
        case Qt::Key_Space:
            if (event->modifiers() & Qt::ControlModifier) {
                this->autoCompleteFromAPIs();
            } else {
                QsciScintilla::keyPressEvent(event);
            }
        break;
        case Qt::Key_Return:
            if (event->modifiers() & Qt::ControlModifier) {
                this->autoCompleteFromDocument();
            } else {
                QsciScintilla::keyPressEvent(event);
            }
        break;
        default:
            QsciScintilla::keyPressEvent(event);
    }
}
