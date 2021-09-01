/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qamigabackingstore.h"
#include "qamigaintegration.h"
#include "qscreen.h"
#include <QtCore/qdebug.h>
#include <qpa/qplatformscreen.h>
#include <private/qguiapplication_p.h>

#define BOOL short
#include <proto/Picasso96API.h>
#include <proto/intuition.h>
#include <proto/graphics.h>

#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE

QAmigaBackingStore::QAmigaBackingStore(QWindow *window)
    : QPlatformBackingStore(window)
    , mDebug(QAmigaIntegration::instance()->options() & QAmigaIntegration::DebugBackingStore)
{
    if (mDebug)
        qDebug() << "QAmigaBackingStore::QAmigaBackingStore:" << (quintptr)this;
}

QAmigaBackingStore::~QAmigaBackingStore()
{
}

QPaintDevice *QAmigaBackingStore::paintDevice()
{
    if (mDebug)
        qDebug("QAmigaBackingStore::paintDevice");

    return &mImage;
}

void QAmigaBackingStore::flush(QWindow *window, const QRegion &region, const QPoint &offset)
{
    Q_UNUSED(region);
    Q_UNUSED(offset);

    if (mDebug) {
        static int c = 0;
        QString filename = QString("output%1.png").arg(c++, 4, 10, QLatin1Char('0'));
        qDebug() << "QAmigaBackingStore::flush() saving contents to" << filename.toLocal8Bit().constData();
        mImage.save(filename);
    }

    QAmigaWindow *amigaWindow = dynamic_cast<QAmigaWindow *>(window->handle());
    if(!amigaWindow) {
        cout << "Not an Amiga window!\n";
        return;
    }

    IGraphics->WritePixelArray(mImage.bits(),
        0, 0,
        4*mImage.width(), PIXF_A8R8G8B8,
        amigaWindow->intuitionWindow->RPort, 0, 0,
        mImage.width(), mImage.height());
}

void QAmigaBackingStore::resize(const QSize &size, const QRegion &)
{
    QImage::Format format = QGuiApplication::primaryScreen()->handle()->format();
    if (mImage.size() != size)
        mImage = QImage(size, format);
}

QT_END_NAMESPACE
