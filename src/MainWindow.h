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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AboutDialog.h"
#include "CodecDialog.h"
#include "Highlighter.h"
#include "GlobalSettings.h"
#include "FindWidget.h"
#include "GoToLineDialog.h"
#include "TextEdit.h"
#include <QMainWindow>
#include <QTextCodec>
#include <QtGui>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QDialog>
#include <QTabWidget>
#include <QCustomEvent>
#include <QSyntaxHighlighter>
#include <QTextStream>
#include <QTextEdit>
#include <QSettings>
#include <Qsci/qsciprinter.h>
#include "finddialog.h"


class QsciScintilla;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow( QWidget * parent = 0, Qt::WFlags f = 0 );
    void createDesign();
    QString loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    QAction *openFileAct;
    QAction *newFileAct;
    QAction *saveFileAct;
    QAction *saveAsFileAct;
    QAction *printAction;
    QAction *closeAction;
    QAction *exitAction;

    QAction *undoAct;
    QAction *redoAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *cutAct;
    QAction *duplicateLine;
    QAction *deleteLine;
    QAction *blockComment;
    QAction *streamComment;
    QAction *findAct;
    QAction *findNextAct;
    QAction *findPrevAct;
    QAction *replaceNextAct;
    QAction *replacePrevAct;
    QAction *goToLineAct;
    QAction *bookMarkAct;
    QAction *nextBookMarkAct;
    QAction *previousBookMarkAct;

    QAction *toolBarVisAct;
    QAction *statusBarVisAct;

    QAction *changeCodecAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *zoomNormalAct;

    QActionGroup *styleActGroup;
    QAction *txtStyleAct;

    QAction *bashStyleAct;
    QAction *batchStyleAct;
    QAction *cmakeStyleAct;
    QAction *cppStyleAct;
    QAction *csharpStyleAct;
    QAction *cssStyleAct;
    QAction *dStyleAct;
    QAction *diffStyleAct;
    QAction *fortran77StyleAct;
    QAction *htmlStyleAct;
    QAction *javaStyleAct;
    QAction *javascriptStyleAct;
    QAction *luaStyleAct;
    QAction *pascalStyleAct;
    QAction *perlStyleAct;
    QAction *phpStyleAct;
    QAction *postscriptStyleAct;
    QAction *povStyleAct;
    QAction *propertiesStyleAct;
    QAction *pythonStyleAct;
    QAction *rubyStyleAct;
    QAction *spiceStyleAct;
    QAction *sqlStyleAct;
    QAction *tclStyleAct;
    QAction *texStyleAct;
    QAction *verilogStyleAct;
    QAction *vhdlStyleAct;
    QAction *xmlStyleAct;
    QAction *yamlStyleAct;

    QAction *textCharactersAct;
    QAction *caseUpperAct;
    QAction *caseLowerAct;
    QAction *escapeQuotesAct;
    QAction *escapeDQuotesAct;
    QAction *unescapeQuotesAct;
    QAction *unescapeDQuotesAct;
    QAction *convertQuotesAct;
    QAction *convertDQuotesAct;

    QAction *settingsAct;

    QAction *about;
    QMenu *fileMenu;
    QMenu *formatMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *documentMenu;
    QMenu *styleHighlightMenu;
    QMenu *textCharactersMenu;
    QMenu *settingsMenu;
    QMenu *helpMenu;
    QToolBar *toolBar;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QString curFile;
    void readSettings();
    void writeSettings();
    QString curCodec;
    QVariant v1;
    Highlighter *highlighter;
    QFont mainFont;
    QLabel *statBar;
    QLabel *textCursorPos;
    QLabel *mousPos;
    QLabel *sizeWindLabel;
    FindWidget *findWidg;
    FindDialog *findDialog;
    QDockWidget *findDockWidget;
    QDir prevDir;
    QTabWidget *tabOpenFiles;
    QTabBar *tabBar;
    QList<QVariant> fileNames;
    QMultiMap<QString,QString> fileTypesAssoc;
    bool found;
    TextEdit *mainText;
    GlobalSettings *myGlobalSettings;
    QString newStyle;
    int index;
    int spaces;

    QString findExpr;
    bool findRE;
    bool findCS;
    bool findWO;
    bool findWrap;
    bool findForward;
    QString replaceTxt;
    int currentZoom;
    int currentLine;
    int currentRow;
    int currentSelection;
    int notFound;
    int docs;
    bool numberBlock;
    bool highlightCurLine;
    bool highlightCurRow;
    bool worldWrap;
    bool rightMarginVisible;
    int rightMargin;
    bool toolbarVisible;
    bool statbarVisible;
    QString lang;
    int tabPosition;
    QTranslator appTranslator;
    QString findText;
    QList<QTextCodec *> codecs;
protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private:
    bool accClose();
    bool findDial;
    void retranlateUi();
    void findCodecs();
    void  extToHightlightStyle(const QString &ext);
public slots:
    void findNext();
    void findPrev();
    void replaceNext();
    void replacePrev();
    void findFirst(const QString &expr, bool re, bool cs, bool wo, bool wrap,
              bool forward = true, int line = -1, int index = -1, bool show = true);
    void replaceFirst(const QString &text);
    void marginClicked(int margin, int line, Qt::KeyboardModifiers state);
    void closeFindWidg();
    void finThread();
    void openFile(const QString &text = "");
    void messReceived(const QString &text = "");
signals:
    void needToShow();
private slots:
    void closeTab(int ind = -1);
    void zoomIn();
    void zoomOut();
    void zoomNormal();
    void undoSlot();
    void redoSlot();
    void copyToClip();
    void pasteToClip();
    void cutToClip();
    void findSlot();
    void goToLine();
    void bookMarkSlot();
    void nextBookMarkSlot();
    void prevBookMarkSlot();
    void newFile();
    void saveFile();
    void saveAsFile();
    void changeCodec();
    void modificationChanged(bool b);
    void copyAvailable(bool b);
    void selStyleHightlight(QAction * actSel);
    void toolBarVis(int state);
    void toolBarVis(bool b);
    void statusBarVis(int state);
    void statusBarVis(bool b);
    void highlightCurrentLine(int state);
    void highlightCurrentRow(int state);
    void rightMargVis(int state);
    void wrapText(int state);
    void rightMarginValChanged(int val);
    void blockNumberSignal(int state);
    void tabPositionChanged(int index);
    void slotSettings();
    void aboutPr();
    void slotPrint();
    void selChanged();
    void cursorPosChanged(int line, int pos);
    void replaceNextClicked();
    void replacePrevClicked();
    void commentLine();
    void streamComments();
    void deleteLines();
    void duplicateLines();
    void caseUpper();
    void caseLower();
    void escapeQuotes();
    void escapeDQuotes();
    void unescapeQuotes();
    void unescapeDQuotes();
    void convertQuotes();
    void convertDQuotes();
    void changeTabIndex(int newIndex);
    void tabMoved(int from, int to);
};
#endif
