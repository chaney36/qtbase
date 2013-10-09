/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QEGLFSWINDOW_H
#define QEGLFSWINDOW_H

#include "qeglfsintegration.h"
#include "qeglfsscreen.h"

#include <qpa/qplatformwindow.h>

QT_BEGIN_NAMESPACE

class QEglFSBackingStore;

class QEglFSWindow : public QPlatformWindow
{
public:
    QEglFSWindow(QWindow *w);
    ~QEglFSWindow();

    void setGeometry(const QRect &);
    QRect geometry() const;
    WId winId() const;
    void setVisible(bool visible);
    void requestActivateWindow();

    EGLSurface surface() const;
    QSurfaceFormat format() const;
    EGLNativeWindowType eglWindow() const;

    QEglFSScreen *screen() const;

    void create();
    void destroy();

    bool hasNativeWindow() const { return m_flags.testFlag(HasNativeWindow); }
    bool isRasterRoot() const { return m_flags.testFlag(IsRasterRoot); }

    QEglFSBackingStore *backingStore() { return m_backingStore; }
    void setBackingStore(QEglFSBackingStore *backingStore) { m_backingStore = backingStore; }

    virtual void invalidateSurface();
    virtual void resetSurface();

protected:
    EGLSurface m_surface;
    EGLNativeWindowType m_window;

private:
    EGLConfig m_config;
    QSurfaceFormat m_format;
    WId m_wid;
    QEglFSBackingStore *m_backingStore;

    enum Flag {
        Created = 0x01,
        HasNativeWindow = 0x02,
        IsRaster = 0x04,
        IsRasterRoot = 0x08
    };
    Q_DECLARE_FLAGS(Flags, Flag);
    Flags m_flags;
};

QT_END_NAMESPACE

#endif // QEGLFSWINDOW_H
