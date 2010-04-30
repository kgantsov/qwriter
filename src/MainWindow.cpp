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

#include "MainWindow.h"

MainWindow::MainWindow(QWidget * parent, Qt::WFlags f)
        : QMainWindow(parent, f), index(-1)
{
    readSettings();
    appTranslator.load(lang, qApp->applicationDirPath());
    qApp->installTranslator(&appTranslator);
    this->createDesign();
    docs = 0;

    fileTypesAssoc.insert("bash", "sh");
    fileTypesAssoc.insert("bash", "run");
    fileTypesAssoc.insert("batch", "bat");
    fileTypesAssoc.insert("csharp", "cs");
    fileTypesAssoc.insert("css", "css");
    fileTypesAssoc.insert("cpp", "cpp");
    fileTypesAssoc.insert("cpp", "h");
    fileTypesAssoc.insert("cpp", "hxx");
    fileTypesAssoc.insert("cpp", "h++");
    fileTypesAssoc.insert("cpp", "c");
    fileTypesAssoc.insert("cpp", "cc");
    fileTypesAssoc.insert("cpp", "cxx");
    fileTypesAssoc.insert("cmake", "cmake");
    fileTypesAssoc.insert("d", "d");
    fileTypesAssoc.insert("d", "di");
    fileTypesAssoc.insert("diff", "diff");
    fileTypesAssoc.insert("diff", "patch");
    fileTypesAssoc.insert("fortran77", "f");
    fileTypesAssoc.insert("fortran77", "f77");
    fileTypesAssoc.insert("fortran77", "f90");
    fileTypesAssoc.insert("fortran77", "f90");
    fileTypesAssoc.insert("html", "html");
    fileTypesAssoc.insert("html", "htm");
    fileTypesAssoc.insert("html", "phtml");
    fileTypesAssoc.insert("html", "dhtml");
    fileTypesAssoc.insert("html", "xhtml");
    fileTypesAssoc.insert("idl", "idl");
    fileTypesAssoc.insert("java", "java");
    fileTypesAssoc.insert("javascript", "js");
    fileTypesAssoc.insert("lua", "lua");
    fileTypesAssoc.insert("lua", "tasklua");
    fileTypesAssoc.insert("php", "php");
    fileTypesAssoc.insert("php", "php4");
    fileTypesAssoc.insert("php", "php5");
    fileTypesAssoc.insert("perl", "pl");
    fileTypesAssoc.insert("perl", "pm");
    fileTypesAssoc.insert("python", "py");
    fileTypesAssoc.insert("ruby", "rb");
    fileTypesAssoc.insert("sql", "sql");
    fileTypesAssoc.insert("tex", "tex");
    fileTypesAssoc.insert("xml", "xml");

    tabOpenFiles->setTabsClosable(true);

    connect(tabOpenFiles, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    //connect(&ftp, SIGNAL(done(bool)), this, SLOT(ftpDone(bool)));
    toolBar->setVisible(toolbarVisible);
    statusBar()->setVisible(statbarVisible);
    this->setMouseTracking(true);
    setAcceptDrops(true);
    if (fileNames.count() > 0) {
        for(int i = 0; i < fileNames.count(); ++i) {

            mainText = new TextEdit(this);

            //connect(mainText, SIGNAL(selectionChanged()), this, SLOT(selChanged()));
            connect(mainText, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(cursorPosChanged(int,int)));
            connect(mainText, SIGNAL(modificationChanged(bool)), this, SLOT(modificationChanged(bool)));
            connect(mainText, SIGNAL(copyAvailable(bool)), this, SLOT(copyAvailable(bool)));
            connect(mainText, SIGNAL(marginClicked(int,int,Qt::KeyboardModifiers)), this, SLOT(marginClicked(int,int,Qt::KeyboardModifiers)));

            /*connect(streamComment, SIGNAL(triggered()), mainText, SLOT(streamComment()));
            connect(duplicateLine, SIGNAL(triggered()), mainText, SLOT(duplicateLine()));
            connect(caseUpperAct, SIGNAL(triggered()), mainText, SLOT(caseUpper()));
            connect(caseLowerAct, SIGNAL(triggered()), mainText, SLOT(caseLower()));
            connect(escapeQuotesAct, SIGNAL(triggered()), mainText, SLOT(escapeQuotes()));
            connect(escapeDQuotesAct, SIGNAL(triggered()), mainText, SLOT(escapeDQuotes()));
            connect(unescapeQuotesAct, SIGNAL(triggered()), mainText, SLOT(unescapeQuotes()));
            connect(unescapeDQuotesAct, SIGNAL(triggered()), mainText, SLOT(unescapeDQuotes()));
            connect(convertQuotesAct, SIGNAL(triggered()), mainText, SLOT(convertQuotes()));
            connect(convertDQuotesAct, SIGNAL(triggered()), mainText, SLOT(convertDQuotes()));*/

            mainText->setWrapMode((worldWrap) ? QsciScintilla::WrapWord : QsciScintilla::WrapNone);
            mainText->setAcceptDrops(false);

            mainText->setEdgeColor(QColor("#e4e4e4"));
            mainText->setEdgeColumn(rightMargin);
            mainText->setEdgeMode((rightMarginVisible) ? QsciScintilla::EdgeLine : QsciScintilla::EdgeNone);
            mainText->setTabWidth(spaces);
            mainText->setMarginWidth(0, (numberBlock) ? 42 : 0);

            mainText->setText(loadFile(fileNames.at(i).toString()));
            mainText->setModified(false);
            this->setWindowTitle(tr("%1 - %2").arg(fileNames.at(i).toString()).arg(tr("QWriter")));
            //mainText->setFont(mainFont);

            QString styleHL = QFileInfo(fileNames.at(i).toString()).fileName();
            QStringList st = styleHL.split(".");
            int k = st.size() - 1;
            extToHightlightStyle(st.at(k));

            //tabOpenFiles->addTab(mainText, QFileInfo(fileNames.at(i).toString()).fileName());
            tabOpenFiles->addTab(mainText, QIcon(":/images/Save.png"), QFileInfo(fileNames.at(i).toString()).fileName());
            tabOpenFiles->setCurrentIndex(tabOpenFiles->count()-1);
        }
        mainText->setFocus();
    }
    else
    {
        saveFileAct->setEnabled(false);
        saveAsFileAct->setEnabled(false);
        printAction->setEnabled(false);
        closeAction->setEnabled(false);
        findAct->setEnabled(false);
        findNextAct->setEnabled(false);
        findPrevAct->setEnabled(false);
        replaceNextAct->setEnabled(false);
        replacePrevAct->setEnabled(false);
        goToLineAct->setEnabled(false);
        bookMarkAct->setEnabled(false);
        nextBookMarkAct->setEnabled(false);
        previousBookMarkAct->setEnabled(false);
        changeCodecAct->setEnabled(false);
        zoomInAct->setEnabled(false);
        zoomOutAct->setEnabled(false);
        zoomNormalAct->setEnabled(false);
        styleHighlightMenu->setEnabled(false);
        convertQuotesAct->setEnabled(false);
        convertDQuotesAct->setEnabled(false);
        caseUpperAct->setEnabled(false);
        caseLowerAct->setEnabled(false);
        escapeQuotesAct->setEnabled(false);
        escapeDQuotesAct->setEnabled(false);
        unescapeQuotesAct->setEnabled(false);
        unescapeDQuotesAct->setEnabled(false);
        settingsMenu->setEnabled(false);
        settingsAct->setEnabled(false);
    }
}

void MainWindow::retranlateUi()
{
    exitAction->setText(tr("&Exit"));
    exitAction->setStatusTip(tr("Exit"));

    closeAction->setText(tr("&Close"));
    closeAction->setStatusTip(tr("Close curent tab"));

    printAction->setText(tr("&Print"));
    printAction->setStatusTip(tr("Print this document"));

    newFileAct->setText(tr("&New"));
    newFileAct->setStatusTip(tr("Create new file"));

    openFileAct->setText(tr("&Open"));
    openFileAct->setStatusTip(tr("Open file"));

    saveFileAct->setText(tr("&Save"));
    saveFileAct->setStatusTip(tr("Save file"));

    saveAsFileAct->setText(tr("Save as..."));
    saveAsFileAct->setStatusTip(tr("Save file as..."));

    undoAct->setText(tr("&Undo"));
    undoAct->setStatusTip(tr("Undo"));

    redoAct->setText(tr("&Redo"));
    redoAct->setStatusTip(tr("Redo"));

    copyAct->setText(tr("&Copy"));
    copyAct->setStatusTip(tr("Copy to clipboard"));

    pasteAct->setText(tr("&Paste"));
    pasteAct->setStatusTip(tr("Paste from clipboard"));

    cutAct->setText(tr("&Cut"));
    cutAct->setStatusTip(tr("Cut to clipboard"));

    blockComment->setText(tr("Block comment"));
    blockComment->setStatusTip(tr("Block comment"));

    streamComment->setText(tr("Stream comment"));
    streamComment->setStatusTip(tr("Stream comment"));

    duplicateLine->setText(tr("Duplicate line"));
    duplicateLine->setStatusTip(tr("Duplicate line"));

    deleteLine->setText(tr("Delete line"));
    deleteLine->setStatusTip(tr("Delete line"));

    findAct->setText(tr("&Find"));
    findAct->setStatusTip(tr("Find"));


    findNextAct->setText(tr("Find Next"));
    findNextAct->setStatusTip(tr("Find Next"));

    findPrevAct->setText(tr("Find Previous"));
    findPrevAct->setStatusTip(tr("Find Previous"));

    replaceNextAct->setText(tr("Replace Next"));
    replaceNextAct->setStatusTip(tr("Replace Next"));

    replacePrevAct->setText(tr("Replace Previous"));
    replacePrevAct->setStatusTip(tr("Replace Previous"));

    goToLineAct->setText(tr("Go to..."));
    goToLineAct->setStatusTip(tr("Go to..."));

    bookMarkAct->setText(tr("Toggle Bookmark"));
    bookMarkAct->setStatusTip(tr("Toggle Bookmark"));

    nextBookMarkAct->setText(tr("Next bookmark"));
    nextBookMarkAct->setStatusTip(tr("Next bookmark"));

    previousBookMarkAct->setText(tr("Previous bookmark"));
    previousBookMarkAct->setStatusTip(tr("Previous bookmark"));


    toolBarVisAct->setText(tr("Toolbar"));
    toolBarVisAct->setStatusTip(tr("Toolbar"));

    statusBarVisAct->setText(tr("Statusbar"));
    statusBarVisAct->setStatusTip(tr("Statusbar"));


    zoomInAct->setText(tr("Zoom In"));
    zoomInAct->setStatusTip(tr("Zoom In"));

    zoomOutAct->setText(tr("Zoom Out"));
    zoomOutAct->setStatusTip(tr("Zoom Out"));

    zoomNormalAct->setText(tr("Zoom Normal"));
    zoomNormalAct->setStatusTip(tr("Zoom Normal"));

    changeCodecAct->setText(tr("&Encoding"));
    changeCodecAct->setStatusTip(tr("Choose encoding"));

    txtStyleAct->setText(tr("Text"));
    txtStyleAct->setStatusTip(tr("Text"));

    bashStyleAct->setText(tr("Bash"));
    bashStyleAct->setStatusTip(tr("Bash"));

    batchStyleAct->setText(tr("Batch"));
    batchStyleAct->setStatusTip(tr("Batch"));

    cmakeStyleAct->setText(tr("Cmake"));
    cmakeStyleAct->setStatusTip(tr("Cmake"));

    cppStyleAct->setText(tr("C++"));
    cppStyleAct->setStatusTip(tr("C++"));

    csharpStyleAct->setText(tr("C#"));
    csharpStyleAct->setStatusTip(tr("C#"));

    cssStyleAct->setText(tr("CSS"));
    cssStyleAct->setStatusTip(tr("CSS"));

    dStyleAct->setText(tr("D"));
    dStyleAct->setStatusTip(tr("D"));

    diffStyleAct->setText(tr("Diff"));
    diffStyleAct->setStatusTip(tr("Diff"));

    fortran77StyleAct->setText(tr("Fortran"));
    fortran77StyleAct->setStatusTip(tr("Fortran"));

    htmlStyleAct->setText(tr("HTML"));
    htmlStyleAct->setStatusTip(tr("HTML"));

    javaStyleAct->setText(tr("Java"));
    javaStyleAct->setStatusTip(tr("Java"));

    javascriptStyleAct->setText(tr("JavaScript"));
    javascriptStyleAct->setStatusTip(tr("JavaScript"));

    luaStyleAct->setText(tr("Lua"));
    luaStyleAct->setStatusTip(tr("Lua"));

    pascalStyleAct->setText(tr("Pascal"));
    pascalStyleAct->setStatusTip(tr("Pascal"));

    perlStyleAct->setText(tr("Perl"));
    perlStyleAct->setStatusTip(tr("Perl"));

    phpStyleAct->setText(tr("PHP"));
    phpStyleAct->setStatusTip(tr("PHP"));

    postscriptStyleAct->setText(tr("PostScript"));
    postscriptStyleAct->setStatusTip(tr("PostScript"));

    povStyleAct->setText(tr("Pov"));
    povStyleAct->setStatusTip(tr("Pov"));

    propertiesStyleAct->setText(tr("Properties"));
    propertiesStyleAct->setStatusTip(tr("Properties"));

    pythonStyleAct->setText(tr("Python"));
    pythonStyleAct->setStatusTip(tr("Python"));

    rubyStyleAct->setText(tr("Ruby"));
    rubyStyleAct->setStatusTip(tr("Ruby"));

    spiceStyleAct->setText(tr("Spice"));
    spiceStyleAct->setStatusTip(tr("Spice"));

    sqlStyleAct->setText(tr("SQL"));
    sqlStyleAct->setStatusTip(tr("SQL"));

    tclStyleAct->setText(tr("TCL"));
    tclStyleAct->setStatusTip(tr("TCL"));

    texStyleAct->setText(tr("Tex"));
    texStyleAct->setStatusTip(tr("Tex"));

    verilogStyleAct->setText(tr("Verilog"));
    verilogStyleAct->setStatusTip(tr("Verilog"));

    vhdlStyleAct->setText(tr("VHDL"));
    vhdlStyleAct->setStatusTip(tr("VHDL"));

    xmlStyleAct->setText(tr("XML"));
    xmlStyleAct->setStatusTip(tr("XML"));

    yamlStyleAct->setText(tr("YAML"));
    yamlStyleAct->setStatusTip(tr("YAML"));



    caseUpperAct->setText(tr("Case Upper"));
    caseLowerAct->setText(tr("Case Lower"));

    escapeQuotesAct->setText(tr("escape ' to \\\'"));
    escapeDQuotesAct->setText(tr("escape \" to \\\""));

    unescapeQuotesAct->setText(tr("unescape \\\' to '"));
    unescapeDQuotesAct->setText(tr("unescape \\\" to \""));

    convertQuotesAct->setText(tr("convert quotes to \'"));
    convertDQuotesAct->setText(tr("convert quotes to \""));

    settingsAct->setText(tr("Settings"));
    settingsAct->setStatusTip(tr("Programm settings"));

    about->setText(tr("&About"));
    about->setStatusTip(tr("About"));
    
    fileMenu->setTitle(tr("&File"));
    editMenu->setTitle(tr("&Edit"));
    styleHighlightMenu->setTitle(tr("S&tyle"));
    viewMenu->setTitle(tr("&View"));
    documentMenu->setTitle(tr("&Document"));
    textCharactersMenu->setTitle(tr("Characters"));
    settingsMenu->setTitle(tr("&Settings"));
    helpMenu->setTitle(tr("&help"));

    findWidg->findLabel->setText(tr("Find"));
    findWidg->replaceLabel->setText(tr("Replace"));
    findWidg->caseCheckBox->setText(tr("Case sensitivity"));
    findWidg->wholeWords->setText(tr("Whole words"));
}


void MainWindow::createDesign()
{
	////---------top menu-----------////
        exitAction = new QAction(this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

        closeAction = new QAction(this);
        closeAction->setShortcut(tr("Ctrl+W"));
        connect(closeAction, SIGNAL(triggered()), this, SLOT(closeTab()));
	
        printAction = new QAction(this);
        printAction->setIcon(QIcon(":/images/imprimante-v2.png"));
        connect(printAction, SIGNAL(triggered()), this, SLOT(slotPrint()));

        newFileAct = new QAction(this);
        newFileAct->setIcon(QIcon(":/images/Document.png"));
	newFileAct->setShortcut(tr("Ctrl+N"));
	connect(newFileAct, SIGNAL(triggered()), this, SLOT(newFile()));

        openFileAct = new QAction(this);
        openFileAct->setIcon(QIcon(":/images/mes-documents.png"));
	openFileAct->setShortcut(tr("Ctrl+O"));
	connect(openFileAct, SIGNAL(triggered()), this, SLOT(openFile()));
	
        saveFileAct = new QAction(this);
        saveFileAct->setIcon(QIcon(":/images/Save.png"));
	saveFileAct->setShortcut(tr("Ctrl+S"));
	connect(saveFileAct, SIGNAL(triggered()), this, SLOT(saveFile()));
	
        saveAsFileAct = new QAction(this);
        saveAsFileAct->setShortcut(tr("Ctrl+Shift+S"));
	connect(saveAsFileAct, SIGNAL(triggered()), this, SLOT(saveAsFile()));
	
        undoAct = new QAction(this);
        undoAct->setIcon(QIcon(":/images/Undo.png"));
        undoAct->setShortcut(tr("Ctrl+Z"));
        connect(undoAct, SIGNAL(triggered()), this, SLOT(undoSlot()));

        redoAct = new QAction(this);
        redoAct->setIcon(QIcon(":/images/Redo.png"));
        redoAct->setShortcut(tr("Ctrl+Shift+Z"));
        connect(redoAct, SIGNAL(triggered()), this, SLOT(redoSlot()));

        copyAct = new QAction(this);
        copyAct->setIcon(QIcon(":/images/Copy.png"));
        copyAct->setShortcut(tr("Ctrl+C"));
        connect(copyAct, SIGNAL(triggered()), this, SLOT(copyToClip()));

        pasteAct = new QAction(this);
        pasteAct->setIcon(QIcon(":/images/Paste.png"));
        pasteAct->setShortcut(tr("Ctrl+V"));
        connect(pasteAct, SIGNAL(triggered()), this, SLOT(pasteToClip()));

        cutAct = new QAction(this);
        cutAct->setIcon(QIcon(":/images/Cut.png"));
        cutAct->setShortcut(tr("Ctrl+X"));
        connect(cutAct, SIGNAL(triggered()), this, SLOT(cutToClip()));

        blockComment = new QAction(this);
        blockComment->setShortcut(tr("Ctrl+/"));
        connect(blockComment, SIGNAL(triggered()), this, SLOT(commentLine()));

        streamComment = new QAction(this);
        streamComment->setShortcut(tr("Ctrl+Alt+/"));
        connect(streamComment, SIGNAL(triggered()), this, SLOT(streamComments()));

        duplicateLine = new QAction(this);
        duplicateLine->setShortcut(tr("Ctrl+D"));
        connect(duplicateLine, SIGNAL(triggered()), this, SLOT(duplicateLines()));

        deleteLine = new QAction(this);
        deleteLine->setShortcut(tr("Ctrl+L"));
        connect(deleteLine, SIGNAL(triggered()), this, SLOT(deleteLines()));

        findAct = new QAction(this);
        findAct->setShortcut(tr("Ctrl+F"));
        findAct->setIcon(QIcon(":/images/loupe.png"));
        connect(findAct, SIGNAL(triggered()), this, SLOT(findSlot()));

        findNextAct = new QAction(this);
        findNextAct->setShortcut(tr("F3"));
        connect(findNextAct, SIGNAL(triggered()), this, SLOT(findNext()));

        findPrevAct = new QAction(this);
        findPrevAct->setShortcut(tr("Shift+F3"));
        connect(findPrevAct, SIGNAL(triggered()), this, SLOT(findPrev()));

        replaceNextAct = new QAction(this);
        replaceNextAct->setShortcut(tr("F4"));
        connect(replaceNextAct, SIGNAL(triggered()), this, SLOT(replaceNext()));

        replacePrevAct = new QAction(this);
        replacePrevAct->setShortcut(tr("Shift+F4"));
        connect(replacePrevAct, SIGNAL(triggered()), this, SLOT(replacePrev()));

        goToLineAct = new QAction(this);
        goToLineAct->setShortcut(tr("Ctrl+G"));
        connect(goToLineAct, SIGNAL(triggered()), this, SLOT(goToLine()));

        bookMarkAct = new QAction(this);
        bookMarkAct->setShortcut(tr("Ctrl+M"));
        connect(bookMarkAct, SIGNAL(triggered()), this, SLOT(bookMarkSlot()));

        nextBookMarkAct = new QAction(this);
        nextBookMarkAct->setShortcut(tr("Ctrl+]"));
        connect(nextBookMarkAct, SIGNAL(triggered()), this, SLOT(nextBookMarkSlot()));

        previousBookMarkAct = new QAction(this);
        previousBookMarkAct->setShortcut(tr("Ctrl+["));
        connect(previousBookMarkAct, SIGNAL(triggered()), this, SLOT(prevBookMarkSlot()));

        toolBarVisAct = new QAction(this);
        toolBarVisAct->setCheckable(true);
        toolBarVisAct->setChecked(toolbarVisible);
        connect(toolBarVisAct, SIGNAL(triggered(bool)), this, SLOT(toolBarVis(bool)));

        statusBarVisAct = new QAction(this);
        statusBarVisAct->setCheckable(true);
        statusBarVisAct->setChecked(statbarVisible);
        connect(statusBarVisAct, SIGNAL(triggered(bool)), this, SLOT(statusBarVis(bool)));

        zoomInAct = new QAction(this);
        zoomInAct->setIcon(QIcon(":/images/Zoom-in.png"));
        zoomInAct->setShortcut(tr("Ctrl+="));
        connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

        zoomOutAct = new QAction(this);
        zoomOutAct->setIcon(QIcon(":/images/Zoom-out.png"));
        zoomOutAct->setShortcut(tr("Ctrl+-"));
        connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

        zoomNormalAct = new QAction(this);
        zoomNormalAct->setIcon(QIcon(":/images/Zoom-Normal.png"));
        connect(zoomNormalAct, SIGNAL(triggered()), this, SLOT(zoomNormal()));

        changeCodecAct = new QAction(this);
	changeCodecAct->setShortcut(tr("Ctrl+Alt+C"));
	connect(changeCodecAct, SIGNAL(triggered()), this, SLOT(changeCodec()));

        styleActGroup = new QActionGroup(this);
        connect(styleActGroup, SIGNAL(selected(QAction*)), this, SLOT(selStyleHightlight(QAction*)));

        txtStyleAct = new QAction(this);
        txtStyleAct->setCheckable(true);
        styleActGroup->addAction(txtStyleAct);

        bashStyleAct = new QAction(this);
        bashStyleAct->setCheckable(true);
        styleActGroup->addAction(bashStyleAct);

        batchStyleAct = new QAction(this);
        batchStyleAct->setCheckable(true);
        styleActGroup->addAction(batchStyleAct);

        cmakeStyleAct = new QAction(this);
        cmakeStyleAct->setCheckable(true);
        styleActGroup->addAction(cmakeStyleAct);

        cppStyleAct = new QAction(this);
        cppStyleAct->setCheckable(true);
        styleActGroup->addAction(cppStyleAct);

        csharpStyleAct = new QAction(this);
        csharpStyleAct->setCheckable(true);
        styleActGroup->addAction(cmakeStyleAct);

        cssStyleAct = new QAction(this);
        cssStyleAct->setCheckable(true);
        styleActGroup->addAction(cssStyleAct);

        dStyleAct = new QAction(this);
        dStyleAct->setCheckable(true);
        styleActGroup->addAction(dStyleAct);

        diffStyleAct = new QAction(this);
        diffStyleAct->setCheckable(true);
        styleActGroup->addAction(diffStyleAct);

        fortran77StyleAct = new QAction(this);
        fortran77StyleAct->setCheckable(true);
        styleActGroup->addAction(fortran77StyleAct);

        htmlStyleAct = new QAction(this);
        htmlStyleAct->setCheckable(true);
        styleActGroup->addAction(htmlStyleAct);

        javaStyleAct = new QAction(this);
        javaStyleAct->setCheckable(true);
        styleActGroup->addAction(javaStyleAct);

        javascriptStyleAct = new QAction(this);
        javascriptStyleAct->setCheckable(true);
        styleActGroup->addAction(javascriptStyleAct);

        luaStyleAct = new QAction(this);
        luaStyleAct->setCheckable(true);
        styleActGroup->addAction(luaStyleAct);

        pascalStyleAct = new QAction(this);
        pascalStyleAct->setCheckable(true);
        styleActGroup->addAction(pascalStyleAct);

        perlStyleAct = new QAction(this);
        perlStyleAct->setCheckable(true);
        styleActGroup->addAction(perlStyleAct);

        phpStyleAct = new QAction(this);
        phpStyleAct->setCheckable(true);
        styleActGroup->addAction(phpStyleAct);

        postscriptStyleAct = new QAction(this);
        postscriptStyleAct->setCheckable(true);
        styleActGroup->addAction(postscriptStyleAct);

        povStyleAct = new QAction(this);
        povStyleAct->setCheckable(true);
        styleActGroup->addAction(povStyleAct);

        propertiesStyleAct = new QAction(this);
        propertiesStyleAct->setCheckable(true);
        styleActGroup->addAction(propertiesStyleAct);

        pythonStyleAct = new QAction(this);
        pythonStyleAct->setCheckable(true);
        styleActGroup->addAction(pythonStyleAct);

        rubyStyleAct = new QAction(this);
        rubyStyleAct->setCheckable(true);
        styleActGroup->addAction(rubyStyleAct);

        spiceStyleAct = new QAction(this);
        spiceStyleAct->setCheckable(true);
        styleActGroup->addAction(spiceStyleAct);

        sqlStyleAct = new QAction(this);
        sqlStyleAct->setCheckable(true);
        styleActGroup->addAction(sqlStyleAct);

        tclStyleAct = new QAction(this);
        tclStyleAct->setCheckable(true);
        styleActGroup->addAction(tclStyleAct);

        texStyleAct = new QAction(this);
        texStyleAct->setCheckable(true);
        styleActGroup->addAction(texStyleAct);

        verilogStyleAct = new QAction(this);
        verilogStyleAct->setCheckable(true);
        styleActGroup->addAction(verilogStyleAct);

        vhdlStyleAct = new QAction(this);
        vhdlStyleAct->setCheckable(true);
        styleActGroup->addAction(vhdlStyleAct);

        xmlStyleAct = new QAction(this);
        xmlStyleAct->setCheckable(true);
        styleActGroup->addAction(xmlStyleAct);

        yamlStyleAct = new QAction(this);
        yamlStyleAct->setCheckable(true);
        styleActGroup->addAction(yamlStyleAct);

        textCharactersAct = new QAction(this);
        textCharactersAct->setText(tr("Characters"));

        caseUpperAct = new QAction(this);
        connect(caseUpperAct, SIGNAL(triggered()), this, SLOT(caseUpper()));
        caseUpperAct->setShortcut(tr("Ctrl+U"));

        caseLowerAct = new QAction(this);
        connect(caseLowerAct, SIGNAL(triggered()), this, SLOT(caseLower()));
        caseLowerAct->setShortcut(tr("Ctrl+Shift+U"));

        escapeQuotesAct = new QAction(this);
        connect(escapeQuotesAct, SIGNAL(triggered()), this, SLOT(escapeQuotes()));

        escapeDQuotesAct = new QAction(this);
        connect(escapeDQuotesAct, SIGNAL(triggered()), this, SLOT(escapeDQuotes()));

        unescapeQuotesAct = new QAction(this);
        connect(unescapeQuotesAct, SIGNAL(triggered()), this, SLOT(unescapeQuotes()));

        unescapeDQuotesAct = new QAction(this);
        connect(unescapeDQuotesAct, SIGNAL(triggered()), this, SLOT(unescapeDQuotes()));

        convertQuotesAct = new QAction(this);
        connect(convertQuotesAct, SIGNAL(triggered()), this, SLOT(convertQuotes()));

        convertDQuotesAct = new QAction(this);
        connect(convertDQuotesAct, SIGNAL(triggered()), this, SLOT(convertDQuotes()));

        settingsAct = new QAction(this);
        settingsAct->setIcon(QIcon(":/images/Config-Tools.png"));
        settingsAct->setShortcut(tr("Ctrl+P"));
        connect(settingsAct, SIGNAL(triggered()), this, SLOT(slotSettings()));

        about = new QAction(this);
        about->setShortcut(tr("Ctrl+F1"));
	connect(about, SIGNAL(triggered()), this, SLOT(aboutPr()));
	
        fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newFileAct);
	fileMenu->addAction(openFileAct);
	fileMenu->addAction(saveFileAct);
	fileMenu->addAction(saveAsFileAct);
        fileMenu->addAction(printAction);
        fileMenu->addSeparator();
        fileMenu->addAction(closeAction);
	fileMenu->addAction(exitAction);
        editMenu = menuBar()->addMenu(tr("&Edit"));
        editMenu->addAction(undoAct);
        editMenu->addAction(redoAct);
        editMenu->addAction(copyAct);
        editMenu->addAction(cutAct);
        editMenu->addAction(pasteAct);
        editMenu->addSeparator();
        editMenu->addAction(blockComment);
        editMenu->addAction(streamComment);
        editMenu->addSeparator();
        editMenu->addAction(duplicateLine);
        editMenu->addAction(deleteLine);
        editMenu->addSeparator();
        editMenu->addAction(findAct);
        editMenu->addAction(findNextAct);
        editMenu->addAction(findPrevAct);
        editMenu->addAction(replaceNextAct);
        editMenu->addAction(replacePrevAct);
        editMenu->addSeparator();
        editMenu->addAction(goToLineAct);
        editMenu->addSeparator();
        editMenu->addAction(bookMarkAct);
        editMenu->addAction(nextBookMarkAct);
        editMenu->addAction(previousBookMarkAct);

        viewMenu = menuBar()->addMenu(tr("&View"));
        viewMenu->addAction(toolBarVisAct);
        viewMenu->addAction(statusBarVisAct);

        viewMenu->addSeparator();
        viewMenu->addAction(zoomInAct);
        viewMenu->addAction(zoomOutAct);
        viewMenu->addAction(zoomNormalAct);

        documentMenu = menuBar()->addMenu(tr("&Document"));

        documentMenu->addAction(changeCodecAct);
        styleHighlightMenu = documentMenu->addMenu(tr("S&tyle"));
        textCharactersMenu = documentMenu->addMenu(tr("Characters"));
        
        textCharactersMenu->addAction(convertQuotesAct);
        textCharactersMenu->addAction(convertDQuotesAct);
        textCharactersMenu->addAction(caseUpperAct);
        textCharactersMenu->addAction(caseLowerAct);
        textCharactersMenu->addAction(escapeQuotesAct);
        textCharactersMenu->addAction(escapeDQuotesAct);
        textCharactersMenu->addAction(unescapeQuotesAct);
        textCharactersMenu->addAction(unescapeDQuotesAct);

        styleHighlightMenu->addActions(styleActGroup->actions());

        documentMenu->addMenu(textCharactersMenu);

        settingsMenu = menuBar()->addMenu(tr("&Settings"));
        settingsMenu->addAction(settingsAct);

	helpMenu = menuBar()->addMenu(tr("&help"));
        helpMenu->addAction(about);
	
        toolBar = new QToolBar(this);
        this->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar->addAction(newFileAct);
        toolBar->addAction(openFileAct);
        toolBar->addAction(saveFileAct);
        toolBar->addSeparator();
        toolBar->addAction(findAct);
        toolBar->addSeparator();
        toolBar->addAction(copyAct);
        toolBar->addAction(cutAct);
        toolBar->addAction(pasteAct);
        toolBar->addSeparator();
        toolBar->addAction(undoAct);
        toolBar->addAction(redoAct);
        toolBar->addSeparator();
        toolBar->addAction(zoomInAct);
        toolBar->addAction(zoomOutAct);
        toolBar->addAction(zoomNormalAct);
        
        #ifdef Q_WS_WIN
        mainFont.setFamily("Monospace");
        mainFont.setPointSize(10);
        #endif
    
        #ifdef Q_WS_X11
        mainFont.setFamily("Monospace");
        mainFont.setPointSize(10);
        #endif

        
        
        tabOpenFiles = new QTabWidget(this);
        tabOpenFiles->setMovable(true);
        tabPositionChanged(tabPosition);
        connect(tabOpenFiles, SIGNAL(currentChanged (int)), this, SLOT(changeTabIndex(int)));
        tabBar = tabOpenFiles->findChild<QTabBar *>();
        connect(tabBar, SIGNAL(tabMoved(int,int)), this, SLOT(tabMoved(int,int)));

        textCursorPos = new QLabel;
        statBar = new QLabel;
        mousPos = new QLabel;
        sizeWindLabel = new QLabel;

        statusBar()->setSizeGripEnabled(false);
        statusBar()->addWidget(statBar, 4);
        statusBar()->addWidget(textCursorPos, 1);
        statusBar()->addWidget(sizeWindLabel, 1);
        statusBar()->addWidget(mousPos, 1);

        findDial = false;
        findWidg = new FindWidget(this);
        findDialog = new FindDialog(this);
        findWidg->hide();
        connect(findNextAct, SIGNAL(triggered()), this, SLOT(findNext()));
        //connect(findWidg, SIGNAL(findNext(QString,QTextDocument::FindFlags)), this, SLOT(findNext(QString,QTextDocument::FindFlags)));
        //connect(findWidg, SIGNAL(findPrev(QString,QTextDocument::FindFlags)), this, SLOT(findNext(QString,QTextDocument::FindFlags)));
        connect(findDialog, SIGNAL(findFirst(QString,bool,bool,bool,bool,bool,int,int,bool)),
                    this, SLOT(findFirst(QString,bool,bool,bool,bool,bool,int,int,bool)));
        connect(findDialog, SIGNAL(replace(QString)), this, SLOT(replaceFirst(QString)));
        //connect(findDialog, SIGNAL(findSignal(QString)), this, SLOT(findSlot(QString)));
        //connect(findWidg->replaceNextButton, SIGNAL(clicked()), this, SLOT(replaceNextClicked()));
        //connect(findWidg->replacePrevButton, SIGNAL(clicked()), this, SLOT(replacePrevClicked()));
        //connect(findWidg, SIGNAL(findCloseClick()),  this, SLOT(closeFindWidg()));
        QSplitter *spliter = new QSplitter(Qt::Vertical);
        spliter->addWidget(tabOpenFiles);
        spliter->addWidget(findWidg);
        spliter->setStretchFactor(0, 100);
        spliter->setStretchFactor(1, 1);
        setCentralWidget(spliter);
        setWindowIcon(QIcon(":/images/Messagerie.png"));
        setWindowTitle(tr("QWriter"));

        retranlateUi();
}

void MainWindow::readSettings()
{
	QSettings settings("kossinc", "koss");
	settings.beginGroup("MainWindow");
        fileNames = settings.value("fileNames", -1).toList();
        lang = settings.value("lang", "languages/qwriter_en.qm").toString();
        tabPosition = settings.value("tabPosition", 0).toInt();
        curFile = settings.value("curFile", false).toString();
        currentZoom = settings.value("currentZoom", 0).toInt();
        worldWrap = settings.value("worldWrap", true).toBool();
        toolbarVisible = settings.value("toolbarVisible", true).toBool();
        statbarVisible = settings.value("statbarVisible", true).toBool();
        numberBlock = settings.value("numberBlock", true).toBool();
        highlightCurLine = settings.value("highlightCurLine", true).toBool();
        highlightCurRow = settings.value("highlightCurRow", true).toBool();
        rightMarginVisible = settings.value("rightMarginVisible", true).toBool();
        rightMargin = settings.value("rightMargin", 100).toInt();
        curCodec = settings.value("curCodec", "UTF-8").toString();
        spaces = settings.value("spaces", 4).toInt();
        int x = settings.value("geometry_x", 200).toInt();
        int y = settings.value("geometry_y", 150).toInt();
	int w = settings.value("geometry_width", 500).toInt();
	int h = settings.value("geometry_height", 400).toInt();
	move(x, y);
	resize(w, h);
	settings.endGroup();
}

void MainWindow::writeSettings()
{
	QSettings settings("kossinc", "koss");
	settings.beginGroup("MainWindow");
        settings.setValue("fileNames", fileNames);
        settings.setValue("lang", lang);
        settings.setValue("tabPosition", tabPosition);
        settings.setValue("curFile", curFile);
        settings.setValue("currentZoom", currentZoom);
        settings.setValue("worldWrap", worldWrap);
        settings.setValue("toolbarVisible", toolbarVisible);
        settings.setValue("statbarVisible", statbarVisible);
        settings.setValue("numberBlock", numberBlock);
        settings.setValue("highlightCurLine", highlightCurLine);
        settings.setValue("highlightCurRow", highlightCurRow);
        settings.setValue("rightMarginVisible", rightMarginVisible);
        settings.setValue("rightMargin", rightMargin);
        settings.setValue("curCodec", curCodec);
        settings.setValue("spaces", spaces);
	settings.setValue("geometry_x", x());
	settings.setValue("geometry_y", y());
	settings.setValue("geometry_width", width());
	settings.setValue("geometry_height", height());
	settings.endGroup();
}

void MainWindow::messReceived(const QString &text)
{
    QString str = text;
    QStringList list1 = str.split(";", QString::SkipEmptyParts);
    for (int i = 0; i < list1.size(); ++i)
        openFile(list1.at(i));
    emit needToShow();
}

void MainWindow::aboutPr()
{
    AboutDialog abD;
    abD.exec();
}

void MainWindow::closeTab(int ind)
{
    if (tabOpenFiles->count() > 0) {
        if (accClose()) {
            int deleteInd = (ind != -1) ? ind : index;
            tabOpenFiles->removeTab(deleteInd);
            fileNames.removeAt(deleteInd);

            if (index >= 0) {
                tabOpenFiles->setCurrentIndex(index);
                this->setWindowTitle(tr("%1 - %2").arg(fileNames.at(index).toString()).arg(tr("QWriter")));
                mainText->setFocus();
            }
        }
    }
}


void MainWindow::newFile()
{
    docs++;
    QString newdoc(tr("new %1").arg(docs));
    mainText = new TextEdit(this);
    texStyleAct->setChecked(true);
    //connect(mainText, SIGNAL(selectionChanged()), this, SLOT(selChanged()));
    connect(mainText, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(cursorPosChanged(int,int)));
    connect(mainText, SIGNAL(modificationChanged(bool)), this, SLOT(modificationChanged(bool)));
    connect(mainText, SIGNAL(copyAvailable(bool)), this, SLOT(copyAvailable(bool)));
    connect(mainText, SIGNAL(marginClicked(int,int,Qt::KeyboardModifiers)), this, SLOT(marginClicked(int,int,Qt::KeyboardModifiers)));

    /*connect(streamComment, SIGNAL(triggered()), mainText, SLOT(streamComment()));
    connect(duplicateLine, SIGNAL(triggered()), mainText, SLOT(duplicateLine()));
    connect(caseUpperAct, SIGNAL(triggered()), mainText, SLOT(caseUpper()));
    connect(caseLowerAct, SIGNAL(triggered()), mainText, SLOT(caseLower()));
    connect(escapeQuotesAct, SIGNAL(triggered()), mainText, SLOT(escapeQuotes()));
    connect(escapeDQuotesAct, SIGNAL(triggered()), mainText, SLOT(escapeDQuotes()));
    connect(unescapeQuotesAct, SIGNAL(triggered()), mainText, SLOT(unescapeQuotes()));
    connect(unescapeDQuotesAct, SIGNAL(triggered()), mainText, SLOT(unescapeDQuotes()));
    connect(convertQuotesAct, SIGNAL(triggered()), mainText, SLOT(convertQuotes()));
    connect(convertDQuotesAct, SIGNAL(triggered()), mainText, SLOT(convertDQuotes()));*/

    mainText->setAcceptDrops(false);

    curFile = "";

    fileNames.push_back(newdoc);

    mainText->setText("");
    mainText->setModified(false);
    mainText->setFocus();
    //mainText->setFont(mainFont);
    mainText->setTabWidth(spaces);
    mainText->setMarginWidth(0, (numberBlock) ? 42 : 0);

    mainText->setEdgeColor(QColor("#e4e4e4"));
    mainText->setEdgeColumn(rightMargin);
    mainText->setEdgeMode((rightMarginVisible) ? QsciScintilla::EdgeLine : QsciScintilla::EdgeNone);

    //tabOpenFiles->addTab(mainText, QFileInfo(fileNames.at(tabOpenFiles->count()).toString()).fileName());
    tabOpenFiles->addTab(mainText, QIcon(":/images/Save.png"), QFileInfo(fileNames.at(tabOpenFiles->count()).toString()).fileName());
    tabOpenFiles->setCurrentIndex(tabOpenFiles->count()-1);
    this->setWindowTitle(tr("QWriter"));
}

void MainWindow::openFile(const QString &text)
{ 
    QString fileName;
    fileName = (text != "") ? text : QFileDialog::getOpenFileName(this, tr("Open File"), prevDir.path(),tr("all formats (*.*)"));
    QFile file(fileName);
    prevDir = QDir(fileName);

    if (file.exists()) {
        bool opened = false;

        for (int i = 0; i < fileNames.count(); ++i) {
            if (fileName == fileNames.at(i)) {
                tabOpenFiles->setCurrentIndex(i);
                opened = true;
                break;
            }
        }

        if (opened == false) {
            mainText = new TextEdit(this);

            //connect(mainText, SIGNAL(selectionChanged()), this, SLOT(selChanged()));
            connect(mainText, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(cursorPosChanged(int,int)));
            connect(mainText, SIGNAL(modificationChanged(bool)), this, SLOT(modificationChanged(bool)));
            connect(mainText, SIGNAL(copyAvailable(bool)), this, SLOT(copyAvailable(bool)));
            connect(mainText, SIGNAL(marginClicked(int,int,Qt::KeyboardModifiers)), this, SLOT(marginClicked(int,int,Qt::KeyboardModifiers)));

            /*connect(streamComment, SIGNAL(triggered()), mainText, SLOT(streamComment()));
            connect(duplicateLine, SIGNAL(triggered()), mainText, SLOT(duplicateLine()));
            connect(caseUpperAct, SIGNAL(triggered()), mainText, SLOT(caseUpper()));
            connect(caseLowerAct, SIGNAL(triggered()), mainText, SLOT(caseLower()));
            connect(escapeQuotesAct, SIGNAL(triggered()), mainText, SLOT(escapeQuotes()));
            connect(escapeDQuotesAct, SIGNAL(triggered()), mainText, SLOT(escapeDQuotes()));
            connect(unescapeQuotesAct, SIGNAL(triggered()), mainText, SLOT(unescapeQuotes()));
            connect(unescapeDQuotesAct, SIGNAL(triggered()), mainText, SLOT(unescapeDQuotes()));
            connect(convertQuotesAct, SIGNAL(triggered()), mainText, SLOT(convertQuotes()));
            connect(convertDQuotesAct, SIGNAL(triggered()), mainText, SLOT(convertDQuotes()));*/

            mainText->setAcceptDrops(false);

            mainText->setEdgeColor(QColor("#e4e4e4"));
            mainText->setEdgeColumn(rightMargin);
            mainText->setEdgeMode((rightMarginVisible) ? QsciScintilla::EdgeLine : QsciScintilla::EdgeNone);

            mainText->setText(loadFile(fileName));
            mainText->setModified(false);
            //mainText->setFont(mainFont);
            mainText->setFocus();
            mainText->setTabWidth(spaces);
            mainText->setMarginWidth(0, (numberBlock) ? 42 : 0);

            QString styleHL = QFileInfo(fileName).fileName();
            QStringList st = styleHL.split(".");
            int k = st.size() - 1;
            extToHightlightStyle(st.at(k));

            fileNames.push_back(fileName);
            //tabOpenFiles->addTab(mainText, QFileInfo(fileNames.at(fileNames.count()-1).toString()).fileName());
            tabOpenFiles->addTab(mainText, QIcon(":/images/Save.png"), QFileInfo(fileNames.at(fileNames.count()-1).toString()).fileName());

            tabOpenFiles->setCurrentIndex(tabOpenFiles->count()-1);
            this->setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("QWriter")));
        }
    }
}

