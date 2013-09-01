/// GameClient.cs - GameClient Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.Net;
using System.Threading;
using System.Collections.Generic;

using Artemis;
using Artemis.System;
using Artemis.Manager;
using NetworkEvents;
using Utilities;
#endregion

/// Game Client
namespace GameClient {

	/// Main Game Client Class
	public class GameClient {

		/// Constructor
		public GameClient(IPAddress serverIPAddress) {

			/// Assign Network Values
			this.IPAddress_ = serverIPAddress;

			/// Initialize Timer
			this.GameTime_ = new GameTime();

			/// Print Message
			Message.Info("Game Client Initialized.");

			/// Initialize Game Systems
			this.InitializeSystems();
		}

		/// Initialize System
		private void InitializeSystems() {

			#region Artemis World Intialization
			/// Artemis World Initialization
			/// NOTE: DO NOT EDIT!!
			this.EntityWorld_ = new EntityWorld(AreEntitiesSorted);
			this.SystemManager_ = EntityWorld_.SystemManager;

			Message.Info("%lite Initiated.", "Artemis Entity System");
			#endregion

			/// Networking Systems
			this.SystemManager_.SetSystem(this.ClientSystem_ = new ClientSystem(NetworkRefreshInterval, 
				this.GameTime_, this.IPAddress_), GameLoopType.Update);
			this.SystemManager_.SetSystem(this.ChatSystem_ = 
				new NSCMessage(NetworkRefreshInterval, this.ClientSystem_), GameLoopType.Update);
			this.SystemManager_.SetSystem(this.MovementInputSystem_ = 
				new NCInputMove(NetworkRefreshInterval, this.ClientSystem_), GameLoopType.Update);
			this.SystemManager_.SetSystem(this.SpellInputSystem_ = 
				new NCInputSpell(NetworkRefreshInterval, this.ClientSystem_), GameLoopType.Update);
			this.SystemManager_.SetSystem(this.WorldLoadingSystem_ = 
				new NSCWorldLoad(NetworkRefreshInterval, this.ClientSystem_), GameLoopType.Update);
			this.SystemManager_.SetSystem(this.WorldUpdateSystem_ =
				new NSWorldUpdate(NetworkRefreshInterval, this.ClientSystem_), GameLoopType.Update);
			this.SystemManager_.SetSystem(this.CharacterDeathSystem_ =
				new NSDeath(NetworkRefreshInterval, this.ClientSystem_), GameLoopType.Update);

			#region System Manager Intialization
			/// Initialize Artemis System Manager
			/// NOTE: DO NOT EDIT!!
			this.EntityWorld_.InitializeAll();
			#endregion
		}

		#region Public Systems
		/// Client System
		private ClientSystem ClientSystem_;
		public ClientSystem ClientSystem {
			get { return this.ClientSystem_; }
		}

		/// Chat System
		private NSCMessage ChatSystem_;
		public NSCMessage Chat {
			get { return this.ChatSystem_; }
		}

		/// Movement Input System
		private NCInputMove MovementInputSystem_;
		public NCInputMove MoveInput {
			get { return this.MovementInputSystem_; }
		}

		/// Spell Input System
		private NCInputSpell SpellInputSystem_;
		public NCInputSpell SpellInput {
			get { return this.SpellInputSystem_; }
		}

		/// World Loading System
		private NSCWorldLoad WorldLoadingSystem_;
		public NSCWorldLoad LoadingSystem {
			get { return this.WorldLoadingSystem_; }
		}

		/// World Update System
		private NSWorldUpdate WorldUpdateSystem_;
		public NSWorldUpdate UpdateSystem {
			get { return this.WorldUpdateSystem_; }
		}

		/// Character Death System
		private NSDeath CharacterDeathSystem_;
		public NSDeath Death {
			get { return this.CharacterDeathSystem_; }
		}
		#endregion

		#region Private Members
		/// Head of the Artemis hierarchy 
		/// that is in charge of everything.
		private EntityWorld EntityWorld_;
		public EntityWorld EntityWorld {
			get { return this.EntityWorld_; }
		}

		/// Keeps a list of systems and their logic
		private SystemManager SystemManager_;
		
		/// Are Entities sorted?
		private const bool AreEntitiesSorted = true;

		/// Network Refresh Interval
		/// Controls how often packets are received, checked, and sent
		private const int NetworkRefreshInterval = 100;
		
		/// Server IP Address
		private IPAddress IPAddress_;

		#region Game Loop
		/// Game Timer
		private GameTime GameTime_;

		/// Update
		private void Update(long deltaTime) {
			this.EntityWorld_.Update(ExecutionType.Synchronous);
		}

		/// Late Update
		private void LateUpdate(long deltaTime) {
			this.EntityWorld_.Draw(ExecutionType.Synchronous);
		}

		/// Runs the Game Update by Update
		public void Run(bool run) {

			/// Game Loop
			while (run) {

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
