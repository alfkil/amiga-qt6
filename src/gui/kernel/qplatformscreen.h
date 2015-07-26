/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORMSCREEN_H
#define QPLATFORMSCREEN_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtCore/qmetatype.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qvariant.h>
#include <QtCore/qrect.h>
#include <QtCore/qobject.h>

#include <QtGui/qcursor.h>
#include <QtGui/qimage.h>
#include <QtGui/qwindowdefs.h>
#include <qpa/qplatformpixmap.h>

QT_BEGIN_NAMESPACE


class QPlatformBackingStore;
class QPlatformOpenGLContext;
class QPlatformScreenPrivate;
class QPlatformWindow;
class QPlatformCursor;
class QScreen;
class QSurfaceFormat;

typedef QPair<qreal, qreal> QDpi;


class Q_GUI_EXPORT QPlatformScreen
{
    Q_DECLARE_PRIVATE(QPlatformScreen)

public:
    enum SubpixelAntialiasingType { // copied from qfontengine_p.h since we can't include private headers
        Subpixel_None,
        Subpixel_RGB,
        Subpixel_BGR,
        Subpixel_VRGB,
        Subpixel_VBGR
    };

    enum PowerState {
        PowerStateOn,
        PowerStateStandby,
        PowerStateSuspend,
        PowerStateOff
    };

    QPlatformScreen();
    virtual ~QPlatformScreen();

    virtual QPixmap grabWindow(WId window, int x, int y, int width, int height) const;

    virtual QRect geometry() const = 0;
    virtual QRect availableGeometry() const {return geometry();}

    virtual int depth() const = 0;
    virtual QImage::Format format() const = 0;

    virtual QSizeF physicalSize() const;
    virtual QDpi logicalDpi() const;
    virtual qreal devicePixelRatio() const;

    virtual qreal refreshRate() const;

    virtual Qt::ScreenOrientation nativeOrientation() const;
    virtual Qt::ScreenOrientation orientation() const;
    virtual void setOrientationUpdateMask(Qt::ScreenOrientations mask);

    virtual QWindow *topLevelAt(const QPoint &point) const;
    virtual QList<QPlatformScreen *> virtualSiblings() const;

    QScreen *screen() const;

    //jl: should this function be in QPlatformIntegration
    //jl: maybe screenForWindow is a better name?
    static QPlatformScreen *platformScreenForWindow(const QWindow *window);

    virtual QString name() const { return QString(); }

    virtual QPlatformCursor *cursor() const;
    virtual SubpixelAntialiasingType subpixelAntialiasingTypeHint() const;

    virtual PowerState powerState() const;
    virtual void setPowerState(PowerState state);

    static int angleBetween(Qt::ScreenOrientation a, Qt::ScreenOrientation b);
    static QTransform transformBetween(Qt::ScreenOrientation a, Qt::ScreenOrientation b, const QRect &target);
    static QRect mapBetween(Qt::ScreenOrientation a, Qt::ScreenOrientation b, const QRect &rect);

protected:
    void resizeMaximizedWindows();

    QScopedPointer<QPlatformScreenPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QPlatformScreen)

    friend class QPlatformIntegration;
};

QT_END_NAMESPACE

#endif // QPLATFORMSCREEN_H
