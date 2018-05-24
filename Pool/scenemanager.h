#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "util.h"
#include "graphic.h"
#include "table.h"
#include "ball.h"
#include "decoration.h"
#include "pocket.h"

#include <unordered_set>
#include <QElapsedTimer>
#include <QSize>
#include <QPaintEvent>



class SceneManager : public Graphic
{
public:
    bool pressOnWhiteBall = false;

	/**
	 * @brief SceneManager Constructor
	 *
	 * @param table
	 * @param balls
	 */
	SceneManager(unique_ptr<Table> table, vector<unique_ptr<Ball>>& balls);
	~SceneManager() {}
	/**
	 * @brief take a timestep of size dtime
	 *
	 * @param dtime
	 */
    void tick(float dtime);
	/**
	 * @brief draw the current scene
	 *
	 * @param painter for rendering objects
	 */
	void draw(QPainter& painter) const;
	/**
	 * @brief retrives the size of the scene
	 *
	 * @return the size of the scene
	 */
	QSize veiwPort() const;

    /**
     * @brief press when a mouse press event occurs, this function
     * receives the position and perform different functionality
     * based on the position. If it presses on the cue ball, member variable
     * 'pressOnWhiteBall' is true, and it will be used for hitting the
     * cue ball.
     * @param pos position where the press event occurs
     * @author Xing DENG
     */
    void press(QVector2D& pos);

    /**
     * @brief releaseMouse checks if 'pressOnWhiteBall' is true, and the velocity
     * of the cue ball is 0. If both true, calculate the strength hitting on the
     * cue ball, and give it according velocity.
     * @param pos position where the mouse release
     * @author Xing DENG
     */
    void releaseMouse(QVector2D& pos);

    bool isBroken(Ball &ballA, const QVector2D &preVel, unsigned long& a);


public:
	unique_ptr<Table> table;
	vector<unique_ptr<Ball>> balls;
    QPoint offset;
};

#endif // SCENEMANAGER_H
