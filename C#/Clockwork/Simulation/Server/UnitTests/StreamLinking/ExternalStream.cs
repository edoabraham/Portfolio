/// ExternalStream.cs - External Stream Class Implementation.
/// Written by Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;

/// GOAL:
/// This project is to test the expected outcome
/// and usefulness of implementing an abstract
/// stream as a abstract output method. This will
/// in effect allow for various derived streams
/// to be able to be referenced and used for output.
/// This eliminates the need to defined different
/// methods for different forms of output.
public class ExternalStream {

	/// Pause between updates
	private const int SleepTime = 5000;

	/// Constructor
	public ExternalStream(Stream outStream =  null) {
		this.OutStream_ = outStream;
		this.InputQueue_ = new Queue<string>();
		this.InitThread();
	}

	/// Output stream
	private Stream OutStream_;
	public Stream OutStream {
		get { 
			if(this.OutStream_ == null)
				throw new Exception("OutStream is null");
			return this.OutStream_; 
		}
		set { this.OutStream_ = value; }
	}

	/// Separate thread for periodic printing
	private Thread WriteThread_;
	private void InitThread() {

		ThreadStart ts = new ThreadStart(() => {
			while (true) {
				this.Update();
				Thread.Sleep(SleepTime);
			}
		});
		this.WriteThread_ = new Thread(ts);
		this.WriteThread_.Start();
	}

	/// Update method used for printing
	private void Update() {

		// Write to the stream
		if (this.OutStream_ != null) {
			while (this.InputQueue_.Count > 0) {
				string line = "Output : ";
				line += this.InputQueue_.Dequeue();
				line += "\n";
				byte[] buffer = this.ToBytes(line);
				this.OutStream_.Write(buffer, 0, buffer.Length);
			}
		}
	}

	/// Allows user to write into the external stream
	public void Write(string line) {
		System.Diagnostics.Debug.Assert(this.InputQueue_ != null);
		this.InputQueue_.Enqueue(line);
	}

	/// Converts a string to a byte array
	private const int SizeOfChar = sizeof(char);
	private byte[] ToBytes(string source) {
		byte[] bytes = new byte[source.Length * SizeOfChar];
		System.Buffer.BlockCopy(source.ToCharArray(), 0, bytes, 0, bytes.Length);
		return bytes;
	}

	/// Queue for storing user input
	private Queue<string> InputQueue_;
}

