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

#ifndef WLSHELLSURFACE_H
#define WLSHELLSURFACE_H

#include "waylandobject.h"

#include <wayland-server.h>
#include <QPoint>

namespace Wayland {

class Compositor;
class Surface;
class ShellSurface;
class ShellSurfaceResizeGrabber;
class ShellSurfaceMoveGrabber;

class Shell
{
public:
    Shell();

    static void bind_func(struct wl_client *client, void *data,
                          uint32_t version, uint32_t id);
private:
    static void get_shell_surface(struct wl_client *client,
                  struct wl_resource *resource,
                  uint32_t id,
                  struct wl_resource *surface);
    static const struct wl_shell_interface shell_interface;

};

class ShellSurface
{
public:
    ShellSurface(struct wl_client *client, uint32_t id, Surface *surface);
    void sendConfigure(uint32_t edges, int32_t width, int32_t height);

    Surface *surface() const;

    void adjustPosInResize();
    QPointF adjustedPosToTransientParent() const;
    void resetResizeGrabber();
    void resetMoveGrabber();

    ShellSurface *transientParent() const;
    void setOffset(const QPointF &offset);

private:
    struct wl_resource *m_shellSurface;
    Surface *m_surface;

    ShellSurfaceResizeGrabber *m_resizeGrabber;
    ShellSurfaceMoveGrabber *m_moveGrabber;

    ShellSurface *m_transientParent;

    int32_t m_xOffset;
    int32_t m_yOffset;

    static void move(struct wl_client *client,
                     struct wl_resource *shell_surface_resource,
                     struct wl_resource *input_device_super,
                     uint32_t time);
    static void resize(struct wl_client *client,
                       struct wl_resource *shell_surface_resource,
                       struct wl_resource *input_device,
                       uint32_t time,
                       uint32_t edges);
    static void set_toplevel(struct wl_client *client,
                             struct wl_resource *shell_surface_resource);
    static void set_transient(struct wl_client *client,
                              struct wl_resource *shell_surface_resource,
                              struct wl_resource *parent_surface_resource,
                              int x,
                              int y,
                              uint32_t flags);
    static void set_fullscreen(struct wl_client *client,
                               struct wl_resource *shell_surface_resource,
                               uint32_t method,
                               uint32_t framerate,
                               struct wl_resource *output);
    static void set_popup(struct wl_client *client,
                          struct wl_resource *resource,
                          struct wl_resource *input_device,
                          uint32_t time,
                          struct wl_resource *parent,
                          int32_t x,
                          int32_t y,
                          uint32_t flags);
    static void set_maximized(struct wl_client *client,
                              struct wl_resource *shell_surface_resource,
                              struct wl_resource *output);
    static void pong(struct wl_client *client,
                     struct wl_resource *resource,
                     uint32_t serial);
    static void set_title(struct wl_client *client,
                          struct wl_resource *resource,
                          const char *title);
    static void set_class(struct wl_client *client,
                          struct wl_resource *resource,
                          const char *class_);

    static const struct wl_shell_surface_interface shell_surface_interface;
};

class ShellSurfaceGrabber : public Object<wl_pointer_grab>
{
public:
    ShellSurfaceGrabber(ShellSurface *shellSurface, const struct wl_pointer_grab_interface *interface);
    ~ShellSurfaceGrabber();

    struct wl_listener surface_destroy_listener;
    static void destroy(struct wl_listener *listener,
             struct wl_resource *resource, uint32_t time);

    ShellSurface *shell_surface;
};

class ShellSurfaceResizeGrabber : public ShellSurfaceGrabber
{
public:
    ShellSurfaceResizeGrabber(ShellSurface *shellSurface);


    enum wl_shell_surface_resize resize_edges;
    int32_t width;
    int32_t height;

    static void focus(struct wl_pointer_grab *grab,
                      struct wl_surface *surface, int32_t x, int32_t y);
    static void motion(struct wl_pointer_grab *grab,
                       uint32_t time, int32_t x, int32_t y);
    static void button(struct wl_pointer_grab *grab,
                       uint32_t time, uint32_t mouse_grabber_button, uint32_t state);
    static const struct wl_pointer_grab_interface resize_grabber_interface;
};

class ShellSurfaceMoveGrabber : public ShellSurfaceGrabber
{
public:
    ShellSurfaceMoveGrabber(ShellSurface *shellSurface);

    int32_t offset_x;
    int32_t offset_y;

    static void focus(struct wl_pointer_grab *grab,
                      struct wl_surface *surface, int32_t x, int32_t y);
    static void motion(struct wl_pointer_grab *grab,
                       uint32_t time, int32_t x, int32_t y);
    static void button(struct wl_pointer_grab *grab,
                       uint32_t time, uint32_t mouse_grabber_button, uint32_t state);
    static const struct wl_pointer_grab_interface move_grabber_interface;
};



}

#endif // WLSHELLSURFACE_H
