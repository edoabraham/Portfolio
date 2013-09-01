using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SlimDX.Windows;

namespace Client {
	public class Program {
		public static void Main(string[] args) {

			var renderDevice = new RenderDevice(MessageList.ClientName);

			MessagePump.Run(renderDevice.Form, () => {
				renderDevice.Context.ClearRenderTargetView(renderDevice.RenderTarget, new SlimDX.Color4(0.5f, 0.5f, 1.0f));
				renderDevice.SwapChain.Present(0, SlimDX.DXGI.PresentFlags.None);
			});

			renderDevice.Dispose();
		}
	}
}
