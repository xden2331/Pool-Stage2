#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include "scenemanager.h"

class SceneBuilder
{
public:
	/**
	 * @brief Constructor
	 */
	SceneBuilder() {}
	~SceneBuilder() {}

	/**
	 * @brief sets the table for the scene
	 *        table can only be used once
	 *
	 * @param table
	 */
	void setTable(unique_ptr<Table> table);
	/**
	 * @brief adds ball to scene
	 *        ball can only be used once
	 *
	 * @param ball
	 */
	void addBall(unique_ptr<Ball> ball);
	/**
	 * @brief creates scene
	 *        a table must be set
	 *
	 * @return the scene with set table and balls
	 */
	unique_ptr<SceneManager> build();

private:
	unique_ptr<Table> table;
	vector<unique_ptr<Ball>> balls;
};

#endif // SCENEBUILDER_H
