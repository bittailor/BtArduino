package ch.bittailor.bt.com;

public class BinaryInputPackage implements IInputPackage {

	private IPackageBuffer mBuffer;
	
	public BinaryInputPackage(IPackageBuffer iBuffer) {
		this.mBuffer = iBuffer;
	}
	
	@Override
	public boolean readBool() {
		int value = mBuffer.get();
		if (value != -1) {
			if (value == 0) {
				return false;

			} else {
				return true;
			}
		}
		return false;

	}

	@Override
	public int readInt8() {
		int value = mBuffer.get();
		if (value != -1) {
			return value;
		}
		return 0;
	}

	@Override
	public int readUInt8() {
		int value = mBuffer.get();
		if (value != -1) {
			return value;
		}
		return 0;
	}

}
