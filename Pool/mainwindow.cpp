#include "mainwindow.h"

MainWindow::MainWindow(unique_ptr<SceneManager> pool_scene, QWidget *parent)
: QMainWindow(parent), updater(this), ticker(this), timer(), scene(std::move(pool_scene))
{
	this->resize(this->scene->veiwPort());
	this->setStyleSheet("Background-color: #000;");
	connect(&this->updater, SIGNAL(timeout()), this, SLOT(nextFrame()));
	connect(&this->ticker, SIGNAL(timeout()), this, SLOT(tick()));

	this->updater.start(1000 / FRAME_RATE);
	this->ticker.start(1000 / TICK_RATE);
	this->timer.start();
    this->setWindowTitle("Love & Peace");
}

void MainWindow::nextFrame() {
	this->update();
}

void MainWindow::tick() {
	double dtime = timer.restart() / 1000.0;
	this->scene->tick(dtime);
}

void MainWindow::paintEvent(QPaintEvent *) {
	QPainter painter(this);
    this->scene->draw(painter);
    //draw stick
    if(m_drawStick){
        QPen pen;
        pen.setColor(Qt::darkYellow);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawLine(m_line);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QVector2D pos;
    pos.setX(event->x());
    pos.setY(event->y());
    scene->press(pos);
    m_drawStick = scene->pressOnWhiteBall;
    //set up line
    if(m_drawStick){
        m_line.setP1(QPoint(pos.x(), pos.y()));
        m_line.setP2(QPoint(pos.x(), pos.y()));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_drawStick = false;
    QVector2D pos;
    pos.setX(event->x());
    pos.setY(event->y());
    scene->releaseMouse(pos);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //update stick position
    if(event->type() == QEvent::MouseMove){
        m_line.setP2(event->pos());
    }
    update();
}

MainWindow::~MainWindow()
{}
