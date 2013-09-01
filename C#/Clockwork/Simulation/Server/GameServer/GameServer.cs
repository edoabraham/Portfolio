/// GameServer.cs - GameServer Class Implementation
/// Written By Jesse Z. Zhong (Takuto)
/// Music : Blu by MitiS & MaHi

using System;
using System.Net;
using System.Collections.Generic;

using Artemis;
using Artemis.System;
using Artemis.Manager;

using Utilities;
using NetworkEvents;
using System.Threading;

/// Game Server
namespace GameServer {

	/// Main Game Server Class
	public sealed class GameServer {

		/// Constructor
		public GameServer(int id, 
			IPAddress serverAddress) {

				/// Assign IP Address to the simulation.
				this.IPAddress_ = serverAddress;

				/// Initialize the game timer.
				this.GameTime_ = new GameTime();

				/// Print Message
				Message.Info("Game Server Instance %lite Online.", ID_.ToString());

				/// Initialize systems after fields are set.
				this.InitializeSystems();
		}

		#region Testing Region
		private PlayerInfo[] PlayerInfoList;
		private void InitPlayerInfoList() {
			PlayerInfoList = new PlayerInfo[3];
			
			// Player 0
			PlayerInfo player0 = new PlayerInfo(1000, "Jesse", ECharacter.Derp, 1);
			player0.ClientEndPoint = new IPEndPoint(
				NetworkConstants.LocalIPAddress(), NetworkConstants.ClientPort);
			
			// Player 1
			PlayerInfo player1 = new PlayerInfo(1100, "Derp", ECharacter.Derp, 1);
			player1.ClientEndPoint = new IPEndPoint(
				IPAddress.Parse("192.168.1.102"), NetworkConstants.ClientPort);

			// Player 2
			PlayerInfo player2 = new PlayerInfo(1110, "Drew", ECharacter.Derp, 1);
			player2.ClientEndPoint = new IPEndPoint(
				IPAddress.Parse("75.102.125.205"), NetworkConstants.ClientPort);

			PlayerInfoList[0] = player0;
			PlayerInfoList[1] = player1;
			PlayerInfoList[2] = player2;
		}
		#endregion

		/// Initialize System
		private void InitializeSystems() {

			#region Artemis World Intialization
			/// Artemis World Initialization
			/// NOTE: DO NOT EDIT!!
			this.EntityWorld_ = new EntityWorld(AreEntitiesSorted);
			this.SystemManager_ = EntityWorld_.SystemManager;
			
			Message.Info("%lite Initiated.", "Artemis Entity System");
			#endregion
			
			/// Update Systems
			this.SystemManager_.SetSystem(new VelocitySystem(), GameLoopType.Update);
			this.SystemManager_.SetSystem(new CollisionSystem(), GameLoopType.Update);

			/// Spell Systems
			this.SystemManager_.SetSystem(new SpellSystem(), GameLoopType.Update);
			this.SystemManager_.SetSystem(new SpellAISystem(), GameLoopType.Update);

			/// Killable Systems
			this.SystemManager_.SetSystem(new UpdateKillableDistance(), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateKillableTime(), GameLoopType.Update);
			this.SystemManager_.SetSystem(new KillableCleanup(), GameLoopType.Update);

			/// Status Effect Systems
			this.SystemManager_.SetSystem(new UpdatePoisons(GlobalData.StatusEffectRefreshInterval), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateSlows(GlobalData.StatusEffectRefreshInterval), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateStuns(GlobalData.StatusEffectRefreshInterval), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateBurning(GlobalData.StatusEffectRefreshInterval), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateBleeding(GlobalData.StatusEffectRefreshInterval), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateOvercharge(GlobalData.StatusEffectRefreshInterval, GlobalData.InterruptFrequency), GameLoopType.Update);
			this.SystemManager_.SetSystem(new UpdateBlinds(GlobalData.StatusEffectRefreshInterval), GameLoopType.Update);

 			/// Reaction Systems
			this.SystemManager_.SetSystem(new MovementSystem(), GameLoopType.Update);
			
			// Testing
			InitPlayerInfoList();

			/// Network Systems
			ServerSystem serverSystem = new ServerSystem(NetRefreshInterval, 
				this.GameTime_, this.PlayerInfoList, this.IPAddress_);
			this.SystemManager_.SetSystem(serverSystem, GameLoopType.Update);
			this.SystemManager_.SetSystem(new NSCWorldLoad(NetRefreshInterval, serverSystem), GameLoopType.Update);
			this.SystemManager_.SetSystem(new NSWorldUpdate(NetRefreshInterval, serverSystem), GameLoopType.Update);
			this.SystemManager_.SetSystem(new NSCMessage(NetRefreshInterval, serverSystem), GameLoopType.Update);
			this.SystemManager_.SetSystem(new NCInputMove(NetRefreshInterval, serverSystem), GameLoopType.Update);
			this.SystemManager_.SetSystem(new NCInputSpell(NetRefreshInterval, serverSystem), GameLoopType.Update);
			this.SystemManager_.SetSystem(new NSDeath(NetRefreshInterval, serverSystem), GameLoopType.Update);

			/// Draw / Late Update Systems


			/// Metering systems and forms
			this.CommandsHandler_ = new MeterSystems(this);

			#region System Manager Intialization
			/// Initialize Artemis System Manager
			/// NOTE: DO NOT EDIT!!
			this.EntityWorld_.InitializeAll();
			#endregion
		}

		#region Private Fields
		/// The server's identification number.
		private int ID_;

		/// The microseconds before another
		/// network update is required.
		private const int NetRefreshInterval = 1000;

		/// Indicates whether entities are sorted.
		private const bool AreEntitiesSorted = true;

		/// The IP Address of this game simulation.
		private IPAddress IPAddress_;

		/// Head of the Artemis hierarchy 
		/// that is in charge of everything.
		private EntityWorld EntityWorld_;
		internal EntityWorld EntityWorld {
			get { return this.EntityWorld_; }
		}

		/// Keeps a list of systems and their logic.
		private SystemManager SystemManager_;

		/// System in charge of monitoring.
		private MeterSystems CommandsHandler_;

		/// The game timer
		private GameTime GameTime_;

		#region Game Loop
		/// Update
		private void Update(long deltaTime) {
			this.EntityWorld_.Update(ExecutionType.Synchronous);
		}

		/// Late Update
		private void LateUpdate(long deltaTime) {
			this.EntityWorld_.Draw(ExecutionType.Synchronous);
		}

		/// Runs the Game Update by Update
		public void Run() {

			/// Game Loop
			while (true) {
				/// Perform First Update
				this.Update(this.GameTime_.DeltaTime);

				/// Perform Late Update
				this.LateUpdate(this.GameTime_.DeltaTime);

				/// Resets the Timer
				this.GameTime_.Reset();

				/// Pause loop
				Thread.Sleep(GameTime.FixedTimeStepValue);
			}
		}
		#endregion
		#endregion
	}
}
