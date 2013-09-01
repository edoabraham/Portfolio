/// EntitiesList.cs - EntitiesList Form Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Reflection;

using Artemis;
using Artemis.Utils;

/// Game Server
namespace GameServer {

	/// This form is used to visually keep track of
	/// all entities and their behaviors, states, etc. 
	/// NOTE: Make sure this is the first class listed in this
	/// document. The forms designer will complain if it is not.
	public partial class EntitiesList : MeterForm {

		/// Form simulation refresh interval in milliseconds
		private const int RefreshInterval = 1500;

		/// Constructor
		public EntitiesList(GameServer gameServer) : base() {
			InitializeComponent();
			this.GameServer_ = gameServer;
		}

		/// Form initialization with a simulation thread used to get server info.
		private void EntitiesList_Load(object sender, EventArgs e) {

			// Initialize component mappers
			this.PCMapper_ = new ComponentMapper<PlayerController>(this.GameServer_.EntityWorld);
			this.TransformMapper_ = new ComponentMapper<Transform>(this.GameServer_.EntityWorld);
			this.VelocityMapper_ = new ComponentMapper<Velocity>(this.GameServer_.EntityWorld);
			this.StatisticsMapper_ = new ComponentMapper<Statistics>(this.GameServer_.EntityWorld);

			// Start concurrent thread with a interval
			// timed loop that is similar to the actual game's.
			Task.Factory.StartNew(() => {

				while (true) {
					Thread.Sleep(RefreshInterval);
					this.Invoke((MethodInvoker)delegate {
						this.UpdateData();
					});
				}
			});
		}

		/// Method in charge of updating all the list items with the current game data.
		private void UpdateData() {

			/// Player Entities

			// Get new list of entities and check for differences.
			// Only make changes to the list view if there are differences.
			Bag<Entity> players = this.GameServer_.EntityWorld.ComponentManager.GetEntities<PlayerController>();
			if (!players.Equals(this.PlayerEntities_)) {
				this.PlayerEntities_ = players;
				
				foreach (Entity item in this.PlayerEntities_) {

					string playerName = "Derp";
					TreeNode playerNode = new TreeNode();
					
					// Localize
					PlayerController pc = this.PCMapper_.Get(item);
					Transform transform = this.TransformMapper_.Get(item);
					Velocity velocity = this.VelocityMapper_.Get(item);
					Statistics stats = this.StatisticsMapper_.Get(item);

					if (pc != null) {
						playerName = pc.Info.Name;
						playerNode.Nodes.Add(this.ListItems(pc));
					}

					if (transform != null)
						playerNode.Nodes.Add(this.ListItems(transform));

					if (velocity != null)
						playerNode.Nodes.Add(this.ListItems(velocity));

					playerNode.Name = playerName;
					playerNode.Text = playerName;
					this.PlayerListTree.Nodes.Add(playerNode);
				}
			}
		}

		/// 
		private TreeNode ListItems(object component) {
			
			Type type = component.GetType();
			TreeNode parent = new TreeNode(type.Name);
			foreach (PropertyInfo item in type.GetProperties()) {

				// Add an exception for PlayerInfo
				if (item.PropertyType == typeof(PlayerInfo))
					parent.Nodes.Add(this.ListItems(((PlayerController)component).Info));

				else {
					try {
						// Load up items and their values for list view
						string[] row = { item.PropertyType.Name, item.Name, 
								   item.GetValue(component, null).ToString() };

						// Create node for each variable to display in tree
						TreeNode child = new TreeNode(item.Name);
						child.Tag = new ListViewItem(row);

						// Add child to the parent node
						parent.Nodes.Add(child);
					} catch (Exception ex) {
						Utilities.Message.Error(ex.Message);
					}
				}
			}

			return parent;
		}

		/// 
		private void PlayerListTree_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e) {

			// Localize node and clear list view
			TreeNode selected = e.Node;
			this.PlayerListView.Items.Clear();

			// Recursively grab all list view items
			List<ListViewItem> list = new List<ListViewItem>();
			list = this.GetItems(selected, list);

			// Load items into list view
			foreach (ListViewItem item in list)
				this.PlayerListView.Items.Add(item);
		}

		/// Recursively aggregate all the Tags of a node and child nodes.
		private List<T> GetItems<T>(TreeNode root, List<T> list) where T : ListViewItem {

			if(root.Nodes.Count == 0) {
				if ((root.Tag != null) && 
					(root.Tag.GetType() == typeof(T)))
					list.Add((T)root.Tag);
			} else {
				foreach (TreeNode item in root.Nodes)
					list = this.GetItems(item, list);
			}

			return list;
		}

		/// Reference to the game server
		private GameServer GameServer_;

		/// Bags of different entities
		private Bag<Entity> PlayerEntities_;
		private Bag<Entity> NPCEntities;
		private Bag<Entity> SpellEntities;

		/// Component Mappers for referencing components
		private ComponentMapper<PlayerController> PCMapper_;
		private ComponentMapper<Transform> TransformMapper_;
		private ComponentMapper<Velocity> VelocityMapper_;
		private ComponentMapper<Statistics> StatisticsMapper_;
	}
}
