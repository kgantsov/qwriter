CONFIG += qt \
    warn_on
DESTDIR = bin
QT += network
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
HEADERS = src/MainWindow.h \
    src/CodecDialog.h \
    src/Highlighter.h \
    src/AboutDialog.h \
    src/GlobalSettings.h \
    src/FindWidget.h \
    src/TextEdit.h \
    src/GoToLineDialog.h \
    src/finddialog.h
SOURCES = src/MainWindow.cpp \
    src/CodecDialog.cpp \
    src/Highlighter.cpp \
    src/main.cpp \
    src/AboutDialog.cpp \
    src/GlobalSettings.cpp \
    src/FindWidget.cpp \
    src/TextEdit.cpp \
    src/GoToLineDialog.cpp \
    src/finddialog.cpp
TEMPLATE = app
RESOURCES = qwriter.qrc
TRANSLATIONS = languages/qwriter_ru.ts
LIBS += -lqscintilla2
CODEC = UTF-8
win32 { 
    RC_FILE = resource/win_win.rc
    include(qtsingleapplication-2.6-opensource/windows/src/qtsingleapplication.pri)
}
linux-*:include(qtsingleapplication-2.6-opensource/linux/src/qtsingleapplication.pri)
macx:
