#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QDebug>
#include <QGraphicsItem>

class GraphicsScene : public QGraphicsScene
{
    QPointF start_point;
    QPointF next_point;

    QVector<QGraphicsItem*> layers;
    QVector<int> layers_counter;
    int layer_count;

public:
    explicit GraphicsScene(QWidget *parent = nullptr);
    ~GraphicsScene();

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    void push_back(QPixmap p);
    void pop_back();
    void repaint();

    enum Tool {
        PEN,
        BOX,
        CIRCLE,
        NOT_PEN,
        // ... etc
    } current_tool = NOT_PEN;

    QPen pen = QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);


};

#endif // GRAPHICSSCENE_H
