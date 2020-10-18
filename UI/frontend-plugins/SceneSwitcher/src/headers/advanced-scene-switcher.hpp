#pragma once

#include <QDialog>
#include <memory>
#include <vector>
#include <string>
#ifdef BUILD_OUT_OF_TREE
#include "../../forms/ui_advanced-scene-switcher.h"
#else
#include "ui_advanced-scene-switcher.h"
#endif
#include "switcher-data-structs.hpp"
#include "volume-control.hpp"

class QCloseEvent;

/*******************************************************************************
 * Advanced Scene Switcher window
 *******************************************************************************/
class SceneSwitcher : public QDialog {
	Q_OBJECT

public:
	std::unique_ptr<Ui_SceneSwitcher> ui;
	VolControl *volMeter = nullptr;
	bool loading = true;

	SceneSwitcher(QWidget *parent);

	void closeEvent(QCloseEvent *event) override;

	void SetStarted();
	void SetStopped();

	int FindByData(const QString &window);
	int SceneSequenceFindByData(const QString &scene1);
	int SceneTransitionsFindByData(const QString &scene1,
				       const QString &scene2);
	int DefaultTransitionsFindByData(const QString &scene);
	int randomFindByData(const QString &scene);

	void UpdateNonMatchingScene(const QString &name);
	void UpdateAutoStopScene(const QString &name);
	void UpdateAutoStartScene(const QString &name);

	void loadUI();
	void populateSceneSelection(QComboBox *sel, bool addPrevious);
	void populateTransitionSelection(QComboBox *sel);
	void setupGeneralTab();
	void setupSequenceTab();
	void setupTransitionsTab();
	void setupRandomTab();
	void setupMediaTab();
	void setupFileTab();
	void setTabOrder();

public slots:
	//void on_switches_currentRowChanged(int idx);

	//void on_add_clicked();
	//void on_remove_clicked();
	void on_noMatchDontSwitch_clicked();
	void on_noMatchSwitch_clicked();
	void on_noMatchRandomSwitch_clicked();
	void on_startupBehavior_currentIndexChanged(int index);
	void on_noMatchSwitchScene_currentTextChanged(const QString &text);
	void on_checkInterval_valueChanged(int value);
	void on_toggleStartButton_clicked();
	void on_tabMoved(int from, int to);

	void on_sceneSequences_currentRowChanged(int idx);
	void on_sceneSequenceAdd_clicked();
	void on_sceneSequenceRemove_clicked();
	void on_sceneSequenceSave_clicked();
	void on_sceneSequenceLoad_clicked();
	void on_sceneSequenceUp_clicked();
	void on_sceneSequenceDown_clicked();
	void on_sceneSequenceDelayUnits_currentIndexChanged(int index);

	void on_autoStopSceneCheckBox_stateChanged(int state);
	void on_autoStopScenes_currentTextChanged(const QString &text);

	void on_autoStartSceneCheckBox_stateChanged(int state);
	void on_autoStartType_currentIndexChanged(int index);
	void on_autoStartScenes_currentTextChanged(const QString &text);

	void on_verboseLogging_stateChanged(int state);

	void on_exportSettings_clicked();
	void on_importSettings_clicked();

	void on_sceneTransitions_currentRowChanged(int idx);
	void on_transitionsAdd_clicked();
	void on_transitionsRemove_clicked();
	void on_defaultTransitions_currentRowChanged(int idx);
	void on_defaultTransitionsAdd_clicked();
	void on_defaultTransitionsRemove_clicked();
	void on_transitionOverridecheckBox_stateChanged(int state);

	void on_browseButton_clicked();
	void on_readFileCheckBox_stateChanged(int state);
	void on_fileType_currentIndexChanged(int idx);
	void on_readPathLineEdit_textChanged(const QString &text);
	void on_writePathLineEdit_textChanged(const QString &text);
	void on_browseButton_2_clicked();

	void on_randomAdd_clicked();
	void on_randomRemove_clicked();
	void on_randomScenesList_currentRowChanged(int idx);

	void on_fileAdd_clicked();
	void on_fileRemove_clicked();
	void on_fileScenesList_currentRowChanged(int idx);
	void on_browseButton_3_clicked();
	void on_fileUp_clicked();
	void on_fileDown_clicked();

	void on_mediaSwitches_currentRowChanged(int idx);
	void on_mediaAdd_clicked();
	void on_mediaRemove_clicked();
	void on_mediaUp_clicked();
	void on_mediaDown_clicked();
	void on_mediaTimeRestrictions_currentIndexChanged(int idx);

	void on_priorityUp_clicked();
	void on_priorityDown_clicked();
	void on_threadPriority_currentTextChanged(const QString &text);

	void on_close_clicked();

private:
};





/********************************************************************************
 * Sceneswitch helper
 ********************************************************************************/
struct obs_weak_source;
typedef struct obs_weak_source obs_weak_source_t;

typedef struct transitionData {
	std::string name = "";
	int duration = 0;
} transitionData;

void setNextTransition(OBSWeakSource &targetScene, obs_source_t *currentSource,
		       OBSWeakSource &transition,
		       bool &transitionOverrideOverride, transitionData &td);
void overwriteTransitionOverride(obs_weak_source_t *sceneWs,
				 obs_source_t *transition, transitionData &td);
void restoreTransitionOverride(obs_source_t *scene, transitionData td);

void switchScene(OBSWeakSource &scene, OBSWeakSource &transition,
		 bool &transitionOverrideOverride,
		 std::unique_lock<std::mutex> &lock);

/********************************************************************************
 * Hotkey helper
 ********************************************************************************/

constexpr auto toggle_hotkey_path = "hotkey_toggle.txt";
constexpr auto stop_hotkey_path = "hotkey_stop.txt";
constexpr auto start_hotkey_path = "hotkey_start.txt";

void stopHotkeyFunc(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey,
		    bool pressed);
void startHotkeyFunc(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey,
		     bool pressed);
void startStopToggleHotkeyFunc(void *data, obs_hotkey_id id,
			       obs_hotkey_t *hotkey, bool pressed);
void loadKeybinding(obs_hotkey_id hotkeyId, std::string path);

/********************************************************************************
 * Main SwitcherData
 ********************************************************************************/
struct SwitcherData;
extern SwitcherData *switcher;
