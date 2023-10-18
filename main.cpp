// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "main.h"

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QVulkanInstance>
#include <QWidget>
#include <cstddef>
#include <qvulkanwindow.h>

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")

//! [2]

//! [2]
void VulkanWindow::resizeEvent(QResizeEvent *event) {
  // 处理事件，然后发出信号
  emit windowResized(event->size().width(), event->size().height());
  QVulkanWindow::resizeEvent(event);
}
// 移动窗口
void VulkanWindow::moveEvent(QMoveEvent *event) {
  // 处理事件，然后发出信号
  emit windowMoved(event->pos().x(), event->pos().y());
  QVulkanWindow::moveEvent(event);
}
// 激活窗口
void VulkanWindow::exposeEvent(QExposeEvent *event) {
  // 处理事件，然后发出信号
  emit windowActivated();
  QVulkanWindow::exposeEvent(event);
}
// 关闭窗口
void VulkanWindow::closeEvent(QCloseEvent *event) {
  // 处理事件，然后发出信号
  emit windowClosed();
  QVulkanWindow::closeEvent(event);
}
QVulkanWindowRenderer *VulkanWindow::createRenderer() {
  m_renderer = new TriangleRenderer(this, true);
  return m_renderer;
}

void VulkanWindow::addSpeed(float delta) {
  auto renderer = static_cast<TriangleRenderer *>(this->renderer());
  renderer->addSpeed(delta);
}
int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

  //! [0]
  QVulkanInstance inst;
  inst.setLayers({"VK_LAYER_KHRONOS_validation"});
  if (!inst.create())
    qFatal("Failed to create Vulkan instance: %d", inst.errorCode());
  //! [0]

  //! [1]
  VulkanWindow w;
  w.setVulkanInstance(&inst);
  w.resize(1024, 768);
  w.show();
  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/demo/main.qml"_qs);
  engine.rootContext()->setContextProperty(u"vulkanWindow"_qs, &w);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  engine.load(url);
  QJSEngine myEngine;
  QJSValue three = myEngine.evaluate("1 + 2");
  qDebug() << three.toInt();
  // ![1]

  return app.exec();
}
