/// LambdaParameters.cs - LambdaParameters Class Implementation.
/// Written By Jesse Z. Zhong

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/// Lambda Parameters
namespace LambdaParameters {

	/// Goal:
	/// This project is used to analyze the behavior
	/// of using lambda functions for parameter passing,
	/// specifically for constructors to use on instantiation.
	public class LambdaParameters {

		public LambdaParameters() {
			this.RCList_ = new List<ReceivingClass>();
			this.ListInstances();
		}

		private List<ReceivingClass> RCList_;
		private void ListInstances() {

			this.RCList_.Add(new ReceivingClass((ReceivingClass rc) => {

			}));

		}
	}

	public delegate void PassedDelegate(ReceivingClass rc);

	public class ReceivingClass {

		public ReceivingClass(PassedDelegate pd) {
			this.ThisDelegate_ = pd;
			if(this.ThisDelegate_ != null)
				this.ThisDelegate_(this);
		}
		private PassedDelegate ThisDelegate_;
	}
}
