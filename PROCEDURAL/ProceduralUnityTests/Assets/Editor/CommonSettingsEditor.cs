using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(CommonSettings)), CanEditMultipleObjects]
public class CommonSettingsEditor : Editor {

    CommonSettings commonSettings;
    Editor settingsEditor;

    public override void OnInspectorGUI() {
        base.OnInspectorGUI();
        drawSettingsEditor(commonSettings.spaceSettings, ref settingsEditor);
        drawSettingsEditor(commonSettings.solarSystemSettings, ref settingsEditor);
        drawSettingsEditor(commonSettings.planetSettings, ref settingsEditor);
    }

    void drawSettingsEditor(Object settings, ref Editor settingsEditor) {
        if (settings != null) {
            EditorGUILayout.InspectorTitlebar(true, settings);
            CreateCachedEditor(settings, null, ref settingsEditor);
            settingsEditor.OnInspectorGUI();
        }
    }

    private void OnEnable() {
        commonSettings = (CommonSettings)target;
    }
}
