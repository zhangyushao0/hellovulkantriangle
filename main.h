#include "trianglerenderer.h"
class VulkanWindow : public QVulkanWindow {
  Q_OBJECT
public:
  QVulkanWindowRenderer *createRenderer() override;
  void resizeEvent(QResizeEvent *event) override;
  void moveEvent(QMoveEvent *event) override;
  void exposeEvent(QExposeEvent *event) override;
  void closeEvent(QCloseEvent *event) override;
  QVulkanWindowRenderer *renderer() const { return m_renderer; }
  Q_INVOKABLE void addSpeed(float delta);
signals:
  void windowResized(int width, int height);
  void windowMoved(int x, int y);
  void windowActivated();
  void windowClosed();

private:
  QVulkanWindowRenderer *m_renderer = nullptr;
};