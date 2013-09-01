/// CommandsHandler.cs - CommandsHandler Class Implementation.
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using Utilities;

/// Game Server
namespace GameServer {

	/// Class used to parse and handle commands fed
	/// through the command line as well as creates
	/// and manages the forms used to visualize data.
	public class MeterSystems {

		/// Thread sleep time
		private const int SleepTime = 1000;

		/// Constructor
		public MeterSystems(GameServer gameServer) {
			this.GameServer_ = gameServer;

			this.FormThreads_ = new Dictionary<string, Thread>();
			this.Forms_ = new Dictionary<string, MeterForm>();
			this.AddForm(new EntitiesList(gameServer));

			this.InitializeForms();
			this.BeginListeningForCommands();
		}

		#region Commands Handling
		/// Begins handling command requests on a separate thread.
		private void BeginListeningForCommands() {
			ThreadStart threadStart = new ThreadStart(this.ParseCommand);
			Thread thread = new Thread(threadStart);
			thread.Name = "Command Handler";
			thread.Start();
		}

		/// Reads, parses, and handles a string command.
		private void ParseCommand() {

			// Maintain a loop for continual listening
			while (true) {

				// Reads in a string from the console
				string command = "";
				command = Console.ReadLine();

				// Handle command request here
				string[] commandPortions = command.Split();
				if (command.Any()) {
					switch (commandPortions[0].ToLower()) {
						case "help":
						case "h":
							#region Help
							{
								// Print the list of commands
								Utilities.Message.HighlitePrint("%lite", "The following commands are usable:\n");
								Utilities.Message.HighlitePrint("%lite Redisplays a form of a given name.", 
									"form [name]     ");


								Utilities.Message.HighlitePrint("%lite Displays a list of all possible commands. LIKE THIS LIST!",
									"help            ");
							}
							break;
							#endregion
						case "form":
							#region Forms
							{
								Thread thread;
								// Check if a name was entered for the form.
								if (commandPortions.Length < 2)
									Console.WriteLine("Please enter the name of a form.");

								// If there is a name, attempt to look up the form and handle the request.
								else if (this.FormThreads_.TryGetValue(commandPortions[1], out thread)) {

									// Check if the thread is still alive. Throw exception if it's not.
									if (thread.IsAlive) {
										MeterForm form;
										if (this.Forms_.TryGetValue(commandPortions[1], out form)) {

											// Check if the form is showing or not.
											if (form.Visible) {
												form.BeginInvoke((MethodInvoker)delegate {
													form.WindowState = FormWindowState.Normal;
													form.Activate();
												});
												Utilities.Message.SysInfo("%lite is already showing.", commandPortions[1]);
											} else
												form.BeginInvoke((MethodInvoker)delegate {
													form.Show();
												});
										} else
											throw new Exception("Form could not be found in Forms_.");
										
									} else
										throw new Exception("Thread has died unexpectedly.");

								// If there is no match for the name in the threads, return message.
								} else {
									Utilities.Message.SysInfo("There is no form of the name %lite.", commandPortions[1]);
								}
								
							}
							break;
							#endregion
						default:
							#region Default
							Utilities.Message.SysInfo("%lite is an invalid command.\n" + 
								"Enter %lite or %lite for a list of commands.", 
								commandPortions[0], "h", "help");
							break;
							#endregion
					}
				}

				Thread.Sleep(SleepTime);
			}
		}
		#endregion

		#region Forms
		/// Initializes and runs all the meter forms.
		private void InitializeForms() {

			foreach (KeyValuePair<string, MeterForm> item in this.Forms_)
				this.StartFormInThread(item.Value);
		}

		/// Starts a form instance on a separate thread.
		private void StartFormInThread(MeterForm form) {

			// Start the form in a separate thread.
			ThreadStart threadStart = new ThreadStart(() => {
				Application.EnableVisualStyles();
				Application.SetCompatibleTextRenderingDefault(false);
				Application.Run(form);
			});
			Thread thread = new Thread(threadStart);
			thread.Name = form.Name;
			thread.Start();

			// Place entry into the dictionary
			this.FormThreads_.Add(form.Name, thread);
		}

		/// Dictionary reference of all the forms and their threads.
		private Dictionary<string, Thread> FormThreads_;

		/// Dictionary reference of all of the forms and their names.
		private Dictionary<string, MeterForm> Forms_;
		private void AddForm(MeterForm form) {
			this.Forms_.Add(form.Name, form);
		}
		#endregion

		/// Reference to the game server
		private GameServer GameServer_;
	}
}
