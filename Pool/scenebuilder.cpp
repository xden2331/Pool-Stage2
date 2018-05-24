#include "scenebuilder.h"

void SceneBuilder::setTable(unique_ptr<Table> table) {
	this->table = std::move(table);
}

void SceneBuilder::addBall(unique_ptr<Ball> ball) {
	this->balls.push_back(std::move(ball));
}

unique_ptr<SceneManager> SceneBuilder::build() {
	return unique_ptr<SceneManager>(
		new SceneManager(std::move(this->table), this->balls)
	);
}