void MainWindow::saveFile()
{
    QFile file(fileNames.at(index).toString());
    if (!file.exists()) {
        QString fileName = QFileDialog::getSaveFileName(this);
        if (fileName.isEmpty())
            return;

        curFile = fileName;
        saveFile(fileName);
        fileNames.removeAt(fileNames.indexOf(fileNames.at(index).toString()));
        fileNames<<fileName;
        tabOpenFiles->setTabText(index, QFileInfo(fileName).fileName());
        this->setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("QWriter")));
        QString styleHL = QFileInfo(fileName).fileName();
        QStringList st = styleHL.split(".");
        int k = st.size() - 1;
        extToHightlightStyle(st.at(k));
        mainText->setModified(false);
    } else {
        saveFile(fileNames.at(index).toString());
        mainText->setModified(false);
    }
}
void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;

    fileNames[index] = fileName;
    curFile = fileName;
    this->setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("QWriter")));
    tabOpenFiles->setTabText(index, QFileInfo(fileName).fileName());
    saveFile(fileName);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize sz = event->size();
    sizeWindLabel->setText(tr("%1, %2").arg(sz.width()).arg(sz.height()));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    /*if (obj == mainText) {
        if (event->type() == QEvent::ContextMenu) {
            QMenu contextMenu(this);
            contextMenu.addAction(undoAct);
            contextMenu.addAction(redoAct);
            contextMenu.addSeparator();
            contextMenu.addAction(copyAct);
            contextMenu.addAction(pasteAct);
            contextMenu.addAction(cutAct);
            contextMenu.exec(QCursor::pos());
            return true;
        } else {
            return false;
        }
    } else {

        return QMainWindow::eventFilter(obj, event);
    }*/
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{

}

