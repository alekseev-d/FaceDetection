#ifndef ZOOMVIEW_H
#define ZOOMVIEW_H

#include <QTimer>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

class ZoomView : public QGraphicsView
{
    QGraphicsPixmapItem *pixmap_item;
    QGraphicsTextItem *text_item;
    QGraphicsRectItem *rect_item;

    QBrush scene_brush;

    QGraphicsScene scene;
    QTimer refresh_timer;

    void redrawScene();

public:
    QPoint origin_pos;

    ZoomView() = default;
    ~ZoomView();
    ZoomView(QWidget *parent = nullptr);

    void setImage(const QPixmap& image);
    void setRectangle(int x, int y, int width, int height, const QString& text);
    void resize(int w, int h);

    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // ZOOMVIEW_H
