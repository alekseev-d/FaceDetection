#include "zoom_view.h"

void ZoomView::redrawScene()
{
    QPoint currentPos = cursor().pos();
    translate(currentPos.x() - origin_pos.x(), origin_pos.y() - currentPos.y());
    origin_pos = currentPos;
}

ZoomView::~ZoomView()
{
    delete text_item;
    delete rect_item;
    delete pixmap_item;
}

ZoomView::ZoomView(QWidget *parent)
{
    text_item = new QGraphicsTextItem();
    rect_item = new QGraphicsRectItem();
    pixmap_item = new QGraphicsPixmapItem();
    text_item->setDefaultTextColor(QColor(Qt::GlobalColor::green));

    setScene(&scene);
    scene.setBackgroundBrush(scene_brush);
    scene.addItem(text_item);
    scene.addItem(rect_item);
    scene.addItem(pixmap_item);

    pixmap_item->setZValue(0);
    rect_item->setZValue(3);
    text_item->setZValue(3);

    connect(&refresh_timer, &QTimer::timeout, this, &ZoomView::redrawScene);
}

void ZoomView::setImage(const QPixmap& image)
{
    pixmap_item->setPixmap(image);
    pixmap_item->setOffset(-image.width() / 2, -image.height() / 2);
}

void ZoomView::resize(int w, int h)
{
    scene.update(0, 0, w, h);
}

void ZoomView::setRectangle(int x, int y, int width, int height, const QString& text)
{
    scale(1.25, 1.25);
    text_item->setScale(1.5);

    rect_item->setRect(x, y, width, height);
    rect_item->setPen(QPen(Qt::green));

    text_item->setPlainText(text);
    text_item->setPos(x, y + height);
}

void ZoomView::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numDegrees.isNull())
    {
        if(numDegrees.y() > 0)
        {
            scale(2.0,2.0);
            text_item->setScale(text_item->scale() / 1.1);
            setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        }
        else
        {
           text_item->setScale(text_item->scale() * 1.1);
           setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
           scale(0.5,0.5);
        }
    }
}

void ZoomView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        origin_pos = event->pos();
        refresh_timer.start(1);
    }
}

void ZoomView::mouseReleaseEvent(QMouseEvent *event)
{
    refresh_timer.stop();
}

