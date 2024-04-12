#include "gameoflife.h"
#include "ui_gameoflife.h"
#include "customGraphicsView.h"

#include <QApplication>

Cell::Cell(bool alive) : alive(alive) {}

bool Cell::isAlive() const {
    return alive;
}

void Cell::setAlive(bool alive) {
    this->alive = alive;
}

GameofLife::GameofLife(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameofLife)
{
    ui->setupUi(this);
    // Создаем сцену для отображения клеток
    scene = new QGraphicsScene();

    ui->customGraphicsView->setScene(scene);


    gameRunning = true;
    addingCellMode = false;


    connect(ui->customGraphicsView, &CustomGraphicsView::mouseClicked, this, &GameofLife::addCell);

    // Создаем таймер для регулярного обновления игры
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameofLife::updateGame);

    // Задаем интервал обновления в миллисекундах (например, каждые 100 мс)
    timer->start(100);

    randomizeCells();
    drawCells();
}

void GameofLife::updateGame() {
    updateCells(); // Обновляем состояние игры
    drawCells(); // Получаем новую сцену с обновленными клетками
}

GameofLife::~GameofLife()
{
    delete ui;
}

void GameofLife::randomizeCells() {
    cells.resize(WINDOW_HEIGHT / CELL_SIZE, std::vector<Cell>(WINDOW_WIDTH / CELL_SIZE));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_row(0, cells.size() - 1);
    std::uniform_int_distribution<int> dis_col(0, cells[0].size() - 1);

    for (int i = 0; i < NUM_INITIAL_CELLS; ++i) {
        int row = dis_row(gen);
        int col = dis_col(gen);
        cells[row][col].setAlive(true);
    }
}

void GameofLife::updateCells() {
    std::vector<std::vector<Cell>> newCells(cells);

    for (size_t i = 0; i < cells.size(); ++i) {
        for (size_t j = 0; j < cells[i].size(); ++j) {
            int aliveNeighbors = countAliveNeighbors(i, j);

            if (cells[i][j].isAlive()) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newCells[i][j].setAlive(false); // Умирает от одиночества или перенаселенности
                }
            }
            else {
                if (aliveNeighbors == 3) {
                    newCells[i][j].setAlive(true); // Воскресает от трех соседей
                }
            }
        }
    }

    cells = newCells;
}

void GameofLife::drawCells() {
    // Очищаем сцену перед добавлением новых элементов
    scene->clear();

    for (size_t i = 0; i < cells.size(); ++i) {
        for (size_t j = 0; j < cells[i].size(); ++j) {
            if (cells[i][j].isAlive()) {
                QGraphicsRectItem* rect = new QGraphicsRectItem(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                rect->setBrush(Qt::black);
                scene->addItem(rect);
            }
        }
    }
}

void GameofLife::clearCells()
{
    scene->clear();

    for (size_t i = 0; i < cells.size(); ++i) {
        for (size_t j = 0; j < cells[i].size(); ++j) {
            cells[i][j].setAlive(false);
        }
    }
}

int GameofLife::countAliveNeighbors(int row, int col) {
    int aliveNeighbors = 0;
    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            int ni = row + di;
            int nj = col + dj;
            if (ni >= 0 && ni < cells.size() && nj >= 0 && nj < cells[0].size() && cells[ni][nj].isAlive()) {
                aliveNeighbors++;
            }
        }
    }
    return aliveNeighbors;
}
void GameofLife::addCell(int x, int y) {
    if (addingCellMode) {
        // Определяем индексы строки и столбца клетки на основе координат x и y
        int row = y / CELL_SIZE;
        int col = x / CELL_SIZE;

        // Проверяем, что индексы находятся в пределах массива клеток
        if (row >= 0 && row < cells.size() && col >= 0 && col < cells[0].size()) {
            // Устанавливаем состояние клетки в живое
            cells[row][col].setAlive(true);

            // Перерисовываем клетки на сцене
            drawCells();
        }
    }
}

void GameofLife::on_pushButton_clicked()
{
    gameRunning = !gameRunning;

    if (gameRunning) {
        timer->start();
        ui->label->setText("Активна");
    } else {
        timer->stop();
        ui->label->setText("Неактивна");
    }

}


void GameofLife::on_pushButton_2_clicked()
{
    clearCells();
    randomizeCells();
}


void GameofLife::on_pushButton_3_clicked()
{
    clearCells();
}


void GameofLife::on_pushButton_4_clicked()
{
    if (addingCellMode) {
        ui->pushButton_4->setText("Добавьте\n клетку");
    } else {
        ui->pushButton_4->setText("Выход\n из режима");
    }
    addingCellMode = !addingCellMode;
}




