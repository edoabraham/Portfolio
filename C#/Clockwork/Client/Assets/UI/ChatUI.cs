/// ChatUI.cs - ChatUI Class Implementation
/// Written By Jesse Z. Zhong
#region Assemblies
using System;
using System.IO;
using System.Collections.Generic;
using Bitverse.Unity.Gui;
using UnityEngine;
using GameClient;
#endregion

using EMessageType = NetworkEvents.NetworkConstants.EMessageType;

/// The chat system front end.
public class ChatUI : MonoBehaviour {

	#region Size and Positions
	/// Dimension
	private static readonly int WindowWidth = 320;
	private static readonly int WindowHeight = (int)(WindowWidth / Utilities.MathConst.Phi);
	private static readonly int DisplayWidth = 300;
	private static readonly int DisplayHeight = WindowHeight - 50;
	private static readonly int WriteWidth = 300;
	private static readonly int WriteHeight = 20;

	/// Position
	private static readonly int WindowX = 10;
	private static readonly int WindowY = Screen.height - (WindowHeight + WriteHeight + 14);
	private static readonly int DisplayX = 0;
	private static readonly int DisplayY = 0;
	private static readonly int WriteX = 0;
	private static readonly int WriteY = WindowHeight - (WriteHeight + 30);

	/// The approximate pixel height of a character.
	private const int CharHeight = 20;

	/// Height of the message display area.
	private int DisplayAreaHeight_;
	#endregion

	/// Name of the chat log.
	public string Name;

	/// Reference to the game system's object.
	public GameObject MainGameObject;

	#region System and Component References
	/// Reference to the main game system.
	private Game Game_;
	private NSCMessage ChatSystem_;

	/// UI Widgets
	private BitWindow Window_;
	private BitScrollView MessageScroller_;
	private BitLabel MessageDisplay_;
	private BitTextArea MessageWrite_;
	#endregion

	/// Initialize UI Widgets and game system references.
	public void Start() {
		#region Object References
		// Attempt to pull main game system from referenced game object.
		this.Game_ = MainGameObject.GetComponent<Game>();
		if (this.Game_ == null) {
			Debug.LogError("Game cannot be found.");
			return;
		}

		// Localize the chat system.
		this.ChatSystem_ = this.Game_.ClockworkGame.Chat;

		// Link window to script.
		this.Window_ = gameObject.GetComponent<BitWindow>();
		if (this.Window_ == null) {
			Debug.LogError("ChatLog window not found.");
			return;
		}
		#endregion
		#region UI Elements
		// Change window settings.
		this.Window_.Text = this.Name;
		this.Window_.Draggable = true;
		this.Window_.Location = new Point(WindowX, WindowY);
		this.Window_.Size = new Bitverse.Unity.Gui.Size(WindowWidth, WindowHeight);

		// Add scrolling area.
		this.MessageScroller_ = this.Window_.AddControl<BitScrollView>();

		// Add message display box and writing area.
		this.MessageDisplay_ = this.MessageScroller_.AddControl<BitLabel>();
		this.MessageWrite_ = this.Window_.AddControl<BitTextArea>();
		this.MessageWrite_.Enabled = false;

		// Adjust message display area dimensions.
		this.MessageScroller_.Location = new Point(DisplayX, DisplayY);
		this.MessageScroller_.Size = new Bitverse.Unity.Gui.Size(DisplayWidth, DisplayHeight);
		this.MessageDisplay_.Location = new Point(0, 0);
		this.DisplayAreaHeight_ = CharHeight;
		this.MessageDisplay_.Size = new Bitverse.Unity.Gui.Size(DisplayWidth, DisplayAreaHeight_);

		// Adjust message writing area dimensions.
		this.MessageWrite_.Location = new Point(WriteX, WriteY);
		this.MessageWrite_.Size = new Bitverse.Unity.Gui.Size(WriteWidth, WriteHeight);
		#endregion
		this.OnInitGUI();
	}

	/// Receive and display messages and handle the sending of messages.
	public void Update() {
		#region Receive and Print Message
		// Handle incoming messages to be displayed.
		if (this.ChatSystem_.NewMessage) {
			
			// Get the message
			string message = this.ChatSystem_.MessageString;

			// Color messages

			// Write messages to log file.

			// Expand the viewing space.
			this.DisplayAreaHeight_ += CharHeight;
			this.MessageDisplay_.Size = new Bitverse.Unity.Gui.Size(WriteWidth, DisplayAreaHeight_);

			// Write messages to window.
			this.MessageDisplay_.Text += message;
		}
		#endregion
		#region Mouse Click Input
		// Poll for mouse click.
		// Only select the chat box if it is selected.
		if(Input.GetMouseButtonDown(0)) {
			this.MessageWrite_.Enabled = 
				(this.MessageWrite_.IsControlHover) ? true : false;

			// Bring into focus.
			if (this.MessageWrite_.Enabled) {
				this.ActivateChat();
			} else
				PlayerControlSystem.ChatMode = false;
		}
		#endregion
		#region Enter Key Input
		// Polls for enter key input.
		if (Input.GetKeyUp(KeyCode.Return)) {

			// Check the state of the window.
			if (this.MessageWrite_.Enabled) {

				// Get the message string.
				string text = this.MessageWrite_.Text;

				// If it is empty, disable the window.
				if ((text == "") || ((text.Length > 0) && (text[0] == '\n'))) {
					this.MessageWrite_.Enabled = false;
					PlayerControlSystem.ChatMode = false;
				} else {
					// Send message and clear box.
					this.ChatSystem_.SendMessage(EMessageType.All, text);
					this.MessageWrite_.Text = "";
				}
			} else {
				// Enable the window if disabled.
				this.MessageWrite_.Enabled = true;

				// Bring into focus.
				this.ActivateChat();
			}
		}
		#endregion
	}

	/// Brings the chat window to focus and change the game to chat mode.
	private void ActivateChat() {
		this.Window_.BringToFront();
		this.Window_.ForceFocus();
		this.MessageWrite_.BringToFront();
		this.MessageWrite_.ForceFocus();
		PlayerControlSystem.ChatMode = true;
	}

	/// Performs action or display a message after the initialization of the GUI.
	private void OnInitGUI() {
		string msg = "Connecting to IP Address: " +
			(this.Game_.ClockworkGame.ClientSystem.ClientIP.ToString()) + "\n";
		this.MessageDisplay_.Text += msg;
	}
}


