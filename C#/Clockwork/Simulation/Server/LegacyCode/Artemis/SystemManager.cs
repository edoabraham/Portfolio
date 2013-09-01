/// SystemManager.cs - SystemManager Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Linq;
using System.Threading.Tasks;
using System.Collections.Generic;

/// Artemis
namespace ArtemisUnity {

	/// The Execution Type 
	/// for Execution Orders
	public enum ExecutionType {
		Draw,
		Update
	}

	/// Manages and Runs All Program Systems
	public sealed class SystemManager {

		/// World Instance for Referencing
		private EntityWorld World_;

		/// Entity Systems Organized by Execution Type
		private Dictionary<Type, List<EntitySystem>> Systems_ = new Dictionary<Type,List<EntitySystem>>();

		/// Entity Systems Ordering
		private Dictionary<int, Bag<EntitySystem>> UpdateLayers_ = new Dictionary<int, Bag<EntitySystem>>();
		private Dictionary<int, Bag<EntitySystem>> DrawLayers_ = new Dictionary<int, Bag<EntitySystem>>();

		/// Bag Containing All Entity Systems
		private Bag<EntitySystem> MergedBag_ = new Bag<EntitySystem>();

		/// Internal Constructor
		internal SystemManager(EntityWorld world) {
			this.World_ = world;
		}


		public T SetSystem<T>(T system, ExecutionType execType, int layer = 0) where T : EntitySystem {
			system.World = World_;

			if (Systems_.ContainsKey(typeof(T))) {
				Systems_[typeof(T)].Add((EntitySystem)system);
			} else {
				Systems_[typeof(T)] = new List<EntitySystem>();
				Systems_[typeof(T)].Add((EntitySystem)system);
			}


			if (execType == ExecutionType.Draw) {

				if (!DrawLayers_.ContainsKey(layer))
					DrawLayers_[layer] = new Bag<EntitySystem>();

				Bag<EntitySystem> drawBag = DrawLayers_[layer];
				if (drawBag == null) {
					drawBag = DrawLayers_[layer] = new Bag<EntitySystem>();
				}
				if (!drawBag.Contains((EntitySystem)system))
					drawBag.Add((EntitySystem)system);
				DrawLayers_ = (from d in DrawLayers_ orderby d.Key ascending select d).ToDictionary(pair => pair.Key, pair => pair.Value);
			} else if (execType == ExecutionType.Update) {

				if (!UpdateLayers_.ContainsKey(layer))
					UpdateLayers_[layer] = new Bag<EntitySystem>();

				Bag<EntitySystem> updateBag = UpdateLayers_[layer];
				if (updateBag == null) {
					updateBag = UpdateLayers_[layer] = new Bag<EntitySystem>();
				}
				if (!updateBag.Contains((EntitySystem)system))
					updateBag.Add((EntitySystem)system);
				UpdateLayers_ = (from d in UpdateLayers_ orderby d.Key ascending select d).ToDictionary(pair => pair.Key, pair => pair.Value);
			}
			if (!MergedBag_.Contains((EntitySystem)system))
				MergedBag_.Add((EntitySystem)system);
			system.SystemBit = SystemBitManager.GetBitFor(system);

			return (T)system;
		}

		public List<EntitySystem> GetSystem<T>() where T : EntitySystem {
			List<EntitySystem> system;

			Systems_.TryGetValue(typeof(T), out system);

			return system;
		}

		public Bag<EntitySystem> Systems {
			get { return MergedBag_; }
		}

		public void InitializeAll() {
			for (int i = 0, j = MergedBag_.Size; i < j; i++) {
				MergedBag_.Get(i).Initialize();
			}
		}


		void UpdatebagSync(Bag<EntitySystem> temp) {
			for (int i = 0, j = temp.Size; i < j; i++) {
				temp.Get(i).Process();
			}
		}

		public void UpdateSynchronous(ExecutionType execType) {
			if (execType == ExecutionType.Draw) {

				foreach (int item in DrawLayers_.Keys) {
					UpdatebagSync(DrawLayers_[item]);
				}
			} else if (execType == ExecutionType.Update) {
				foreach (int item in UpdateLayers_.Keys) {
					UpdatebagSync(UpdateLayers_[item]);
				}
			}
		}

		TaskFactory Factory_ = new TaskFactory(TaskScheduler.Default);
		List<Task> Tasks_ = new List<Task>();

		void UpdatebagASSync(Bag<EntitySystem> temp) {
			Tasks_.Clear();
			for (int i = 0, j = temp.Size; i < j; i++) {
				EntitySystem es = temp.Get(i);
				Tasks_.Add(Factory_.StartNew(
					() => {
						es.Process();
					}
				));

			}
			Task.WaitAll(Tasks_.ToArray());
		}
		public void UpdateAsynchronous(ExecutionType execType) {
			if (execType == ExecutionType.Draw) {
				foreach (int item in DrawLayers_.Keys) {
					UpdatebagASSync(DrawLayers_[item]);
				}
			} else if (execType == ExecutionType.Update) {
				foreach (int item in UpdateLayers_.Keys) {
					UpdatebagASSync(UpdateLayers_[item]);
				}
			}

		}
	}
}