QString MainWindow::loadFile(const QString &fileName)
{
    QString strIn;
    QFile file(fileName);
    if (file.exists()) {

        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            //QMessageBox::warning(this, tr("SDI"), tr("Cannot read file %1:\n%2."). arg(fileName). arg(file.errorString()));
            return "";
        }

        v1 = curCodec;
        QTextCodec *incodec = QTextCodec::codecForName(v1.toByteArray());
        QTextStream in(&file);
        in.setCodec(incodec);
        QApplication::setOverrideCursor(Qt::WaitCursor);

        strIn = in.readAll();

        QApplication::restoreOverrideCursor();
    } else {
        this->curFile = "";
    }
    return strIn;
}

void MainWindow::finThread()
{

}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << mainText->text();
    QApplication::restoreOverrideCursor();
    return true;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    event->acceptProposedAction();

    if(urls.isEmpty())
        return;

    QString fileName;

    for (int i = 0; i < urls.size(); ++i) {
        fileName = urls.at(i).toLocalFile();
        //qDebug() << urls.at(i).scheme();
        /*
        if (urls.at(i).scheme() == "ftp") {
            QString localFileName = QFileInfo(urls.at(i).path()).fileName();
            ftpFile.setFileName(localFileName);
            if (!ftpFile.open(QIODevice::WriteOnly)) {
                return;
            }
            qDebug() << urls.at(i).host() << urls.at(i).port() << urls.at(i).userName() << urls.at(i).password() << urls.at(i).authority();
           ftp.connectToHost(urls.at(i).host(), urls.at(i).port(21));
           if (!urls.at(i).userName().isEmpty()) {
                ftp.login(urls.at(i).userName(), urls.at(i).password());
            } else {
                ftp.login();
            }
            ftp.get(urls.at(i).path(), &ftpFile);
            ftp.close();

        } else { 
        */
            QFile file(fileName);
            if (file.exists())
                openFile(fileName);
        //}
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QString fileName;
    if (tabOpenFiles->count() > 0) {
        for (int i = 0; i < tabOpenFiles->count(); ++i) {
            tabOpenFiles->setCurrentIndex(i);
            if (mainText->isModified()) {
                QMessageBox msgBox;
                msgBox.setWindowTitle(QObject::tr("Exit"));
                msgBox.setText(tr("Save file:\n %1?").arg(fileNames.at(i).toString()));
                QPushButton *saveButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
                QPushButton *discardButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
                QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
                msgBox.setDefaultButton(saveButton);
                msgBox.setEscapeButton(cancelButton);
                msgBox.exec();

                if (msgBox.clickedButton() == saveButton) {
                    QFile file(fileNames.at(index).toString());

                    if (!file.exists()) {
                        fileName = QFileDialog::getSaveFileName(this);
                        if (fileName.isEmpty())
                            return;

                        if (saveFile(fileName)) {
                            if(i == (tabOpenFiles->count()-1))
                                break;
                        }
                    } else {
                        index = i;
                        saveFile(fileNames.at(i).toString());
                        if (i == (tabOpenFiles->count()-1))
                            break;
                    }
                }

                if (msgBox.clickedButton() == discardButton) {
                    if(i == (tabOpenFiles->count()-1))
                        break;
                }

                if (msgBox.clickedButton() == cancelButton) {
                    event->ignore();
                    return;
                }
            }
        }
    }
    event->accept();
}

