/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Compositor.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDSERVERBUFFERINTEGRATION_H
#define QWAYLANDSERVERBUFFERINTEGRATION_H

#include <QtCore/qglobal.h>
#include <QtCore/QSize>
#include <QtGui/qopengl.h>

#include <QtCompositor/qwaylandexport.h>

QT_BEGIN_NAMESPACE

class QWaylandCompositor;
class QOpenGLContext;
struct wl_client;
struct wl_resource;

namespace QtWayland {
    class Display;
}

class Q_COMPOSITOR_EXPORT QWaylandServerBuffer
{
public:
    QWaylandServerBuffer();
    virtual ~QWaylandServerBuffer();

    virtual void sendToClient(struct ::wl_client *);

    virtual GLuint createTexture(QOpenGLContext *);
    virtual bool isYInverted(struct ::wl_resource *) const;

    virtual QSize size() const;
};

class Q_COMPOSITOR_EXPORT QWaylandServerBufferIntegration
{
public:
    QWaylandServerBufferIntegration();
    virtual ~QWaylandServerBufferIntegration();

    virtual void initializeHardware(QWaylandCompositor *);

    virtual QWaylandServerBuffer *createServerBuffer();
};

QT_END_NAMESPACE

#endif //QWAYLANDSERVERBUFFERINTEGRATION_H
