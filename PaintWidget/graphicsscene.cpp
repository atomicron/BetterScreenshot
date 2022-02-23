#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QWidget *parent)
: QGraphicsScene(parent)
{
}

GraphicsScene::~GraphicsScene()
{
   for (auto x : layers)
       delete x;

   for (auto x : items())
       delete x;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    start_point = event->scenePos();
    next_point = start_point;
    layer_count = 0;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
   next_point = event->scenePos();

   if (current_tool == PEN)
   {
       layers.push_back(addLine(QLineF(start_point, next_point), pen));
       ++layer_count;
       start_point = next_point;
   }

   if (current_tool == BOX)
   {
       if (layer_count) // if it's not first click
       {
         layers.pop_back();
         --layer_count;
       }

       QGraphicsItem* item = addRect(QRectF(start_point, next_point), pen);
       layers.push_back(item);
       ++layer_count;

       repaint();
   }

   if (current_tool == CIRCLE)
   {
       if (layer_count) // if it's not first click
       {
         layers.pop_back();
         --layer_count;
       }

       QGraphicsItem* item = addEllipse(QRectF(start_point,next_point), pen);
       layers.push_back(item);
       ++layer_count;

       repaint();
   }

}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    layers_counter.push_back(layer_count);
    repaint();
}

void GraphicsScene::push_back(QPixmap p)
{
    layers.push_back(addPixmap(p));
}

void GraphicsScene::pop_back()
{
    if (layers.count() > 0 && layers_counter.count() > 0)
    {
        for (int i = 0; i < layers_counter.back(); ++i)
            layers.pop_back();
        layers_counter.pop_back();
    }
    repaint();
}

void GraphicsScene::repaint()
{
    for (auto item : items())
        removeItem(item);

    for (auto layer : layers)
        addItem(layer);
}