bool MainWindow::accClose()
{
   if(mainText->isModified())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("Exit"));
        msgBox.setText(tr("Save file:\n %1?").arg(fileNames.at(index).toString()));
        QPushButton *saveButton = msgBox.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *discardButton = msgBox.addButton(tr("No"), QMessageBox::ActionRole);
        QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::ActionRole);
        msgBox.setDefaultButton(saveButton);
        msgBox.setEscapeButton(cancelButton);
        msgBox.exec();

        if (msgBox.clickedButton() == saveButton) {
            QFile file(fileNames.at(index).toString());

            if (!file.exists()) {
                QString fileName = QFileDialog::getSaveFileName(this);
                if (fileName.isEmpty())
                    return false;
                saveFile(fileName);
                return true;

            } else {
                saveFile(fileNames.at(index).toString());
                return true;
            }
        }

        if (msgBox.clickedButton() == discardButton)
            return true;

        if (msgBox.clickedButton() == cancelButton)
            return false;

    } else {
        return true;
    }
}

void MainWindow::extToHightlightStyle(const QString &ext)
{
    QString extention;
    QMultiMap<QString,QString>::iterator it = fileTypesAssoc.begin();
    for (; it != fileTypesAssoc.end(); ++it) {
        if (it.value() == ext) {
            //qDebug() << it.key() << it.value();
            extention = it.key();
            break;
        } else {
            extention = "none";
        }
    }

    if (extention == "none") {
        txtStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("none");
    }

    if (extention == "bash") {
        bashStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("bash");
    }

    if (extention == "batch") {
        batchStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("batch");
    }

    if (extention == "cmake") {
        cmakeStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("cmake");
    }

    if(extention == "cpp") {
        cppStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("cpp");
    }

    if (extention == "csharp") {
        csharpStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("csharp");
    }

    if (extention == "css") {
        cssStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("css");
    }

    if (extention == "d") {
        mainText->setSyntaxHighlighter("d");
    }

    if (extention == "diff") {
        diffStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("diff");
    }

    if (extention == "fortran77") {
        fortran77StyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("fortran77");
    }

    if (extention == "html") {
        htmlStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("html");
    }

    if (extention == "java") {
        javaStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("java");
    }

    if (extention == "javascript") {
        javascriptStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("javascript");
    }

    if (extention == "lua") {
        luaStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("lua");
    }

    if (extention == "pascal") {
        pascalStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("pascal");
    }

    if (extention == "perl") {
        perlStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("perl");
    }

    if (extention == "php") {
        phpStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("php");
    }

    if (extention == "postscript") {
        postscriptStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("postscript");
    }

    if (extention == "pov") {
        povStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("pov");
    }

    if (extention == "properties") {
        propertiesStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("properties");
    }

    if (extention == "python") {
        pythonStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("python");
    }

    if (extention == "ruby") {
        rubyStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("ruby");
    }

    if (extention == "spice") {
        spiceStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("spice");
    }

    if (extention == "sql") {
        sqlStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("sql");
    }

    if (extention == "tcl") {
        tclStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("tcl");
    }

    if (extention == "tex") {
        texStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("tex");
    }

    if (extention == "verilog") {
        verilogStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("verilog");
    }

    if (extention == "vhdl") {
        vhdlStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("vhdl");
    }

    if (extention == "xml") {
        xmlStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("xml");
    }

    if (extention == "yaml") {
        yamlStyleAct->setChecked(true);
        mainText->setSyntaxHighlighter("yaml");
    }

}

