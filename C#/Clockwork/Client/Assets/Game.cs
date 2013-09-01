#region Project Clockwork
/// Game Client for Project Clockwork
/// All Code and Systems are Written
/// and Designed by Jesse Z. Zhong
#endregion

#region System Using Statements
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Threading;

using Artemis;
using Artemis.Manager;
using UnityEngine;
using GameClient;
#endregion

/// Game
public class Game : MonoBehaviour {

	/// Initialize Game Systems
	void Awake() {

		#region Artemis World Initialization
		/// Artemis World Initialization
		/// NOTE: DO NOT EDIT!!
		this.EntityWorld_ = new EntityWorld(true);
		this.SystemManager_ = EntityWorld_.SystemManager;
		#endregion

		/// Initialize the object with this parent object.
		this.ClockworkObject = gameObject;

		/// Initialize the game simulation.
		ClockworkGame = new GameClient.GameClient(IPAddress.Parse("192.168.1.100"));
		this.InitializeSimulation();

		/// Artemis Update Systems

		/// Player Control and Physics
		this.SystemManager_.SetSystem(new PlayerControlSystem(), GameLoopType.Update);
		this.SystemManager_.SetSystem(new VelocitySystem(), GameLoopType.Update);
		this.SystemManager_.SetSystem(new MovementSystem(), GameLoopType.Update);

		/// Artemis Draw Systems
		this.SystemManager_.SetSystem(new GraphicsSystem(), GameLoopType.Draw);
		this.SystemManager_.SetSystem(new CameraSystem(), GameLoopType.Draw);

		// Test Region
		this.InitMainCharacter();

		#region Artemis System Manager Initialization
		/// Initialize Artemis System Manager
		/// NOTE: DO NOT EDIT!!
		this.EntityWorld_.InitializeAll();
		#endregion
	}

	#region Test
	/// Temporary Main Character for Testing
	private void InitMainCharacter() {

		Entity e = this.EntityWorld_.CreateEntity();
		e.AddComponent(new Elemental());
		e.AddComponent(new Velocity());
		e.AddComponent(new PlayerMouse());

		ObjectController objController = 
			ScriptableObject.CreateInstance<ObjectController>();
		objController.AssetName = "Katarina";
		e.AddComponent(new OCComponent(objController));
		e.AddComponent(new Player());
		e.Refresh();
		e.Tag = "Player0";
	}

	/// Test the chat system
	private MemoryStream Stream_;
	private void SpamChat() {
		this.Stream_ = new MemoryStream();
		if (ClockworkGame != null)
			ClockworkGame.Chat.SetOutStream(this.Stream_);

		// Create thread
		ThreadStart ts = new ThreadStart(() => {

			while (true) {

				int size = (int)this.Stream_.Length;
				if (size != 0) {
					byte[] buffer = new byte[size];
					this.Stream_.Read(buffer, 0, size);
					Debug.Log(System.Text.Encoding.ASCII.GetString(buffer));
				}

				if (ClockworkGame != null) {
					ClockworkGame.Chat.SendMessage(NetworkEvents.NetworkConstants.EMessageType.All,
						"Some shit");
				}

				Thread.Sleep(1000);
			}
		});
		Thread thread = new Thread(ts);
		thread.Start();
	}
	#endregion

	#region Members
	/// Game Object Reference
	public GameObject ClockworkObject;

	/// Entity World Instance
	private EntityWorld EntityWorld_;
	private SystemManager SystemManager_;

	/// Game Simulation
	public GameClient.GameClient ClockworkGame;
	private bool SimulationRunning_;
	private Thread SimulationThread_;
	private void InitializeSimulation() {

		// Set the state of the simulation.
		this.SimulationRunning_ = true;

		// Create thread start with method.
		ThreadStart ts = new ThreadStart(() => {

			// Start game loop
			if (ClockworkGame != null)
				ClockworkGame.Run(this.SimulationRunning_);
		});
		this.SimulationThread_ = new Thread(ts);
		this.SimulationThread_.Start();
	}

	/// Destroy parallel thread when system shuts down.
	public void OnDestroy() {
		this.SimulationRunning_ = false;
	}
	public void OnApplicationQuit() {
		this.SimulationRunning_ = false;
	}

	#region Game Update Loop
	/// Update Function [Game Loop : First Priority]
	/// NOTE: Please Avoid Changing Anything in the Update Function
	void Update() {
		this.EntityWorld_.Update(ExecutionType.Synchronous);
	}

	/// Draw (Late Update) Function [Game Loop : Second Priority]
	/// NOTE: Please Avoid Changing Anything in the Draw (Late Update) Function
	void LateUpdate() {
		this.EntityWorld_.Draw(ExecutionType.Synchronous);
	}
	#endregion
	#endregion
}

