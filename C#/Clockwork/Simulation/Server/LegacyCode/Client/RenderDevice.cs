/// RenderDevice.cs - RenderDevice Class Implementation
/// Written By Jesse Z. Zhong

using System;
using System.Windows.Forms;

using SlimDX;
using SlimDX.Direct3D11;
using SlimDX.DXGI;
using SlimDX.Windows;
using Device = SlimDX.Direct3D11.Device;
using Resource = SlimDX.Direct3D11.Resource;

/// Client
namespace Client {

	/// Sets the users graphics device
	/// with the appropriate settings.
	public class RenderDevice {

		/// Default form dimensions.
		private const int DefaultWidth = 800;
		private const int DefaultHeight = 600;

		/// Constructor
		/// NOTE: Make sure to incorporate user settings later.
		public RenderDevice(string formName) {
			this.Name_ = formName;
			this.WindowMode_ = true;
			this.Buffers = 1;
			this.Width_ = DefaultWidth;
			this.Height_ = DefaultHeight;

			// Initialize
			this.Initialize();
		}

		/// The name of the form.
		private string Name_;
		public string Name {
			get { return this.Name_; }
			set { this.Name_ = value; }
		}

		/// Form used to render the game's graphics.
		private RenderForm Form_;
		public RenderForm Form {
			get { return this.Form_; }
		}

		/// Virtual adapter used for rendering graphics.
		private Device Device_;

		/// In charge of drawing and storing images.
		private SwapChain SwapChain_;
		public SwapChain SwapChain {
			get { return this.SwapChain_; }
		}

		/// In charge of rendering commands.
		private DeviceContext Context_;
		public DeviceContext Context {
			get { return this.Context_; }
		}

		/// Identifies sub-resources for the render target.
		private RenderTargetView RenderTarget_;
		public RenderTargetView RenderTarget {
			get { return this.RenderTarget_; }
		}

		/// Initialize and ready the graphics device for rendering.
		public void Initialize() {

			// Create a new form with the client name.
			this.Form_ = new RenderForm(this.Name);

			// Resize the form.
			this.Form_.Width = this.Width_;
			this.Form_.Height = this.Height_;

			// Create the device description with the appropriate settings.
			var description = new SwapChainDescription() {
				BufferCount = this.Buffers_,
				Usage = Usage.RenderTargetOutput,
				OutputHandle = this.Form_.Handle,
				IsWindowed = this.WindowMode_,
				ModeDescription = new ModeDescription(0, 0, new Rational(60, 1), Format.R8G8B8A8_UNorm),
				SampleDescription = new SampleDescription(1, 0),
				Flags = SwapChainFlags.AllowModeSwitch,
				SwapEffect = SwapEffect.Discard
			};

			// Initialize the device and swap chain.
			Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, 
				description, out this.Device_, out this.SwapChain_);

			// Set up the view for render target.
			using (var resource = Resource.FromSwapChain<Texture2D>(this.SwapChain_, 0))
				this.RenderTarget_ = new RenderTargetView(this.Device_, resource);

			// Set up the view port for rendering.
			this.Context_ = this.Device_.ImmediateContext;
			var viewport = new Viewport(0.0f, 0.0f, this.Form_.ClientSize.Width, this.Form_.ClientSize.Height);
			this.Context_.OutputMerger.SetTargets(this.RenderTarget_);
			this.Context_.Rasterizer.SetViewports(viewport);

			// Prevent DXGI handling of Alt+Enter.
			using(var factory = this.SwapChain_.GetParent<Factory>())
				factory.SetWindowAssociation(this.Form_.Handle, WindowAssociationFlags.IgnoreAltEnter);

			// Replace Alt+Enter handling behavior.
			this.Form_.KeyDown += (o, e) => {
				if (e.Alt && e.KeyCode == Keys.Enter) {
					this.SwapChain_.IsFullScreen = !this.SwapChain_.IsFullScreen;
					this.WindowMode_ = !this.SwapChain_.IsFullScreen;
				}
			};
		}

		/// Clean up all the resources used in rendering.
		public void Dispose() {
			this.RenderTarget_.Dispose();
			this.SwapChain_.Dispose();
			this.Device_.Dispose();
		}

		/// User Settings

		/// Toggles the state of the window
		/// to either window or full screen.
		private bool WindowMode_;
		public bool WindowMode {
			get { return this.WindowMode_; }
			set { this.WindowMode_ = value; }
		}
		public bool FullScreenMode {
			get { return !this.WindowMode_; }
			set { this.WindowMode_ = !value; }
		}

		/// Client window width.
		private int Width_;
		public int Width {
			get { return this.Width_; }
			set { this.Width_ = value; }
		}

		/// Client window height.
		private int Height_;
		public int Height {
			get { return this.Height_; }
			set { this.Height_ = value; }
		}


		/// Advanced User Settings

		/// The number of buffers used to render frames.
		private int Buffers_;
		public int Buffers {
			get { return this.Buffers_; }
			set { this.Buffers_ = value; }
		}
	}
}
