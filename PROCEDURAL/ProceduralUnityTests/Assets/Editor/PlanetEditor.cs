using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(PlanetTestTool)), CanEditMultipleObjects]
public class PlanetEditor : Editor{

    PlanetTestTool planet;
    Editor settingsEditor;

    public override void OnInspectorGUI() {
        using (var check = new EditorGUI.ChangeCheckScope()) {
            base.OnInspectorGUI();
            if (check.changed) {
                planet.generatePlanet();
            }
        }
        drawSettingsEditor(planet.settings, ref planet.settingsFoldout, ref settingsEditor);
    }

    void drawSettingsEditor(Object settings, ref bool foldout, ref Editor settingsEditor) {
        if (settings != null) {
            foldout = EditorGUILayout.InspectorTitlebar(foldout, settings);
            using (var check = new EditorGUI.ChangeCheckScope()) {
                if (foldout) {
                    CreateCachedEditor(settings, null, ref settingsEditor);
                    settingsEditor.OnInspectorGUI();
                    if (check.changed) {
                        planet.generatePlanet();
                    }
                }
            }
        }
    }

    private void OnEnable() {
        planet = (PlanetTestTool)target;
    }
}
