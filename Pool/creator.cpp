#include "creator.h"
#include "scenebuilder.h"
#include <QJsonArray>

unique_ptr<SceneManager> Creator::makeScene(const QJsonObject &spec) {
	SceneBuilder builder;
	builder.setTable(
		this->makeTable(spec["table"].toObject())
    );
	for (const auto& item : spec["balls"].toArray())
		builder.addBall(
            this->makeBall(item.toObject())
		);

	return builder.build();
}
