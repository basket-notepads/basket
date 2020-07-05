/***************************************************************************
 *   Copyright (C) 2003 by Sébastien Laoût                                 *
 *   slaout@linux62.org                                                    *
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

#include "application.h"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QTimer>
#include <QCommandLineParser>
#include <QDir>

#include <KLocalizedString>

#include "global.h"
#include "bnpview.h"
#include "config.h"
#include "aboutdata.h"
#include "mainwindow.h"

#ifdef WITH_LIBGIT2
extern "C" {
#include <git2.h>
}
#endif

Application::Application(int &argc, char **argv)
        : QApplication(argc, argv)
        , m_service(KDBusService::Unique)
{

    KLocalizedString::setApplicationDomain("basket");
    KAboutData::setApplicationData(AboutData());
    //BasketPart::createAboutData();

    connect(&m_service, &KDBusService::activateRequested, this, &Application::onActivateRequested);

    newInstance();


    #ifdef WITH_LIBGIT2
        #if LIBGIT2_VER_MAJOR >= 1
            git_libgit2_init();
        #elif LIBGIT2_VER_MINOR >= 22  // v0.22
            git_libgit2_init();
        #else
            git_threads_init();
        #endif
    #endif
}

Application::~Application()
{
    #ifdef WITH_LIBGIT2
        #if LIBGIT2_VER_MAJOR >= 1
            git_libgit2_shutdown();
        #elif LIBGIT2_VER_MINOR >= 22  // v0.22
            git_libgit2_shutdown();
        #else
            git_threads_shutdown();
        #endif
    #endif
}

int Application::newInstance()
{
    //KUniqueApplication::newInstance();

    return 0;
}

void Application::tryLoadFile(const QStringList& args, const QString& workingDir)
{
    // Open the basket archive or template file supplied as argument:
    if (args.count() >= 1) {
        QString fileName = QDir(workingDir).filePath(args.last());

        if (QFile::exists(fileName)) {
            QFileInfo fileInfo(fileName);
            if (fileInfo.absoluteFilePath().contains(Global::basketsFolder())) {
                QString folder = fileInfo.absolutePath().split("/").last();
                folder.append("/");
                BNPView::s_basketToOpen = folder;
                QTimer::singleShot(100, Global::bnpView, SLOT(delayedOpenBasket()));
            } else if (!fileInfo.isDir()) { // Do not mis-interpret data-folder param!
                // Tags are not loaded until Global::bnpView::lateInit() is called.
                // It is called 0ms after the application start.
                BNPView::s_fileToOpen = fileName;
                QTimer::singleShot(100, Global::bnpView, SLOT(delayedOpenArchive()));
                //              Global::bnpView->openArchive(fileName);

            }
        }
    }
}

void Application::onActivateRequested(const QStringList& args, const QString& workingDir)
{
  if (MainWindow* wnd = Global::mainWindow()) {
      //Restore window:
      wnd->show(); //from tray
      wnd->setWindowState(Qt::WindowActive); //from minimized
      //Raise to the top
      wnd->raise();
  }
  tryLoadFile(args, workingDir);
}
