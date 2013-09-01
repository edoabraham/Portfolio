/// GraphicsAssets.cs - GraphicsAssets Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Collections.Generic;
using UnityEngine;
#endregion

/// Lists All Graphics Assets
/// Note: Use Unity to Populate List
public static class GraphicsAssets {

	/// List of game objects
	private static Dictionary<String, GameObject> GameObjectList;

	/// Constructor
	static GraphicsAssets() {
		// Initialize the list.
		GameObjectList = new Dictionary<String, GameObject>();

		// NOTE: List Assets Here!!
		LoadContent("Katarina", "Prefabs/Katarina");
	}

	/// Load Content
	private static void LoadContent(String key, String filePath) {
		GameObject item = Resources.Load(filePath) as UnityEngine.GameObject;
		GameObjectList.Add(key, item);
	}

	/// Looks Up and Returns the Asset
	public static GameObject GetTransformAsset(String assetName) {
		GameObject item;
		GameObjectList.TryGetValue(assetName, out item);
		return item;
	}
}
