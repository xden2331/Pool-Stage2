#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QPainter>

#include "util.h"
#include "scenemanager.h"

/**
 * @brief The top level class for controlling the window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
		/**
		 * @brief Constructor
		 *
		 * @param scene a Scene for the program to render
		 * @param parent the parent Qt Object
		 */
	MainWindow(unique_ptr<SceneManager> scene, QWidget* parent = 0);
    ~MainWindow();
public slots:
	/**
	 * @brief move the scene by a small timestep
	 */
	void tick();
	/**
	 * @brief draws the next frame
	 */
	void nextFrame();

protected:
    /**
     * @brief draws objects on the window
     *
     * @param event specifies regions to render
     */
	void paintEvent(QPaintEvent* event);

    /**
     * @brief mousePressEvent catches the press of mouse, and pass the position
     * to sceneManager to perform functionalities
     * @param event specifies the position where mouse press occurs
     */
    void mousePressEvent(QMouseEvent* event);

    /**
     * @brief mouseReleaseEvent catches the release of mouse, and passes it
     * to sceneManager to perform functionalities
     * @param event specifies the position where mouse releases
     */
    void mouseReleaseEvent(QMouseEvent* event);

    /**
     * @brief mouseMoveEvent catches the current position (after mouse pressed)
     * and updates stick positionti
     * @param event
     */
    void mouseMoveEvent(QMouseEvent* event);

private:
	QTimer updater;
	QTimer ticker;
	QElapsedTimer timer;
	unique_ptr<SceneManager> scene;

    //Xing
    bool m_drawStick = false;
    QLine m_line;
};

#endif // MAINWINDOW_H