void MainWindow::ftpDone(bool b) {
    if (b) {
        qDebug() << qPrintable(ftp.errorString());
        return;
    }
    ftpFile.close();
}

void MainWindow::reconnect() {

}

void MainWindow::zoomIn()
{
    if(index < 0)
        return;


    ++currentZoom;
    mainText->zoomTo(currentZoom + 1);
}

void MainWindow::zoomOut() {
    if(index < 0)
        return;

    --currentZoom;
    mainText->zoomTo(currentZoom);
}

void MainWindow::zoomNormal()
{
    if(index < 0)
        return;

    currentZoom = 0;
    mainText->zoomTo(currentZoom);
}

void MainWindow::changeCodec()
{
    if(index < 0)
        return;

    findCodecs();
    QStringList lst;
    foreach (QTextCodec *codec, codecs) {
        QString text = tr("%1").arg(QString(codec->name()));
        lst.push_back(text);
    }

    CodecDialog mydialog(this);
    mydialog.setCodecList(lst);
    mydialog.setCodecCombo(this->curCodec);
    if(mydialog.exec())	{

    }

    if (this->curCodec != mydialog.curentCodec) {
        this->curCodec = mydialog.curentCodec;
        //QString currentText = mainText->text();

        QFile file(fileNames.at(index).toString());
        //if(file.exists())
        mainText->setText(loadFile(fileNames.at(index).toString()));
        mainText->setModified(false);
    }
}

