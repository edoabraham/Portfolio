/// MeterForm.cs - MeterForm Class Implementation
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

using Artemis;
using Artemis.Utils;

/// Game Server
namespace GameServer {

	/// Base class for all the forms used in metering.
	/// This base class overrides some of the behaviors
	/// of the Form class to achieve certain effects.
	public class MeterForm : Form {

		/// Constructor
		public MeterForm()
			: base() {
				this.WindowState = FormWindowState.Minimized;
		}

		/// Catching the closing event and hide window instead of closing.
		protected override void OnFormClosing(FormClosingEventArgs e) {
			e.Cancel = true;
			this.Hide();
		}
	}
}
