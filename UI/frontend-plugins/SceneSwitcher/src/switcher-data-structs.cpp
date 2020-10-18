#include "headers/switcher-data-structs.hpp"
#include "headers/utility.hpp"

void SwitcherData::Prune()
{
	if (nonMatchingScene && !WeakSourceValid(nonMatchingScene)) {
		switchIfNotMatching = NO_SWITCH;
		nonMatchingScene = nullptr;
	}

	for (size_t i = 0; i < randomSwitches.size(); i++) {
		RandomSwitch &s = randomSwitches[i];
		if (!s.valid())
			randomSwitches.erase(randomSwitches.begin() + i--);
	}


	for (size_t i = 0; i < sceneSequenceSwitches.size(); i++) {
		SceneSequenceSwitch &s = sceneSequenceSwitches[i];
		if (!s.valid())
			sceneSequenceSwitches.erase(
				sceneSequenceSwitches.begin() + i--);
	}

	if (!WeakSourceValid(autoStopScene)) {
		autoStopScene = nullptr;
		autoStopEnable = false;
	}

	for (size_t i = 0; i < sceneTransitions.size(); i++) {
		SceneTransition &s = sceneTransitions[i];
		if (!s.valid())
			sceneTransitions.erase(sceneTransitions.begin() + i--);
	}

	for (size_t i = 0; i < defaultSceneTransitions.size(); i++) {
		DefaultSceneTransition &s = defaultSceneTransitions[i];
		if (!s.valid())
			defaultSceneTransitions.erase(
				defaultSceneTransitions.begin() + i--);
	}

	for (size_t i = 0; i < fileSwitches.size(); i++) {
		FileSwitch &s = fileSwitches[i];
		if (!s.valid())
			fileSwitches.erase(fileSwitches.begin() + i--);
	}

	

	for (size_t i = 0; i < mediaSwitches.size(); i++) {
		MediaSwitch &s = mediaSwitches[i];
		if (!s.valid())
			mediaSwitches.erase(mediaSwitches.begin() + i--);
	}
}