void MainWindow::modificationChanged(bool b) {
    if (b) {
        tabOpenFiles->setTabIcon(index, QIcon(":/images/tab_icon_red.png"));
        undoAct->setEnabled(mainText->isUndoAvailable());
        redoAct->setEnabled(mainText->isRedoAvailable());
    } else {
        tabOpenFiles->setTabIcon(index, QIcon(":/images/Save.png"));
    }
}

void MainWindow::copyAvailable(bool b) {
    copyAct->setEnabled(b);
    cutAct->setEnabled(b);
    //qDebug() << "sss";
}

void MainWindow::findCodecs()
{
    QMap<QString, QTextCodec *> codecMap;
    QRegExp iso8859RegExp("ISO[- ]8859-([0-9]+).*");

    foreach (int mib, QTextCodec::availableMibs()) {
        QTextCodec *codec = QTextCodec::codecForMib(mib);

        QString sortKey = codec->name().toUpper();
        int rank;

        if (sortKey.startsWith("UTF-8")) {
            rank = 1;
        } else if (sortKey.startsWith("UTF-16")) {
            rank = 2;
        } else if (iso8859RegExp.exactMatch(sortKey)) {
            if (iso8859RegExp.cap(1).size() == 1)
                rank = 3;
            else
                rank = 4;
        } else {
            rank = 5;
        }
        sortKey.prepend(QChar('0' + rank));

        codecMap.insert(sortKey, codec);
    }
    codecs = codecMap.values();
}

void MainWindow::copyToClip()
{
    if (index < 0)
        return;
    mainText->copy();
}

void MainWindow::pasteToClip()
{
    if (index < 0)
        return;
    mainText->paste();
}

void MainWindow::cutToClip()
{
    if (index < 0)
        return;
    mainText->cut();
}

void MainWindow::undoSlot()
{
    if (index < 0)
        return;
    mainText->undo();
    undoAct->setEnabled(mainText->isUndoAvailable());
    redoAct->setEnabled(mainText->isRedoAvailable());
}

void MainWindow::redoSlot()
{
    if (index < 0)
        return;
    mainText->redo();
    undoAct->setEnabled(mainText->isUndoAvailable());
    redoAct->setEnabled(mainText->isRedoAvailable());
}

void MainWindow::toolBarVis(int state)
{
    toolbarVisible = (state == Qt::Checked) ? true : false;
    toolBar->setVisible(toolbarVisible);
}

void MainWindow::statusBarVis(int state)
{
    statbarVisible = (state == Qt::Checked) ? true : false;
    statusBar()->setVisible(statbarVisible);
}

void MainWindow::toolBarVis(bool b)
{
    toolbarVisible = b;
    toolBar->setVisible(toolbarVisible);
}

void MainWindow::statusBarVis(bool b)
{
    statbarVisible = b;
    statusBar()->setVisible(statbarVisible);
}

void MainWindow::highlightCurrentLine(int state)
{
    if (index < 0)
        return;
    highlightCurLine = (state == Qt::Checked) ? true : false;
    mainText->setCaretLineVisible(highlightCurLine);
}

void MainWindow::highlightCurrentRow(int state)
{
    if (index < 0)
        return;
    highlightCurRow = (state == Qt::Checked) ? true : false;
    //mainText->highlightCurentRow(highlightCurRow);
}

void MainWindow::rightMargVis(int state) {
    if (index < 0)
        return;
    mainText->setEdgeMode((state == Qt::Checked) ? QsciScintilla::EdgeLine : QsciScintilla::EdgeNone);
}

void MainWindow::wrapText(int state) {
    if (index < 0)
        return;
    mainText->setWrapMode((state == Qt::Checked) ? QsciScintilla::WrapWord : QsciScintilla::WrapNone);
}

void MainWindow::rightMarginValChanged(int val) {
    if (index < 0)
        return;
    rightMargin = val;
    mainText->setEdgeColumn(rightMargin);
}

void MainWindow::blockNumberSignal(int state) {
    if (index < 0)
        return;
    numberBlock = (state == Qt::Checked) ? true : false;
    //mainText->numberBlockVisible(numberBlock);
    mainText->setMarginWidth(0, (numberBlock) ? 42 : 0);
}

void MainWindow::tabPositionChanged(int index) {
    tabPosition = index;
    switch(tabPosition) {
        case 0:
            tabOpenFiles->setTabPosition(QTabWidget::North);
        break;
        case 1:
            tabOpenFiles->setTabPosition(QTabWidget::South);
        break;
        case 2:
            tabOpenFiles->setTabPosition(QTabWidget::West);
        break;
        case 3:
            tabOpenFiles->setTabPosition(QTabWidget::East);
        break;
        default:
            tabOpenFiles->setTabPosition(QTabWidget::North);
        break;
    }
}

void MainWindow::selChanged()
{

}

void MainWindow::cursorPosChanged(int line, int pos)
{
    currentLine = line;
    currentRow = pos;

    QString selTxt(mainText->selectedText());
    int currentSelection = selTxt.count();

    textCursorPos->setText(tr("Ln: %1 Col: %2 Sel: %3").arg(currentLine + 1).arg(currentRow + 1).arg(currentSelection));
}

