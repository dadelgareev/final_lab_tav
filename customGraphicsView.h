#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView> // Включаем заголовочный файл QGraphicsView
#include <QMouseEvent>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    CustomGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {}


protected:
    void mousePressEvent(QMouseEvent *event) override {
        // Передаем событие нажатия мыши в родительский класс QGraphicsView
        QGraphicsView::mousePressEvent(event);
        emit mouseClicked(event->pos().x(), event->pos().y());
    }

signals:
    // Создаем сигнал, который будет отправлять координаты нажатия мыши
    void mouseClicked(int x, int y);
};

#endif // CUSTOMGRAPHICSVIEW_H
