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

#include <QtGui/QApplication>
#include "MainWindow.h"
#include "qtsingleapplication.h"

int main(int argc, char ** argv)
{
    QTextCodec *codec = QTextCodec::codecForLocale();
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);

    QtSingleApplication app("QWriter", argc, argv);
    QString strMess;
    for(int i = 1; i < argc; ++i) {
        strMess += argv[i];
        if (i < argc-1)
            strMess += ";";
    }

    if (app.sendMessage(strMess))
        return 0;


    MainWindow win;
    win.show();

    for(int i = 1; i < argc; ++i)
        win.openFile(argv[i]);

    app.setActivationWindow(&win, false);

    QObject::connect(&app, SIGNAL(messageReceived(const QString&)),
                     &win, SLOT(messReceived(const QString&)));

    QObject::connect(&win, SIGNAL(needToShow()), &app, SLOT(activateWindow()));

    return app.exec();

}