void MainWindow::slotSettings()
{
    if (index < 0)
        return;
    myGlobalSettings = new GlobalSettings(this);

    if (lang == "languages/qwriter_en.qm")
        myGlobalSettings->languageComboBox->setCurrentIndex(0);
    if (lang == "languages/qwriter_ru.qm")
        myGlobalSettings->languageComboBox->setCurrentIndex(1);

    myGlobalSettings->toolbarVis->setChecked(toolbarVisible);
    connect(myGlobalSettings->toolbarVis, SIGNAL(stateChanged(int)), this, SLOT(toolBarVis(int)));

    myGlobalSettings->statbarVis->setChecked(statbarVisible);
    connect(myGlobalSettings->statbarVis, SIGNAL(stateChanged(int)), this, SLOT(statusBarVis(int)));

    myGlobalSettings->tabSpacesSpinBox->setValue(spaces);

    myGlobalSettings->tabPositionComboBox->setCurrentIndex(tabPosition);
    connect(myGlobalSettings->tabPositionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tabPositionChanged(int)));

    myGlobalSettings->WrapText->setChecked(worldWrap);
    connect(myGlobalSettings->WrapText, SIGNAL(stateChanged(int)), this, SLOT(wrapText(int)));

    myGlobalSettings->highlightCurLine->setChecked(highlightCurLine);
    connect(myGlobalSettings->highlightCurLine, SIGNAL(stateChanged(int)), this, SLOT(highlightCurrentLine(int)));

    myGlobalSettings->highlightCurRow->setChecked(highlightCurRow);
    connect(myGlobalSettings->highlightCurRow, SIGNAL(stateChanged(int)), this, SLOT(highlightCurrentRow(int)));

    myGlobalSettings->displayRightMargin->setChecked(rightMarginVisible);
    connect(myGlobalSettings->displayRightMargin, SIGNAL(stateChanged(int)), this, SLOT(rightMargVis(int)));

    myGlobalSettings->rightMarginSpinBox->setValue(rightMargin);
    connect(myGlobalSettings->rightMarginSpinBox, SIGNAL(valueChanged(int)), this, SLOT(rightMarginValChanged(int)));

    myGlobalSettings->numberBlockCheckBox->setChecked(numberBlock);
    connect(myGlobalSettings->numberBlockCheckBox, SIGNAL(stateChanged(int)), this, SLOT(blockNumberSignal(int)));

    myGlobalSettings->exec();

    spaces = myGlobalSettings->tabSpacesSpinBox->value();

    mainText->setTabWidth(spaces);

    rightMarginVisible = myGlobalSettings->displayRightMargin->isChecked();

    rightMargin = myGlobalSettings->rightMarginSpinBox->value();

    worldWrap = myGlobalSettings->WrapText->isChecked();

    lang = myGlobalSettings->languageApp;

    if (index >= 0)
        mainText->setWrapMode((worldWrap) ? QsciScintilla::WrapWord : QsciScintilla::WrapNone);

    if (!lang.isEmpty()) {
        if (lang == "RU")
           lang = "languages/qwriter_ru.qm";
        if (lang == "EN")
           lang = "qwriter_en.qm";

        qApp->removeTranslator(&appTranslator);
        appTranslator.load(lang, qApp->applicationDirPath());
        qApp->installTranslator(&appTranslator);
        retranlateUi();
    }
}

void MainWindow::selStyleHightlight(QAction * actSel)
{
    if (index < 0)
        return;

    if (actSel == txtStyleAct) {
        mainText->setSyntaxHighlighter("none");
    }

    if (actSel == bashStyleAct) {
        mainText->setSyntaxHighlighter("bash");
    }

    if (actSel == batchStyleAct) {
        mainText->setSyntaxHighlighter("batch");
    }

    if (actSel == cmakeStyleAct) {
        mainText->setSyntaxHighlighter("cmake");
    }

    if (actSel == cppStyleAct) {
        mainText->setSyntaxHighlighter("cpp");
    }

    if (actSel == csharpStyleAct) {
        mainText->setSyntaxHighlighter("csharp");
    }

    if (actSel == dStyleAct) {
        mainText->setSyntaxHighlighter("d");
    }

    if (actSel == diffStyleAct) {
        mainText->setSyntaxHighlighter("diff");
    }

    if (actSel == fortran77StyleAct) {
        mainText->setSyntaxHighlighter("fortran77");
    }

    if (actSel == htmlStyleAct) {
        mainText->setSyntaxHighlighter("html");
    }

    if (actSel == javaStyleAct) {
        mainText->setSyntaxHighlighter("java");
    }

    if (actSel == javascriptStyleAct) {
        mainText->setSyntaxHighlighter("javascript");
    }

    if (actSel == luaStyleAct) {
        mainText->setSyntaxHighlighter("lua");
    }

    if (actSel == pascalStyleAct) {
        mainText->setSyntaxHighlighter("pascal");
    }

    if (actSel == perlStyleAct) {
        mainText->setSyntaxHighlighter("perl");
    }

    if (actSel == phpStyleAct) {
        mainText->setSyntaxHighlighter("php");
    }

    if (actSel == postscriptStyleAct) {
        mainText->setSyntaxHighlighter("postscript");
    }

    if (actSel == povStyleAct) {
        mainText->setSyntaxHighlighter("pov");
    }

    if (actSel == propertiesStyleAct) {
        mainText->setSyntaxHighlighter("properties");
    }


    if (actSel == pythonStyleAct) {
        mainText->setSyntaxHighlighter("python");
    }

    if (actSel == rubyStyleAct) {
        mainText->setSyntaxHighlighter("ruby");
    }

    if (actSel == spiceStyleAct) {
        mainText->setSyntaxHighlighter("spice");
    }

    if (actSel == sqlStyleAct) {
        mainText->setSyntaxHighlighter("sql");
    }

    if (actSel == tclStyleAct) {
        mainText->setSyntaxHighlighter("tcl");
    }

    if (actSel == texStyleAct) {
        mainText->setSyntaxHighlighter("tex");
    }

    if (actSel == verilogStyleAct) {
        mainText->setSyntaxHighlighter("verilog");
    }

    if (actSel == vhdlStyleAct) {
        mainText->setSyntaxHighlighter("vhdl");
    }

    if (actSel == xmlStyleAct) {
        mainText->setSyntaxHighlighter("xml");
    }

    if (actSel == yamlStyleAct) {
        mainText->setSyntaxHighlighter("yaml");
    }
}

void MainWindow::slotPrint()
{
    if (index < 0)
        return;
    QsciPrinter printer;
    QPrintDialog printDial(&printer, this);

    if (printDial.exec() == QDialog::Accepted) {
        printer.printRange(mainText, 0);
    }
}

void MainWindow::findSlot()
{
    if (index >= 0) {
        if (mainText->hasSelectedText()) {
            findDialog->setSearchedText(mainText->selectedText());
        }
        findDialog->show();
    }
}

void MainWindow::findNext()
{
    if (index < 0)
        return;
    if (notFound == 1)
        return;

    if(!mainText->findFirst(findExpr, findRE, findCS, findWO, findWrap, true, currentLine, currentRow)) {
        if (!mainText->findFirst(findExpr, findRE, findCS, findWO, findWrap, true, 0, 0)) {
            notFound = 1;
        }
    }
}

void MainWindow::findPrev()
{
    if (index < 0)
        return;

    if (mainText->hasSelectedText()) {
        int lineFrom;
        int indexFrom;
        int lineTo;
        int indexTo;

        mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);

        if (!mainText->findFirst(findExpr, findRE, findCS, findWO, findWrap, false, currentLine, indexFrom)) {
            if (!mainText->findFirst(findExpr, findRE, findCS, findWO, findWrap, false, mainText->lines(), mainText->text(mainText->lines() - 1).length())) {
                notFound = 1;
            }
        }
    } else {
        mainText->findFirst(findExpr, findRE, findCS, findWO, findWrap, false, currentLine, currentRow);
    }

}

void MainWindow::replaceNext()
{
    if (index < 0)
        return;
    findNext();
    mainText->replace(replaceTxt);
}

void MainWindow::replacePrev()
{
    if (index < 0)
        return;
    findPrev();
    mainText->replace(replaceTxt);
}

void MainWindow::closeFindWidg()
{
    if(index >= 0)
        mainText->setFocus();
    findWidg->hide();
}

void MainWindow::findFirst(const QString &expr, bool re, bool cs,
                          bool wo, bool wrap, bool forward,
                          int line, int index, bool show)
{
    //if(index < 0)
    //    return;
    //qDebug() << "find slot!!!" << expr;

    findExpr = expr;
    findRE = re;
    findCS = cs;
    findWO = wo;
    findWrap = wrap;
    findForward = forward;
    notFound = 0;

    if (findForward)
        findNext();
    else
        findPrev();
}

void MainWindow::marginClicked(int margin, int line, Qt::KeyboardModifiers state) {
    if (mainText->markersAtLine(line) == 0)
        mainText->markerAdd(line, 0);
    else
        mainText->markerDelete(line, 0);
}

void MainWindow::replaceFirst(const QString &text) {
    replaceTxt = text;

    mainText->replace(replaceTxt);
}

void MainWindow::goToLine()
{
    if(index < 0)
        return;

    int line, pos;
    mainText->getCursorPosition(&line, &pos);

    GoToLineDialog goToLinedial(this, line, mainText->lines());
    goToLinedial.exec();
    int toLine = goToLinedial.toLine() - 1;
    mainText->setCursorPosition(toLine, 0);
}

void MainWindow::bookMarkSlot()
{
    if(index < 0)
        return;
    int line, pos;
    mainText->getCursorPosition(&line, &pos);

    if (mainText->markersAtLine(line) == 0)
        mainText->markerAdd(line, 0);
    else
        mainText->markerDelete(line, 0);
}

void MainWindow::nextBookMarkSlot()
{
    if(index < 0)
        return;

    int line, pos;
    mainText->getCursorPosition(&line, &pos);

    mainText->setCursorPosition(mainText->markerFindNext(line + 1, 1), 0);
}

