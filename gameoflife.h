#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include <random>
#include <QTimer>
#include <QMouseEvent>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 10;
const int NUM_INITIAL_CELLS = 500;

namespace Ui {
class GameofLife;
}

class Cell {
public:
    Cell(bool alive = false);

    bool isAlive() const;
    void setAlive(bool alive);

private:
    bool alive;
};

class GameofLife : public QMainWindow
{
    Q_OBJECT

public:
    GameofLife(QWidget *parent = nullptr);
    ~GameofLife();

    void randomizeCells();
    void updateCells();
    void drawCells();
    void clearCells();
    int countAliveNeighbors(int row, int col);
    void updateGame();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::GameofLife *ui;
    std::vector<std::vector<Cell>> cells;
    QTimer *timer;
    QGraphicsScene* scene;
    bool gameRunning;
    bool addingCellMode;
};

#endif // GAMEOFLIFE_H

