package ch.bittailor.bt.com;

public class BinaryOutputPackage implements IOutputPackage {

	private IPackageBuffer mBuffer;
	
	public BinaryOutputPackage(IPackageBuffer iBuffer) {
		this.mBuffer = iBuffer;
	}

	@Override
	public IOutputPackage writeBoolean(boolean iValue) {
		if (iValue) {
			mBuffer.put((byte)1);
		} else {
			mBuffer.put((byte)0);
		}
		return this;
	}

	@Override
	public IOutputPackage writeInt8(int iValue) {
		mBuffer.put((byte)iValue);
		return this;
	}

	@Override
	public IOutputPackage writeUInt8(int iValue) {
		mBuffer.put((byte)iValue);
		return this;
	}

}