void MainWindow::prevBookMarkSlot()
{
    if(index < 0)
        return;

    int line, pos;
    mainText->getCursorPosition(&line, &pos);

    mainText->setCursorPosition(mainText->markerFindPrevious(line - 1, 1), 0);
}

void MainWindow::replaceNextClicked()
{

}


void MainWindow::replacePrevClicked()
{

}

void MainWindow::commentLine() {
    if (index < 0)
        return;
    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    if (mainText->hasSelectedText()) {
        mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);

        //mainText->setSelection(lineFrom, 0, lineTo, mainText->text(lineTo).length() - 1);

        for (int i = lineFrom, j = 0; i <= lineTo; ++i, ++j) {
            QString text = mainText->text(i);
            if (text.contains(QRegExp("^[ \t]*//"))) {
                mainText->setSelection(i, 0, i, text.length());
                mainText->removeSelectedText();
                text.remove(QRegExp("^[ \t]*//"));
                mainText->insertAt(text, i, 0);
            } else {
                mainText->insertAt("//", i, 0);
            }
        }
    } else {
        QString text = mainText->text(currentLine);
        if (text.contains(QRegExp("^[ \t]*//"))) {
            mainText->setSelection(currentLine, 0, currentLine, text.length());
            mainText->removeSelectedText();
            text.remove(QRegExp("^[ \t]*//"));
            mainText->insertAt(text, currentLine, 0);
        } else {
            mainText->insertAt("//", currentLine, 0);
        }
    }
    mainText->endUndoAction();
}

void MainWindow::streamComments() {
    if (index < 0)
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    mainText->beginUndoAction();
    mainText->insertAt("/*", lineFrom, indexFrom);
    mainText->insertAt("*/", lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::deleteLines() {
    if (index < 0)
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    if (mainText->hasSelectedText()) {
        mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
        mainText->setSelection(lineFrom, 0, lineTo, mainText->text(lineTo).length());
        mainText->removeSelectedText();
    } else {
        mainText->setSelection(currentLine, 0, currentLine, mainText->text(currentLine).length());
        mainText->removeSelectedText();
    }
    mainText->endUndoAction();
}

void MainWindow::duplicateLines() {
    if (index < 0)
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    if (mainText->hasSelectedText()) {
        mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
        mainText->setSelection(lineFrom, 0, lineTo, mainText->text(lineTo).length());
        QString text = mainText->selectedText();
        mainText->insertAt(text, lineTo, mainText->text(lineTo).length());
        mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    } else {
        QString text = mainText->text(currentLine);
        mainText->insertAt(text, currentLine, 0);
    }
    mainText->endUndoAction();
}

void MainWindow::caseUpper() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);

    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.toUpper(), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::caseLower() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);

    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.toLower(), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::escapeQuotes() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.replace(QString("'"), QString("\\\'")), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();

}

void MainWindow::escapeDQuotes() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.replace(QString("\""), QString("\\\"")), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::unescapeQuotes() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.replace(QString("\\\'"), QString("'")), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::unescapeDQuotes() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.replace(QString("\\\""), QString("\"")), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::convertQuotes() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.replace(QString("\""), QString("\'")), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::convertDQuotes() {
    if (index < 0)
        return;

    if (!mainText->hasSelectedText())
        return;

    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;

    mainText->beginUndoAction();
    mainText->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
    QString text = mainText->selectedText();
    mainText->removeSelectedText();
    mainText->insertAt(text.replace(QString("\'"), QString("\"")), lineFrom, indexFrom);
    mainText->setSelection(lineFrom, indexFrom, lineTo, indexTo);
    mainText->endUndoAction();
}

void MainWindow::changeTabIndex(int newIndex) {
    index = newIndex;    
    if (index == -1) {
        saveFileAct->setEnabled(false);
        saveAsFileAct->setEnabled(false);
        printAction->setEnabled(false);
        closeAction->setEnabled(false);
        findAct->setEnabled(false);
        findNextAct->setEnabled(false);
        findPrevAct->setEnabled(false);
        replaceNextAct->setEnabled(false);
        replacePrevAct->setEnabled(false);
        goToLineAct->setEnabled(false);
        bookMarkAct->setEnabled(false);
        nextBookMarkAct->setEnabled(false);
        previousBookMarkAct->setEnabled(false);
        changeCodecAct->setEnabled(false);
        zoomInAct->setEnabled(false);
        zoomOutAct->setEnabled(false);
        zoomNormalAct->setEnabled(false);
        styleHighlightMenu->setEnabled(false);
        convertQuotesAct->setEnabled(false);
        convertDQuotesAct->setEnabled(false);
        caseUpperAct->setEnabled(false);
        caseLowerAct->setEnabled(false);
        escapeQuotesAct->setEnabled(false);
        escapeDQuotesAct->setEnabled(false);
        unescapeQuotesAct->setEnabled(false);
        unescapeDQuotesAct->setEnabled(false);
        settingsMenu->setEnabled(false);
        settingsAct->setEnabled(false);
        this->setWindowTitle(tr("%1").arg(tr("QWriter")));
        return;
    } else {
        saveFileAct->setEnabled(true);
        saveAsFileAct->setEnabled(true);
        printAction->setEnabled(true);
        closeAction->setEnabled(true);
        pasteAct->setEnabled(true);
        findAct->setEnabled(true);
        findNextAct->setEnabled(true);
        findPrevAct->setEnabled(true);
        replaceNextAct->setEnabled(true);
        replacePrevAct->setEnabled(true);
        goToLineAct->setEnabled(true);
        bookMarkAct->setEnabled(true);
        nextBookMarkAct->setEnabled(true);
        previousBookMarkAct->setEnabled(true);
        changeCodecAct->setEnabled(true);
        zoomInAct->setEnabled(true);
        zoomOutAct->setEnabled(true);
        zoomNormalAct->setEnabled(true);
        styleHighlightMenu->setEnabled(true);
        settingsMenu->setEnabled(true);
        settingsAct->setEnabled(true);
        tabOpenFiles->setCurrentIndex(index);
        mainText->setFocus();
    }
    mainText = qobject_cast<TextEdit *>(tabOpenFiles->widget(index));

    mainText->setCaretLineVisible(highlightCurLine);
    mainText->setTabWidth(spaces);
    mainText->setMarginWidth(0, (numberBlock) ? 42 : 0);
    mainText->zoomTo(currentZoom);
    curFile = fileNames.at(index).toString();

    undoAct->setEnabled(mainText->isUndoAvailable());
    redoAct->setEnabled(mainText->isRedoAvailable());

    QString selTxt(mainText->selectedText());
    int sel = selTxt.count();
    if (sel > 0) {
        copyAct->setEnabled(true);
        cutAct->setEnabled(true);
    } else {
        copyAct->setEnabled(false);
        cutAct->setEnabled(false);
    }

    this->setWindowTitle(tr("%1 - %2").arg(fileNames.at(index).toString()).arg(tr("QWriter")));

    mainText->setWrapMode((worldWrap) ? QsciScintilla::WrapWord : QsciScintilla::WrapNone);

    QString styleHL = mainText->syntaxHighlighter();

    if (styleHL == "none") {
        txtStyleAct->setChecked(true);
    }

    if (styleHL == "bash") {
        bashStyleAct->setChecked(true);
    }

    if (styleHL == "batch") {
        batchStyleAct->setChecked(true);
    }

    if (styleHL == "cmake") {
        cmakeStyleAct->setChecked(true);
    }

    if(styleHL == "cpp") {
        cppStyleAct->setChecked(true);
    }

    if (styleHL == "csharp") {
        csharpStyleAct->setChecked(true);
    }

    if (styleHL == "css") {
        cssStyleAct->setChecked(true);
    }

    if (styleHL == "d") {
        dStyleAct->setChecked(true);
    }

    if (styleHL == "diff") {
        diffStyleAct->setChecked(true);
    }

    if (styleHL == "fortran77") {
        fortran77StyleAct->setChecked(true);
    }

    if (styleHL == "html") {
        htmlStyleAct->setChecked(true);
    }

    if (styleHL == "java") {
        javaStyleAct->setChecked(true);
    }

    if (styleHL == "javascript") {
        javascriptStyleAct->setChecked(true);
    }

    if (styleHL == "lua") {
        luaStyleAct->setChecked(true);
    }

    if (styleHL == "pascal") {
        pascalStyleAct->setChecked(true);
    }

    if (styleHL == "perl") {
        perlStyleAct->setChecked(true);
    }

    if (styleHL == "php") {
        phpStyleAct->setChecked(true);
    }

    if (styleHL == "postscript") {
        postscriptStyleAct->setChecked(true);
    }

    if (styleHL == "pov") {
        povStyleAct->setChecked(true);
    }

    if (styleHL == "properties") {
        propertiesStyleAct->setChecked(true);
    }

    if (styleHL == "python") {
        pythonStyleAct->setChecked(true);
    }

    if (styleHL == "ruby") {
        rubyStyleAct->setChecked(true);
    }

    if (styleHL == "spice") {
        spiceStyleAct->setChecked(true);
    }

    if (styleHL == "sql") {
        sqlStyleAct->setChecked(true);
    }

    if (styleHL == "tcl") {
        tclStyleAct->setChecked(true);
    }

    if (styleHL == "tex") {
        texStyleAct->setChecked(true);
    }

    if (styleHL == "verilog") {
        verilogStyleAct->setChecked(true);
    }

    if (styleHL == "vhdl") {
        vhdlStyleAct->setChecked(true);
    }

    if (styleHL == "xml") {
        xmlStyleAct->setChecked(true);
    }

    if (styleHL == "yaml") {
        yamlStyleAct->setChecked(true);
    }
}

void MainWindow::tabMoved(int from, int to) {
    QString str = fileNames.at(from).toString();
    fileNames.removeAt(from);
    fileNames.insert(to, str);
    index = tabOpenFiles->currentIndex();
    //qDebug() << from << to << index << tabOpenFiles->currentIndex();
}
